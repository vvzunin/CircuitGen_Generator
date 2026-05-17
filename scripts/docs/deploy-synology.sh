#!/usr/bin/env bash
# Deploy generated documentation (HTML + PDF, en/ru) to Synology NAS via File Station API.
# See Synology File Station Official API guide (SYNO.API.Auth, SYNO.FileStation.*).
#
# Expects docs under build/docs/{html,pdf}/{en,ru}/ after scripts/ci/docs.sh.
#
# Required CI/CD variables (GitLab → Settings → CI/CD → Variables):
#   NAS_USER   — File Station account
#   NAS_PASS   — password (masked)
#   NAS_DOCS   — destination folder on NAS (e.g. /volume1/web/docs/circuitgen)
#
# Optional (see .gitlab-ci.yml and scripts/docs/nas-docs-names.sh):
#   NAS_URL              — DSM base URL (default in CI: https://vvzunin.me:5001)
#   NAS_DEPLOY_STRICT    — "true" fails the job on deploy errors; default true in CI, false locally
#   NAS_INSECURE_SSL     — "true" to pass curl -k (self-signed TLS only)
#   NAS_OTP_CODE         — 2FA one-time password if DSM requires it (SYNO.API.Auth error 403)
#   NAS_AUTH_API_VERSION — override SYNO.API.Auth version (default: NAS maxVersion, fallback 3 on error 119)
#   DOCS_PDF_BASE_NAME   — Doxygen PDF basename without .pdf (default: CMake project() name)
#   REPO_DOCS_NAME       — HTML subfolder and PDF prefix (default: project name without CircuitGen)
#
# SYNO.API.Auth login errors: 400 bad credentials, 401 account disabled, 402 no File Station
# permission for NAS_USER, 403/404 two-step verification (use NAS_OTP_CODE or app password).

set -euo pipefail

NAS_URL="${NAS_URL:-}"
NAS_USER="${NAS_USER:-}"
NAS_PASS="${NAS_PASS:-}"
NAS_DOCS="${NAS_DOCS:-}"
NAS_OTP_CODE="${NAS_OTP_CODE:-}"
NAS_INSECURE_SSL="${NAS_INSECURE_SSL:-false}"
# CI must upload docs to NAS; local runs skip when credentials are unset unless forced.
if [[ -n "${CI:-}" ]]; then
  NAS_DEPLOY_STRICT="${NAS_DEPLOY_STRICT:-true}"
else
  NAS_DEPLOY_STRICT="${NAS_DEPLOY_STRICT:-false}"
fi

# Per Synology File Station API guide (SYNO.API.Auth).
AUTH_API_VERSION="${AUTH_API_VERSION:-3}"
FILESTATION_API_VERSION="${FILESTATION_API_VERSION:-2}"

CURL_OPTS=()
if [[ "${NAS_INSECURE_SSL}" == "true" ]]; then
  CURL_OPTS+=(-k)
fi

handle_deploy_error() {
  local msg="$1"
  if [[ "${NAS_DEPLOY_STRICT}" == "true" ]]; then
    echo "deploy-synology: ERROR: ${msg}" >&2
    exit 1
  fi
  echo "deploy-synology: WARNING: ${msg} (NAS_DEPLOY_STRICT=false, continuing)" >&2
  exit 0
}

require_tool() {
  local tool="$1"
  if ! command -v "${tool}" >/dev/null 2>&1; then
    echo "deploy-synology: missing required tool: ${tool}" >&2
    exit 1
  fi
}

