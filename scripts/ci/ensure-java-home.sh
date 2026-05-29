#!/usr/bin/env bash
# Ensure JAVA_HOME points at an installed JDK (Chisel tests invoke java/sbt).
# CI images may ship a stale JAVA_HOME from another distro (see dockerfile/Dockerfile.ci).
#
# Usage: source scripts/ci/ensure-java-home.sh

if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
  echo "ensure-java-home.sh: source this script, do not execute it" >&2
  exit 1
fi

_resolve_java_home() {
  if [[ -f /etc/circuitgen-java-home ]]; then
    tr -d '\n' </etc/circuitgen-java-home
    return 0
  fi
  if ! command -v java >/dev/null 2>&1; then
    return 1
  fi
  local java_bin java_home
  java_bin="$(readlink -f "$(command -v java)")"
  java_home="$(dirname "$(dirname "${java_bin}")")"
  if [[ -x "${java_home}/bin/java" ]]; then
    printf '%s' "${java_home}"
    return 0
  fi
  return 1
}

if [[ -n "${JAVA_HOME:-}" && ! -x "${JAVA_HOME}/bin/java" ]]; then
  unset JAVA_HOME
fi

if [[ -z "${JAVA_HOME:-}" ]]; then
  if _jh="$(_resolve_java_home)"; then
    JAVA_HOME="${_jh}"
  fi
fi

if [[ -n "${JAVA_HOME:-}" && -x "${JAVA_HOME}/bin/java" ]]; then
  export JAVA_HOME
  export PATH="${JAVA_HOME}/bin:${PATH}"
fi
