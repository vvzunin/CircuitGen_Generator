#!/usr/bin/env bash
set -euo pipefail

# Debug build with examples using the local `dev` preset (CMakeUserPresets.json).
# Copy CMakeUserPresets.json.example to CMakeUserPresets.json if you have not already.

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

JOBS="${JOBS:-$(nproc)}"

rm -rf build/dev
cmake --preset=dev
cmake --build --preset=dev -j "${JOBS}"
cmake --build build/dev --target run-examples -j "${JOBS}"
