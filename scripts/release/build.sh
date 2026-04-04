#!/usr/bin/env bash
set -euo pipefail

# Build optimized release profile (without tests).

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

JOBS="${JOBS:-$(nproc)}"

rm -rf build/release
cmake --preset=release
cmake --build --preset=release -j "${JOBS}"
