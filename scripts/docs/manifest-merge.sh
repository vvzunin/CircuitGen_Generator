#!/usr/bin/env bash
# Build or update manifest.json for the CircuitGen documentation portal.

set -euo pipefail

manifest_entry_from_meta() {
  local meta_path="$1"
  local slug="${2:-}"
  jq -c --arg slug "${slug}" '
    . as $meta
    | ($slug | if . == "" then $meta.id else . end) as $s
    | {
        id: $meta.id,
        name: $meta.name,
        description: ($meta.description // null),
        version: $meta.version,
        builtAt: $meta.builtAt,
        commit: $meta.commit,
        ref: $meta.ref,
        pipelineId: $meta.pipelineId,
        repo: $meta.repo,
        docker: ($meta.docker // null),
        planned: false,
        basePath: ("modules/" + $s),
        formats: {
          pdf: {
            ru: ("modules/" + $s + "/" + $meta.formats.pdf.ru),
            en: ("modules/" + $s + "/" + $meta.formats.pdf.en)
          },
          html: {
            ru: ("modules/" + $s + "/" + $meta.formats.html.ru),
            en: ("modules/" + $s + "/" + $meta.formats.html.en)
          }
        }
      }
  ' "${meta_path}"
}

write_manifest() {
  local output_path="${1:?output path required}"
  local module_meta_path="${2:?module meta.json path required}"
  local remote_manifest_path="${3:-}"
  local remote_metas_path="${4:-}"

  local base_url="${DOCS_PUBLIC_BASE_URL:-https://vvzunin.me/docs/CircuitGen}"
  base_url="${base_url%/}"
  local updated_at
  updated_at="$(date -u +"%Y-%m-%dT%H:%M:%SZ")"

  local current_entry
  current_entry="$(manifest_entry_from_meta "${module_meta_path}" "${DOCS_MODULE_SLUG}")"

  local from_manifest='[]'
  if [[ -n "${remote_manifest_path}" && -f "${remote_manifest_path}" ]]; then
    if jq -e '.modules | type == "array"' "${remote_manifest_path}" >/dev/null 2>&1; then
      from_manifest="$(jq -c '.modules' "${remote_manifest_path}")"
    fi
  fi

  local from_meta_entries='[]'
  if [[ -n "${remote_metas_path}" && -f "${remote_metas_path}" ]]; then
    if jq -e 'type == "array"' "${remote_metas_path}" >/dev/null 2>&1; then
      from_meta_entries="$(jq -c --arg slug "${DOCS_MODULE_SLUG}" '
        [ .[] | . as $meta
          | ($slug | if . == "" then $meta.id else . end) as $s
          | {
              id: $meta.id,
              name: $meta.name,
              description: ($meta.description // null),
              version: $meta.version,
              builtAt: $meta.builtAt,
              commit: $meta.commit,
              ref: $meta.ref,
              pipelineId: $meta.pipelineId,
              repo: $meta.repo,
              docker: ($meta.docker // null),
              planned: false,
              basePath: ("modules/" + $s),
              formats: {
                pdf: {
                  ru: ("modules/" + $s + "/" + $meta.formats.pdf.ru),
                  en: ("modules/" + $s + "/" + $meta.formats.pdf.en)
                },
                html: {
                  ru: ("modules/" + $s + "/" + $meta.formats.html.ru),
                  en: ("modules/" + $s + "/" + $meta.formats.html.en)
                }
              }
            }
        ]
      ' "${remote_metas_path}")"
    fi
  fi

  jq -n \
    --argjson from_manifest "${from_manifest}" \
    --argjson from_meta_entries "${from_meta_entries}" \
    --argjson current "${current_entry}" \
    --arg baseUrl "${base_url}" \
    --arg updatedAt "${updated_at}" \
    '
      ($from_manifest + $from_meta_entries + [$current])
      | group_by(.id)
      | map(.[-1])
      | sort_by(.id)
      | {
          schemaVersion: 1,
          baseUrl: $baseUrl,
          updatedAt: $updatedAt,
          modules: .
        }
    ' >"${output_path}"

  local count
  count="$(jq '.modules | length' "${output_path}")"
  echo "manifest-merge: wrote ${output_path} (module ${DOCS_MODULE_SLUG}, ${count} module(s) in manifest)"
}
