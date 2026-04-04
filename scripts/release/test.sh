#!/usr/bin/env bash
set -euo pipefail

# Build and test release profile with CI parity.

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

JOBS="${JOBS:-$(nproc)}"

rm -rf build/release-ci
cmake --preset=release-ci
cmake --build --preset=release-ci -j "${JOBS}"
ctest --preset=release-ci
