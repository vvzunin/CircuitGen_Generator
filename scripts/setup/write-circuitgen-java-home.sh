#!/usr/bin/env bash
# Record JAVA_HOME for CI/runtime (paths differ between Ubuntu, Fedora, Debian).
set -euo pipefail

if ! command -v java >/dev/null 2>&1; then
  echo "write-circuitgen-java-home: java not found in PATH" >&2
  exit 1
fi

java_bin="$(readlink -f "$(command -v java)")"
java_home="$(dirname "$(dirname "${java_bin}")")"

if [[ ! -x "${java_home}/bin/java" ]]; then
  echo "write-circuitgen-java-home: invalid JAVA_HOME candidate: ${java_home}" >&2
  exit 1
fi

printf '%s\n' "${java_home}" >/etc/circuitgen-java-home
chmod 644 /etc/circuitgen-java-home

cat >/etc/profile.d/circuitgen-java.sh <<EOF
export JAVA_HOME=${java_home}
export PATH="\${JAVA_HOME}/bin:\${PATH}"
EOF
chmod 644 /etc/profile.d/circuitgen-java.sh

echo "write-circuitgen-java-home: JAVA_HOME=${java_home}"
