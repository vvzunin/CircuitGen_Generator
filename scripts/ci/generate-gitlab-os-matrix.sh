#!/usr/bin/env bash
set -euo pipefail

# Update marked sections in .gitlab-ci.yml from scripts/config/supported-os.sh (single source of truth).
# Emits one GitLab job per OS (variables only), not parallel.matrix — many YAML schemas reject matrix.
#
# Usage:
#   bash scripts/ci/generate-gitlab-os-matrix.sh           # print generated blocks to stdout
#   bash scripts/ci/generate-gitlab-os-matrix.sh --write # rewrite markers in .gitlab-ci.yml
#   bash scripts/ci/generate-gitlab-os-matrix.sh --check # exit 1 if markers differ from generator

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
GITLAB_CI="${ROOT}/.gitlab-ci.yml"

BEGIN_DOCKER='# BEGIN generated: docker-images jobs (generate-gitlab-os-matrix.sh)'
END_DOCKER='# END generated: docker-images jobs (generate-gitlab-os-matrix.sh)'
BEGIN_RELEASE='# BEGIN generated: docker-release jobs (generate-gitlab-os-matrix.sh)'
END_RELEASE='# END generated: docker-release jobs (generate-gitlab-os-matrix.sh)'
BEGIN_VAL='# BEGIN generated: os-system-validation-main jobs (generate-gitlab-os-matrix.sh)'
END_VAL='# END generated: os-system-validation-main jobs (generate-gitlab-os-matrix.sh)'
BEGIN_SEC_CHECK='# BEGIN generated: secondary-os check jobs (generate-gitlab-os-matrix.sh)'
END_SEC_CHECK='# END generated: secondary-os check jobs (generate-gitlab-os-matrix.sh)'
BEGIN_SEC_TEST='# BEGIN generated: secondary-os test jobs (generate-gitlab-os-matrix.sh)'
END_SEC_TEST='# END generated: secondary-os test jobs (generate-gitlab-os-matrix.sh)'

# shellcheck source=../config/supported-os.sh
source "${ROOT}/scripts/config/supported-os.sh"

emit_docker_images_jobs() {
  local line slug idv first=1
  for line in "${SUPPORTED_OS_ENTRIES[@]}"; do
    slug="${line%%|*}"
    idv="${line#*|}"
    if [[ "${slug}" == "ubuntu-24.04" ]]; then
      continue
    fi
    if [[ "${first}" -eq 1 ]]; then
      first=0
    else
      echo ""
    fi
    echo "docker-images-${slug}:"
    echo "  stage: docker-matrix"
    echo "  extends:"
    echo "    - .docker-images-base"
    echo "    - .secondary-os-matrix-rules"
    echo "  needs:"
    echo "    - job: docker-images-ubuntu-24.04"
    echo "      artifacts: false"
    echo "    - job: tests"
    echo "      artifacts: false"
    echo "    - job: examples"
    echo "      artifacts: false"
    echo "  variables:"
    echo "    TARGET_OS: ${slug}"
    echo "    DOCKER_CI_SYSTEM: ${idv}"
    echo "    IMAGE_OS_SUFFIX: ${slug}"
  done
}

emit_docker_release_jobs() {
  local line slug idv first=1
  for line in "${SUPPORTED_OS_ENTRIES[@]}"; do
    slug="${line%%|*}"
    idv="${line#*|}"
    if [[ "${first}" -eq 1 ]]; then
      first=0
    else
      echo ""
    fi
    echo "docker-release-${slug}:"
    echo "  stage: docker-matrix"
    echo "  extends: .docker-release-base"
    echo "  needs:"
    echo "    - job: tests"
    echo "      artifacts: false"
    echo "    - job: examples"
    echo "      artifacts: false"
    echo "  variables:"
    echo "    TARGET_OS: ${slug}"
    echo "    DOCKER_CI_SYSTEM: ${idv}"
    echo "    IMAGE_OS_SUFFIX: ${slug}"
  done
}

