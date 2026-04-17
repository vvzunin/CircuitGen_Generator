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

# Prefer Harbor proxy cache for Docker Hub base images in CI.
DOCKER_CI_SYSTEM="$(REGISTRY_URL="${REGISTRY_URL}" DOCKER_HUB_PROXY_PROJECT="${DOCKER_HUB_PROXY_PROJECT:-}" \
  bash "${ROOT_DIR}/scripts/ci/docker-hub-proxy-image.sh" "${DOCKER_CI_SYSTEM}")"

nexus_url="${NAS_NEXUS_URL:-${NAS_Nexus_URL:-}}"
nexus_user="${NAS_NEXUS_USER:-${NAS_Nexus_USER:-}}"
nexus_pass="${NAS_NEXUS_PASS:-${NAS_Nexus_PASS:-}}"
nexus_repo="${NAS_NEXUS_PYPI_REPO:-${NAS_Nexus_PYPI_REPO:-pypi-proxy}}"
pip_index_url=""
pip_trusted_host=""
pip_conf_file="$(mktemp)"
build_secrets_args=(--secret "id=pip_conf,src=${pip_conf_file}")
if [[ -n "${nexus_url}" ]]; then
  [[ "${nexus_url}" =~ ^https?:// ]] || nexus_url="http://${nexus_url}"
  nexus_url="${nexus_url%/}"
  pip_trusted_host="${nexus_url#http://}"
  pip_trusted_host="${pip_trusted_host#https://}"
  if [[ -n "${nexus_user}" && -n "${nexus_pass}" ]]; then
    if [[ "${nexus_url}" == https://* ]]; then
      pip_index_url="https://${nexus_user}:${nexus_pass}@${pip_trusted_host}/repository/${nexus_repo}/simple"
    else
      pip_index_url="http://${nexus_user}:${nexus_pass}@${pip_trusted_host}/repository/${nexus_repo}/simple"
    fi
  else
    pip_index_url="${nexus_url}/repository/${nexus_repo}/simple"
  fi
fi

{
  echo "[global]"
  if [[ -n "${pip_index_url}" ]]; then
    echo "index-url = ${pip_index_url}"
  fi
  if [[ -n "${pip_trusted_host}" ]]; then
    echo "trusted-host = ${pip_trusted_host}"
  fi
  echo "timeout = 60"
  echo "retries = 5"
} > "${pip_conf_file}"

if [[ -n "${CI:-}" ]]; then
  sha_image=""
  if [[ -n "${CI_COMMIT_SHORT_SHA:-}" ]]; then
    sha_image="${DOCKER_CI_IMAGE%:*}:${CI_COMMIT_SHORT_SHA}"
  fi
  if bash "${ROOT_DIR}/scripts/ci/docker-skip-if-unchanged.sh" ci; then
    if [[ -n "${sha_image}" && "${sha_image}" != "${DOCKER_CI_IMAGE}" ]]; then
      main_exists=0
      sha_exists=0
      if docker manifest inspect "${DOCKER_CI_IMAGE}" >/dev/null 2>&1; then
        main_exists=1
      fi
      if docker manifest inspect "${sha_image}" >/dev/null 2>&1; then
        sha_exists=1
      fi

      if [[ "${main_exists}" -eq 1 && "${sha_exists}" -eq 0 ]]; then
        echo "Publishing immutable CI image tag from existing image: ${sha_image}"
        docker pull "${DOCKER_CI_IMAGE}"
        docker image tag "${DOCKER_CI_IMAGE}" "${sha_image}"
        docker image push "${sha_image}"
      elif [[ "${main_exists}" -eq 0 && "${sha_exists}" -eq 1 ]]; then
        echo "Promoting immutable SHA image to branch tag: ${DOCKER_CI_IMAGE}"
        docker pull "${sha_image}"
        docker image tag "${sha_image}" "${DOCKER_CI_IMAGE}"
        docker image push "${DOCKER_CI_IMAGE}"
      fi
    fi
    exit 0
  fi
fi

echo "Creating docker image with tag ${DOCKER_CI_TAG}"
echo "Image will push to ${DOCKER_CI_IMAGE}"

sha_image=""
if [[ -n "${CI_COMMIT_SHORT_SHA:-}" ]]; then
  sha_image="${DOCKER_CI_IMAGE%:*}:${CI_COMMIT_SHORT_SHA}"
fi

docker buildx build --pull --rm --provenance=false --no-cache \
  --build-arg "system=${DOCKER_CI_SYSTEM}" \
  "${build_secrets_args[@]}" \
  -f "${DOCKERFILE_CI_NAME}" \
  -t "${DOCKER_CI_IMAGE}" .
docker image push "${DOCKER_CI_IMAGE}"
if [[ -n "${sha_image}" && "${sha_image}" != "${DOCKER_CI_IMAGE}" ]]; then
  echo "Publishing immutable CI image tag: ${sha_image}"
  docker image tag "${DOCKER_CI_IMAGE}" "${sha_image}"
  docker image push "${sha_image}"
fi

rm -f "${pip_conf_file}"
