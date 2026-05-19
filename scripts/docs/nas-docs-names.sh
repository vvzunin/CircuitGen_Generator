#!/usr/bin/env bash
# Resolve REPO_DOCS_NAME and DOCS_PDF_BASE_NAME for Synology NAS documentation deploy.
#
# Priority: environment variables, then CMake project() from CMakeLists.txt.
# REPO_DOCS_NAME defaults to the project name without a leading "CircuitGen" prefix
# (CircuitGenGenerator → Generator, CircuitGenGraph → Graph, etc.).
#
# normalize_nas_docs_path: File Station API paths are share-relative (/share/...).
# DSM absolute paths (/volume1/share/...) are accepted in CI and normalized here.

normalize_nas_docs_path() {
  local path="${1%/}"
  if [[ "${path}" =~ ^/volume[0-9]+/(.+)$ ]]; then
    path="/${BASH_REMATCH[1]}"
  fi
  printf '%s' "${path}"
}

resolve_nas_docs_names() {
  local project_root="${1:?project root required}"
  local cmake_file="${project_root}/CMakeLists.txt"

  if [[ -z "${DOCS_PDF_BASE_NAME:-}" ]]; then
    if [[ ! -f "${cmake_file}" ]]; then
      echo "nas-docs-names: CMakeLists.txt not found: ${cmake_file}" >&2
      return 1
    fi
    DOCS_PDF_BASE_NAME="$(
      awk '
        /^[[:space:]]*project\(/ { in_project = 1; next }
        in_project && /^[[:space:]]*[A-Za-z_][A-Za-z0-9_]*/ {
          gsub(/^[[:space:]]+|[[:space:]]*,?[[:space:]]*$/, "", $0)
          print
          exit
        }
      ' "${cmake_file}"
    )"
  fi

  if [[ -z "${DOCS_PDF_BASE_NAME}" ]]; then
    echo "nas-docs-names: could not read project() name from ${cmake_file}" >&2
    return 1
  fi

  if [[ -z "${REPO_DOCS_NAME:-}" ]]; then
    if [[ "${DOCS_PDF_BASE_NAME}" == CircuitGen* ]]; then
      REPO_DOCS_NAME="${DOCS_PDF_BASE_NAME#CircuitGen}"
    else
      REPO_DOCS_NAME="${DOCS_PDF_BASE_NAME}"
    fi
  fi

  export DOCS_PDF_BASE_NAME REPO_DOCS_NAME
}
