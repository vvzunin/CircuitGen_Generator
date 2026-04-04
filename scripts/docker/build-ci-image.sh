#!/usr/bin/env bash
set -euo pipefail

# Build only local CI Docker image.
# Optional: TARGET_OS=ubuntu-24.04 (see scripts/docker/docker-paths.sh)

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
# shellcheck source=docker-paths.sh
source "${ROOT_DIR}/scripts/docker/docker-paths.sh"

DOCKERFILE_CI_NAME="${DOCKERFILE_CI_NAME:-dockerfile/Dockerfile.ci}"
DOCKERFILE_CI="${DOCKERFILE_CI:-${DOCKERFILE_CI_NAME}}"
docker_paths_load_registry
docker_paths_apply_target_os
docker_paths_image_os_suffix
docker_paths_local_ci_dev

echo "Building local CI image: ${CI_IMAGE_TAG}"
echo "  DOCKER_CI_SYSTEM=${DOCKER_CI_SYSTEM}  IMAGE_OS_SUFFIX=${IMAGE_OS_SUFFIX}"

pull_arg=()
if [[ "${DOCKER_BUILD_PULL:-}" == "1" ]]; then
  pull_arg=(--pull)
fi

docker build \
  "${pull_arg[@]}" \
  --build-arg "system=${DOCKER_CI_SYSTEM}" \
  -f "${ROOT_DIR}/${DOCKERFILE_CI}" \
  -t "${CI_IMAGE_TAG}" \
  "${ROOT_DIR}"
