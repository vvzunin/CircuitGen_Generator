#!/usr/bin/env bash
set -euo pipefail

# Map a short Docker Hub image reference (e.g. ubuntu:24.04) to Harbor proxy cache.
# If DOCKER_HUB_PROXY_PROJECT or REGISTRY_URL is not set, returns input as-is.
#
# Example:
#   REGISTRY_URL=vvzunin.me:5201 DOCKER_HUB_PROXY_PROJECT=proxy_cache_docker_hub \
#     docker-hub-proxy-image.sh ubuntu:24.04
#   -> vvzunin.me:5201/proxy_cache_docker_hub/library/ubuntu:24.04

ref="${1:?image reference required}"

if [[ -z "${DOCKER_HUB_PROXY_PROJECT:-}" || -z "${REGISTRY_URL:-}" ]]; then
  echo "${ref}"
  exit 0
fi

# If ref already looks like a registry/repo path, do not rewrite.
if [[ "${ref}" == *"/"* ]]; then
  echo "${ref}"
  exit 0
fi

name="${ref%%:*}"
tag="${ref#*:}"
if [[ "${tag}" == "${ref}" ]]; then
  tag="latest"
fi

echo "${REGISTRY_URL}/${DOCKER_HUB_PROXY_PROJECT}/library/${name}:${tag}"

