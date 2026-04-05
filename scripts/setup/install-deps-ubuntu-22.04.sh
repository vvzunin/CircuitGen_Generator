#!/usr/bin/env bash
set -euo pipefail

# Install project dependencies on Ubuntu 22.04.
# By default installs only missing packages.

if [[ "${EUID}" -ne 0 ]]; then
  echo "Run as root (sudo)."
  exit 1
fi

if [[ ! -f /etc/os-release ]]; then
  echo "/etc/os-release not found."
  exit 1
fi

# shellcheck disable=SC1091
source /etc/os-release
if [[ "${ID:-}" != "ubuntu" || "${VERSION_ID:-}" != "22.04" ]]; then
  echo "This script is for Ubuntu 22.04 only (detected: ${ID:-unknown} ${VERSION_ID:-unknown})."
  exit 1
fi
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Docker/CI: debconf must not prompt (e.g. tzdata "Geographic area:") or the image build hangs.
export DEBIAN_FRONTEND=noninteractive
export TZ="${TZ:-Europe/Moscow}"
debconf-set-selections <<'EOF'
tzdata tzdata/Areas select Europe
tzdata tzdata/Zones/Europe select Moscow
EOF

# Docs: Doxygen + m.css + LaTeX PDF need xelatex + DejaVu (fontspec in docs/doxygen-cyrillic.sty), Ghostscript (libgs),
# and texlive-lang-cyrillic (t2aenc.def) when Doxygen emits Russian LaTeX with [T2A]{fontenc} (also if pdfLaTeX is used).
PACKAGES=(
  bison
  build-essential
  clang
  clang-tidy
  cmake
  codespell
  cppcheck
  curl
  flex
  fonts-dejavu-core
  g++
  gcc
  ghostscript
  libgs9
  git
  graphviz
  lcov
  libcapture-tiny-perl
  libdatetime-perl
  libclang-dev
  llvm-dev
  make
  ninja-build
  openssl
  python3
  python3-dev
  python3-pip
  python3-venv
  texlive-fonts-recommended
  texlive-lang-cyrillic
  texlive-latex-base
  texlive-latex-extra
  texlive-latex-recommended
  texlive-xetex
  wget
)

MISSING=()
for pkg in "${PACKAGES[@]}"; do
  if ! dpkg -s "${pkg}" >/dev/null 2>&1; then
    MISSING+=("${pkg}")
  fi
done

if [[ "${#MISSING[@]}" -eq 0 ]]; then
  echo "All required packages are already installed."
else
  echo "Installing missing packages: ${MISSING[*]}"
  apt-get update
  apt-get install -y "${MISSING[@]}"
fi

if ! command -v codespell >/dev/null 2>&1; then
  echo "codespell command not found after apt install, installing into venv (${CIRCUITGEN_PYTHON_VENV:-/opt/circuitgen-venv})."
  bash "${SCRIPT_DIR}/ci-python-venv.sh" codespell
  ln -sf "${CIRCUITGEN_PYTHON_VENV:-/opt/circuitgen-venv}/bin/codespell" /usr/local/bin/codespell
fi

if ! command -v pdflatex >/dev/null 2>&1; then
  echo "ERROR: pdflatex not found after package install (texlive-* packages)."
  exit 1
fi
if ! command -v gs >/dev/null 2>&1; then
  echo "ERROR: gs (ghostscript) not found after package install."
  exit 1
fi

# Jammy ships CMake 3.22; CMakePresets.json uses format version 6 (needs CMake >= 3.25).
CMAKE_VER_LINE="$(cmake --version 2>/dev/null | head -1 || true)"
CMAKE_VER="$(echo "${CMAKE_VER_LINE}" | sed -nE 's/.* ([0-9]+)\.([0-9]+)\.([0-9]+).*/\1.\2.\3/p')"
if [[ -z "${CMAKE_VER}" ]]; then
  CMAKE_VER="0.0.0"
fi
if dpkg --compare-versions "${CMAKE_VER}" lt 3.26.0; then
  echo "CMake ${CMAKE_VER} < 3.26; installing Kitware CMake (required for CMakePresets.json version 6)."
  apt-get update
  apt-get install -y gnupg wget
  wget -qO- https://apt.kitware.com/keys/kitware-archive-latest.asc | gpg --dearmor -o /usr/share/keyrings/kitware-archive-keyring.gpg
  echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main' >/etc/apt/sources.list.d/kitware-cmake.list
  apt-get update
  apt-get install -y --upgrade cmake cmake-data
fi

bash "${SCRIPT_DIR}/install-clang-format-ci.sh"

bash "${SCRIPT_DIR}/install-lcov-ci.sh"

bash "${SCRIPT_DIR}/install-doxygen-llvm.sh"

echo "Dependency installation finished for Ubuntu 22.04."