trim_credential() {
  local value="$1"
  value="${value//$'\r'/}"
  value="${value//$'\n'/}"
  value="${value#"${value%%[![:space:]]*}"}"
  value="${value%"${value##*[![:space:]]}"}"
  printf '%s' "${value}"
}

require_tool curl
require_tool jq
require_tool zip

if [[ -z "${NAS_URL}" || -z "${NAS_USER}" || -z "${NAS_PASS}" || -z "${NAS_DOCS}" ]]; then
  if [[ "${NAS_DEPLOY_STRICT}" == "true" ]]; then
    echo "deploy-synology: ERROR: NAS_URL, NAS_USER, NAS_PASS, and NAS_DOCS must be set" >&2
    echo "deploy-synology: configure them in GitLab CI/CD Variables (NAS_URL may be set in .gitlab-ci.yml)" >&2
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

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
# shellcheck source=nas-docs-names.sh
source "${SCRIPT_DIR}/nas-docs-names.sh"
resolve_nas_docs_names "${PROJECT_ROOT}"

ARCHIVE_NAME="${ARCHIVE_NAME:-${REPO_DOCS_NAME}_docs_deploy.zip}"

DOCS_BASE="${PROJECT_ROOT}/build/docs"
STAGING_DIR="${PROJECT_ROOT}/build/docs-nas-staging"
ARCHIVE_PATH="${PROJECT_ROOT}/${ARCHIVE_NAME}"

RU_PDF_SRC="${DOCS_BASE}/pdf/ru/${DOCS_PDF_BASE_NAME}.pdf"
EN_PDF_SRC="${DOCS_BASE}/pdf/en/${DOCS_PDF_BASE_NAME}.pdf"
RU_HTML_SRC="${DOCS_BASE}/html/ru"
EN_HTML_SRC="${DOCS_BASE}/html/en"

for path in "${RU_PDF_SRC}" "${EN_PDF_SRC}" "${RU_HTML_SRC}" "${EN_HTML_SRC}"; do
  if [[ ! -e "${path}" ]]; then
    handle_deploy_error "documentation artifact not found: ${path}"
  fi
done

echo "deploy-synology: preparing deployment bundle"
echo "  NAS URL: ${NAS_URL}"
echo "  NAS path: ${NAS_DOCS}"
echo "  strict mode: ${NAS_DEPLOY_STRICT}"
echo "  docs bundle: ${REPO_DOCS_NAME} (PDF base: ${DOCS_PDF_BASE_NAME})"

rm -rf "${STAGING_DIR}"
mkdir -p "${STAGING_DIR}/${REPO_DOCS_NAME}"

cp -a "${RU_HTML_SRC}" "${STAGING_DIR}/${REPO_DOCS_NAME}/ru"
cp -a "${EN_HTML_SRC}" "${STAGING_DIR}/${REPO_DOCS_NAME}/en"
cp "${RU_PDF_SRC}" "${STAGING_DIR}/${REPO_DOCS_NAME}.pdf"
cp "${EN_PDF_SRC}" "${STAGING_DIR}/${REPO_DOCS_NAME}_en.pdf"

rm -f "${ARCHIVE_PATH}"
(
  cd "${STAGING_DIR}"
  zip -rq "${ARCHIVE_PATH}" .
)

ARCHIVE_SIZE="$(du -h "${ARCHIVE_PATH}" | cut -f1)"
echo "deploy-synology: archive ${ARCHIVE_NAME} (${ARCHIVE_SIZE})"

COOKIE_JAR="$(mktemp)"
chmod 600 "${COOKIE_JAR}"
SID=""
cleanup() {
  if [[ -n "${SID}" ]]; then
    curl -s "${CURL_OPTS[@]}" -b "${COOKIE_JAR}" -G "${NAS_URL}/webapi/auth.cgi" \
      --data-urlencode "api=SYNO.API.Auth" \
      --data-urlencode "version=1" \
      --data-urlencode "method=logout" \
      --data-urlencode "session=FileStation" \
      --data-urlencode "_sid=${SID}" >/dev/null || true
  fi
  rm -f "${COOKIE_JAR}" "${ARCHIVE_PATH}"
  rm -rf "${STAGING_DIR}"
}
trap cleanup EXIT

syno_post() {
  curl -s "${CURL_OPTS[@]}" -b "${COOKIE_JAR}" -X POST "${NAS_URL}/webapi/entry.cgi" "$@"
}

syno_get() {
  curl -s "${CURL_OPTS[@]}" -b "${COOKIE_JAR}" -G "${NAS_URL}/webapi/entry.cgi" "$@"
}

json_success() {
  local response="$1"
  [[ "$(echo "${response}" | jq -r '.success // false')" == "true" ]]
}

json_error_code() {
  local response="$1"
  echo "${response}" | jq -r '.error.code // empty'
}

syno_api_auth_error_hint() {
  local code="$1"
  case "${code}" in
    400)
      echo "No such account or incorrect password — check NAS_USER and NAS_PASS in CI/CD Variables."
      ;;
    401)
      echo "Account is disabled in DSM."
      ;;
    402)
      echo "Permission denied — enable File Station for NAS_USER (DSM → Control Panel → User & Group → Applications → File Station: Allow)."
      ;;
    403)
      echo "2-step verification required — set masked NAS_OTP_CODE in CI/CD or use an application-specific password."
      ;;
    404)
      echo "Invalid 2-step verification code — check NAS_OTP_CODE."
      ;;
    *)
      echo "See Synology File Station API guide (SYNO.API.Auth error codes)."
      ;;
  esac
}

