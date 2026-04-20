#!/usr/bin/env bash
set -euo pipefail

# Local pre-push checks:
# 1) configure dev preset
# 2) run basic static checks (format + spell); if format-check fails, run format-fix and re-check
# 3) build and run tests for dev and release-ci profiles

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

JOBS="${JOBS:-$(nproc)}"

echo "==> Checking required tools"
command -v cmake >/dev/null 2>&1 || { echo "cmake is required"; exit 1; }
command -v ninja >/dev/null 2>&1 || { echo "ninja is required"; exit 1; }
command -v codespell >/dev/null 2>&1 || { echo "codespell is required for spell-check"; exit 1; }

echo "==> Cleaning local build tree"
rm -rf build
shopt -s nullglob
for _cg_pre_push_build_dir in build-*; do
  rm -rf "${_cg_pre_push_build_dir}"
done
shopt -u nullglob

echo "==> Configure dev preset"
cmake --preset=dev

echo "==> Basic checks: format-check + spell-check"
if ! cmake --build --preset=dev -t format-check -j "${JOBS}"; then
  echo "==> format-check failed; running format-fix"
  cmake --build --preset=dev -t format-fix -j "${JOBS}"
  echo "==> Re-running format-check after format-fix"
  cmake --build --preset=dev -t format-check -j "${JOBS}"
fi
cmake --build --preset=dev -t spell-check -j "${JOBS}"

echo "==> Build and test dev preset"
cmake --build --preset=dev -j "${JOBS}"
ctest --preset=dev

echo "==> Build and test release-ci preset (CI parity)"
cmake --preset=release-ci
cmake --build --preset=release-ci -j "${JOBS}"
ctest --preset=release-ci

echo "All pre-push checks passed."
