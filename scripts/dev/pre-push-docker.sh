#!/usr/bin/env bash
set -euo pipefail

# Run local pre-push checks inside the local dev Docker image.
# (scripts/dev/pre-push.sh runs format-fix automatically if format-check fails.)

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"
# shellcheck source=../docker/docker-paths.sh
source "${ROOT_DIR}/scripts/docker/docker-paths.sh"
if [[ -z "${DEV_IMAGE_TAG:-}" ]]; then
  docker_paths_load_registry
  docker_paths_apply_target_os
  docker_paths_image_os_suffix
  docker_paths_local_ci_dev
fi
JOBS="${JOBS:-$(nproc)}"

echo "==> Running pre-push checks inside Docker image: ${DEV_IMAGE_TAG}"
echo "==> Workspace: ${ROOT_DIR}"

docker run --rm -t \
  -u "$(id -u):$(id -g)" \
  -e "JOBS=${JOBS}" \
  -v "${ROOT_DIR}:${ROOT_DIR}" \
  -w "${ROOT_DIR}" \
  "${DEV_IMAGE_TAG}" \
  bash scripts/dev/pre-push.sh
