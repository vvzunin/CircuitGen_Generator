#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

PATTERNS="${PATTERNS:-src/*.cpp;src/*/*.cpp;src/*/*.hpp;include/*/*.hpp;include/*/*.hpp.in;test/*/*.cpp;test/*/*.hpp}"

# Prefer /usr/local/bin/clang-format from install-clang-format-ci.sh (PyPI pin), then clang-format-18, then PATH.
if [[ -z "${FORMAT_COMMAND:-}" ]]; then
  if [[ -x /usr/local/bin/clang-format ]]; then
    FORMAT_COMMAND="/usr/local/bin/clang-format"
  elif command -v clang-format-18 >/dev/null 2>&1; then
    FORMAT_COMMAND="clang-format-18"
  elif [[ -x /usr/local/bin/clang-format-18 ]]; then
    FORMAT_COMMAND="/usr/local/bin/clang-format-18"
  elif command -v clang-format >/dev/null 2>&1; then
    FORMAT_COMMAND="clang-format"
  else
    echo "No clang-format found. Run scripts/setup/install-clang-format-ci.sh or: pip install clang-format==18.1.8"
    exit 1
  fi
fi

if ! command -v "${FORMAT_COMMAND}" >/dev/null 2>&1; then
  echo "Required formatter '${FORMAT_COMMAND}' is not installed."
  exit 1
fi

# Validate that the formatter can parse project .clang-format.
"${FORMAT_COMMAND}" --style=file --dump-config >/dev/null

FORMAT_VERSION="$("${FORMAT_COMMAND}" --version || true)"
if [[ "${FORMAT_VERSION}" != *"version 18."* ]]; then
  echo "Warning: expected clang-format 18.x (project pin 18.1.8 via PyPI) for stable formatting across CI."
  echo "${FORMAT_VERSION}"
fi

cmake -D "FORMAT_COMMAND=${FORMAT_COMMAND}" -D "PATTERNS=${PATTERNS}" -P cmake/lint.cmake
cmake -P cmake/spell.cmake
