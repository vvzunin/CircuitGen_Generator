#!/usr/bin/env bash
set -euo pipefail

# Run full CI checks inside an OS-specific CI image.

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
REPO_DIR_NAME="$(basename "${ROOT_DIR}")"
CONTAINER_WORKDIR="/circuitgen/${REPO_DIR_NAME}"
cd "${ROOT_DIR}"

TARGET_OS="${TARGET_OS:-}"
DOCKER_URL="${DOCKER_URL:-}"
DOCKER_CI_TAG="${DOCKER_CI_TAG:-latest}"

if [[ -z "${TARGET_OS}" || -z "${DOCKER_URL}" ]]; then
  echo "TARGET_OS and DOCKER_URL must be set."
  exit 1
fi

OS_IMAGE_TAG="${DOCKER_URL}/os-${TARGET_OS}:${DOCKER_CI_TAG}"

echo "Running full checks in image: ${OS_IMAGE_TAG}"
docker run --rm -t \
  -e "DOCS_RUNNER=local" \
  -e "DOXYGEN_CLANG_ASSISTED_PARSING=YES" \
  -v "${ROOT_DIR}:${CONTAINER_WORKDIR}" \
  -w "${CONTAINER_WORKDIR}" \
  "${OS_IMAGE_TAG}" \
  bash scripts/ci/run-all.sh
