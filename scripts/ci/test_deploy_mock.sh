#!/usr/bin/env bash
# Validate Synology deploy staging/archive layout without contacting a real NAS.
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

# shellcheck source=../docs/nas-docs-names.sh
source "${ROOT_DIR}/scripts/docs/nas-docs-names.sh"
# shellcheck source=../docs/stage-module-docs.sh
source "${ROOT_DIR}/scripts/docs/stage-module-docs.sh"
# shellcheck source=../docs/versions-index.sh
source "${ROOT_DIR}/scripts/docs/versions-index.sh"
# shellcheck source=../docs/manifest-merge.sh
source "${ROOT_DIR}/scripts/docs/manifest-merge.sh"

resolve_nas_docs_names "${ROOT_DIR}"

DEPLOY_SCRIPT="scripts/docs/deploy-synology.sh"
NAMES_SCRIPT="scripts/docs/nas-docs-names.sh"
STAGE_SCRIPT="scripts/docs/stage-module-docs.sh"
VERSIONS_SCRIPT="scripts/docs/versions-index.sh"
MANIFEST_SCRIPT="scripts/docs/manifest-merge.sh"
API_SCRIPT="scripts/docs/nas-filestation-api.sh"

echo "=== test_deploy_mock: NAS path normalization ==="
[[ "$(normalize_nas_docs_path '/volume1/web/docs/CircuitGen/test')" == '/web/docs/CircuitGen/test' ]]
[[ "$(normalize_nas_docs_path '/web/docs/CircuitGen/test')" == '/web/docs/CircuitGen/test' ]]
[[ "$(normalize_nas_docs_path '/volume2/share/folder/')" == '/share/folder' ]]

ARCHIVE_NAME="${ARCHIVE_NAME:-${DOCS_MODULE_SLUG}_docs_deploy.zip}"
STAGING_DIR="${ROOT_DIR}/build/docs-nas-staging-mock"
ARCHIVE_PATH="${ROOT_DIR}/${ARCHIVE_NAME}"
DOCS_BASE="${ROOT_DIR}/build/docs-mock"
CHANNEL_DIR="${STAGING_DIR}/modules/${DOCS_MODULE_SLUG}/versions/${DOCS_VERSION_CHANNEL}"

echo "=== test_deploy_mock: dependencies ==="
for tool in zip bash python3 jq; do
  command -v "${tool}" >/dev/null
done
for f in "${NAMES_SCRIPT}" "${STAGE_SCRIPT}" "${VERSIONS_SCRIPT}" "${MANIFEST_SCRIPT}" "${API_SCRIPT}" \
  scripts/docs/modules-registry.json scripts/docs/portal/index.html; do
  test -f "${f}"
done

echo "=== test_deploy_mock: deploy script checks ==="
for s in "${DEPLOY_SCRIPT}" "${NAMES_SCRIPT}" "${STAGE_SCRIPT}" "${VERSIONS_SCRIPT}" "${MANIFEST_SCRIPT}" "${API_SCRIPT}"; do
  bash -n "${s}"
done
grep -q 'NAS_USER' "${DEPLOY_SCRIPT}"
grep -q 'NAS_DOCS' "${DEPLOY_SCRIPT}"
grep -q 'versions/${DOCS_VERSION_CHANNEL}' "${DEPLOY_SCRIPT}"
grep -q 'write_module_versions_index' "${DEPLOY_SCRIPT}"
grep -q 'nas_fs_collect_remote_modules_for_manifest' "${DEPLOY_SCRIPT}"
grep -q 'SYNO.FileStation.Extract' "${DEPLOY_SCRIPT}"
! grep -q 'SYNO.FileStation.BackgroundTask' "${DEPLOY_SCRIPT}"

echo "=== test_deploy_mock: resolved names (slug=${DOCS_MODULE_SLUG}, channel=${DOCS_VERSION_CHANNEL}) ==="
[[ -n "${DOCS_MODULE_SLUG}" && -n "${DOCS_PDF_BASE_NAME}" && "${DOCS_VERSION_CHANNEL}" == "main" ]]

echo "=== test_deploy_mock: staging layout (main channel) ==="
rm -rf "${STAGING_DIR}" "${ARCHIVE_PATH}" "${DOCS_BASE}"
mkdir -p "${DOCS_BASE}/pdf/ru" "${DOCS_BASE}/pdf/en" "${DOCS_BASE}/html/ru" "${DOCS_BASE}/html/en"
echo '%PDF-mock-ru' >"${DOCS_BASE}/pdf/ru/${DOCS_PDF_BASE_NAME}.pdf"
echo '%PDF-mock-en' >"${DOCS_BASE}/pdf/en/${DOCS_PDF_BASE_NAME}.pdf"
echo '<html lang="ru"></html>' >"${DOCS_BASE}/html/ru/index.html"
echo '<html lang="en"></html>' >"${DOCS_BASE}/html/en/index.html"

