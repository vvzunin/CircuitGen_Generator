#!/usr/bin/env bash
# Exit 0 if docker build for this layer can be skipped (registry has image and context unchanged).
# Exit 1 if a build is required.
# Caller must set DOCKER_CI_IMAGE / DOCKER_DEV_IMAGE / DOCKER_RELEASE_IMAGE (for role).
# Usage: docker-skip-if-unchanged.sh ci|dev|release
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
role="${1:?role required}"

case "${role}" in
  ci) img="${DOCKER_CI_IMAGE:?}" ;;
  dev) img="${DOCKER_DEV_IMAGE:?}" ;;
  release) img="${DOCKER_RELEASE_IMAGE:?}" ;;
  *)
    echo "Unknown role: ${role}" >&2
    exit 2
    ;;
esac

# In MR pipelines, prefer immutable SHA tag if it already exists:
# commit pipeline may have built and pushed it just before MR pipeline started.
sha_img=""
if [[ "${role}" == "ci" && -n "${CI_COMMIT_SHORT_SHA:-}" ]]; then
  sha_img="${img%:*}:${CI_COMMIT_SHORT_SHA}"
fi
if [[ -n "${sha_img}" && docker manifest inspect "${sha_img}" >/dev/null 2>&1 ]]; then
  echo "Skipping ${role} build: immutable SHA image exists (${sha_img})."
  exit 0
fi

if docker manifest inspect "${img}" >/dev/null 2>&1; then
  echo "Skipping ${role} build: ${img} exists and relevant paths unchanged."
  exit 0
fi

# Build is required when relevant context files changed.
if bash "${ROOT_DIR}/scripts/ci/docker-context-changed.sh" "${role}"; then
  exit 1
fi

# In MR pipelines, branch and MR jobs can race on the same image tag.
# Give the branch pipeline a small window to finish push before rebuilding.
if [[ "${CI_PIPELINE_SOURCE:-}" == "merge_request_event" ]]; then
  wait_seconds="${DOCKER_SKIP_WAIT_SECONDS:-60}"
  interval_seconds="${DOCKER_SKIP_WAIT_INTERVAL_SECONDS:-10}"
  elapsed=0
  while [[ "${elapsed}" -lt "${wait_seconds}" ]]; do
    echo "Image ${img} not found yet; waiting ${interval_seconds}s (${elapsed}/${wait_seconds})..."
    sleep "${interval_seconds}"
    elapsed=$((elapsed + interval_seconds))
    if [[ -n "${sha_img}" && docker manifest inspect "${sha_img}" >/dev/null 2>&1 ]]; then
      echo "Skipping ${role} build: immutable SHA image appeared (${sha_img})."
      exit 0
    fi
    if docker manifest inspect "${img}" >/dev/null 2>&1; then
      echo "Skipping ${role} build: ${img} appeared in registry and context is unchanged."
      exit 0
    fi
  done
fi

exit 1
