#!/usr/bin/env bash
# Log in to the Harbor/registry used by CI.
#
# Primary: NAS_Harbor_USER + NAS_Harbor_PASS (GitLab → CI/CD → Variables).
# Optional fallbacks when primary is empty: HARBOR_CI_USER + HARBOR_CI_PASSWORD
# (e.g. non-protected copies for merge request pipelines — see below).
#
# Merge request pipelines often do not receive Protected variables (GitLab only
# injects them for pipelines tied to protected branches/tags in a way that MR
# refs may not satisfy). Branch/tag pipelines then see the vars, MR jobs get
# empty NAS_Harbor_USER — use unprotected duplicates or HARBOR_CI_* fallbacks.
set -euo pipefail

: "${REGISTRY_URL:?REGISTRY_URL is not set}"

user="${NAS_Harbor_USER:-${HARBOR_CI_USER:-}}"
pass="${NAS_Harbor_PASS:-${HARBOR_CI_PASSWORD:-}}"

if [ -z "$user" ] || [ -z "$pass" ]; then
  echo "docker-registry-login: Harbor credentials are empty (need NAS_Harbor_USER and NAS_Harbor_PASS," >&2
  echo "or optional unprotected fallbacks HARBOR_CI_USER and HARBOR_CI_PASSWORD with the same values)." >&2
  if [ "${CI_PIPELINE_SOURCE:-}" = "merge_request_event" ]; then
    echo "This job is a merge request pipeline: Protected CI variables are often not injected here." >&2
    echo "Fix: turn off Protected on those variables, or add non-protected HARBOR_CI_USER/HARBOR_CI_PASSWORD." >&2
  else
    echo "If variables are Protected, run on a protected branch/tag or clear the Protected flag." >&2
  fi
  exit 1
fi

printf '%s' "$pass" | docker login "$REGISTRY_URL" -u "$user" --password-stdin
