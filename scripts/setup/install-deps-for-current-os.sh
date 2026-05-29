#!/usr/bin/env bash
set -euo pipefail

# Run the correct install-deps-<slug>.sh for the current OS (/etc/os-release).
# Used by dockerfile/Dockerfile.ci.

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
# shellcheck source=../config/supported-os.sh
source "${ROOT}/scripts/config/supported-os.sh"

if [[ ! -f /etc/os-release ]]; then
  echo "/etc/os-release not found."
  exit 1
fi

# shellcheck disable=SC1091
source /etc/os-release
KEY="${ID}:${VERSION_ID}"

if ! SLUG="$(supported_os_id_version_to_slug "${KEY}")"; then
  echo "Unsupported OS for CI image: ${KEY}"
  echo "Supported: $(supported_os_print_expected_slugs)"
  exit 1
fi

SETUP_SCRIPT="${ROOT}/scripts/setup/install-deps-${SLUG}.sh"
if [[ ! -f "${SETUP_SCRIPT}" ]]; then
  echo "Missing installer: ${SETUP_SCRIPT}"
  exit 1
fi

exec bash "${SETUP_SCRIPT}"
