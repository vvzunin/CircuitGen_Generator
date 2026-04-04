#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

JOBS="${JOBS:-$(nproc)}"

rm -rf build/coverage
cmake --preset=ci-coverage
cmake --build build/coverage -j "${JOBS}"
ctest --test-dir build/coverage --output-on-failure --no-tests=error -j "${JOBS}"
cmake --build build/coverage -t coverage

if [[ -f "build/coverage/coverage_summary.txt" ]]; then
  sed -n '1,200p' "build/coverage/coverage_summary.txt"
fi
