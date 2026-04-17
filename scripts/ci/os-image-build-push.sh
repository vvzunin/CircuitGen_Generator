#!/usr/bin/env bash
set -euo pipefail

# Build an OS-specific CI image with project dependencies installed.
# Mirrors dockerfile/Dockerfile.ci after install-deps: shared venv with packages needed for docs (jinja2, …).

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

# shellcheck source=../config/supported-os.sh
source "${ROOT_DIR}/scripts/config/supported-os.sh"

TARGET_OS="${TARGET_OS:-}"
DOCKER_URL="${DOCKER_URL:-}"
DOCKER_CI_TAG="${DOCKER_CI_TAG:-latest}"

if [[ -z "${TARGET_OS}" || -z "${DOCKER_URL}" ]]; then
  echo "TARGET_OS and DOCKER_URL must be set."
  exit 1
fi

if ! supported_os_is_valid_slug "${TARGET_OS}"; then
  echo "Unsupported TARGET_OS: ${TARGET_OS}"
  echo "Supported: $(supported_os_print_expected_slugs)"
  exit 1
fi

BASE_IMAGE="$(supported_os_slug_to_id_version "${TARGET_OS}")"
SETUP_SCRIPT="scripts/setup/install-deps-${TARGET_OS}.sh"

OS_IMAGE_TAG="${DOCKER_URL}/os-${TARGET_OS}:${DOCKER_CI_TAG}"

REGISTRY_URL="${REGISTRY_URL:-vvzunin.me:5201}"
# Prefer Harbor proxy cache for Docker Hub base images in CI.
BASE_IMAGE="$(REGISTRY_URL="${REGISTRY_URL}" DOCKER_HUB_PROXY_PROJECT="${DOCKER_HUB_PROXY_PROJECT:-}" \
  bash "${ROOT_DIR}/scripts/ci/docker-hub-proxy-image.sh" "${BASE_IMAGE}")"

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

echo "Building OS image: ${OS_IMAGE_TAG}"
docker buildx build --pull --rm --provenance=false --no-cache \
  --build-arg "BASE_IMAGE=${BASE_IMAGE}" \
  --build-arg "SETUP_SCRIPT=${SETUP_SCRIPT}" \
  "${build_secrets_args[@]}" \
  -t "${OS_IMAGE_TAG}" \
  -f - "${ROOT_DIR}" <<'EOF'
# syntax=docker/dockerfile:1.6
ARG BASE_IMAGE
FROM ${BASE_IMAGE}
WORKDIR /workspace
COPY . /workspace
ARG SETUP_SCRIPT
RUN --mount=type=secret,id=pip_conf,target=/tmp/pip.conf,required=false \
    PIP_CONFIG_FILE=/tmp/pip.conf \
    bash "${SETUP_SCRIPT}"
RUN --mount=type=secret,id=pip_conf,target=/tmp/pip.conf,required=false \
    PIP_CONFIG_FILE=/tmp/pip.conf \
    bash scripts/setup/ci-python-venv.sh jinja2 Pygments synology-drive-api
ENV CIRCUITGEN_PYTHON_VENV=/opt/circuitgen-venv
ENV PATH="/opt/circuitgen-venv/bin:${PATH}"
EOF

echo "OS image built locally (no registry push): ${OS_IMAGE_TAG}"

rm -f "${pip_conf_file}"