emit_secondary_os_check_jobs() {
  local line slug idv first=1
  for line in "${SUPPORTED_OS_ENTRIES[@]}"; do
    slug="${line%%|*}"
    idv="${line#*|}"
    if [[ "${slug}" == "ubuntu-24.04" ]]; then
      continue
    fi
    if [[ "${first}" -eq 1 ]]; then
      first=0
    else
      echo ""
    fi
    echo "lint-os-${slug}:"
    echo "  stage: check-os"
    echo "  extends:"
    echo "    - .ci-cmake-job"
    echo "    - .secondary-os-matrix-rules"
    echo "  variables:"
    echo "    TARGET_OS: ${slug}"
    echo "    DOCKER_CI_SYSTEM: ${idv}"
    echo "    IMAGE_OS_SUFFIX: ${slug}"
    echo "    DOCKER_CI_IMAGE: \$DOCKER_URL/${slug}/ci:\$DOCKER_CI_TAG"
    echo "  needs:"
    echo "    - job: docker-images-${slug}"
    echo "      artifacts: false"
    echo "  before_script:"
    echo "    - python3 --version"
    echo "  script:"
    echo "    - bash scripts/ci/lint.sh"
    echo ""
    echo "sanitize-os-${slug}:"
    echo "  stage: check-os"
    echo "  extends:"
    echo "    - .ci-cmake-job"
    echo "    - .secondary-os-matrix-rules"
    echo "  variables:"
    echo "    TARGET_OS: ${slug}"
    echo "    DOCKER_CI_SYSTEM: ${idv}"
    echo "    IMAGE_OS_SUFFIX: ${slug}"
    echo "    DOCKER_CI_IMAGE: \$DOCKER_URL/${slug}/ci:\$DOCKER_CI_TAG"
    echo "  needs:"
    echo "    - job: docker-images-${slug}"
    echo "      artifacts: false"
    echo "  script:"
    echo "    - bash scripts/ci/sanitize.sh"
    echo ""
    echo "static-analysis-os-${slug}:"
    echo "  stage: check-os"
    echo "  extends:"
    echo "    - .ci-cmake-job"
    echo "    - .secondary-os-matrix-rules"
    echo "  variables:"
    echo "    TARGET_OS: ${slug}"
    echo "    DOCKER_CI_SYSTEM: ${idv}"
    echo "    IMAGE_OS_SUFFIX: ${slug}"
    echo "    DOCKER_CI_IMAGE: \$DOCKER_URL/${slug}/ci:\$DOCKER_CI_TAG"
    echo "  needs:"
    echo "    - job: docker-images-${slug}"
    echo "      artifacts: false"
    echo "  script:"
    echo "    - bash scripts/ci/static-analysis.sh"
  done
}

emit_secondary_os_test_jobs() {
  local line slug idv first=1
  for line in "${SUPPORTED_OS_ENTRIES[@]}"; do
    slug="${line%%|*}"
    idv="${line#*|}"
    if [[ "${slug}" == "ubuntu-24.04" ]]; then
      continue
    fi
    if [[ "${first}" -eq 1 ]]; then
      first=0
    else
      echo ""
    fi
    echo "coverage-os-${slug}:"
    echo "  stage: test-os"
    echo "  extends:"
    echo "    - .ci-cmake-job"
    echo "    - .secondary-os-matrix-rules"
    echo "  variables:"
    echo "    TARGET_OS: ${slug}"
    echo "    DOCKER_CI_SYSTEM: ${idv}"
    echo "    IMAGE_OS_SUFFIX: ${slug}"
    echo "    DOCKER_CI_IMAGE: \$DOCKER_URL/${slug}/ci:\$DOCKER_CI_TAG"
    echo "  needs:"
    echo "    - job: docker-images-${slug}"
    echo "      artifacts: false"
    echo "    - job: lint-os-${slug}"
    echo "      artifacts: false"
    echo "    - job: sanitize-os-${slug}"
    echo "      artifacts: false"
    echo "    - job: static-analysis-os-${slug}"
    echo "      artifacts: false"
    echo "  dependencies: []"
    echo "  coverage: '/TOTAL_COVERAGE=([0-9]+(?:\.[0-9]+)?)%/'"
    echo "  script:"
    echo "    - bash scripts/ci/coverage.sh"
    echo "  artifacts:"
    echo "    when: always"
    echo "    paths:"
    echo "      - build/coverage/coverage.info"
    echo "      - build/coverage/coverage_summary.txt"
    echo "      - build/coverage/html"
    echo ""
    echo "tests-os-${slug}:"
    echo "  stage: test-os"
    echo "  extends:"
    echo "    - .ci-cmake-job"
    echo "    - .secondary-os-matrix-rules"
    echo "  variables:"
    echo "    TARGET_OS: ${slug}"
    echo "    DOCKER_CI_SYSTEM: ${idv}"
    echo "    IMAGE_OS_SUFFIX: ${slug}"
    echo "    DOCKER_CI_IMAGE: \$DOCKER_URL/${slug}/ci:\$DOCKER_CI_TAG"
    echo "  needs:"
    echo "    - job: docker-images-${slug}"
    echo "      artifacts: false"
    echo "    - job: lint-os-${slug}"
    echo "      artifacts: false"
    echo "    - job: sanitize-os-${slug}"
    echo "      artifacts: false"
    echo "    - job: static-analysis-os-${slug}"
    echo "      artifacts: false"
    echo "  dependencies: []"
    echo "  script:"
    echo "    - bash scripts/ci/tests.sh"
    echo ""
    echo "examples-os-${slug}:"
    echo "  stage: test-os"
    echo "  extends:"
    echo "    - .ci-cmake-job"
    echo "    - .secondary-os-matrix-rules"
    echo "  variables:"
    echo "    TARGET_OS: ${slug}"
    echo "    DOCKER_CI_SYSTEM: ${idv}"
    echo "    IMAGE_OS_SUFFIX: ${slug}"
    echo "    DOCKER_CI_IMAGE: \$DOCKER_URL/${slug}/ci:\$DOCKER_CI_TAG"
    echo "  needs:"
    echo "    - job: docker-images-${slug}"
    echo "      artifacts: false"
    echo "    - job: lint-os-${slug}"
    echo "      artifacts: false"
    echo "  dependencies: []"
    echo "  script:"
    echo "    - bash scripts/ci/examples.sh"
    echo "  artifacts:"
    echo "    when: always"
    echo "    paths:"
    echo "      - build/release-ci/ctest_results.xml"
    echo "    reports:"
    echo "      junit: build/release-ci/ctest_results.xml"
  done
}