rm -rf "${STAGING_DIR}"
mkdir -p "${STAGING_DIR}"
stage_module_docs "${STAGING_DIR}" "${DOCS_BASE}"
write_module_versions_index "${STAGING_DIR}" "${CHANNEL_DIR}/meta.json" ""
stage_portal_assets "${STAGING_DIR}" "${ROOT_DIR}/scripts/docs/portal"
write_manifest "${STAGING_DIR}/manifest.json" "${CHANNEL_DIR}/meta.json" "" "[]"

[[ -f "${CHANNEL_DIR}/pdf/ru.pdf" ]]
[[ -f "${CHANNEL_DIR}/meta.json" ]]
[[ -f "${STAGING_DIR}/modules/${DOCS_MODULE_SLUG}/versions.json" ]]
jq -e '.channels | map(.id) | index("main")' "${STAGING_DIR}/modules/${DOCS_MODULE_SLUG}/versions.json" >/dev/null
jq -e '.schemaVersion == 2' "${STAGING_DIR}/manifest.json" >/dev/null

echo "=== test_deploy_mock: release channel + multi-module manifest ==="
export DOCS_VERSION_CHANNEL=v1.6.0
export CI_COMMIT_TAG=v1.6.0
stage_module_docs "${STAGING_DIR}" "${DOCS_BASE}"
write_module_versions_index "${STAGING_DIR}" \
  "${STAGING_DIR}/modules/${DOCS_MODULE_SLUG}/versions/v1.6.0/meta.json" \
  "${STAGING_DIR}/modules/${DOCS_MODULE_SLUG}/versions.json"
export DOCS_VERSION_CHANNEL=main
unset CI_COMMIT_TAG
jq -e '[.channels[].id] | sort == ["main", "v1.6.0"]' \
  "${STAGING_DIR}/modules/${DOCS_MODULE_SLUG}/versions.json" >/dev/null

REMOTE_MODULES="${STAGING_DIR}/remote-modules.json"
OTHER_SLUG="other-module-mock"
jq -n --arg id "${OTHER_SLUG}" '{
  id: $id,
  name: { ru: "Other", en: "Other" },
  defaultChannel: "main",
  channels: [{
    id: "main",
    kind: "branch",
    label: "main",
    version: "0.0.0",
    builtAt: "2020-01-01T00:00:00Z",
    formats: {
      pdf: { ru: ("modules/" + $id + "/versions/main/pdf/ru.pdf"), en: ("modules/" + $id + "/versions/main/pdf/en.pdf") },
      html: { ru: ("modules/" + $id + "/versions/main/html/ru/"), en: ("modules/" + $id + "/versions/main/html/en/") }
    }
  }]
}' >"${REMOTE_MODULES}"
write_manifest "${STAGING_DIR}/manifest-merged.json" \
  "${CHANNEL_DIR}/meta.json" "" "${REMOTE_MODULES}"
jq -e --arg id "${DOCS_MODULE_SLUG}" \
  '.modules[] | select(.id == $id) | .channels | map(.id) | index("v1.6.0")' \
  "${STAGING_DIR}/manifest-merged.json" >/dev/null

meta="${CHANNEL_DIR}/meta.json"
jq -e '(.docker.images | length) == 3' "${meta}" >/dev/null

(
  cd "${STAGING_DIR}"
  zip -rq "${ARCHIVE_PATH}" .
)

unzip -l "${ARCHIVE_PATH}" | grep -q "modules/${DOCS_MODULE_SLUG}/versions/main/pdf/ru.pdf"
unzip -l "${ARCHIVE_PATH}" | grep -q "modules/${DOCS_MODULE_SLUG}/versions/v1.6.0/meta.json"
unzip -l "${ARCHIVE_PATH}" | grep -q 'manifest.json'

echo "=== test_deploy_mock: .gitlab-ci.yml ==="
python3 -c "import yaml; yaml.safe_load(open('.gitlab-ci.yml'))"
grep -q 'deploy-synology.sh' .gitlab-ci.yml

rm -rf "${STAGING_DIR}" "${ARCHIVE_PATH}" "${DOCS_BASE}"
echo "test_deploy_mock: OK"
