#!/usr/bin/env bash
set -euo pipefail

# Create a GitLab Release for the current tag via release-cli (see release-from-tag job).
# - Description (Markdown): source archive link + docker pull lines for each supported OS (supported-os.sh).
# - Release assets (HTTPS links): source .tar.gz, optional per-OS links if RELEASE_DOCKER_IMAGE_WEB_URL_TEMPLATE is set.
#
# Optional CI variables:
#   HARBOR_WEB_UI_URL — HTTPS URL of the Harbor web UI (e.g. https://vvzunin.me or project page). If set,
#     added to release description and as a release asset link. Images are pushed to REGISTRY_URL (Harbor) by CI.
#   RELEASE_DOCKER_IMAGE_WEB_URL_TEMPLATE — if set, one extra HTTPS asset link per OS, e.g.
#     https://harbor.example/harbor/circuitgen/projects/1/repositories/generator%2Fubuntu-24.04%2Frelease/artifacts-tab
#     Placeholders: {slug}, {tag}

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
# shellcheck source=../config/supported-os.sh
source "${ROOT}/scripts/config/supported-os.sh"

: "${CI_COMMIT_TAG:?}"
: "${CI_PROJECT_URL:?}"
: "${CI_PROJECT_NAME:?}"

REGISTRY_URL="${REGISTRY_URL:-}"
GROUP_NAME="${GROUP_NAME:-}"
REPO_NAME="${REPO_NAME:-}"
DOCKER_URL="${DOCKER_URL:-}"
if [[ -z "${DOCKER_URL}" && -n "${REGISTRY_URL}" && -n "${GROUP_NAME}" && -n "${REPO_NAME}" ]]; then
  DOCKER_URL="${REGISTRY_URL}/${GROUP_NAME}/${REPO_NAME}"
fi

ARCHIVE_URL="${CI_PROJECT_URL}/-/archive/${CI_COMMIT_TAG}/${CI_PROJECT_NAME}-${CI_COMMIT_TAG}.tar.gz"

cd "${ROOT}"
DESC_NAME="release-notes.md"
rm -f "${DESC_NAME}"

{
  echo "## ${CI_PROJECT_NAME} ${CI_COMMIT_TAG}"
  echo
  echo "### Source code"
  echo
  echo "Archive of this tag (tar.gz):"
  echo
  echo "- [${CI_PROJECT_NAME}-${CI_COMMIT_TAG}.tar.gz](${ARCHIVE_URL})"
  echo
  echo "### Docker release images"
  echo
  echo "Release images use the same tag as this Git release. Pull example:"
  echo
  echo "| OS | Image |"
  echo "|----|-------|"
  for line in "${SUPPORTED_OS_ENTRIES[@]}"; do
    slug="${line%%|*}"
    img="${DOCKER_URL}/${slug}/release:${CI_COMMIT_TAG}"
    echo "| ${slug} | \`${img}\` |"
  done
  echo
  echo "\`\`\`bash"
  for line in "${SUPPORTED_OS_ENTRIES[@]}"; do
    slug="${line%%|*}"
    echo "docker pull ${DOCKER_URL}/${slug}/release:${CI_COMMIT_TAG}"
  done
  echo "\`\`\`"
  echo
  echo "### Registry (Harbor)"
  echo
  echo "CI pushes release images to **Harbor** at \`${REGISTRY_URL:-$DOCKER_URL}\` (Docker registry endpoint)."
  echo
  echo "- Image path: \`${DOCKER_URL}/<os-slug>/release:<tag>\`"
  if [[ -n "${HARBOR_WEB_UI_URL:-}" ]]; then
    echo "- [Harbor (web UI)](${HARBOR_WEB_UI_URL})"
  fi
} >"${DESC_NAME}"

json_link() {
  # Args: name url  (no double quotes in name)
  local n="$1"
  local u="$2"
  printf '{"name":"%s","url":"%s"}' "${n//\"/\\\"}" "${u//\"/\\\"}"
}

run_release_cli() {
  release-cli create \
    --tag-name "${CI_COMMIT_TAG}" \
    --name "Release ${CI_COMMIT_TAG}" \
    --description "${DESC_NAME}" \
    "$@"
}

ASSET_ARGS=()
ASSET_ARGS+=(--assets-link "$(json_link "${CI_PROJECT_NAME}-${CI_COMMIT_TAG}.tar.gz (source code)" "${ARCHIVE_URL}")")

if [[ -n "${HARBOR_WEB_UI_URL:-}" ]]; then
  ASSET_ARGS+=(--assets-link "$(json_link "Harbor (web UI)" "${HARBOR_WEB_UI_URL}")")
fi

if [[ -n "${RELEASE_DOCKER_IMAGE_WEB_URL_TEMPLATE:-}" ]]; then
  for line in "${SUPPORTED_OS_ENTRIES[@]}"; do
    slug="${line%%|*}"
    url="${RELEASE_DOCKER_IMAGE_WEB_URL_TEMPLATE//\{slug\}/${slug}}"
    url="${url//\{tag\}/${CI_COMMIT_TAG}}"
    ASSET_ARGS+=(--assets-link "$(json_link "Docker release image — ${slug}" "${url}")")
  done
fi

run_release_cli "${ASSET_ARGS[@]}"

rm -f "${DESC_NAME}"
