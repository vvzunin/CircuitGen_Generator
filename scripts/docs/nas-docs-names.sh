#!/usr/bin/env bash
# Resolve documentation deploy names from CMake and CI variables.
#
# Exports:
#   DOCS_PDF_BASE_NAME  — Doxygen PDF basename (CMake project() name)
#   REPO_DOCS_NAME      — display name (Graph, Generator, …)
#   DOCS_MODULE_SLUG    — URL path segment under modules/ (graph, generator, …)
#   PROJECT_VERSION     — from CMake project(VERSION …)
#   DOCS_MODULE_REPO    — repository URL (CMake HOMEPAGE_URL or DOCS_MODULE_REPO)
#
# normalize_nas_docs_path: File Station API paths are share-relative (/share/...).

normalize_nas_docs_path() {
  local path="${1%/}"
  if [[ "${path}" =~ ^/volume[0-9]+/(.+)$ ]]; then
    path="/${BASH_REMATCH[1]}"
  fi
  printf '%s' "${path}"
}

_cmake_project_field() {
  local cmake_file="$1"
  local field="$2"
  awk -v want="${field}" '
    /^[[:space:]]*project\(/ { in_project = 1; next }
    in_project && /^[[:space:]]*VERSION[[:space:]]/ {
      gsub(/^[[:space:]]+|[[:space:]]*,?[[:space:]]*$/, "", $0)
      sub(/^VERSION[[:space:]]+/, "", $0)
      if (want == "version") { print; exit }
    }
    in_project && /^[[:space:]]*HOMEPAGE_URL[[:space:]]/ {
      gsub(/^[[:space:]]+|[[:space:]]*,?[[:space:]]*$/, "", $0)
      sub(/^HOMEPAGE_URL[[:space:]]+/, "", $0)
      gsub(/^"/, "", $0)
      gsub(/"$/, "", $0)
      if (want == "homepage") { print; exit }
    }
    in_project && /^[[:space:]]*[A-Za-z_][A-Za-z0-9_]*/ {
      gsub(/^[[:space:]]+|[[:space:]]*,?[[:space:]]*$/, "", $0)
      if (want == "name" && $0 !~ /^(VERSION|DESCRIPTION|HOMEPAGE_URL|LANGUAGES)/) {
        print
        exit
      }
    }
  ' "${cmake_file}"
}

resolve_nas_docs_names() {
  local project_root="${1:?project root required}"
  local cmake_file="${project_root}/CMakeLists.txt"

  if [[ -z "${DOCS_PDF_BASE_NAME:-}" ]]; then
    if [[ ! -f "${cmake_file}" ]]; then
      echo "nas-docs-names: CMakeLists.txt not found: ${cmake_file}" >&2
      return 1
    fi
    DOCS_PDF_BASE_NAME="$(_cmake_project_field "${cmake_file}" name)"
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

  if [[ -z "${DOCS_MODULE_SLUG:-}" ]]; then
    DOCS_MODULE_SLUG="$(printf '%s' "${REPO_DOCS_NAME}" | tr '[:upper:]' '[:lower:]')"
  fi

  if [[ -z "${PROJECT_VERSION:-}" && -f "${cmake_file}" ]]; then
    PROJECT_VERSION="$(_cmake_project_field "${cmake_file}" version)"
  fi
  PROJECT_VERSION="${PROJECT_VERSION:-unknown}"

  if [[ -z "${DOCS_MODULE_REPO:-}" && -f "${cmake_file}" ]]; then
    DOCS_MODULE_REPO="$(_cmake_project_field "${cmake_file}" homepage)"
  fi

  export DOCS_PDF_BASE_NAME REPO_DOCS_NAME DOCS_MODULE_SLUG PROJECT_VERSION DOCS_MODULE_REPO
}
