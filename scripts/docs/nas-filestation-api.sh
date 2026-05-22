#!/usr/bin/env bash
# Synology File Station API helpers (sourced by deploy-synology.sh).

nas_fs_json_success() {
  local response="$1"
  [[ "$(echo "${response}" | jq -r '.success // false')" == "true" ]]
}

nas_fs_json_error_code() {
  local response="$1"
  echo "${response}" | jq -r '.error.code // empty'
}

nas_fs_auth_error_hint() {
  local code="$1"
  case "${code}" in
    400) echo "No such account or incorrect password — check NAS_USER and NAS_PASS." ;;
    401) echo "Account is disabled in DSM." ;;
    402) echo "Permission denied — enable File Station for NAS_USER." ;;
    403) echo "2-step verification required — set NAS_OTP_CODE or app password." ;;
    404) echo "Invalid 2-step verification code — check NAS_OTP_CODE." ;;
    *) echo "See Synology File Station API guide (SYNO.API.Auth error codes)." ;;
  esac
}

nas_fs_resolve_auth_api_version() {
  if [[ -n "${NAS_AUTH_API_VERSION:-}" ]]; then
    NAS_FS_AUTH_VERSION="${NAS_AUTH_API_VERSION}"
    return
  fi
  NAS_FS_AUTH_VERSION=3
  local info max_ver
  info="$(curl -s "${NAS_FS_CURL_OPTS[@]}" -G "${NAS_URL}/webapi/query.cgi" \
    --data-urlencode "api=SYNO.API.Info" \
    --data-urlencode "version=1" \
    --data-urlencode "method=query" \
    --data-urlencode "query=SYNO.API.Auth")"
  max_ver="$(echo "${info}" | jq -r '.data["SYNO.API.Auth"].maxVersion // empty')"
  if [[ -n "${max_ver}" && "${max_ver}" =~ ^[0-9]+$ ]]; then
    NAS_FS_AUTH_VERSION="${max_ver}"
  fi
}

nas_fs_syno_post() {
  curl -s "${NAS_FS_CURL_OPTS[@]}" -b "${NAS_FS_COOKIE_JAR}" -X POST "${NAS_URL}/webapi/entry.cgi" "$@"
}

nas_fs_syno_get() {
  curl -s "${NAS_FS_CURL_OPTS[@]}" -b "${NAS_FS_COOKIE_JAR}" -G "${NAS_URL}/webapi/entry.cgi" "$@"
}

nas_fs_login() {
  local auth_args=(
    -c "${NAS_FS_COOKIE_JAR}"
    -b "${NAS_FS_COOKIE_JAR}"
    -G "${NAS_URL}/webapi/auth.cgi"
    --data-urlencode "api=SYNO.API.Auth"
    --data-urlencode "version=${NAS_FS_AUTH_VERSION}"
    --data-urlencode "method=login"
    --data-urlencode "account=${NAS_USER}"
    --data-urlencode "passwd=${NAS_PASS}"
    --data-urlencode "session=FileStation"
    --data-urlencode "format=sid"
  )
  if [[ -n "${NAS_OTP_CODE:-}" ]]; then
    auth_args+=(--data-urlencode "otp_code=${NAS_OTP_CODE}")
  fi
  curl -s "${NAS_FS_CURL_OPTS[@]}" "${auth_args[@]}"
}

nas_fs_establish_session() {
  echo "deploy-synology: authenticating (SYNO.API.Auth v${NAS_FS_AUTH_VERSION}, user=${NAS_USER})"
  local auth_response
  auth_response="$(nas_fs_login)"

  if ! nas_fs_json_success "${auth_response}"; then
    local auth_err_code auth_hint
    auth_err_code="$(nas_fs_json_error_code "${auth_response}")"
    auth_hint="$(nas_fs_auth_error_hint "${auth_err_code}")"
    nas_fs_handle_error "login failed (code ${auth_err_code}): ${auth_hint} Response: ${auth_response}"
  fi

  NAS_FS_SID="$(echo "${auth_response}" | jq -r '.data.sid')"
  if [[ -z "${NAS_FS_SID}" || "${NAS_FS_SID}" == "null" ]]; then
    nas_fs_handle_error "login returned empty SID: ${auth_response}"
  fi
}

