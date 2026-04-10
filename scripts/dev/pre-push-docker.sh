#!/usr/bin/env bash
set -euo pipefail

# Run local pre-push checks inside the local dev Docker image.
# (scripts/dev/pre-push.sh runs format-fix automatically if format-check fails.)
#
# Workspace sync with the host checkout:
#   - bind (default): bind-mount the repo at CONTAINER_WORKDIR so format-fix and
#     build outputs are written straight to the host tree.
#   - copy: set PRE_PUSH_DOCKER_SYNC_MODE=copy when bind mounts do not propagate
#     writes reliably (some Docker Desktop / remote filesystem setups). The repo
#     is copied into the container, pre-push runs, then the tree is copied back.

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd -P)"
REPO_DIR_NAME="$(basename "${ROOT_DIR}")"
CONTAINER_WORKDIR="/circuitgen/${REPO_DIR_NAME}"
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
SYNC_MODE="${PRE_PUSH_DOCKER_SYNC_MODE:-bind}"
HOST_UID="$(id -u)"
HOST_GID="$(id -g)"

echo "==> Running pre-push checks inside Docker image: ${DEV_IMAGE_TAG}"
echo "==> Host workspace: ${ROOT_DIR}"
echo "==> Container workdir: ${CONTAINER_WORKDIR} (sync mode: ${SYNC_MODE})"

run_prepush_bind() {
  docker run --rm -t \
    --user "${HOST_UID}:${HOST_GID}" \
    -e "JOBS=${JOBS}" \
    -v "${ROOT_DIR}:${CONTAINER_WORKDIR}" \
    -w "${CONTAINER_WORKDIR}" \
    "${DEV_IMAGE_TAG}" \
    bash scripts/dev/pre-push.sh
}

run_prepush_copy() {
  local cname="prepush-${REPO_DIR_NAME}-${HOST_UID}-$$"

  cleanup() {
    docker rm -f "${cname}" >/dev/null 2>&1 || true
  }
  trap cleanup EXIT

  docker create --name "${cname}" -t \
    -e "JOBS=${JOBS}" \
    --user "0:0" \
    -w "${CONTAINER_WORKDIR}" \
    "${DEV_IMAGE_TAG}" \
    sleep infinity >/dev/null
  docker start "${cname}" >/dev/null

  echo "==> [copy] Sending workspace to container ${cname} ..."
  docker cp "${ROOT_DIR}/." "${cname}:${CONTAINER_WORKDIR}/"

  echo "==> [copy] Fixing ownership to ${HOST_UID}:${HOST_GID} ..."
  docker exec "${cname}" chown -R "${HOST_UID}:${HOST_GID}" "${CONTAINER_WORKDIR}"

  echo "==> [copy] Running pre-push checks ..."
  docker exec -t --user "${HOST_UID}:${HOST_GID}" -w "${CONTAINER_WORKDIR}" -e "JOBS=${JOBS}" \
    "${cname}" bash scripts/dev/pre-push.sh

  echo "==> [copy] Fixing ownership before copy-back (root-owned artifacts) ..."
  docker exec "${cname}" chown -R "${HOST_UID}:${HOST_GID}" "${CONTAINER_WORKDIR}"

  echo "==> [copy] Copying workspace back to host ..."
  docker cp "${cname}:${CONTAINER_WORKDIR}/." "${ROOT_DIR}/"

  docker rm -f "${cname}" >/dev/null
  trap - EXIT
}

case "${SYNC_MODE}" in
  bind)
    run_prepush_bind
    ;;
  copy)
    run_prepush_copy
    ;;
  *)
    echo "Unsupported PRE_PUSH_DOCKER_SYNC_MODE='${SYNC_MODE}' (expected bind or copy)" >&2
    exit 1
    ;;
esac
