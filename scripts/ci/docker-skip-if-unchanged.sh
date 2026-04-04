#!/usr/bin/env bash
# Exit 0 if docker build for this layer can be skipped (registry has image and context unchanged).
# Exit 1 if a build is required.
# Caller must set DOCKER_CI_IMAGE / DOCKER_DEV_IMAGE / DOCKER_RELEASE_IMAGE (for role).
# Usage: docker-skip-if-unchanged.sh ci|dev|release
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
role="${1:?role required}"

case "${role}" in
  ci) img="${DOCKER_CI_IMAGE:?}" ;;
  dev) img="${DOCKER_DEV_IMAGE:?}" ;;
  release) img="${DOCKER_RELEASE_IMAGE:?}" ;;
  *)
    echo "Unknown role: ${role}" >&2
    exit 2
    ;;
esac

if ! docker manifest inspect "${img}" >/dev/null 2>&1; then
  exit 1
fi

if bash "${ROOT_DIR}/scripts/ci/docker-context-changed.sh" "${role}"; then
  exit 1
fi

echo "Skipping ${role} build: ${img} exists and relevant paths unchanged."
exit 0
