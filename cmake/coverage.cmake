# ---- Variables ----
# We use variables separate from what CTest uses, because those have
# customization issues.
set(COVERAGE_FOLDER "coverage")
set(COVERAGE_HTML_FOLDER "html")
set(COVERAGE_INFO "coverage.info")

option(COVERAGE_ENABLE_HTML "Generate HTML report with genhtml" ON)

# Validate lcov early to fail fast in CI/local coverage runs.
execute_process(
  COMMAND lcov --version
  RESULT_VARIABLE lcov_version_result
  OUTPUT_VARIABLE lcov_version_out
  ERROR_VARIABLE lcov_version_err
)
if(NOT lcov_version_result EQUAL 0)
  message(FATAL_ERROR "Error: lcov not found. Install it and try again. ${lcov_version_err}")
endif()
string(REGEX MATCH "[0-9]+\\.[0-9]+([.][0-9]+)?" LCOV_VERSION "${lcov_version_out}")

# Paths to exclude from report to keep product coverage meaningful.
set(
  COVERAGE_EXCLUDE_PATTERNS
  "${PROJECT_BINARY_DIR}/*;${PROJECT_SOURCE_DIR}/test/*;${PROJECT_SOURCE_DIR}/lib/*;${PROJECT_SOURCE_DIR}/_deps/*;/usr/*"
  CACHE STRING
  "Semicolon-separated lcov --remove patterns"
)

# Include only project tree in final aggregated report.
set(
  COVERAGE_INCLUDE_PATTERN
  "${PROJECT_SOURCE_DIR}/*"
  CACHE STRING
  "Pattern for lcov --include"
)

# Ninja runs the custom command through a shell; ';' inside -D values is lost or
# mangled. Encode the list with '|' (paths do not contain it); decode in coverage-report.cmake.
set(_coverage_exclude_for_cmd "${COVERAGE_EXCLUDE_PATTERNS}")
string(REPLACE ";" "|" _coverage_exclude_for_cmd "${_coverage_exclude_for_cmd}")

# ---- Coverage target ----
add_custom_target(
  coverage
  # Delegate heavy coverage logic to a dedicated script for easier maintenance.
  COMMAND "${CMAKE_COMMAND}"
    -DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
    -DPROJECT_BINARY_DIR="${PROJECT_BINARY_DIR}"
    -DCOVERAGE_HTML_FOLDER="${COVERAGE_HTML_FOLDER}"
    -DCOVERAGE_INFO="${COVERAGE_INFO}"
    -DCOVERAGE_ENABLE_HTML="${COVERAGE_ENABLE_HTML}"
    -DCOVERAGE_EXCLUDE_PATTERNS="${_coverage_exclude_for_cmd}"
    -DCOVERAGE_INCLUDE_PATTERN="${COVERAGE_INCLUDE_PATTERN}"
    -P "${PROJECT_SOURCE_DIR}/cmake/coverage-report.cmake"
  COMMENT "Generating coverage report"
  VERBATIM
)
