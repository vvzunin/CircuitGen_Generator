#!/usr/bin/env bash
set -euo pipefail

# Run one CI task either on local system or inside local CI Docker image.
#
# Usage:
#   bash scripts/ci/run-task.sh <task>
#
# Environment:
#   CI_RUNNER=local|docker        (default: local)
#   CI_IMAGE_TAG=<image>          (default: ${DOCKER_URL}/${IMAGE_OS_SUFFIX}/ci:local)
#   TARGET_OS / DOCKER_CI_SYSTEM  (see scripts/docker/docker-paths.sh)

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
REPO_DIR_NAME="$(basename "${ROOT_DIR}")"
CONTAINER_WORKDIR="/circuitgen/${REPO_DIR_NAME}"
cd "${ROOT_DIR}"
# shellcheck source=../docker/docker-paths.sh
source "${ROOT_DIR}/scripts/docker/docker-paths.sh"
if [[ -z "${CI_IMAGE_TAG:-}" ]]; then
  docker_paths_load_registry
  docker_paths_apply_target_os
  docker_paths_image_os_suffix
  docker_paths_local_ci_dev
fi

TASK="${1:-}"
if [[ -z "${TASK}" ]]; then
  echo "Usage: bash scripts/ci/run-task.sh <task>"
  echo "Available tasks: lint sanitize static-analysis coverage tests examples docs"
  exit 1
fi

SCRIPT_PATH="scripts/ci/${TASK}.sh"
if [[ ! -f "${SCRIPT_PATH}" ]]; then
  echo "Unknown task: ${TASK}"
  echo "Available tasks: lint sanitize static-analysis coverage tests examples docs"
  exit 1
fi

CI_RUNNER="${CI_RUNNER:-local}"

if [[ "${CI_RUNNER}" == "local" ]]; then
  bash "${SCRIPT_PATH}"
  exit 0
fi

if [[ "${CI_RUNNER}" == "docker" ]]; then
  docker run --rm -t \
    -u "$(id -u):$(id -g)" \
    -e "CI_DEFAULT_BRANCH=${CI_DEFAULT_BRANCH:-}" \
    -e "JOBS=${JOBS:-$(nproc)}" \
    -v "${ROOT_DIR}:${CONTAINER_WORKDIR}" \
    -w "${CONTAINER_WORKDIR}" \
    "${CI_IMAGE_TAG}" \
    bash "${SCRIPT_PATH}"
  exit 0
fi

echo "Unsupported CI_RUNNER value: ${CI_RUNNER}"
echo "Supported values: local, docker"
exit 1