resolve_auth_api_version() {
  if [[ -n "${NAS_AUTH_API_VERSION:-}" ]]; then
    AUTH_API_VERSION="${NAS_AUTH_API_VERSION}"
    return
  fi
  # File Station guide documents Auth v3; DSM 7+ often reports maxVersion 7 in SYNO.API.Info.
  AUTH_API_VERSION=3
  local info max_ver
  info="$(curl -s "${CURL_OPTS[@]}" -G "${NAS_URL}/webapi/query.cgi" \
    --data-urlencode "api=SYNO.API.Info" \
    --data-urlencode "version=1" \
    --data-urlencode "method=query" \
    --data-urlencode "query=SYNO.API.Auth")"
  max_ver="$(echo "${info}" | jq -r '.data["SYNO.API.Auth"].maxVersion // empty')"
  if [[ -n "${max_ver}" && "${max_ver}" =~ ^[0-9]+$ ]]; then
    AUTH_API_VERSION="${max_ver}"
  fi
}

syno_establish_session() {
  echo "deploy-synology: authenticating (SYNO.API.Auth v${AUTH_API_VERSION}, user=${NAS_USER})"
  AUTH_RESPONSE="$(syno_login)"

  if ! json_success "${AUTH_RESPONSE}"; then
    auth_err_code="$(json_error_code "${AUTH_RESPONSE}")"
    auth_hint="$(syno_api_auth_error_hint "${auth_err_code}")"
    handle_deploy_error "login failed (code ${auth_err_code}): ${auth_hint} Response: ${AUTH_RESPONSE}"
  fi

  SID="$(echo "${AUTH_RESPONSE}" | jq -r '.data.sid')"
  if [[ -z "${SID}" || "${SID}" == "null" ]]; then
    handle_deploy_error "login returned empty SID: ${AUTH_RESPONSE}"
  fi
}

syno_upload_archive() {
  local upload_sid_query
  upload_sid_query="$(jq -rn --arg sid "${SID}" '"_sid=" + ($sid|@uri)')"
  curl -s "${CURL_OPTS[@]}" -b "${COOKIE_JAR}" -X POST \
    "${NAS_URL}/webapi/entry.cgi?${upload_sid_query}" \
    -F "api=SYNO.FileStation.Upload" \
    -F "version=${FILESTATION_API_VERSION}" \
    -F "method=upload" \
    -F "path=${NAS_DOCS}" \
    -F "create_parents=true" \
    -F "overwrite=true" \
    -F "file=@${ARCHIVE_PATH};filename=${ARCHIVE_NAME}"
}

syno_login() {
  local auth_args=(
    -c "${COOKIE_JAR}"
    -b "${COOKIE_JAR}"
    -G "${NAS_URL}/webapi/auth.cgi"
    --data-urlencode "api=SYNO.API.Auth"
    --data-urlencode "version=${AUTH_API_VERSION}"
    --data-urlencode "method=login"
    --data-urlencode "account=${NAS_USER}"
    --data-urlencode "passwd=${NAS_PASS}"
    --data-urlencode "session=FileStation"
    --data-urlencode "format=sid"
  )
  if [[ -n "${NAS_OTP_CODE}" ]]; then
    auth_args+=(--data-urlencode "otp_code=${NAS_OTP_CODE}")
  fi
  curl -s "${CURL_OPTS[@]}" "${auth_args[@]}"
}

# Non-blocking Delete/Extract tasks must be polled via each API's status method (not BackgroundTask).
wait_filestation_task() {
  local api="$1"
  local task_id="$2"
  local attempt=0
  local max_attempts=120
  local quoted_task_id
  quoted_task_id="$(jq -n --arg t "${task_id}" '$t')"

  while (( attempt < max_attempts )); do
    local response
    response="$(syno_get \
      --data-urlencode "api=${api}" \
      --data-urlencode "version=${FILESTATION_API_VERSION}" \
      --data-urlencode "method=status" \
      --data-urlencode "taskid=${quoted_task_id}" \
      --data-urlencode "_sid=${SID}")"

    if ! json_success "${response}"; then
      handle_deploy_error "${api} status failed: ${response}"
    fi

    local finished
    finished="$(echo "${response}" | jq -r '.data.finished // false')"
    if [[ "${finished}" == "true" ]]; then
      return 0
    fi

    sleep 2
    attempt=$((attempt + 1))
  done

  handle_deploy_error "timeout waiting for ${api} task ${task_id}"
}

resolve_auth_api_version
syno_establish_session

DELETE_PATHS_JSON="$(jq -n \
  --arg pdf_ru "${NAS_DOCS}/${REPO_DOCS_NAME}.pdf" \
  --arg pdf_en "${NAS_DOCS}/${REPO_DOCS_NAME}_en.pdf" \
  --arg html_dir "${NAS_DOCS}/${REPO_DOCS_NAME}" \
  --arg archive "${NAS_DOCS}/${ARCHIVE_NAME}" \
  '[$pdf_ru, $pdf_en, $html_dir, $archive]')"

