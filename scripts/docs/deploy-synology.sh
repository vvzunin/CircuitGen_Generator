#!/usr/bin/env bash
# Deploy generated documentation (HTML + PDF, en/ru) to Synology NAS via File Station API.
#
# Layout on NAS (under NAS_DOCS, e.g. /web/docs/CircuitGen):
#   index.html, manifest.json (schema v2), modules-registry.json
#   modules/<slug>/versions.json
#   modules/<slug>/versions/<channel>/  — channel is main or release tag (v1.6.0)
#     meta.json, pdf/{ru,en}.pdf, html/{ru,en}/
#
# See docs/en/DEPLOY.md and Synology File Station Official API guide.

set -euo pipefail

NAS_URL="${NAS_URL:-}"
NAS_USER="${NAS_USER:-}"
NAS_PASS="${NAS_PASS:-}"
NAS_DOCS="${NAS_DOCS:-}"
NAS_OTP_CODE="${NAS_OTP_CODE:-}"
NAS_INSECURE_SSL="${NAS_INSECURE_SSL:-false}"
if [[ -n "${CI:-}" ]]; then
  NAS_DEPLOY_STRICT="${NAS_DEPLOY_STRICT:-true}"
else
  NAS_DEPLOY_STRICT="${NAS_DEPLOY_STRICT:-false}"
fi

NAS_FS_API_VERSION="${FILESTATION_API_VERSION:-2}"
NAS_FS_AUTH_VERSION="${AUTH_API_VERSION:-3}"
NAS_FS_SID=""
NAS_FS_COOKIE_JAR=""
NAS_FS_CURL_OPTS=()

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

# shellcheck source=nas-docs-names.sh
source "${SCRIPT_DIR}/nas-docs-names.sh"
# shellcheck source=stage-module-docs.sh
source "${SCRIPT_DIR}/stage-module-docs.sh"
# shellcheck source=manifest-merge.sh
source "${SCRIPT_DIR}/manifest-merge.sh"
# shellcheck source=versions-index.sh
source "${SCRIPT_DIR}/versions-index.sh"
# shellcheck source=nas-filestation-api.sh
source "${SCRIPT_DIR}/nas-filestation-api.sh"

nas_fs_handle_error() {
  local msg="$1"
  if [[ "${NAS_DEPLOY_STRICT}" == "true" ]]; then
    echo "deploy-synology: ERROR: ${msg}" >&2
    exit 1
  fi
  echo "deploy-synology: WARNING: ${msg} (NAS_DEPLOY_STRICT=false, continuing)" >&2
  exit 0
}

