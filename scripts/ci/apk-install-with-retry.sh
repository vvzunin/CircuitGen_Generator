#!/usr/bin/env sh
set -eu

if [ "$#" -eq 0 ]; then
  echo "Usage: $0 <apk-package> [<apk-package> ...]" >&2
  exit 2
fi

retries="${APK_INSTALL_RETRIES:-4}"
sleep_seconds="${APK_INSTALL_SLEEP_SECONDS:-5}"

if [ -n "${ALPINE_MIRROR:-}" ]; then
  alpine_version="$(cut -d. -f1,2 /etc/alpine-release)"
  mirror="${ALPINE_MIRROR%/}"
  printf '%s\n%s\n' \
    "${mirror}/v${alpine_version}/main" \
    "${mirror}/v${alpine_version}/community" > /etc/apk/repositories
fi

attempt=1
while [ "${attempt}" -le "${retries}" ]; do
  if apk add --no-cache "$@"; then
    exit 0
  fi

  if [ "${attempt}" -eq "${retries}" ]; then
    echo "apk install failed after ${retries} attempts: $*" >&2
    exit 1
  fi

  echo "apk install attempt ${attempt}/${retries} failed, retrying in ${sleep_seconds}s..." >&2
  sleep "${sleep_seconds}"
  attempt=$((attempt + 1))
done
