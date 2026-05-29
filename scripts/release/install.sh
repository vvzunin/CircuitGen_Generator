#!/usr/bin/env bash
set -euo pipefail

# Install artifacts from release build tree.

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

INSTALL_PREFIX="${INSTALL_PREFIX:-prefix/release}"

cmake --install build/release --prefix "${INSTALL_PREFIX}"
