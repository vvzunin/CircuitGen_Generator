#!/usr/bin/env bash
# Build or update manifest.json for the CircuitGen documentation portal (schema v2).

set -euo pipefail

manifest_module_from_meta() {
  local meta_path="$1"
  local slug="$2"
  local channel="$3"
  jq -c --arg slug "${slug}" --arg channel "${channel}" '
    . as $meta
    | ("modules/" + $slug + "/versions/" + $channel) as $base
    | {
        id: $meta.id,
        name: $meta.name,
        description: ($meta.description // null),
        repo: $meta.repo,
        docker: ($meta.docker // null),
        planned: false,
        defaultChannel: $channel,
        channels: [
          {
            id: $channel,
            kind: ($meta.docsKind // (if $channel == "main" then "branch" else "release" end)),
            label: ($meta.docsLabel // $channel),
            version: $meta.version,
            builtAt: $meta.builtAt,
            commit: $meta.commit,
            ref: $meta.ref,
            pipelineId: $meta.pipelineId,
            formats: {
              pdf: {
                ru: ($base + "/pdf/ru.pdf"),
                en: ($base + "/pdf/en.pdf")
              },
              html: {
                ru: ($base + "/html/ru/"),
                en: ($base + "/html/en/")
              }
            }
          }
        ]
      }
  ' "${meta_path}"
}

_merge_module_channels() {
  local module_json="$1"
  local extra_channels_json="$2"
  jq -n \
    --argjson module "${module_json}" \
    --argjson extra "${extra_channels_json}" \
    '
      ($module.channels // []) as $base
      | ($extra // []) as $add
      | ($base + $add)
      | group_by(.id)
      | map(.[-1])
      | sort_by(.id) as $channels
      | $module
      | .channels = $channels
      | .defaultChannel = (
          if (.defaultChannel // "") != "" then .defaultChannel
          elif ($channels | map(.id) | index("main")) != null then "main"
          elif ($channels | length) > 0 then $channels[0].id
          else "main"
          end
        )
    '
}

write_manifest() {
  local output_path="${1:?output path required}"
  local module_meta_path="${2:?module meta.json path required}"
  local remote_manifest_path="${3:-}"
  local remote_modules_path="${4:-}"

  local base_url="${DOCS_PUBLIC_BASE_URL:-https://vvzunin.me/docs/CircuitGen}"
  base_url="${base_url%/}"
  local updated_at
  updated_at="$(date -u +"%Y-%m-%dT%H:%M:%SZ")"

  local current_module
  current_module="$(manifest_module_from_meta "${module_meta_path}" "${DOCS_MODULE_SLUG}" "${DOCS_VERSION_CHANNEL}")"

  local from_manifest='[]'
  if [[ -n "${remote_manifest_path}" && -f "${remote_manifest_path}" ]]; then
    if jq -e '.modules | type == "array"' "${remote_manifest_path}" >/dev/null 2>&1; then
      from_manifest="$(jq -c '.modules' "${remote_manifest_path}")"
    fi
  fi

  local from_remote_modules='[]'
  if [[ -n "${remote_modules_path}" && -f "${remote_modules_path}" ]]; then
    if jq -e 'type == "array"' "${remote_modules_path}" >/dev/null 2>&1; then
      from_remote_modules="$(cat "${remote_modules_path}")"
    fi
  fi

  local extra_channels='[]'
  local versions_root
  versions_root="$(dirname "$(dirname "${module_meta_path}")")"
  if [[ -d "${versions_root}" ]]; then
    local meta_file channel ch_entry
    for meta_file in "${versions_root}"/*/meta.json; do
      [[ -f "${meta_file}" ]] || continue
      channel="$(basename "$(dirname "${meta_file}")")"
      ch_entry="$(manifest_module_from_meta "${meta_file}" "${DOCS_MODULE_SLUG}" "${channel}" | jq -c '.channels[0]')"
      extra_channels="$(jq -c --argjson e "${ch_entry}" '. + [$e]' <<<"${extra_channels}")"
    done
  fi

  current_module="$(_merge_module_channels "${current_module}" "${extra_channels}")"

  jq -n \
    --argjson from_manifest "${from_manifest}" \
    --argjson from_remote_modules "${from_remote_modules}" \
    --argjson current "${current_module}" \
    --arg baseUrl "${base_url}" \
    --arg updatedAt "${updated_at}" \
    --arg currentId "${DOCS_MODULE_SLUG}" \
    '
      def legacy_to_v2:
        if (.channels? | type) == "array" then .
        else
          . as $m
          | ($m.basePath // ("modules/" + $m.id)) as $base
          | {
              id: $m.id,
              name: $m.name,
              description: ($m.description // null),
              repo: $m.repo,
              docker: ($m.docker // null),
              planned: ($m.planned // false),
              defaultChannel: "main",
              channels: [
                {
                  id: "main",
                  kind: "branch",
                  label: "main",
                  version: $m.version,
                  builtAt: $m.builtAt,
                  commit: $m.commit,
                  ref: $m.ref,
                  pipelineId: $m.pipelineId,
                  formats: (
                    if ($m.formats? | type) == "object" then $m.formats
                    else {
                      pdf: {
                        ru: ($base + "/pdf/ru.pdf"),
                        en: ($base + "/pdf/en.pdf")
                      },
                      html: {
                        ru: ($base + "/html/ru/"),
                        en: ($base + "/html/en/")
                      }
                    }
                    end
                  )
                }
              ]
            }
        end;

      (
        [ $from_manifest[]?, $from_remote_modules[]? ]
        | map(legacy_to_v2)
        | map(select(.id != $currentId))
      ) as $others
      | ($others + [ $current | legacy_to_v2 ])
      | sort_by(.id)
      | {
          schemaVersion: 2,
          baseUrl: $baseUrl,
          updatedAt: $updatedAt,
          modules: .
        }
    ' >"${output_path}"

  local count channels
  count="$(jq '.modules | length' "${output_path}")"
  channels="$(jq --arg id "${DOCS_MODULE_SLUG}" '.modules[] | select(.id == $id) | .channels | length' "${output_path}")"
  echo "manifest-merge: wrote ${output_path} (${count} module(s), ${DOCS_MODULE_SLUG} has ${channels} doc channel(s))"
}
