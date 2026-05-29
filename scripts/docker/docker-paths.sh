#!/usr/bin/env bash
# shellcheck shell=bash
# Shared Docker image naming (matches .gitlab-ci.yml):
#   ${DOCKER_URL}/${IMAGE_OS_SUFFIX}/ci:<tag>
#   ${DOCKER_URL}/${IMAGE_OS_SUFFIX}/dev:<tag>
#   ${DOCKER_URL}/${IMAGE_OS_SUFFIX}/release:<tag>
#
# Source this file from scripts/docker/*.sh after ROOT_DIR is set.
# Optional: TARGET_OS — see scripts/config/supported-os.sh
# Optional: DOCKER_CI_SYSTEM=ubuntu:22.04 (overridden by TARGET_OS if set)

_DPS_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
# shellcheck source=../config/supported-os.sh
source "${_DPS_ROOT}/scripts/config/supported-os.sh"

docker_paths_load_registry() {
  if [[ -n "${DOCKER_URL:-}" ]]; then
    return 0
  fi
  if [[ -n "${REGISTRY_URL:-}" && -n "${GROUP_NAME:-}" && -n "${REPO_NAME:-}" ]]; then
    DOCKER_URL="${REGISTRY_URL}/${GROUP_NAME}/${REPO_NAME}"
  else
    DOCKER_URL="circuitgen/generator"
  fi
}

docker_paths_apply_target_os() {
  local slug="${TARGET_OS:-}"
  if [[ -z "${slug}" ]]; then
    return 0
  fi
  if ! supported_os_is_valid_slug "${slug}"; then
    echo "Unsupported TARGET_OS: ${TARGET_OS}" >&2
    echo "Expected: $(supported_os_print_expected_slugs)" >&2
    exit 1
  fi
  DOCKER_CI_SYSTEM="$(supported_os_slug_to_id_version "${slug}")"
}

docker_paths_image_os_suffix() {
  local default_idv
  default_idv="$(supported_os_slug_to_id_version "${DEFAULT_TARGET_OS_SLUG}")"
  DOCKER_CI_SYSTEM="${DOCKER_CI_SYSTEM:-${default_idv}}"
  IMAGE_OS_SUFFIX="${IMAGE_OS_SUFFIX:-$(echo "${DOCKER_CI_SYSTEM}" | tr ':' '-')}"
}

docker_paths_local_ci_dev() {
  local tag="${LOCAL_IMAGE_TAG:-local}"
  CI_IMAGE_TAG="${CI_IMAGE_TAG:-${DOCKER_URL}/${IMAGE_OS_SUFFIX}/ci:${tag}}"
  DEV_IMAGE_TAG="${DEV_IMAGE_TAG:-${DOCKER_URL}/${IMAGE_OS_SUFFIX}/dev:${tag}}"
  RELEASE_IMAGE_TAG="${RELEASE_IMAGE_TAG:-${DOCKER_URL}/${IMAGE_OS_SUFFIX}/release:${tag}}"
}

docker_paths_ci_registry_tags() {
  DOCKER_CI_TAG="${DOCKER_CI_TAG:-latest}"
  if [[ -z "${DOCKER_CI_IMAGE:-}" || "${DOCKER_CI_IMAGE}" == *: ]]; then
    DOCKER_CI_IMAGE="${DOCKER_URL}/${IMAGE_OS_SUFFIX}/ci:${DOCKER_CI_TAG}"
  fi
  if [[ -z "${DOCKER_DEV_IMAGE:-}" || "${DOCKER_DEV_IMAGE}" == *: ]]; then
    DOCKER_DEV_IMAGE="${DOCKER_URL}/${IMAGE_OS_SUFFIX}/dev:${DOCKER_CI_TAG}"
  fi
  if [[ -z "${DOCKER_RELEASE_IMAGE:-}" || "${DOCKER_RELEASE_IMAGE}" == *: ]]; then
    DOCKER_RELEASE_IMAGE="${DOCKER_URL}/${IMAGE_OS_SUFFIX}/release:${DOCKER_CI_TAG}"
  fi
}
