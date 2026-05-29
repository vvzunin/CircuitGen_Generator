#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

JOBS="${JOBS:-$(nproc)}"

if ! command -v cppcheck >/dev/null 2>&1; then
  echo "cppcheck is required for static analysis."
  exit 1
fi

rm -rf build/static-analysis
cmake --preset=ci-static-analysis
cmake --build --preset=ci-static-analysis -j "${JOBS}"

# Project-wide cppcheck (compile_commands.json). CMake's per-TU CMAKE_CXX_CPPCHECK wrapper is unreliable here
# (LTO flags, etc.). Third-party paths are suppressed for known parser noise; use stricter --enable locally if needed.
COMPILE_DB="${ROOT_DIR}/build/static-analysis/compile_commands.json"
cppcheck \
  --project="${COMPILE_DB}" \
  --inline-suppr \
  --suppress=missingIncludeSystem:* \
  --suppress=syntaxError:*nlohmann* \
  --suppress=preprocessorErrorDirective:*nlohmann* \
  --suppress=*:*/easyloggingpp/* \
  --suppress=returnTempReference:*lib/fmt/* \
  --suppress=normalCheckLevelMaxBranches:* \
  -i "${ROOT_DIR}/build/static-analysis/_deps" \
  -i "${ROOT_DIR}/lib" \
  -j "${JOBS}" \
  --error-exitcode=1