echo "deploy-synology: removing previous documentation on NAS"
DELETE_RESPONSE="$(syno_post \
  --data-urlencode "api=SYNO.FileStation.Delete" \
  --data-urlencode "version=${FILESTATION_API_VERSION}" \
  --data-urlencode "method=start" \
  --data-urlencode "path=${DELETE_PATHS_JSON}" \
  --data-urlencode "recursive=true" \
  --data-urlencode "_sid=${SID}")"

if json_success "${DELETE_RESPONSE}"; then
  DELETE_TASK_ID="$(echo "${DELETE_RESPONSE}" | jq -r '.data.taskid // empty')"
  if [[ -n "${DELETE_TASK_ID}" ]]; then
    wait_filestation_task "SYNO.FileStation.Delete" "${DELETE_TASK_ID}"
  fi
else
  # Non-fatal when targets are already absent (first deploy).
  echo "deploy-synology: delete skipped or not needed: $(echo "${DELETE_RESPONSE}" | jq -c '.error // .')"
fi

echo "deploy-synology: uploading ${ARCHIVE_NAME}"
# RFC 1867: file part must be last. _sid goes in the query string (not a form field).
UPLOAD_RESPONSE="$(syno_upload_archive)"
if [[ -n "${UPLOAD_RESPONSE}" ]] && ! json_success "${UPLOAD_RESPONSE}"; then
  if [[ "$(json_error_code "${UPLOAD_RESPONSE}")" == "119" && "${AUTH_API_VERSION}" != "3" ]]; then
    echo "deploy-synology: upload got SID not found (119) with Auth v${AUTH_API_VERSION}, retrying with v3"
    AUTH_API_VERSION=3
    syno_establish_session
    UPLOAD_RESPONSE="$(syno_upload_archive)"
  fi
fi

if [[ -n "${UPLOAD_RESPONSE}" ]] && ! json_success "${UPLOAD_RESPONSE}"; then
  handle_deploy_error "upload failed: ${UPLOAD_RESPONSE}"
fi

REMOTE_ARCHIVE="${NAS_DOCS}/${ARCHIVE_NAME}"
echo "deploy-synology: extracting archive on NAS"
EXTRACT_RESPONSE="$(syno_post \
  --data-urlencode "api=SYNO.FileStation.Extract" \
  --data-urlencode "version=${FILESTATION_API_VERSION}" \
  --data-urlencode "method=start" \
  --data-urlencode "file_path=${REMOTE_ARCHIVE}" \
  --data-urlencode "dest_folder_path=${NAS_DOCS}" \
  --data-urlencode "overwrite=true" \
  --data-urlencode "keep_dir=true" \
  --data-urlencode "create_subfolder=false" \
  --data-urlencode "_sid=${SID}")"

if ! json_success "${EXTRACT_RESPONSE}"; then
  handle_deploy_error "extract failed: ${EXTRACT_RESPONSE}"
fi

EXTRACT_TASK_ID="$(echo "${EXTRACT_RESPONSE}" | jq -r '.data.taskid // empty')"
if [[ -n "${EXTRACT_TASK_ID}" ]]; then
  wait_filestation_task "SYNO.FileStation.Extract" "${EXTRACT_TASK_ID}"
fi

echo "deploy-synology: removing remote archive"
ARCHIVE_DELETE_PATH="$(jq -n --arg p "${REMOTE_ARCHIVE}" '[$p]')"
ARCHIVE_DELETE_RESPONSE="$(syno_post \
  --data-urlencode "api=SYNO.FileStation.Delete" \
  --data-urlencode "version=${FILESTATION_API_VERSION}" \
  --data-urlencode "method=start" \
  --data-urlencode "path=${ARCHIVE_DELETE_PATH}" \
  --data-urlencode "recursive=false" \
  --data-urlencode "_sid=${SID}")"

if json_success "${ARCHIVE_DELETE_RESPONSE}"; then
  ARCHIVE_TASK_ID="$(echo "${ARCHIVE_DELETE_RESPONSE}" | jq -r '.data.taskid // empty')"
  if [[ -n "${ARCHIVE_TASK_ID}" ]]; then
    wait_filestation_task "SYNO.FileStation.Delete" "${ARCHIVE_TASK_ID}"
  fi
else
  echo "deploy-synology: warning: failed to delete remote archive: ${ARCHIVE_DELETE_RESPONSE}"
fi

echo "deploy-synology: deployment complete"
echo "  PDF (ru): ${NAS_DOCS}/${REPO_DOCS_NAME}.pdf"
echo "  PDF (en): ${NAS_DOCS}/${REPO_DOCS_NAME}_en.pdf"
echo "  HTML (ru): ${NAS_DOCS}/${REPO_DOCS_NAME}/ru/index.html"
echo "  HTML (en): ${NAS_DOCS}/${REPO_DOCS_NAME}/en/index.html"
