#!/usr/bin/env bash
set -euo pipefail

# Minimal packages for release build only; called from dockerfile/Dockerfile.release.
# OS list must match scripts/config/supported-os.sh (ID:VERSION).
# clang-tidy / clang-tools-extra: required by FetchContent dependency CircuitGenGraph (CMake FATAL_ERROR if missing).

if [[ ! -f /etc/os-release ]]; then
  echo "Missing /etc/os-release"
  exit 1
fi

# shellcheck disable=SC1091
source /etc/os-release
KEY="${ID}:${VERSION_ID}"

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
# shellcheck source=../config/supported-os.sh
source "${ROOT}/scripts/config/supported-os.sh"

if ! supported_os_id_version_to_slug "${KEY}" >/dev/null; then
  echo "Unsupported BASE_IMAGE for release: ${KEY}"
  echo "Supported: $(supported_os_print_expected_slugs)"
  exit 1
fi

set -eux
case "${KEY}" in
  ubuntu:22.04)
    apt-get update
    apt-get install -y --no-install-recommends \
      ca-certificates gnupg wget
    wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null \
      | gpg --dearmor -o /usr/share/keyrings/kitware-archive-keyring.gpg
    echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main' \
      > /etc/apt/sources.list.d/kitware.list
    apt-get update
    apt-get install -y --no-install-recommends \
      clang-tidy cmake ninja-build git build-essential libssl-dev make
    apt-get clean
    rm -rf /var/lib/apt/lists/*
    ;;
  ubuntu:24.04)
    apt-get update
    apt-get install -y --no-install-recommends \
      ca-certificates clang-tidy git build-essential cmake ninja-build libssl-dev make
    apt-get clean
    rm -rf /var/lib/apt/lists/*
    ;;
  debian:13)
    apt-get update
    apt-get install -y --no-install-recommends \
      ca-certificates clang-tidy git build-essential cmake ninja-build libssl-dev make
    apt-get clean
    rm -rf /var/lib/apt/lists/*
    ;;
  fedora:42|fedora:43)
    dnf -y --setopt=fedora-cisco-openh264.enabled=0 install \
      clang-tools-extra gcc gcc-c++ cmake ninja-build git openssl-devel make
    dnf clean all
    rm -rf /var/cache/dnf/*
    ;;
  *)
    echo "Unsupported BASE_IMAGE for release: ${KEY}"
    exit 1
    ;;
esac
