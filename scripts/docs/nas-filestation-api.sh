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

nas_fs_list_folder() {
  local folder_path="$1"
  nas_fs_syno_get \
    --data-urlencode "api=SYNO.FileStation.List" \
    --data-urlencode "version=${NAS_FS_API_VERSION}" \
    --data-urlencode "method=list" \
    --data-urlencode "folder_path=${folder_path}" \
    --data-urlencode "_sid=${NAS_FS_SID}"
}

nas_fs_fetch_remote_versions_index() {
  local dest="$1"
  local remote="${NAS_DOCS}/modules/${DOCS_MODULE_SLUG}/versions.json"
  if nas_fs_download_file "${remote}" "${dest}"; then
    echo "deploy-synology: merged with existing versions.json for ${DOCS_MODULE_SLUG}"
    return 0
  fi
  echo "deploy-synology: no remote versions.json for ${DOCS_MODULE_SLUG}"
  return 1
}

# Build one manifest module object from versions.json + per-channel meta on NAS.
_nas_fs_module_from_slug() {
  local modules_root="$1"
  local slug="$2"
  local tmp_dir="$3"

  local versions_tmp="${tmp_dir}/${slug}-versions.json"
  local legacy_meta="${tmp_dir}/${slug}-legacy-meta.json"

  if nas_fs_download_file "${modules_root}/${slug}/versions.json" "${versions_tmp}"; then
    local channels_json="[]"
    while IFS= read -r channel; do
      [[ -z "${channel}" ]] && continue
      local meta_tmp="${tmp_dir}/${slug}-${channel}-meta.json"
      if ! nas_fs_download_file "${modules_root}/${slug}/versions/${channel}/meta.json" "${meta_tmp}"; then
        continue
      fi
      local ch_entry
      ch_entry="$(jq -c --arg slug "${slug}" --arg channel "${channel}" '
        . as $meta
        | ("modules/" + $slug + "/versions/" + $channel) as $base
        | {
            id: $channel,
            kind: ($meta.docsKind // (if $channel == "main" then "branch" else "release" end)),
            label: ($meta.docsLabel // $channel),
            version: $meta.version,
            builtAt: $meta.builtAt,
            commit: $meta.commit,
            ref: $meta.ref,
            pipelineId: $meta.pipelineId,
            formats: {
              pdf: { ru: ($base + "/pdf/ru.pdf"), en: ($base + "/pdf/en.pdf") },
              html: { ru: ($base + "/html/ru/"), en: ($base + "/html/en/") }
            }
          }
      ' "${meta_tmp}")"
      channels_json="$(jq -c --argjson ch "${ch_entry}" '. + [$ch]' <<<"${channels_json}")"
    done < <(jq -r '.channels[]?.id // empty' "${versions_tmp}")

    if [[ "$(jq 'length' <<<"${channels_json}")" -gt 0 ]]; then
      jq -n \
        --arg id "${slug}" \
        --argjson channels "${channels_json}" \
        --slurpfile idx "${versions_tmp}" \
        '{
          id: $id,
          name: { ru: $id, en: $id },
          planned: false,
          defaultChannel: ($idx[0].defaultChannel // "main"),
          channels: $channels
        }'
      return 0
    fi
  fi

  if nas_fs_download_file "${modules_root}/${slug}/meta.json" "${legacy_meta}"; then
    if jq -e '.id and .formats' "${legacy_meta}" >/dev/null 2>&1; then
      jq -c '
        . as $meta
        | ("modules/" + $meta.id) as $base
        | {
            id: $meta.id,
            name: ($meta.name // { ru: $meta.id, en: $meta.id }),
            repo: $meta.repo,
            docker: ($meta.docker // null),
            planned: false,
            defaultChannel: "main",
            channels: [
              {
                id: "main",
                kind: "branch",
                label: "main",
                version: $meta.version,
                builtAt: $meta.builtAt,
                commit: $meta.commit,
                ref: $meta.ref,
                pipelineId: $meta.pipelineId,
                formats: {
                  pdf: {
                    ru: ($base + "/" + $meta.formats.pdf.ru),
                    en: ($base + "/" + $meta.formats.pdf.en)
                  },
                  html: {
                    ru: ($base + "/" + $meta.formats.html.ru),
                    en: ($base + "/" + $meta.formats.html.en)
                  }
                }
              }
            ]
          }
      ' "${legacy_meta}"
      return 0
    fi
  fi

  return 1
}

# JSON array of sibling module manifest entries (schema v2). Skips current slug.
nas_fs_collect_remote_modules_for_manifest() {
  local output_path="$1"
  local modules_root="${NAS_DOCS}/modules"
  local list_response collected=0

  list_response="$(nas_fs_list_folder "${modules_root}")"
  if ! nas_fs_json_success "${list_response}"; then
    echo "deploy-synology: modules list unavailable (empty or first deploy)"
    echo "[]" >"${output_path}"
    return 0
  fi

  local tmp_dir entries=()
  tmp_dir="$(mktemp -d)"
  while IFS= read -r slug; do
    [[ -z "${slug}" ]] && continue
    if [[ "${slug}" == "${DOCS_MODULE_SLUG}" ]]; then
      continue
    fi
    local module_json
    if module_json="$(_nas_fs_module_from_slug "${modules_root}" "${slug}" "${tmp_dir}")"; then
      entries+=("${module_json}")
      collected=$((collected + 1))
    fi
  done < <(echo "${list_response}" | jq -r '.data.files[]? | select(.isdir == true or .isdir == "dir") | .name')

  rm -rf "${tmp_dir}"

  if ((${#entries[@]} > 0)); then
    printf '%s\n' "${entries[@]}" | jq -s '.' >"${output_path}"
  else
    echo "[]" >"${output_path}"
  fi
  echo "deploy-synology: collected ${collected} sibling module(s) with versioned docs from NAS"
}

# Backward-compatible alias (older deploy scripts).
nas_fs_collect_remote_module_metas() {
  nas_fs_collect_remote_modules_for_manifest "$@"
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
