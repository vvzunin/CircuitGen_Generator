#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"
# shellcheck source=../docker/docker-paths.sh
source "${ROOT_DIR}/scripts/docker/docker-paths.sh"

DOCKERFILE_CI_NAME="${DOCKERFILE_CI_NAME:-dockerfile/Dockerfile.ci}"
DOCKER_CI_SYSTEM="${DOCKER_CI_SYSTEM:-ubuntu:24.04}"
DOCKER_CI_TAG="${DOCKER_CI_TAG:-latest}"
REGISTRY_URL="${REGISTRY_URL:-vvzunin.me:5201}"
GROUP_NAME="${GROUP_NAME:-circuitgen}"
REPO_NAME="${REPO_NAME:-generator}"
docker_paths_load_registry
docker_paths_apply_target_os
docker_paths_image_os_suffix
docker_paths_ci_registry_tags

if [[ -n "${CI:-}" ]]; then
  if bash "${ROOT_DIR}/scripts/ci/docker-skip-if-unchanged.sh" ci; then
    exit 0
  fi
fi

echo "Creating docker image with tag ${DOCKER_CI_TAG}"
echo "Image will push to ${DOCKER_CI_IMAGE}"

docker buildx build --pull --rm --provenance=false --no-cache \
  --build-arg "system=${DOCKER_CI_SYSTEM}" \
  -f "${DOCKERFILE_CI_NAME}" \
  -t "${DOCKER_CI_IMAGE}" .
docker image push "${DOCKER_CI_IMAGE}"
