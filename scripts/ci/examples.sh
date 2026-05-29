#!/usr/bin/env bash
set -euo pipefail

# Verify example programs: Debug (dev-mode) and Release builds, then run the aggregate target run-examples.

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

JOBS="${JOBS:-$(nproc)}"

rm -rf build/ci-examples-dev
cmake --preset=ci-examples-dev
cmake --build --preset=ci-examples-dev -j "${JOBS}"
cmake --build --preset=ci-examples-dev --target run-examples -j "${JOBS}"

rm -rf build/release-examples
cmake --preset=release-examples
cmake --build --preset=release-examples -j "${JOBS}"
cmake --build --preset=release-examples --target run-examples -j "${JOBS}"
