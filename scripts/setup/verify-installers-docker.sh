#!/usr/bin/env bash
set -euo pipefail

# Verify dependency installers inside Docker images.

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
# shellcheck source=../config/supported-os.sh
source "${ROOT_DIR}/scripts/config/supported-os.sh"

TARGET_OS="${1:-${TARGET_OS:-all}}"

run_check() {
  local target="$1"
  local image="$2"
  local script_path="$3"

  if [[ "${TARGET_OS}" != "all" && "${TARGET_OS}" != "${target}" ]]; then
    return 0
  fi

  echo "==> Verifying ${script_path} in ${image}"
  docker run --rm \
    -v "${ROOT_DIR}:${ROOT_DIR}" \
    -w "${ROOT_DIR}" \
    "${image}" \
    bash "${script_path}"
}

for slug in $(supported_os_list_slugs); do
  idv="$(supported_os_slug_to_id_version "${slug}")"
  run_check "${slug}" "${idv}" "scripts/setup/install-deps-${slug}.sh"
done

if [[ "${TARGET_OS}" == "all" ]]; then
  echo "All installer checks completed successfully."
else
  echo "Installer check completed successfully for ${TARGET_OS}."
fi
