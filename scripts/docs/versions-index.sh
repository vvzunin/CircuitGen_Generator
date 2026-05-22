#!/usr/bin/env bash
# Per-module versions.json index (main + release tags) for the documentation portal.

set -euo pipefail

# Build a channel descriptor from modules/<slug>/versions/<channel>/meta.json
channel_from_meta() {
  local meta_path="$1"
  local slug="$2"
  local channel="$3"
  jq -c --arg slug "${slug}" --arg channel "${channel}" '
    . as $meta
    | {
        id: $channel,
        kind: ($meta.docsKind // (if $channel == "main" then "branch" else "release" end)),
        label: ($meta.docsLabel // $channel),
        version: $meta.version,
        builtAt: $meta.builtAt,
        commit: $meta.commit,
        ref: $meta.ref,
        pipelineId: $meta.pipelineId
      }
  ' "${meta_path}"
}

_collect_staging_version_channels() {
  local staging_dir="$1"
  local slug="$2"
  local versions_root="${staging_dir}/modules/${slug}/versions"
  local channels='[]'

  if [[ ! -d "${versions_root}" ]]; then
    echo "${channels}"
    return 0
  fi

  local meta_path channel entry
  for meta_path in "${versions_root}"/*/meta.json; do
    [[ -f "${meta_path}" ]] || continue
    channel="$(basename "$(dirname "${meta_path}")")"
    entry="$(channel_from_meta "${meta_path}" "${slug}" "${channel}")"
    channels="$(jq -c --argjson e "${entry}" '. + [$e]' <<<"${channels}")"
  done
  echo "${channels}"
}

write_module_versions_index() {
  local staging_dir="${1:?staging directory required}"
  local meta_path="${2:?meta.json path required}"
  local remote_versions_path="${3:-}"

  local index_path="${staging_dir}/modules/${DOCS_MODULE_SLUG}/versions.json"
  local new_channel staging_channels merged_channels
  new_channel="$(channel_from_meta "${meta_path}" "${DOCS_MODULE_SLUG}" "${DOCS_VERSION_CHANNEL}")"
  staging_channels="$(_collect_staging_version_channels "${staging_dir}" "${DOCS_MODULE_SLUG}")"

  local existing='{"schemaVersion":1,"defaultChannel":"main","channels":[]}'
  if [[ -n "${remote_versions_path}" && -f "${remote_versions_path}" ]]; then
    if jq -e '.channels | type == "array"' "${remote_versions_path}" >/dev/null 2>&1; then
      existing="$(cat "${remote_versions_path}")"
    fi
  fi

  merged_channels="$(jq -n \
    --argjson existing "$(jq -c '.channels // []' <<<"${existing}")" \
    --argjson staged "${staging_channels}" \
    --argjson newChannel "${new_channel}" \
    '
      ($existing + $staged + [$newChannel])
      | group_by(.id)
      | map(.[-1])
      | sort_by(.id)
    ')"

  jq -n \
    --argjson channels "${merged_channels}" \
    --arg deployChannel "${DOCS_VERSION_CHANNEL}" \
    --argjson existing "${existing}" \
    '
      ($channels | map(.id)) as $ids
      | {
          schemaVersion: 1,
          defaultChannel: (
            if ($ids | index("main")) != null then "main"
            elif (($existing.defaultChannel // "") | length) > 0 then $existing.defaultChannel
            else $deployChannel
            end
          ),
          channels: $channels
        }
    ' >"${index_path}"

  local count
  count="$(jq '.channels | length' "${index_path}")"
  echo "versions-index: wrote ${index_path} (channel ${DOCS_VERSION_CHANNEL}, ${count} total)"
}
