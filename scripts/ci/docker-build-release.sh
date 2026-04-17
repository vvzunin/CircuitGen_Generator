#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"
# shellcheck source=../docker/docker-paths.sh
source "${ROOT_DIR}/scripts/docker/docker-paths.sh"

DOCKERFILE_RELEASE_NAME="${DOCKERFILE_RELEASE_NAME:-dockerfile/Dockerfile.release}"
DOCKER_CI_SYSTEM="${DOCKER_CI_SYSTEM:-ubuntu:24.04}"
DOCKER_CI_TAG="${DOCKER_CI_TAG:-latest}"
REGISTRY_URL="${REGISTRY_URL:-vvzunin.me:5201}"
GROUP_NAME="${GROUP_NAME:-circuitgen}"
REPO_NAME="${REPO_NAME:-generator}"
docker_paths_load_registry
docker_paths_apply_target_os
docker_paths_image_os_suffix
docker_paths_ci_registry_tags

# Prefer Harbor proxy cache for Docker Hub base images in CI.
DOCKER_CI_SYSTEM="$(REGISTRY_URL="${REGISTRY_URL}" DOCKER_HUB_PROXY_PROJECT="${DOCKER_HUB_PROXY_PROJECT:-}" \
  bash "${ROOT_DIR}/scripts/ci/docker-hub-proxy-image.sh" "${DOCKER_CI_SYSTEM}")"

if [[ -n "${CI:-}" ]]; then
  if bash "${ROOT_DIR}/scripts/ci/docker-skip-if-unchanged.sh" release; then
    exit 0
  fi
fi

echo "Creating docker image with tag release_${DOCKER_CI_TAG}"
echo "Image will push to ${DOCKER_RELEASE_IMAGE}"

docker buildx build --pull --rm --provenance=false --no-cache \
  --build-arg "BASE_IMAGE=${DOCKER_CI_SYSTEM}" \
  -f "${DOCKERFILE_RELEASE_NAME}" \
  -t "${DOCKER_RELEASE_IMAGE}" .
docker image push "${DOCKER_RELEASE_IMAGE}"
