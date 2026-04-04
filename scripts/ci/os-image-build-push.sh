#!/usr/bin/env bash
set -euo pipefail

# Build and push an OS-specific CI image with project dependencies installed.
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

echo "Building OS image: ${OS_IMAGE_TAG}"
docker buildx build --pull --rm --provenance=false --no-cache \
  --build-arg "BASE_IMAGE=${BASE_IMAGE}" \
  --build-arg "SETUP_SCRIPT=${SETUP_SCRIPT}" \
  -t "${OS_IMAGE_TAG}" \
  -f - "${ROOT_DIR}" <<'EOF'
ARG BASE_IMAGE
FROM ${BASE_IMAGE}
WORKDIR /workspace
COPY . /workspace
ARG SETUP_SCRIPT
RUN bash "${SETUP_SCRIPT}"
RUN bash scripts/setup/ci-python-venv.sh jinja2 Pygments synology-drive-api
ENV CIRCUITGEN_PYTHON_VENV=/opt/circuitgen-venv
ENV PATH="/opt/circuitgen-venv/bin:${PATH}"
EOF

echo "Pushing OS image: ${OS_IMAGE_TAG}"
docker image push "${OS_IMAGE_TAG}"
