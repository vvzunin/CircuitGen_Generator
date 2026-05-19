#!/usr/bin/env bash
# Validate Synology deploy staging/archive layout without contacting a real NAS.
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

# shellcheck source=../docs/nas-docs-names.sh
source "${ROOT_DIR}/scripts/docs/nas-docs-names.sh"
resolve_nas_docs_names "${ROOT_DIR}"

DEPLOY_SCRIPT="scripts/docs/deploy-synology.sh"
NAMES_SCRIPT="scripts/docs/nas-docs-names.sh"

echo "=== test_deploy_mock: NAS path normalization ==="
[[ "$(normalize_nas_docs_path '/volume1/web/docs/CircuitGen/test')" == '/web/docs/CircuitGen/test' ]]
[[ "$(normalize_nas_docs_path '/web/docs/CircuitGen/test')" == '/web/docs/CircuitGen/test' ]]
[[ "$(normalize_nas_docs_path '/volume2/share/folder/')" == '/share/folder' ]]
grep -q 'normalize_nas_docs_path' "${DEPLOY_SCRIPT}"

ARCHIVE_NAME="${ARCHIVE_NAME:-${REPO_DOCS_NAME}_docs_deploy.zip}"
STAGING_DIR="${ROOT_DIR}/build/docs-nas-staging-mock"
ARCHIVE_PATH="${ROOT_DIR}/${ARCHIVE_NAME}"

echo "=== test_deploy_mock: dependencies ==="
for tool in zip bash python3; do
  command -v "${tool}" >/dev/null
done
test -f "${NAMES_SCRIPT}"
grep -q 'require_tool jq' "${DEPLOY_SCRIPT}"
grep -q 'require_tool curl' "${DEPLOY_SCRIPT}"
grep -q 'resolve_nas_docs_names' "${DEPLOY_SCRIPT}"
grep -q 'nas-docs-names.sh' "${DEPLOY_SCRIPT}"

echo "=== test_deploy_mock: deploy script checks ==="
bash -n "${DEPLOY_SCRIPT}"
bash -n "${NAMES_SCRIPT}"
grep -q 'NAS_USER' "${DEPLOY_SCRIPT}"
grep -q 'NAS_PASS' "${DEPLOY_SCRIPT}"
grep -q 'NAS_DOCS' "${DEPLOY_SCRIPT}"
grep -q 'NAS_URL' "${DEPLOY_SCRIPT}"
grep -q 'SYNO.FileStation.Delete' "${DEPLOY_SCRIPT}"
grep -q 'SYNO.FileStation.Extract' "${DEPLOY_SCRIPT}"
grep -q 'method=status' "${DEPLOY_SCRIPT}"
grep -q 'AUTH_API_VERSION' "${DEPLOY_SCRIPT}"
! grep -q 'SYNO.FileStation.BackgroundTask' "${DEPLOY_SCRIPT}"
! grep -q 'remove_archive' "${DEPLOY_SCRIPT}"
grep -q '${REPO_DOCS_NAME}.pdf' "${DEPLOY_SCRIPT}"
grep -q '${REPO_DOCS_NAME}_en.pdf' "${DEPLOY_SCRIPT}"
grep -q '${REPO_DOCS_NAME}/ru' "${DEPLOY_SCRIPT}"
grep -q '${REPO_DOCS_NAME}/en' "${DEPLOY_SCRIPT}"
! grep -q 'SYNOLOGY_' "${DEPLOY_SCRIPT}"
! grep -q '.env.example' "${DEPLOY_SCRIPT}"

echo "=== test_deploy_mock: resolved names (${REPO_DOCS_NAME}, ${DOCS_PDF_BASE_NAME}) ==="
[[ -n "${REPO_DOCS_NAME}" && -n "${DOCS_PDF_BASE_NAME}" ]]

echo "=== test_deploy_mock: staging layout ==="
rm -rf "${STAGING_DIR}" "${ARCHIVE_PATH}"
mkdir -p "${STAGING_DIR}/${REPO_DOCS_NAME}/ru" "${STAGING_DIR}/${REPO_DOCS_NAME}/en"
echo '<html lang="ru"></html>' >"${STAGING_DIR}/${REPO_DOCS_NAME}/ru/index.html"
echo '<html lang="en"></html>' >"${STAGING_DIR}/${REPO_DOCS_NAME}/en/index.html"
echo '%PDF-mock-ru' >"${STAGING_DIR}/${REPO_DOCS_NAME}.pdf"
echo '%PDF-mock-en' >"${STAGING_DIR}/${REPO_DOCS_NAME}_en.pdf"

(
  cd "${STAGING_DIR}"
  zip -rq "${ARCHIVE_PATH}" .
)

unzip -l "${ARCHIVE_PATH}" | grep -q "${REPO_DOCS_NAME}/ru/index.html"
unzip -l "${ARCHIVE_PATH}" | grep -q "${REPO_DOCS_NAME}/en/index.html"
unzip -l "${ARCHIVE_PATH}" | grep -q "${REPO_DOCS_NAME}.pdf"
unzip -l "${ARCHIVE_PATH}" | grep -q "${REPO_DOCS_NAME}_en.pdf"

echo "=== test_deploy_mock: .gitlab-ci.yml ==="
python3 -c "import yaml; yaml.safe_load(open('.gitlab-ci.yml'))"
grep -q 'deploy-synology.sh' .gitlab-ci.yml
grep -q 'NAS_URL' .gitlab-ci.yml
grep -q 'NAS_DEPLOY_STRICT: "true"' .gitlab-ci.yml
grep -q 'REPO_DOCS_NAME:' .gitlab-ci.yml
grep -q 'DOCS_PDF_BASE_NAME:' .gitlab-ci.yml
grep -q 'NAS_DEPLOY_STRICT:-true' "${DEPLOY_SCRIPT}"
! grep -q 'SYNOLOGY_' .gitlab-ci.yml

rm -rf "${STAGING_DIR}" "${ARCHIVE_PATH}"
echo "test_deploy_mock: OK"