emit_validation_main_jobs() {
  local line slug first=1
  for line in "${SUPPORTED_OS_ENTRIES[@]}"; do
    slug="${line%%|*}"
    if [[ "${first}" -eq 1 ]]; then
      first=0
    else
      echo ""
    fi
    echo "os-system-validation-main-${slug}:"
    echo "  extends: .os-setup-check-job"
    echo "  variables:"
    echo "    TARGET_OS: ${slug}"
    echo "  rules:"
    echo "    - if: (\$CI_COMMIT_BRANCH == \$CI_DEFAULT_BRANCH) && (\$CI_COMMIT_TAG == null)"
    echo "      when: manual"
  done
}

extract_between_markers() {
  local file="$1" begin="$2" end="$3"
  awk -v b="$begin" -v e="$end" '
    $0 == b { p = 1; next }
    $0 == e { p = 0; next }
    p
  ' "$file"
}

assert_marker_pair() {
  local file="$1" begin="$2" end="$3" label="$4"
  if ! grep -qxF "$begin" "$file"; then
    echo >&2 "Missing or wrong begin marker (${label}) in ${file}"
    exit 1
  fi
  if ! grep -qxF "$end" "$file"; then
    echo >&2 "Missing or wrong end marker (${label}) in ${file}"
    exit 1
  fi
}

replace_between_markers() {
  local file="$1" begin="$2" end="$3"
  shift 3
  local -a emit_cmd=("$@")
  local tmp out=0
  tmp="$(mktemp)"
  while IFS= read -r line || [[ -n "${line}" ]]; do
    if [[ "${out}" -eq 1 ]]; then
      if [[ "${line}" == "${end}" ]]; then
        printf '%s\n' "${end}" >>"${tmp}"
        out=0
      fi
      continue
    fi
    if [[ "${line}" == "${begin}" ]]; then
      printf '%s\n' "${begin}" >>"${tmp}"
      "${emit_cmd[@]}" >>"${tmp}"
      out=1
      continue
    fi
    printf '%s\n' "${line}" >>"${tmp}"
  done <"${file}"
  mv "${tmp}" "${file}"
}

check_block() {
  local label="$1" begin="$2" end="$3"
  shift 3
  local -a emit_cmd=("$@")
  local expected actual
  expected="$(mktemp)"
  actual="$(mktemp)"
  "${emit_cmd[@]}" >"${expected}"
  extract_between_markers "${GITLAB_CI}" "${begin}" "${end}" >"${actual}"
  if ! diff -u "${expected}" "${actual}"; then
    rm -f "${expected}" "${actual}"
    echo >&2 ""
    echo >&2 ".gitlab-ci.yml (${label}) is out of date. Regenerate with:"
    echo >&2 "  bash scripts/ci/generate-gitlab-os-matrix.sh --write"
    exit 1
  fi
  rm -f "${expected}" "${actual}"
}

