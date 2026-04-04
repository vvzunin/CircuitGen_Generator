#!/usr/bin/env bash
set -euo pipefail

# Build and install Doxygen with LLVM/libclang support.

if [[ "${EUID}" -ne 0 ]]; then
  echo "Run as root (sudo)."
  exit 1
fi

DOXYGEN_VERSION="${DOXYGEN_VERSION:-1.13.2}"
DOXYGEN_FORCE_REBUILD="${DOXYGEN_FORCE_REBUILD:-0}"

has_libclang_support() {
  if ! command -v doxygen >/dev/null 2>&1; then
    return 1
  fi
  # Doxygen 1.9+ prints "clang support" in `doxygen -V` when built with libclang.
  # Do not use `doxygen -x_noenv` without a config: since 1.13 it prints help instead of defaults.
  if doxygen -V 2>&1 | grep -qiE 'clang support'; then
    return 0
  fi
  # Linux: verify the binary is linked against libclang (covers edge cases / older -V output).
  if [[ "$(uname -s)" == "Linux" ]]; then
    local bin
    bin="$(command -v doxygen)"
    if ldd "${bin}" 2>/dev/null | grep -qE 'libclang(\.so|-[0-9])'; then
      return 0
    fi
  fi
  return 1
}

current_version() {
  if command -v doxygen >/dev/null 2>&1; then
    doxygen --version 2>/dev/null || true
  fi
}

if [[ "${DOXYGEN_FORCE_REBUILD}" != "1" ]]; then
  if has_libclang_support && [[ "$(current_version)" == "${DOXYGEN_VERSION}" ]]; then
    echo "Doxygen ${DOXYGEN_VERSION} with LLVM/libclang support is already installed."
    exit 0
  fi
fi

TMP_DIR="$(mktemp -d)"
cleanup() {
  rm -rf "${TMP_DIR}"
}
trap cleanup EXIT

ARCHIVE_URL="https://www.doxygen.nl/files/doxygen-${DOXYGEN_VERSION}.src.tar.gz"
ARCHIVE_PATH="${TMP_DIR}/doxygen-${DOXYGEN_VERSION}.src.tar.gz"
SRC_DIR="${TMP_DIR}/doxygen-${DOXYGEN_VERSION}"
BUILD_DIR="${SRC_DIR}/build"

echo "Building Doxygen ${DOXYGEN_VERSION} with LLVM/libclang support..."
wget -O "${ARCHIVE_PATH}" "${ARCHIVE_URL}"
tar xf "${ARCHIVE_PATH}" -C "${TMP_DIR}"
mkdir -p "${BUILD_DIR}"

cmake -S "${SRC_DIR}" -B "${BUILD_DIR}" -G Ninja -Duse_libclang=ON
cmake --build "${BUILD_DIR}" -j "$(nproc)"
cmake --install "${BUILD_DIR}"

hash -r
if ! has_libclang_support; then
  echo "Installed doxygen does not expose CLANG_ASSISTED_PARSING."
  exit 1
fi

echo "Doxygen $(current_version) with LLVM/libclang support installed successfully."
