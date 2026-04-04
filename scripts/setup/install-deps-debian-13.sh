#!/usr/bin/env bash
set -euo pipefail

# Install project dependencies on Debian 13 (trixie).
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
if [[ "${ID:-}" != "debian" || "${VERSION_ID:-}" != "13" ]]; then
  echo "This script is for Debian 13 only (detected: ${ID:-unknown} ${VERSION_ID:-unknown})."
  exit 1
fi
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

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
  libgs10
  git
  graphviz
  lcov
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

bash "${SCRIPT_DIR}/install-clang-format-ci.sh"

bash "${SCRIPT_DIR}/install-doxygen-llvm.sh"

echo "Dependency installation finished for Debian 13."
