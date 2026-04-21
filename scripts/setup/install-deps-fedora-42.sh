#!/usr/bin/env bash
set -euo pipefail

# Install project dependencies on Fedora Workstation 42.
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
if [[ "${ID:-}" != "fedora" || "${VERSION_ID:-}" != "42" ]]; then
  echo "This script is for Fedora 42 only (detected: ${ID:-unknown} ${VERSION_ID:-unknown})."
  exit 1
fi
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Docs: Doxygen + m.css + LaTeX PDF need xelatex + DejaVu (fontspec in docs/doxygen-cyrillic.sty), Ghostscript (libgs),
# texlive-cyrillic (t2aenc.def) for Russian [T2A]{fontenc} from Doxygen, and texlive-xetex for xelatex.
# texlive-wasysym: wasy7 metrics for \\usepackage{wasysym} in Doxygen refman (avoids mktextfm hang).
# Doxygen 1.13+ latex/header.tex loads unicode-math and etoc ([deeplevels]) under XeTeX/LuaTeX; on Fedora these are
# separate texlive-* RPMs and are not always pulled by texlive-collection-latexextra alone.
PACKAGES=(
  bison
  clang
  clang-devel
  clang-tools-extra
  cmake
  cppcheck
  curl
  dejavu-sans-fonts
  dejavu-sans-mono-fonts
  dejavu-serif-fonts
  flex
  gcc
  gcc-c++
  glibc-devel
  ghostscript
  libgs
  git
  graphviz
  lcov
  libasan
  libstdc++-devel
  libubsan
  llvm-devel
  make
  ninja-build
  openssl-devel
  # venv is in Python's stdlib; Fedora has no separate python3-venv RPM (unlike Debian/Ubuntu).
  python3
  python3-devel
  python3-pip
  texlive-collection-latexextra
  texlive-cyrillic
  texlive-etoc
  texlive-latex
  texlive-scheme-basic
  texlive-unicode-math
  texlive-wasysym
  texlive-xetex
  wget
)

MISSING=()
for pkg in "${PACKAGES[@]}"; do
  if ! rpm -q "${pkg}" >/dev/null 2>&1; then
    MISSING+=("${pkg}")
  fi
done

if [[ "${#MISSING[@]}" -eq 0 ]]; then
  echo "All required packages are already installed."
else
  echo "Installing missing packages: ${MISSING[*]}"
  dnf -y --setopt=fedora-cisco-openh264.enabled=0 install "${MISSING[@]}"
fi

if ! command -v codespell >/dev/null 2>&1; then
  echo "Installing codespell into venv (${CIRCUITGEN_PYTHON_VENV:-/opt/circuitgen-venv})."
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

echo "Dependency installation finished for Fedora 42."
