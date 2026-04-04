#!/usr/bin/env bash
set -euo pipefail

# Build only local DEV Docker image (expects CI image to exist).
# Optional: TARGET_OS=ubuntu-24.04 (see scripts/docker/docker-paths.sh)

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
# shellcheck source=docker-paths.sh
source "${ROOT_DIR}/scripts/docker/docker-paths.sh"

DOCKERFILE_DEV_NAME="${DOCKERFILE_DEV_NAME:-dockerfile/Dockerfile.dev}"
DOCKERFILE_DEV="${DOCKERFILE_DEV:-${DOCKERFILE_DEV_NAME}}"
docker_paths_load_registry
docker_paths_apply_target_os
docker_paths_image_os_suffix
docker_paths_local_ci_dev

echo "Building local DEV image: ${DEV_IMAGE_TAG}"
echo "Using base CI image: ${CI_IMAGE_TAG}"
echo "  DOCKER_CI_SYSTEM=${DOCKER_CI_SYSTEM}  IMAGE_OS_SUFFIX=${IMAGE_OS_SUFFIX}"

pull_arg=()
if [[ "${DOCKER_BUILD_PULL:-}" == "1" ]]; then
  pull_arg=(--pull)
fi

docker build \
  "${pull_arg[@]}" \
  --build-arg "system=${CI_IMAGE_TAG}" \
  -f "${ROOT_DIR}/${DOCKERFILE_DEV}" \
  -t "${DEV_IMAGE_TAG}" \
  "${ROOT_DIR}"
