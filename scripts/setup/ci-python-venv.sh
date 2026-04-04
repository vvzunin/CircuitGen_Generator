#!/usr/bin/env bash
# Create a shared venv at CIRCUITGEN_PYTHON_VENV (default /opt/circuitgen-venv) and pip install packages.
# Use this instead of pip install into the system interpreter (CI images, install-deps fallbacks).
set -euo pipefail

VENV="${CIRCUITGEN_PYTHON_VENV:-/opt/circuitgen-venv}"

if [[ ! -x "${VENV}/bin/python" ]]; then
  python3 -m venv "${VENV}"
fi
"${VENV}/bin/python" -m pip install --upgrade pip
if [[ "$#" -gt 0 ]]; then
  "${VENV}/bin/pip" install "$@"
fi