nas_fs_upload_archive() {
  local archive_path="$1"
  local archive_name="$2"
  local upload_sid_query
  upload_sid_query="$(jq -rn --arg sid "${NAS_FS_SID}" '"_sid=" + ($sid|@uri)')"
  curl -s "${NAS_FS_CURL_OPTS[@]}" -b "${NAS_FS_COOKIE_JAR}" -X POST \
    "${NAS_URL}/webapi/entry.cgi?${upload_sid_query}" \
    -F "api=SYNO.FileStation.Upload" \
    -F "version=${NAS_FS_API_VERSION}" \
    -F "method=upload" \
    -F "path=${NAS_DOCS}" \
    -F "create_parents=true" \
    -F "overwrite=true" \
    -F "file=@${archive_path};filename=${archive_name}"
}

nas_fs_wait_task() {
  local api="$1"
  local task_id="$2"
  local attempt=0
  local max_attempts=120
  local quoted_task_id
  quoted_task_id="$(jq -n --arg t "${task_id}" '$t')"

  while (( attempt < max_attempts )); do
    local response finished
    response="$(nas_fs_syno_get \
      --data-urlencode "api=${api}" \
      --data-urlencode "version=${NAS_FS_API_VERSION}" \
      --data-urlencode "method=status" \
      --data-urlencode "taskid=${quoted_task_id}" \
      --data-urlencode "_sid=${NAS_FS_SID}")"

    if ! nas_fs_json_success "${response}"; then
      nas_fs_handle_error "${api} status failed: ${response}"
    fi

    finished="$(echo "${response}" | jq -r '.data.finished // false')"
    if [[ "${finished}" == "true" ]]; then
      return 0
    fi

    sleep 2
    attempt=$((attempt + 1))
  done

  nas_fs_handle_error "timeout waiting for ${api} task ${task_id}"
}

nas_fs_delete_paths() {
  local paths_json="$1"
  local response task_id
  response="$(nas_fs_syno_post \
    --data-urlencode "api=SYNO.FileStation.Delete" \
    --data-urlencode "version=${NAS_FS_API_VERSION}" \
    --data-urlencode "method=start" \
    --data-urlencode "path=${paths_json}" \
    --data-urlencode "recursive=true" \
    --data-urlencode "_sid=${NAS_FS_SID}")"

  if nas_fs_json_success "${response}"; then
    task_id="$(echo "${response}" | jq -r '.data.taskid // empty')"
    if [[ -n "${task_id}" ]]; then
      nas_fs_wait_task "SYNO.FileStation.Delete" "${task_id}"
    fi
    return 0
  fi
  echo "deploy-synology: delete skipped or not needed: $(echo "${response}" | jq -c '.error // .')"
}

nas_fs_download_file() {
  local remote_path="$1"
  local local_path="$2"
  local paths_json response dlink
  paths_json="$(jq -n --arg p "${remote_path}" '[$p]')"

  response="$(nas_fs_syno_post \
    --data-urlencode "api=SYNO.FileStation.Download" \
    --data-urlencode "version=${NAS_FS_API_VERSION}" \
    --data-urlencode "method=download" \
    --data-urlencode "path=${paths_json}" \
    --data-urlencode "mode=download" \
    --data-urlencode "_sid=${NAS_FS_SID}")"

  if ! nas_fs_json_success "${response}"; then
    return 1
  fi

  dlink="$(echo "${response}" | jq -r '.data[0].path // empty')"
  if [[ -z "${dlink}" ]]; then
    return 1
  fi

  curl -sf "${NAS_FS_CURL_OPTS[@]}" -b "${NAS_FS_COOKIE_JAR}" -o "${local_path}" "${dlink}"
}

nas_fs_fetch_remote_manifest() {
  local dest="$1"
  local remote="${NAS_DOCS}/manifest.json"
  if nas_fs_download_file "${remote}" "${dest}"; then
    echo "deploy-synology: merged with existing manifest.json from NAS"
    return 0
  fi
  echo "deploy-synology: no remote manifest.json (first deploy or unavailable)"
  return 1
}
