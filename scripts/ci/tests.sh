#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

JOBS="${JOBS:-$(nproc)}"
INSTALL_PREFIX="${INSTALL_PREFIX:-prefix/release}"

rm -rf build/release-ci
cmake --preset=release-ci
cmake --build --preset=release-ci -j "${JOBS}"
cmake --install build/release-ci --prefix "${INSTALL_PREFIX}"
ctest --test-dir build/release-ci --output-on-failure --no-tests=error --output-junit build/release-ci/ctest_results.xml -j "${JOBS}"
