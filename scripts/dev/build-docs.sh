#!/usr/bin/env bash
# Local documentation: same pipeline as scripts/ci/docs.sh, but outputs under build/dev/docs/{html,xml,latex,pdf}/{en,ru}/.
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

export PYTHONUNBUFFERED=1
: "${DOXYGEN_SKIP_DOT_GRAPHS:=OFF}"
: "${DOXYGEN_SKIP_REFMAN_PDF:=OFF}"
: "${DOXYGEN_CLANG_ASSISTED_PARSING:=YES}"
: "${DOXYGEN_CLANG_DATABASE_PATH:=}"
DOXYGEN_LANG_VARIANTS="${DOXYGEN_LANG_VARIANTS:-}"
if [[ -z "${DOXYGEN_LANG_VARIANTS}" ]]; then
  DOXYGEN_LANG_VARIANTS="en=english;ru=russian"
fi
export DOXYGEN_LANG_VARIANTS

echo "==> Configure dev preset (compile_commands.json for Doxygen)"
echo "    Note: full docs (en + ru) run Doxygen twice, m.css, Graphviz, LaTeX — often 10–40+ minutes."
echo "    On WSL2, projects under /mnt/c/ are much slower. Faster iteration:"
echo "    DOXYGEN_SKIP_DOT_GRAPHS=ON DOXYGEN_SKIP_REFMAN_PDF=ON ./scripts/dev/build-docs.sh"
cmake --preset=dev

# Full docs need Ghostscript and a LaTeX engine (same as scripts/ci/docs.sh).
if ! command -v gs >/dev/null 2>&1; then
  echo "ERROR: 'gs' not found. Install Ghostscript (see scripts/setup/install-deps-<os>.sh)."
  exit 1
fi
if ! command -v xelatex >/dev/null 2>&1 && ! command -v pdflatex >/dev/null 2>&1; then
  echo "ERROR: neither 'xelatex' nor 'pdflatex' found. Install texlive-xetex or a TeX stack."
  exit 1
fi

if [[ "${DOXYGEN_CLANG_ASSISTED_PARSING}" == "YES" && -z "${DOXYGEN_CLANG_DATABASE_PATH}" ]]; then
  DOXYGEN_CLANG_DATABASE_PATH="${ROOT_DIR}/build/dev"
fi

if [[ "${DOXYGEN_CLANG_ASSISTED_PARSING}" == "YES" ]]; then
  if ! doxygen -V 2>&1 | grep -qiE 'clang support'; then
    if [[ "$(uname -s)" != "Linux" ]] || ! ldd "$(command -v doxygen)" 2>/dev/null | grep -qE 'libclang(\.so|-[0-9])'; then
      echo "Doxygen without LLVM/libclang support detected. Install LLVM-enabled doxygen (see scripts/setup/install-deps-*.sh)."
      exit 1
    fi
  fi
fi

export DOXYGEN_CLANG_ASSISTED_PARSING
export DOXYGEN_CLANG_OPTIONS="${DOXYGEN_CLANG_OPTIONS:--std=c++17}"
export DOXYGEN_CLANG_DATABASE_PATH
export DOXYGEN_SKIP_DOT_GRAPHS
export DOXYGEN_SKIP_REFMAN_PDF

export DOCGEN_ROOT="${ROOT_DIR}"
export DOCGEN_CMAKE_PROJECT_BINARY_DIR="${ROOT_DIR}/build/dev"
export DOCGEN_OUTPUT_BASE="${ROOT_DIR}/build/dev/docs"
export DOCGEN_STAGING_BASE="${ROOT_DIR}/build/dev/docs-tmp"

echo "==> Build documentation (en + ru under build/dev/docs/...)"
bash "${ROOT_DIR}/scripts/docs/build-doxygen-lang-variants.sh"

echo "==> Done"
echo "    HTML: ${ROOT_DIR}/build/dev/docs/html/en/  ${ROOT_DIR}/build/dev/docs/html/ru/"
echo "    PDF:  ${ROOT_DIR}/build/dev/docs/pdf/en/   ${ROOT_DIR}/build/dev/docs/pdf/ru/   (CircuitGenGenerator.pdf per language folder)"
