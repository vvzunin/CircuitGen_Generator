#!/usr/bin/env bash
# Validate Synology deploy staging/archive layout without contacting a real NAS.
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

# shellcheck source=../docs/nas-docs-names.sh
source "${ROOT_DIR}/scripts/docs/nas-docs-names.sh"
# shellcheck source=../docs/stage-module-docs.sh
source "${ROOT_DIR}/scripts/docs/stage-module-docs.sh"
# shellcheck source=../docs/manifest-merge.sh
source "${ROOT_DIR}/scripts/docs/manifest-merge.sh"

resolve_nas_docs_names "${ROOT_DIR}"

DEPLOY_SCRIPT="scripts/docs/deploy-synology.sh"
NAMES_SCRIPT="scripts/docs/nas-docs-names.sh"
STAGE_SCRIPT="scripts/docs/stage-module-docs.sh"
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

echo "=== test_deploy_mock: dependencies ==="
for tool in zip bash python3 jq; do
  command -v "${tool}" >/dev/null
done
for f in "${NAMES_SCRIPT}" "${STAGE_SCRIPT}" "${MANIFEST_SCRIPT}" "${API_SCRIPT}" \
  scripts/docs/modules-registry.json scripts/docs/portal/index.html; do
  test -f "${f}"
done

echo "=== test_deploy_mock: deploy script checks ==="
for s in "${DEPLOY_SCRIPT}" "${NAMES_SCRIPT}" "${STAGE_SCRIPT}" "${MANIFEST_SCRIPT}" "${API_SCRIPT}"; do
  bash -n "${s}"
done
grep -q 'NAS_USER' "${DEPLOY_SCRIPT}"
grep -q 'NAS_DOCS' "${DEPLOY_SCRIPT}"
grep -q 'SYNO.FileStation.Delete' "${API_SCRIPT}"
grep -q 'SYNO.FileStation.Extract' "${DEPLOY_SCRIPT}"
grep -q 'nas_fs_delete_paths' "${DEPLOY_SCRIPT}"
grep -q 'stage_module_docs' "${DEPLOY_SCRIPT}"
grep -q 'write_manifest' "${DEPLOY_SCRIPT}"
grep -q 'modules/${DOCS_MODULE_SLUG}' "${DEPLOY_SCRIPT}"
! grep -q '${REPO_DOCS_NAME}.pdf' "${DEPLOY_SCRIPT}"
! grep -q 'legacy_pdf' "${DEPLOY_SCRIPT}"
! grep -q 'nginx-legacy-redirects' "${DEPLOY_SCRIPT}"
! grep -q 'SYNO.FileStation.BackgroundTask' "${DEPLOY_SCRIPT}"

echo "=== test_deploy_mock: resolved names (slug=${DOCS_MODULE_SLUG}, pdf=${DOCS_PDF_BASE_NAME}) ==="
[[ -n "${DOCS_MODULE_SLUG}" && -n "${DOCS_PDF_BASE_NAME}" && -n "${REPO_DOCS_NAME}" ]]

echo "=== test_deploy_mock: staging layout ==="
rm -rf "${STAGING_DIR}" "${ARCHIVE_PATH}" "${DOCS_BASE}"
mkdir -p "${DOCS_BASE}/pdf/ru" "${DOCS_BASE}/pdf/en" "${DOCS_BASE}/html/ru" "${DOCS_BASE}/html/en"
echo '%PDF-mock-ru' >"${DOCS_BASE}/pdf/ru/${DOCS_PDF_BASE_NAME}.pdf"
echo '%PDF-mock-en' >"${DOCS_BASE}/pdf/en/${DOCS_PDF_BASE_NAME}.pdf"
echo '<html lang="ru"></html>' >"${DOCS_BASE}/html/ru/index.html"
echo '<html lang="en"></html>' >"${DOCS_BASE}/html/en/index.html"

rm -rf "${STAGING_DIR}"
mkdir -p "${STAGING_DIR}"
stage_module_docs "${STAGING_DIR}" "${DOCS_BASE}"
stage_portal_assets "${STAGING_DIR}" "${ROOT_DIR}/scripts/docs/portal"
write_manifest "${STAGING_DIR}/manifest.json" "${STAGING_DIR}/modules/${DOCS_MODULE_SLUG}/meta.json" ""

[[ -f "${STAGING_DIR}/modules/${DOCS_MODULE_SLUG}/pdf/ru.pdf" ]]
[[ -f "${STAGING_DIR}/modules/${DOCS_MODULE_SLUG}/pdf/en.pdf" ]]
[[ -f "${STAGING_DIR}/modules/${DOCS_MODULE_SLUG}/html/ru/index.html" ]]
[[ -f "${STAGING_DIR}/modules/${DOCS_MODULE_SLUG}/meta.json" ]]
[[ -f "${STAGING_DIR}/manifest.json" ]]
[[ -f "${STAGING_DIR}/index.html" ]]
[[ -f "${STAGING_DIR}/modules-registry.json" ]]

jq -e --arg id "${DOCS_MODULE_SLUG}" '.modules[] | select(.id == $id)' "${STAGING_DIR}/manifest.json" >/dev/null

(
  cd "${STAGING_DIR}"
  zip -rq "${ARCHIVE_PATH}" .
)

unzip -l "${ARCHIVE_PATH}" | grep -q "modules/${DOCS_MODULE_SLUG}/pdf/ru.pdf"
unzip -l "${ARCHIVE_PATH}" | grep -q "modules/${DOCS_MODULE_SLUG}/html/en/index.html"
unzip -l "${ARCHIVE_PATH}" | grep -q 'manifest.json'
unzip -l "${ARCHIVE_PATH}" | grep -q 'portal.js'

echo "=== test_deploy_mock: .gitlab-ci.yml ==="
python3 -c "import yaml; yaml.safe_load(open('.gitlab-ci.yml'))"
grep -q 'deploy-synology.sh' .gitlab-ci.yml
grep -q 'DOCS_MODULE_SLUG:' .gitlab-ci.yml
grep -q 'DOCS_PUBLIC_BASE_URL:' .gitlab-ci.yml
grep -q 'REPO_DOCS_NAME:' .gitlab-ci.yml

rm -rf "${STAGING_DIR}" "${ARCHIVE_PATH}" "${DOCS_BASE}"
echo "test_deploy_mock: OK"
