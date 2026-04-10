#!/usr/bin/env bash
# shellcheck shell=bash
# Single source of truth for supported OS targets (slug | base image for Docker).
# Used by scripts/docker/docker-paths.sh, CI helpers, Dockerfiles (via helper scripts).
# GitLab matrix: run scripts/ci/generate-gitlab-os-matrix.sh --write after changing entries.
#
# Slug format: ubuntu-22.04, ubuntu-24.04, fedora-43 (matches install-deps-<slug>.sh and IMAGE_OS_SUFFIX).

_SUPPORTED_OS_CONFIG_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"

# Each entry: "<slug>|<ID>:<VERSION>" (ID:VERSION from /etc/os-release)
SUPPORTED_OS_ENTRIES=(
  "ubuntu-22.04|ubuntu:22.04"
  "ubuntu-24.04|ubuntu:24.04"
  "fedora-43|fedora:43"
)

# Default slug for local docs / examples (matches .gitlab-ci default CI image).
# Exported for consumers that source this file (e.g. docker-paths.sh).
export DEFAULT_TARGET_OS_SLUG="ubuntu-24.04"

supported_os_list_slugs() {
  local line
  for line in "${SUPPORTED_OS_ENTRIES[@]}"; do
    echo "${line%%|*}"
  done
}

supported_os_slug_to_id_version() {
  local slug="$1"
  local line
  for line in "${SUPPORTED_OS_ENTRIES[@]}"; do
    if [[ "${line%%|*}" == "${slug}" ]]; then
      echo "${line#*|}"
      return 0
    fi
  done
  return 1
}

supported_os_id_version_to_slug() {
  local idv="$1"
  local line
  for line in "${SUPPORTED_OS_ENTRIES[@]}"; do
    if [[ "${line#*|}" == "${idv}" ]]; then
      echo "${line%%|*}"
      return 0
    fi
  done
  return 1
}

supported_os_is_valid_slug() {
  local slug="$1"
  supported_os_slug_to_id_version "${slug}" >/dev/null 2>&1
}

supported_os_slug_to_setup_script() {
  local slug="$1"
  if ! supported_os_is_valid_slug "${slug}"; then
    return 1
  fi
  echo "${_SUPPORTED_OS_CONFIG_ROOT}/scripts/setup/install-deps-${slug}.sh"
}

supported_os_print_expected_slugs() {
  local out=""
  local line
  for line in "${SUPPORTED_OS_ENTRIES[@]}"; do
    out="${out:+$out, }${line%%|*}"
  done
  echo "${out}"
}
