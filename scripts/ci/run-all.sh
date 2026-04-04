#!/usr/bin/env bash
set -euo pipefail

# Run the full CI check sequence in selected environment.
#
# Environment:
#   CI_RUNNER=local|docker        (default: local)
#   CI_IMAGE_TAG=<image>          (default: see scripts/docker/docker-paths.sh)

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

bash scripts/ci/run-task.sh lint
bash scripts/ci/run-task.sh static-analysis
bash scripts/ci/run-task.sh sanitize
bash scripts/ci/run-task.sh coverage
bash scripts/ci/run-task.sh tests
bash scripts/ci/run-task.sh examples
bash scripts/ci/run-task.sh docs
