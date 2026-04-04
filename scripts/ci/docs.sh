#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
# shellcheck source=../docker/docker-paths.sh
source "${ROOT_DIR}/scripts/docker/docker-paths.sh"
if [[ -z "${CI_IMAGE_TAG:-}" ]]; then
  docker_paths_load_registry
  docker_paths_apply_target_os
  docker_paths_image_os_suffix
  docker_paths_local_ci_dev
fi
CLANG_PARSE="${DOXYGEN_CLANG_ASSISTED_PARSING:-YES}"
CLANG_DB_PATH="${DOXYGEN_CLANG_DATABASE_PATH:-}"
DOXYGEN_ENABLED_SECTIONS="${DOXYGEN_ENABLED_SECTIONS:-english}"
DOXYGEN_LANG_VARIANTS="${DOXYGEN_LANG_VARIANTS:-}"
DOCS_RUNNER="${DOCS_RUNNER:-auto}"
: "${DOXYGEN_SKIP_DOT_GRAPHS:=OFF}"
: "${DOXYGEN_SKIP_REFMAN_PDF:=OFF}"

echo "Commit received. Building docs for ${CI_DEFAULT_BRANCH:-default-branch}"

# By default, local execution uses the CI image where Doxygen is built
# with LLVM/libclang support. In CI container execution remains local.
if [[ "${DOCS_RUNNER}" == "auto" ]]; then
  if [[ -n "${CI:-}" || -f "/.dockerenv" ]]; then
    DOCS_RUNNER="local"
  else
    DOCS_RUNNER="docker"
  fi
fi

if [[ "${DOCS_RUNNER}" == "docker" ]]; then
  docker run --rm -t \
    -u "$(id -u):$(id -g)" \
    -e "DOCS_RUNNER=local" \
    -e "CI_DEFAULT_BRANCH=${CI_DEFAULT_BRANCH:-}" \
    -e "DOXYGEN_CLANG_ASSISTED_PARSING=${CLANG_PARSE}" \
    -e "DOXYGEN_CLANG_OPTIONS=${DOXYGEN_CLANG_OPTIONS:--std=c++17}" \
    -e "DOXYGEN_CLANG_DATABASE_PATH=${CLANG_DB_PATH}" \
    -e "DOXYGEN_ENABLED_SECTIONS=${DOXYGEN_ENABLED_SECTIONS}" \
    -e "DOXYGEN_LANG_VARIANTS=${DOXYGEN_LANG_VARIANTS}" \
    -e "DOXYGEN_SKIP_DOT_GRAPHS=${DOXYGEN_SKIP_DOT_GRAPHS}" \
    -e "DOXYGEN_SKIP_REFMAN_PDF=${DOXYGEN_SKIP_REFMAN_PDF}" \
    -v "${ROOT_DIR}:${ROOT_DIR}" \
    -w "${ROOT_DIR}" \
    "${CI_IMAGE_TAG}" \
    bash scripts/ci/docs.sh
  exit 0
fi

# Full docs (HTML + LaTeX PDF) need Ghostscript (libgs) and xelatex or pdflatex; see scripts/setup/install-deps-*.sh.
if ! command -v gs >/dev/null 2>&1; then
  echo "ERROR: 'gs' not found. Install Ghostscript (see scripts/setup/install-deps-<os>.sh)."
  exit 1
fi
if ! command -v xelatex >/dev/null 2>&1 && ! command -v pdflatex >/dev/null 2>&1; then
  echo "ERROR: neither 'xelatex' nor 'pdflatex' found. Install texlive-xetex or a TeX stack (see scripts/setup/install-deps-<os>.sh)."
  exit 1
fi

# If libclang parsing is enabled and no compilation database is provided,
# generate one from ci-examples-dev (in CMakePresets.json). The local-only "dev"
# preset lives in CMakeUserPresets.json and is not available in clean CI checkouts.
if [[ "${CLANG_PARSE}" == "YES" && -z "${CLANG_DB_PATH}" ]]; then
  _docs_compile_db="${ROOT_DIR}/build/ci-examples-dev"
  if [[ ! -f "${_docs_compile_db}/compile_commands.json" ]]; then
    cmake --preset=ci-examples-dev >/dev/null
  fi
  CLANG_DB_PATH="${_docs_compile_db}"
fi

if [[ "${CLANG_PARSE}" == "YES" ]]; then
  if ! doxygen -V 2>&1 | grep -qiE 'clang support'; then
    if [[ "$(uname -s)" != "Linux" ]] || ! ldd "$(command -v doxygen)" 2>/dev/null | grep -qE 'libclang(\.so|-[0-9])'; then
      echo "Doxygen without LLVM/libclang support detected."
      echo "Use CI image runner or install LLVM-enabled doxygen via scripts/setup/install-deps-*.sh."
      exit 1
    fi
  fi
fi

# Default: English and Russian in build/docs/{html,xml,latex,pdf}/{en,ru}/.
# Override with DOXYGEN_LANG_VARIANTS="en=english" only, or custom section lists.
if [[ -z "${DOXYGEN_LANG_VARIANTS}" ]]; then
  DOXYGEN_LANG_VARIANTS="en=english;ru=russian"
fi
export DOXYGEN_LANG_VARIANTS

export DOXYGEN_CLANG_ASSISTED_PARSING="${CLANG_PARSE}"
export DOXYGEN_CLANG_OPTIONS="${DOXYGEN_CLANG_OPTIONS:--std=c++17}"
export DOXYGEN_CLANG_DATABASE_PATH="${CLANG_DB_PATH}"
export DOXYGEN_SKIP_DOT_GRAPHS="${DOXYGEN_SKIP_DOT_GRAPHS}"
export DOXYGEN_SKIP_REFMAN_PDF="${DOXYGEN_SKIP_REFMAN_PDF}"

export DOCGEN_ROOT="${ROOT_DIR}"
export DOCGEN_CMAKE_PROJECT_BINARY_DIR="${ROOT_DIR}/build"
export DOCGEN_OUTPUT_BASE="${ROOT_DIR}/build/docs"
export DOCGEN_STAGING_BASE="${ROOT_DIR}/build/docs-tmp"

bash "${ROOT_DIR}/scripts/docs/build-doxygen-lang-variants.sh"
