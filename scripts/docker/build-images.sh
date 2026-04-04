#!/usr/bin/env bash
set -euo pipefail

# Local helper for building CI, DEV and RELEASE container images.
# Mirrors CI flow: build CI base image first, then dependent images from it.
#
# Optional:
#   TARGET_OS — slug from scripts/config/supported-os.sh
#   DOCKER_CI_SYSTEM — if TARGET_OS is not set, default from supported-os.sh
#   DOCKER_BUILD_PULL=1 — pass --pull to docker build (re-fetch base image metadata from the registry).
#     Default is off: use local base images so flaky auth.docker.io token requests do not break builds.
# See scripts/docker/docker-paths.sh

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
# shellcheck source=docker-paths.sh
source "${ROOT_DIR}/scripts/docker/docker-paths.sh"

DOCKERFILE_CI_NAME="${DOCKERFILE_CI_NAME:-dockerfile/Dockerfile.ci}"
DOCKERFILE_DEV_NAME="${DOCKERFILE_DEV_NAME:-dockerfile/Dockerfile.dev}"
DOCKERFILE_RELEASE_NAME="${DOCKERFILE_RELEASE_NAME:-dockerfile/Dockerfile.release}"
DOCKERFILE_CI="${DOCKERFILE_CI:-${DOCKERFILE_CI_NAME}}"
DOCKERFILE_DEV="${DOCKERFILE_DEV:-${DOCKERFILE_DEV_NAME}}"
DOCKERFILE_RELEASE="${DOCKERFILE_RELEASE:-${DOCKERFILE_RELEASE_NAME}}"
docker_paths_load_registry
docker_paths_apply_target_os
docker_paths_image_os_suffix
docker_paths_local_ci_dev

export DOCKERFILE_CI DOCKERFILE_DEV DOCKERFILE_RELEASE DOCKER_CI_SYSTEM CI_IMAGE_TAG DEV_IMAGE_TAG RELEASE_IMAGE_TAG DOCKER_URL IMAGE_OS_SUFFIX

echo "[1/3] Building local CI image: ${CI_IMAGE_TAG}"
bash "${ROOT_DIR}/scripts/docker/build-ci-image.sh"

echo "[2/3] Building local DEV image: ${DEV_IMAGE_TAG}"
bash "${ROOT_DIR}/scripts/docker/build-dev-only-image.sh"

echo "[3/3] Building local RELEASE image: ${RELEASE_IMAGE_TAG}"
bash "${ROOT_DIR}/scripts/docker/build-release-only-image.sh"

echo "Done."
echo "Run container example:"
echo "  docker run --rm -it ${DEV_IMAGE_TAG} bash"
