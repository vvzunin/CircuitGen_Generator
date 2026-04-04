#!/usr/bin/env bash
set -euo pipefail

# Local coverage run using the coverage preset.

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

JOBS="${JOBS:-$(nproc)}"

rm -rf build/coverage
cmake --preset=coverage
cmake --build --preset=coverage -j "${JOBS}"
ctest --preset=coverage
cmake --build --preset=coverage -t coverage -j "${JOBS}"
