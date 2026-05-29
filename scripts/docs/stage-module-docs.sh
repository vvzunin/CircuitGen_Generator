#!/usr/bin/env bash
# Stage built documentation for Synology deploy (modules/<slug>/versions/<channel>/ layout).
# Requires resolve_nas_docs_names() and DOCS_BASE paths to exist.

set -euo pipefail

stage_module_docs() {
  local staging_dir="${1:?staging directory required}"
  local docs_base="${2:?docs base directory required}"

  local module_root="${staging_dir}/modules/${DOCS_MODULE_SLUG}/versions/${DOCS_VERSION_CHANNEL}"
  local ru_pdf_src="${docs_base}/pdf/ru/${DOCS_PDF_BASE_NAME}.pdf"
  local en_pdf_src="${docs_base}/pdf/en/${DOCS_PDF_BASE_NAME}.pdf"
  local ru_html_src="${docs_base}/html/ru"
  local en_html_src="${docs_base}/html/en"

  for path in "${ru_pdf_src}" "${en_pdf_src}" "${ru_html_src}" "${en_html_src}"; do
    if [[ ! -e "${path}" ]]; then
      echo "stage-module-docs: missing artifact: ${path}" >&2
      return 1
    fi
  done

  rm -rf "${module_root}"
  mkdir -p "${module_root}/pdf" "${module_root}/html"

  cp -a "${ru_html_src}" "${module_root}/html/ru"
  cp -a "${en_html_src}" "${module_root}/html/en"
  cp "${ru_pdf_src}" "${module_root}/pdf/ru.pdf"
  cp "${en_pdf_src}" "${module_root}/pdf/en.pdf"

  local built_at registry_host group_name image_repo dev_tag release_tag harbor_base os_list_json
  local docs_kind docs_label
  built_at="$(date -u +"%Y-%m-%dT%H:%M:%SZ")"
  registry_host="${REGISTRY_URL:-vvzunin.me:5201}"
  group_name="${GROUP_NAME:-circuitgen}"
  image_repo="${REPO_NAME:-${DOCS_MODULE_SLUG}}"
  dev_tag="${DOCKER_DEV_TAG:-main}"
  if [[ -n "${CI_COMMIT_TAG:-}" ]]; then
    release_tag="${CI_COMMIT_TAG}"
    docs_kind="release"
    docs_label="${CI_COMMIT_TAG}"
  else
    release_tag="v${PROJECT_VERSION#v}"
    docs_kind="branch"
    docs_label="main"
  fi
  if [[ -n "${DOCKER_RELEASE_TAG:-}" ]]; then
    release_tag="${DOCKER_RELEASE_TAG}"
  fi
  harbor_base="${DOCS_HARBOR_WEB_BASE:-https://vvzunin.me/harbor/projects/circuitgen/repositories}"
  harbor_base="${harbor_base%/}"
  os_list_json="${DOCKER_OS_LIST_JSON:-[\"ubuntu-22.04\",\"ubuntu-24.04\",\"fedora-43\"]}"

  jq -n \
    --arg id "${DOCS_MODULE_SLUG}" \
    --arg name "${REPO_DOCS_NAME}" \
    --arg version "${PROJECT_VERSION}" \
    --arg builtAt "${built_at}" \
    --arg commit "${CI_COMMIT_SHA:-}" \
    --arg ref "${CI_COMMIT_REF_NAME:-}" \
    --arg pipeline "${CI_PIPELINE_ID:-}" \
    --arg repo "${DOCS_MODULE_REPO:-}" \
    --arg docsChannel "${DOCS_VERSION_CHANNEL}" \
    --arg docsKind "${docs_kind}" \
    --arg docsLabel "${docs_label}" \
    --arg registryHost "${registry_host}" \
    --arg group "${group_name}" \
    --arg imageRepo "${image_repo}" \
    --arg devTag "${dev_tag}" \
    --arg releaseTag "${release_tag}" \
    --arg harborWebBase "${harbor_base}" \
    --argjson osList "${os_list_json}" \
    '
      def harbor_url($os; $flavor):
        ($harborWebBase + "/" + ($imageRepo + "/" + $os + "/" + $flavor | @uri) + "/artifacts-tab");
      def pull_ref($os; $flavor; $tag):
        ($registryHost + "/" + $group + "/" + $imageRepo + "/" + $os + "/" + $flavor + ":" + $tag);
      {
        id: $id,
        name: { ru: $name, en: $name },
        version: $version,
        builtAt: $builtAt,
        commit: (if $commit == "" then null else $commit end),
        ref: (if $ref == "" then null else $ref end),
        pipelineId: (if $pipeline == "" then null else $pipeline end),
        repo: (if $repo == "" then null else $repo end),
        docsChannel: $docsChannel,
        docsKind: $docsKind,
        docsLabel: $docsLabel,
        docker: {
          registryHost: $registryHost,
          group: $group,
          imageRepo: $imageRepo,
          osList: $osList,
          devTag: $devTag,
          releaseTag: $releaseTag,
          harborWebBase: $harborWebBase,
          images: [
            $osList[] | . as $os | {
              os: $os,
              dev: {
                pull: pull_ref($os; "dev"; $devTag),
                harborUrl: harbor_url($os; "dev")
              },
              release: {
                pull: pull_ref($os; "release"; $releaseTag),
                harborUrl: harbor_url($os; "release")
              }
            }
          ]
        },
        formats: {
          pdf: { ru: "pdf/ru.pdf", en: "pdf/en.pdf" },
          html: { ru: "html/ru/", en: "html/en/" }
        }
      }
    ' >"${module_root}/meta.json"

  echo "stage-module-docs: staged modules/${DOCS_MODULE_SLUG}/versions/${DOCS_VERSION_CHANNEL}/"
}

stage_portal_assets() {
  local staging_dir="${1:?staging directory required}"
  local portal_dir="${2:?portal source directory required}"

  if [[ ! -d "${portal_dir}" ]]; then
    echo "stage-portal: portal directory not found: ${portal_dir}" >&2
    return 1
  fi

  cp -a "${portal_dir}/." "${staging_dir}/"
  if [[ -f "${portal_dir}/../modules-registry.json" ]]; then
    cp "${portal_dir}/../modules-registry.json" "${staging_dir}/modules-registry.json"
  fi
  echo "stage-portal: copied portal assets"
}