trim_credential() {
  local value="$1"
  value="${value//$'\r'/}"
  value="${value//$'\n'/}"
  value="${value#"${value%%[![:space:]]*}"}"
  value="${value%"${value##*[![:space:]]}"}"
  printf '%s' "${value}"
}

require_tool() {
  local tool="$1"
  if ! command -v "${tool}" >/dev/null 2>&1; then
    echo "deploy-synology: missing required tool: ${tool}" >&2
    exit 1
  fi
}

require_tool curl
require_tool jq
require_tool zip

if [[ -z "${NAS_URL}" || -z "${NAS_USER}" || -z "${NAS_PASS}" || -z "${NAS_DOCS}" ]]; then
  if [[ "${NAS_DEPLOY_STRICT}" == "true" ]]; then
    echo "deploy-synology: ERROR: NAS_URL, NAS_USER, NAS_PASS, and NAS_DOCS must be set" >&2
    exit 1
  fi
  echo "deploy-synology: credentials not set — skipping upload (non-strict local run)"
  exit 0
fi

NAS_USER="$(trim_credential "${NAS_USER}")"
NAS_PASS="$(trim_credential "${NAS_PASS}")"
NAS_DOCS="$(trim_credential "${NAS_DOCS}")"
if [[ -n "${NAS_OTP_CODE}" ]]; then
  NAS_OTP_CODE="$(trim_credential "${NAS_OTP_CODE}")"
fi

NAS_DOCS="${NAS_DOCS%/}"
NAS_URL="${NAS_URL%/}"
_orig_nas_docs="${NAS_DOCS}"
NAS_DOCS="$(normalize_nas_docs_path "${NAS_DOCS}")"
if [[ "${NAS_DOCS}" != "${_orig_nas_docs}" ]]; then
  echo "deploy-synology: normalized NAS_DOCS: ${_orig_nas_docs} -> ${NAS_DOCS}"
fi

resolve_nas_docs_names "${PROJECT_ROOT}"

if [[ "${NAS_INSECURE_SSL}" == "true" ]]; then
  NAS_FS_CURL_OPTS+=(-k)
fi

ARCHIVE_NAME="${ARCHIVE_NAME:-${DOCS_MODULE_SLUG}_docs_deploy.zip}"
DOCS_BASE="${PROJECT_ROOT}/build/docs"
STAGING_DIR="${PROJECT_ROOT}/build/docs-nas-staging"
ARCHIVE_PATH="${PROJECT_ROOT}/${ARCHIVE_NAME}"
PORTAL_DIR="${SCRIPT_DIR}/portal"
MODULE_VERSION_DIR="${NAS_DOCS}/modules/${DOCS_MODULE_SLUG}/versions/${DOCS_VERSION_CHANNEL}"
REMOTE_MANIFEST_TMP="$(mktemp)"
REMOTE_MODULES_TMP="$(mktemp)"
REMOTE_VERSIONS_TMP="$(mktemp)"

echo "deploy-synology: preparing deployment bundle"
echo "  NAS URL: ${NAS_URL}"
echo "  NAS path: ${NAS_DOCS}"
echo "  module slug: ${DOCS_MODULE_SLUG} (display: ${REPO_DOCS_NAME})"
echo "  docs channel: ${DOCS_VERSION_CHANNEL}"
echo "  PDF base: ${DOCS_PDF_BASE_NAME}"

rm -rf "${STAGING_DIR}"
mkdir -p "${STAGING_DIR}"

if ! stage_module_docs "${STAGING_DIR}" "${DOCS_BASE}"; then
  nas_fs_handle_error "failed to stage module documentation"
fi
stage_portal_assets "${STAGING_DIR}" "${PORTAL_DIR}"

COOKIE_JAR="$(mktemp)"
chmod 600 "${COOKIE_JAR}"
NAS_FS_COOKIE_JAR="${COOKIE_JAR}"

cleanup() {
  if [[ -n "${NAS_FS_SID}" ]]; then
    curl -s "${NAS_FS_CURL_OPTS[@]}" -b "${NAS_FS_COOKIE_JAR}" -G "${NAS_URL}/webapi/auth.cgi" \
      --data-urlencode "api=SYNO.API.Auth" \
      --data-urlencode "version=1" \
      --data-urlencode "method=logout" \
      --data-urlencode "session=FileStation" \
      --data-urlencode "_sid=${NAS_FS_SID}" >/dev/null || true
  fi
  rm -f "${COOKIE_JAR}" "${ARCHIVE_PATH}" "${REMOTE_MANIFEST_TMP}" "${REMOTE_MODULES_TMP}" "${REMOTE_VERSIONS_TMP}"
  rm -rf "${STAGING_DIR}"
}
trap cleanup EXIT

nas_fs_resolve_auth_api_version
nas_fs_establish_session

nas_fs_fetch_remote_manifest "${REMOTE_MANIFEST_TMP}" || true
nas_fs_fetch_remote_versions_index "${REMOTE_VERSIONS_TMP}" || true
write_module_versions_index \
  "${STAGING_DIR}" \
  "${STAGING_DIR}/modules/${DOCS_MODULE_SLUG}/versions/${DOCS_VERSION_CHANNEL}/meta.json" \
  "${REMOTE_VERSIONS_TMP}"
nas_fs_collect_remote_modules_for_manifest "${REMOTE_MODULES_TMP}"
write_manifest \
  "${STAGING_DIR}/manifest.json" \
  "${STAGING_DIR}/modules/${DOCS_MODULE_SLUG}/versions/${DOCS_VERSION_CHANNEL}/meta.json" \
  "${REMOTE_MANIFEST_TMP}" \
  "${REMOTE_MODULES_TMP}"

rm -f "${ARCHIVE_PATH}"
(
  cd "${STAGING_DIR}"
  zip -rq "${ARCHIVE_PATH}" .
)

ARCHIVE_SIZE="$(du -h "${ARCHIVE_PATH}" | cut -f1)"
echo "deploy-synology: archive ${ARCHIVE_NAME} (${ARCHIVE_SIZE})"

DELETE_PATHS_JSON="$(jq -n \
  --arg version_dir "${MODULE_VERSION_DIR}" \
  --arg archive "${NAS_DOCS}/${ARCHIVE_NAME}" \
  '[$version_dir, $archive]')"

echo "deploy-synology: removing previous docs for channel ${DOCS_VERSION_CHANNEL} on NAS"
nas_fs_delete_paths "${DELETE_PATHS_JSON}"

echo "deploy-synology: uploading ${ARCHIVE_NAME}"
UPLOAD_RESPONSE="$(nas_fs_upload_archive "${ARCHIVE_PATH}" "${ARCHIVE_NAME}")"
if [[ -n "${UPLOAD_RESPONSE}" ]] && ! nas_fs_json_success "${UPLOAD_RESPONSE}"; then
  if [[ "$(nas_fs_json_error_code "${UPLOAD_RESPONSE}")" == "119" && "${NAS_FS_AUTH_VERSION}" != "3" ]]; then
    echo "deploy-synology: upload SID not found (119), retrying Auth v3"
    NAS_FS_AUTH_VERSION=3
    nas_fs_establish_session
    UPLOAD_RESPONSE="$(nas_fs_upload_archive "${ARCHIVE_PATH}" "${ARCHIVE_NAME}")"
  fi
fi
if [[ -n "${UPLOAD_RESPONSE}" ]] && ! nas_fs_json_success "${UPLOAD_RESPONSE}"; then
  nas_fs_handle_error "upload failed: ${UPLOAD_RESPONSE}"
fi

REMOTE_ARCHIVE="${NAS_DOCS}/${ARCHIVE_NAME}"
echo "deploy-synology: extracting archive on NAS"
EXTRACT_RESPONSE="$(nas_fs_syno_post \
  --data-urlencode "api=SYNO.FileStation.Extract" \
  --data-urlencode "version=${NAS_FS_API_VERSION}" \
  --data-urlencode "method=start" \
  --data-urlencode "file_path=${REMOTE_ARCHIVE}" \
  --data-urlencode "dest_folder_path=${NAS_DOCS}" \
  --data-urlencode "overwrite=true" \
  --data-urlencode "keep_dir=true" \
  --data-urlencode "create_subfolder=false" \
  --data-urlencode "_sid=${NAS_FS_SID}")"

if ! nas_fs_json_success "${EXTRACT_RESPONSE}"; then
  nas_fs_handle_error "extract failed: ${EXTRACT_RESPONSE}"
fi

EXTRACT_TASK_ID="$(echo "${EXTRACT_RESPONSE}" | jq -r '.data.taskid // empty')"
if [[ -n "${EXTRACT_TASK_ID}" ]]; then
  nas_fs_wait_task "SYNO.FileStation.Extract" "${EXTRACT_TASK_ID}"
fi

ARCHIVE_DELETE_PATH="$(jq -n --arg p "${REMOTE_ARCHIVE}" '[$p]')"
nas_fs_delete_paths "${ARCHIVE_DELETE_PATH}" || true

BASE_PUBLIC="${DOCS_PUBLIC_BASE_URL:-https://vvzunin.me/docs/CircuitGen}"
BASE_PUBLIC="${BASE_PUBLIC%/}"
echo "deploy-synology: deployment complete"
DOC_BASE="${BASE_PUBLIC}/modules/${DOCS_MODULE_SLUG}/versions/${DOCS_VERSION_CHANNEL}"
echo "  Portal: ${BASE_PUBLIC}/"
echo "  Channel: ${DOCS_VERSION_CHANNEL}"
echo "  PDF (ru): ${DOC_BASE}/pdf/ru.pdf"
echo "  PDF (en): ${DOC_BASE}/pdf/en.pdf"
echo "  HTML (ru): ${DOC_BASE}/html/ru/"
echo "  HTML (en): ${DOC_BASE}/html/en/"
