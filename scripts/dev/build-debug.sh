#!/usr/bin/env bash
set -euo pipefail

# Simple local Debug build using the dev preset.

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

JOBS="${JOBS:-$(nproc)}"

rm -rf build/dev
cmake --preset=dev
cmake --build --preset=dev -j "${JOBS}"
