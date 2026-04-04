#!/usr/bin/env bash
# Return 0 if git diff touches paths that affect the given image layer, 1 otherwise.
# Usage: docker-context-changed.sh ci|dev|release
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

role="${1:-ci}"

# Prefer MR merge base; else previous commit on push pipelines.
base="${CI_MERGE_REQUEST_DIFF_BASE_SHA:-${CI_COMMIT_BEFORE_SHA:-}}"
if [[ -z "${base}" || "${base}" == "0000000000000000000000000000000000000000" ]]; then
  exit 0
fi

case "${role}" in
  ci)
    paths=(
      dockerfile/Dockerfile.ci
      scripts/setup
      scripts/config/supported-os.sh
      scripts/ci/docker-build-ci.sh
      scripts/ci/docker-skip-if-unchanged.sh
      scripts/ci/docker-context-changed.sh
    )
    ;;
  dev)
    paths=(
      dockerfile/Dockerfile.dev
      scripts/ci/docker-build-dev.sh
      scripts/ci/docker-skip-if-unchanged.sh
      scripts/ci/docker-context-changed.sh
    )
    ;;
  release)
    paths=(
      dockerfile/Dockerfile.release
      scripts/ci/docker-build-release.sh
      scripts/ci/docker-skip-if-unchanged.sh
      scripts/ci/docker-context-changed.sh
    )
    ;;
  *)
    echo "Unknown role: ${role}" >&2
    exit 2
    ;;
esac

if ! out="$(git diff --name-only "${base}" "${CI_COMMIT_SHA}" -- "${paths[@]}" 2>/dev/null)"; then
  exit 0
fi
if [[ -n "${out}" ]]; then
  exit 0
fi
exit 1
