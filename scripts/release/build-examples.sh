#!/usr/bin/env bash
set -euo pipefail

# Optimized Release build including example programs (preset release-examples from CMakePresets.json).

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

JOBS="${JOBS:-$(nproc)}"

rm -rf build/release-examples
cmake --preset=release-examples
cmake --build --preset=release-examples -j "${JOBS}"
cmake --build build/release-examples --target run-examples -j "${JOBS}"