write_gitlab_ci_sections() {
  assert_marker_pair "${GITLAB_CI}" "${BEGIN_DOCKER}" "${END_DOCKER}" docker-images-jobs
  assert_marker_pair "${GITLAB_CI}" "${BEGIN_RELEASE}" "${END_RELEASE}" docker-release-jobs
  assert_marker_pair "${GITLAB_CI}" "${BEGIN_VAL}" "${END_VAL}" os-system-validation-main-jobs
  assert_marker_pair "${GITLAB_CI}" "${BEGIN_SEC_CHECK}" "${END_SEC_CHECK}" secondary-os-check-jobs
  assert_marker_pair "${GITLAB_CI}" "${BEGIN_SEC_TEST}" "${END_SEC_TEST}" secondary-os-test-jobs
  replace_between_markers "${GITLAB_CI}" "${BEGIN_DOCKER}" "${END_DOCKER}" emit_docker_images_jobs
  replace_between_markers "${GITLAB_CI}" "${BEGIN_RELEASE}" "${END_RELEASE}" emit_docker_release_jobs
  replace_between_markers "${GITLAB_CI}" "${BEGIN_VAL}" "${END_VAL}" emit_validation_main_jobs
  replace_between_markers "${GITLAB_CI}" "${BEGIN_SEC_CHECK}" "${END_SEC_CHECK}" emit_secondary_os_check_jobs
  replace_between_markers "${GITLAB_CI}" "${BEGIN_SEC_TEST}" "${END_SEC_TEST}" emit_secondary_os_test_jobs
  echo "Wrote generated OS job sections in ${GITLAB_CI}"
}

print_generated() {
  echo "=== docker-images-* jobs (non-ubuntu-24.04) ==="
  emit_docker_images_jobs
  echo ""
  echo "=== docker-release-* jobs ==="
  emit_docker_release_jobs
  echo ""
  echo "=== os-system-validation-main-* jobs ==="
  emit_validation_main_jobs
  echo ""
  echo "=== secondary-os check jobs ==="
  emit_secondary_os_check_jobs
  echo ""
  echo "=== secondary-os test jobs ==="
  emit_secondary_os_test_jobs
}

case "${1:-}" in
  --write)
    write_gitlab_ci_sections
    ;;
  --check)
    assert_marker_pair "${GITLAB_CI}" "${BEGIN_DOCKER}" "${END_DOCKER}" docker-images-jobs
    assert_marker_pair "${GITLAB_CI}" "${BEGIN_RELEASE}" "${END_RELEASE}" docker-release-jobs
    assert_marker_pair "${GITLAB_CI}" "${BEGIN_VAL}" "${END_VAL}" os-system-validation-main-jobs
    assert_marker_pair "${GITLAB_CI}" "${BEGIN_SEC_CHECK}" "${END_SEC_CHECK}" secondary-os-check-jobs
    assert_marker_pair "${GITLAB_CI}" "${BEGIN_SEC_TEST}" "${END_SEC_TEST}" secondary-os-test-jobs
    check_block docker-images-jobs "${BEGIN_DOCKER}" "${END_DOCKER}" emit_docker_images_jobs
    check_block docker-release-jobs "${BEGIN_RELEASE}" "${END_RELEASE}" emit_docker_release_jobs
    check_block os-system-validation-main-jobs "${BEGIN_VAL}" "${END_VAL}" emit_validation_main_jobs
    check_block secondary-os-check-jobs "${BEGIN_SEC_CHECK}" "${END_SEC_CHECK}" emit_secondary_os_check_jobs
    check_block secondary-os-test-jobs "${BEGIN_SEC_TEST}" "${END_SEC_TEST}" emit_secondary_os_test_jobs
    echo "OK: ${GITLAB_CI} matches scripts/config/supported-os.sh"
    ;;
  -h | --help)
    cat <<'USAGE'
Usage: bash scripts/ci/generate-gitlab-os-matrix.sh [OPTION]

  (no args)   print generated blocks to stdout
  --write     update marked sections in .gitlab-ci.yml
  --check     fail if markers do not match the generator (for CI)
  -h, --help  this help

Source of truth: scripts/config/supported-os.sh
USAGE
    ;;
  "")
    print_generated
    ;;
  *)
    echo "Unknown option: $1" >&2
    exit 1
    ;;
esac
