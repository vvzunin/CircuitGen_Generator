#!/usr/bin/env bash
# Build or update manifest.json for the CircuitGen documentation portal.

set -euo pipefail

write_manifest() {
  local output_path="${1:?output path required}"
  local module_meta_path="${2:?module meta.json path required}"
  local remote_manifest_path="${3:-}"

  local base_url="${DOCS_PUBLIC_BASE_URL:-https://vvzunin.me/docs/CircuitGen}"
  base_url="${base_url%/}"
  local updated_at
  updated_at="$(date -u +"%Y-%m-%dT%H:%M:%SZ")"

  local module_entry
  module_entry="$(jq -c --arg base "${base_url}" --arg slug "${DOCS_MODULE_SLUG}" '
    . as $meta
    | {
        id: $meta.id,
        name: $meta.name,
        description: $meta.description,
        version: $meta.version,
        builtAt: $meta.builtAt,
        commit: $meta.commit,
        ref: $meta.ref,
        pipelineId: $meta.pipelineId,
        repo: $meta.repo,
        planned: false,
        basePath: ("modules/" + $slug),
        formats: {
          pdf: {
            ru: ("modules/" + $slug + "/" + $meta.formats.pdf.ru),
            en: ("modules/" + $slug + "/" + $meta.formats.pdf.en)
          },
          html: {
            ru: ("modules/" + $slug + "/" + $meta.formats.html.ru),
            en: ("modules/" + $slug + "/" + $meta.formats.html.en)
          }
        }
      }
  ' "${module_meta_path}")"

  local existing='{"schemaVersion":1,"baseUrl":"","updatedAt":"","modules":[]}'
  if [[ -n "${remote_manifest_path}" && -f "${remote_manifest_path}" ]]; then
    if jq -e '.modules | type == "array"' "${remote_manifest_path}" >/dev/null 2>&1; then
      existing="$(cat "${remote_manifest_path}")"
    fi
  fi

  jq -n \
    --argjson existing "${existing}" \
    --argjson entry "${module_entry}" \
    --arg baseUrl "${base_url}" \
    --arg updatedAt "${updated_at}" \
    '
      ($existing.modules // []) as $mods
      | ($mods | map(select(.id != $entry.id))) + [$entry]
      | sort_by(.id)
      | {
          schemaVersion: 1,
          baseUrl: $baseUrl,
          updatedAt: $updatedAt,
          modules: .
        }
    ' >"${output_path}"

  echo "manifest-merge: wrote ${output_path} (module ${DOCS_MODULE_SLUG})"
}
