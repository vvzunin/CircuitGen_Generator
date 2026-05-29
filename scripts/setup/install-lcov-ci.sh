#!/usr/bin/env bash
set -euo pipefail

# Install LTP lcov 2.x to PREFIX (default /usr/local). cmake/coverage-report.cmake requires lcov >= 2.
# Ubuntu 22.04 apt ships lcov 1.x; keep the apt lcov for base Perl stack, and install libcapture-tiny-perl
# + libdatetime-perl (lcov 2.x requires Capture::Tiny and DateTime; Jammy's lcov package does not pull them).
# This script installs a newer lcov ahead on PATH (/usr/local/bin before /usr/bin).
# Override: LCOV_CI_VERSION=2.0.2 LCOV_CI_PREFIX=/usr/local

VERSION="${LCOV_CI_VERSION:-2.3.2}"
PREFIX="${LCOV_CI_PREFIX:-/usr/local}"
TARBALL="lcov-${VERSION}.tar.gz"
SRCDIR="lcov-${VERSION}"

lcov_major() {
  lcov --version 2>&1 | sed -nE 's/.*[Vv]ersion[[:space:]]+([0-9]+).*/\1/p' | head -1
}

if command -v lcov >/dev/null 2>&1; then
  maj="$(lcov_major || true)"
  if [[ -n "${maj}" && "${maj}" -ge 2 ]]; then
    echo "lcov ${maj}.x already on PATH ($(lcov --version 2>&1 | head -1))"
    exit 0
  fi
fi

cd /tmp 2>/dev/null || cd /
rm -rf "${SRCDIR}" "${TARBALL}"
echo "Installing lcov ${VERSION} -> ${PREFIX} (required for coverage; Jammy apt is 1.x)"
wget -q "https://github.com/linux-test-project/lcov/releases/download/v${VERSION}/${TARBALL}"
tar xzf "${TARBALL}"
cd "${SRCDIR}"
make install PREFIX="${PREFIX}"
cd /
rm -rf "${SRCDIR}" "${TARBALL}"

if ! [[ -x "${PREFIX}/bin/lcov" ]]; then
  echo "ERROR: ${PREFIX}/bin/lcov missing after install."
  exit 1
fi
maj="$("${PREFIX}/bin/lcov" --version 2>&1 | sed -nE 's/.*[Vv]ersion[[:space:]]+([0-9]+).*/\1/p' | head -1)"
if [[ -z "${maj}" || "${maj}" -lt 2 ]]; then
  echo "ERROR: expected lcov major >= 2 after install, got '${maj}' from $("${PREFIX}/bin/lcov" --version 2>&1 | head -1)"
  exit 1
fi
"${PREFIX}/bin/lcov" --version
