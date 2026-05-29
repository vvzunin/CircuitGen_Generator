#!/usr/bin/env bash
set -euo pipefail

# Pin clang-format via PyPI (manylinux wheel) so Ubuntu, Debian, and Fedora CI use the same binary.
# Uses a dedicated venv (PEP 668 blocks system pip on Debian/Ubuntu 24.04+ without --break-system-packages).
# Override: CLANG_FORMAT_PINNED_VERSION=19.1.7 (must match docs and lint.sh expectations).

VERSION="${CLANG_FORMAT_PINNED_VERSION:-18.1.8}"
MAJOR="${VERSION%%.*}"
VENV="${CIRCUITGEN_CLANG_FORMAT_VENV:-/opt/circuitgen-clang-format-venv}"

if ! command -v python3 >/dev/null 2>&1; then
  echo "ERROR: python3 required to install pinned clang-format."
  exit 1
fi

# pip probes os.getcwd() at startup; CWD may be missing (deleted tree, WSL /mnt/c edge cases) -> FileNotFoundError.
cd /tmp 2>/dev/null || cd /

echo "Installing clang-format ${VERSION} into ${VENV} (PyPI wheel), symlinks -> /usr/local/bin/clang-format"
if [[ ! -x "${VENV}/bin/pip" ]]; then
  python3 -m venv "${VENV}"
fi

"${VENV}/bin/pip" install --no-cache-dir --upgrade "clang-format==${VERSION}"

BIN="${VENV}/bin/clang-format"
if [[ ! -x "${BIN}" ]]; then
  echo "ERROR: ${BIN} missing after pip install."
  exit 1
fi
if ! "${BIN}" --version | grep -qE "version ${MAJOR}\\."; then
  echo "ERROR: ${BIN} is not ${MAJOR}.x after pip install."
  exit 1
fi

ln -sf "${BIN}" /usr/local/bin/clang-format
ln -sf "${BIN}" "/usr/local/bin/clang-format-${MAJOR}"
"${BIN}" --version
