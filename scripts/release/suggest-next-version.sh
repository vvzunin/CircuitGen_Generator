#!/usr/bin/env bash
# Suggest the next SemVer release tag from git history using Conventional Commits.
# Requires commit subjects in the form: type(scope)!: summary  (see docs/*/CONTRIBUTING.md).
# Usage (from repo root): bash scripts/release/suggest-next-version.sh [options]
# Options:
#   --prefix v       Prefix for printed tag (default: v)
#   --any-patch      If no feat/fix/breaking is found but there are commits, bump PATCH anyway
#   --verbose        Show classification per commit
#   -h, --help       This help

set -euo pipefail

usage() {
  sed -n '1,20p' "$0" | tail -n +2
  exit "${1:-0}"
}

PREFIX="v"
ANY_PATCH=0
VERBOSE=0

while [[ $# -gt 0 ]]; do
  case "$1" in
    --prefix)
      PREFIX="${2:?}"
      shift 2
      ;;
    --any-patch)
      ANY_PATCH=1
      shift
      ;;
    --verbose|-v)
      VERBOSE=1
      shift
      ;;
    -h|--help)
      usage 0
      ;;
    *)
      echo "Unknown option: $1" >&2
      usage 1
      ;;
  esac
done

ROOT_DIR="$(git rev-parse --show-toplevel 2>/dev/null)" || {
  echo "error: not a git repository" >&2
  exit 1
}
cd "$ROOT_DIR"

# Latest annotated/lightweight tag that looks like SemVer (optional leading v).
find_latest_semver_tag() {
  git tag -l 2>/dev/null | grep -E '^v?[0-9]+\.[0-9]+\.[0-9]+$' | sort -V | tail -n1
}

latest_tag="$(find_latest_semver_tag || true)"
base_version="0.0.0"

if [[ -n "$latest_tag" ]]; then
  base_version="${latest_tag#v}"
fi

IFS=. read -r major minor patch <<<"${base_version}"
major="${major:-0}"
minor="${minor:-0}"
patch="${patch:-0}"

if [[ -n "$latest_tag" ]]; then
  range="${latest_tag}..HEAD"
else
  range="HEAD"
fi

# Collect commits since last tag (or entire history if no tag).
commits=()
while IFS= read -r sha; do
  [[ -n "$sha" ]] || continue
  commits+=("$sha")
done < <(
  if [[ -n "$latest_tag" ]]; then
    git rev-list --no-merges "${range}" 2>/dev/null || true
  else
    git rev-list --no-merges --reverse HEAD 2>/dev/null || true
  fi
)

if [[ ${#commits[@]} -eq 0 ]]; then
  echo "No commits found in range; current base: ${PREFIX}${base_version}${latest_tag:+ (tag $latest_tag)}"
  echo "${PREFIX}${base_version}"
  exit 0
fi

has_breaking=0
has_feat=0
has_fix=0

is_breaking_subject() {
  # feat!, fix!, chore(scope)!:, etc.
  grep -E -q '^[a-z]+(\([^)]*\))?!:' <<<"$1"
}

is_type_subject() {
  local type="$1"
  local subj="$2"
  grep -E -q "^${type}(\([^)]*\))?:" <<<"$subj"
}

body_has_breaking() {
  grep -Eiq '^(BREAKING CHANGE|BREAKING-CHANGE)' <<<"$1"
}

for c in "${commits[@]}"; do
  subj="$(git log -1 --format=%s "$c")"
  body="$(git log -1 --format=%b "$c")"
  classified=""

  if is_breaking_subject "$subj" || body_has_breaking "$body"; then
    has_breaking=1
    classified="BREAKING"
  elif is_type_subject "feat" "$subj"; then
    has_feat=1
    classified="${classified:-feat}"
  elif is_type_subject "fix" "$subj" || is_type_subject "perf" "$subj"; then
    has_fix=1
    classified="${classified:-fix/perf}"
  fi

  if [[ "$VERBOSE" -eq 1 ]]; then
    short="$(git rev-parse --short "$c")"
    echo "${short} ${classified:-other} $subj" >&2
  fi
done

if [[ "$has_breaking" -eq 1 ]]; then
  major=$((major + 1))
  minor=0
  patch=0
elif [[ "$has_feat" -eq 1 ]]; then
  minor=$((minor + 1))
  patch=0
elif [[ "$has_fix" -eq 1 ]]; then
  patch=$((patch + 1))
elif [[ "$ANY_PATCH" -eq 1 ]]; then
  patch=$((patch + 1))
else
  echo "No conventional bump signals (feat / fix|perf / breaking) in range ${range}." >&2
  echo "Use --any-patch to bump PATCH when only docs/ci/chore/etc. changed, or follow Conventional Commits." >&2
  echo "${PREFIX}${base_version}"
  exit 2
fi

next="${major}.${minor}.${patch}"
echo "${PREFIX}${next}"
