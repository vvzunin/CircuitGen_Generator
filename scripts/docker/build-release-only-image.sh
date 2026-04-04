#!/usr/bin/env bash
set -euo pipefail

# Build only local RELEASE Docker image (slim OS base + minimal build deps; no CI fat image).
# Optional: TARGET_OS=ubuntu-24.04 (see scripts/docker/docker-paths.sh)

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
# shellcheck source=docker-paths.sh
source "${ROOT_DIR}/scripts/docker/docker-paths.sh"

DOCKERFILE_RELEASE_NAME="${DOCKERFILE_RELEASE_NAME:-dockerfile/Dockerfile.release}"
DOCKERFILE_RELEASE="${DOCKERFILE_RELEASE:-${DOCKERFILE_RELEASE_NAME}}"
docker_paths_load_registry
docker_paths_apply_target_os
docker_paths_image_os_suffix
docker_paths_local_ci_dev

echo "Building local RELEASE image: ${RELEASE_IMAGE_TAG}"
echo "Using base OS image: ${DOCKER_CI_SYSTEM}"
echo "  IMAGE_OS_SUFFIX=${IMAGE_OS_SUFFIX}"

pull_arg=()
if [[ "${DOCKER_BUILD_PULL:-}" == "1" ]]; then
  pull_arg=(--pull)
fi

docker build \
  "${pull_arg[@]}" \
  --build-arg "BASE_IMAGE=${DOCKER_CI_SYSTEM}" \
  -f "${ROOT_DIR}/${DOCKERFILE_RELEASE}" \
  -t "${RELEASE_IMAGE_TAG}" \
  "${ROOT_DIR}"
