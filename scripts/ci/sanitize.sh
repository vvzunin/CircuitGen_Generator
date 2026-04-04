#!/usr/bin/env bash
set -euo pipefail

# Default ASAN/UBSAN options for ctest; override ASAN_OPTIONS / UBSAN_OPTIONS in the environment if needed.
export ASAN_OPTIONS="${ASAN_OPTIONS:-strict_string_checks=1:detect_stack_use_after_return=1:check_initialization_order=1:strict_init_order=1:detect_leaks=1:detect_odr_violation=1}"
export UBSAN_OPTIONS="${UBSAN_OPTIONS:-print_stacktrace=1}"

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

# Sanitizer builds use much more RAM per compiler/link job than a normal build.
# Full nproc parallelism on small GitLab runners often triggers OOM (SIGKILL, exit 137).
if [[ -z "${JOBS:-}" ]]; then
  JOBS="$(nproc)"
  if [[ -n "${CI:-}" ]]; then
    _max="${CI_SANITIZE_MAX_JOBS:-4}"
    if (( JOBS > _max )); then
      JOBS="${_max}"
    fi
  fi
fi

rm -rf build/sanitize
cmake --preset=ci-sanitize
cmake --build build/sanitize -j "${JOBS}"
ctest --test-dir build/sanitize --output-on-failure --no-tests=error -j "${JOBS}"
