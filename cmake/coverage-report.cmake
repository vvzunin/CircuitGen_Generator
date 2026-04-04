# Ninja invokes cmake through a shell; stray quotes on -D values break paths (e.g. .../dir"/file).
foreach(_v IN ITEMS PROJECT_BINARY_DIR PROJECT_SOURCE_DIR COVERAGE_HTML_FOLDER COVERAGE_INFO COVERAGE_INCLUDE_PATTERN)
  string(STRIP "${${_v}}" _stripped)
  if(_stripped MATCHES "^\"(.*)\"$")
    set(_stripped "${CMAKE_MATCH_1}")
  endif()
  set(${_v} "${_stripped}")
endforeach()

# Encoded in cmake/coverage.cmake so Ninja/shell does not break ';' in -DCOVERAGE_EXCLUDE_PATTERNS=...
string(STRIP "${COVERAGE_EXCLUDE_PATTERNS}" COVERAGE_EXCLUDE_PATTERNS)
if(COVERAGE_EXCLUDE_PATTERNS MATCHES "^\"(.*)\"$")
  set(COVERAGE_EXCLUDE_PATTERNS "${CMAKE_MATCH_1}")
endif()
string(REPLACE "|" ";" COVERAGE_EXCLUDE_PATTERNS "${COVERAGE_EXCLUDE_PATTERNS}")

set(coverage_base_info "${PROJECT_BINARY_DIR}/coverage.base.info")
set(coverage_test_info "${PROJECT_BINARY_DIR}/coverage.test.info")
set(coverage_total_info "${PROJECT_BINARY_DIR}/coverage.total.info")
set(coverage_info "${PROJECT_BINARY_DIR}/${COVERAGE_INFO}")
set(coverage_html_dir "${PROJECT_BINARY_DIR}/${COVERAGE_HTML_FOLDER}")
set(coverage_summary_file "${PROJECT_BINARY_DIR}/coverage_summary.txt")

find_program(LCOV_BIN lcov REQUIRED)

# Ensure output directory exists (geninfo fails with ENOENT if missing).
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}")

execute_process(
  COMMAND "${LCOV_BIN}" --version
  RESULT_VARIABLE lcov_version_result
  OUTPUT_VARIABLE lcov_version_out
  ERROR_VARIABLE lcov_version_err
)
if(NOT lcov_version_result EQUAL 0)
  message(FATAL_ERROR "lcov is required: ${lcov_version_err}")
endif()

# This script uses lcov 2 --ignore-errors tokens only. Ubuntu 22.04 apt ships 1.14 — use scripts/setup/install-lcov-ci.sh in CI images.
set(_lcov_ver_text "${lcov_version_out}${lcov_version_err}")
if(_lcov_ver_text MATCHES "version[ ]+([0-9]+)")
  set(LCOV_VERSION_MAJOR "${CMAKE_MATCH_1}")
else()
  message(FATAL_ERROR "Could not parse lcov version from: ${_lcov_ver_text}")
endif()
if(LCOV_VERSION_MAJOR LESS 2)
  message(FATAL_ERROR
    "lcov 2.0 or newer is required for coverage (found major ${LCOV_VERSION_MAJOR}). "
    "Install from https://github.com/linux-test-project/lcov/releases or run scripts/setup/install-lcov-ci.sh (Ubuntu 22.04 CI).")
endif()

set(LCOV_IGNORE_GENINFO "mismatch,gcov,unused,empty,inconsistent")
set(LCOV_IGNORE_REMOVE "mismatch,gcov,unused,inconsistent,corrupt")
set(LCOV_IGNORE_MERGE "empty,source,inconsistent,corrupt")

message(STATUS "Capturing baseline coverage data")
execute_process(
  COMMAND "${LCOV_BIN}" --capture --initial
    --directory "."
    --output-file "coverage.base.info"
    --ignore-errors "${LCOV_IGNORE_GENINFO}"
    --rc branch_coverage=1
  WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
  RESULT_VARIABLE capture_base_result
  OUTPUT_VARIABLE capture_base_out
  ERROR_VARIABLE capture_base_err
)
if(NOT capture_base_result EQUAL 0)
  message(FATAL_ERROR "Failed to capture baseline coverage: ${capture_base_err}")
endif()
if(NOT EXISTS "${coverage_base_info}")
  message(WARNING "Baseline tracefile was not created at ${coverage_base_info}; continuing without baseline merge.")
endif()

message(STATUS "Capturing test coverage data")
execute_process(
  COMMAND "${LCOV_BIN}" --capture
    --directory "."
    --output-file "coverage.test.info"
    --include "${COVERAGE_INCLUDE_PATTERN}"
    --ignore-errors "${LCOV_IGNORE_GENINFO}"
    --rc branch_coverage=1
  WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
  RESULT_VARIABLE capture_test_result
  OUTPUT_VARIABLE capture_test_out
  ERROR_VARIABLE capture_test_err
)
if(NOT capture_test_result EQUAL 0)
  message(FATAL_ERROR "Failed to capture test coverage: ${capture_test_err}")
endif()
if(NOT EXISTS "${coverage_test_info}")
  message(FATAL_ERROR "Test tracefile was not created: ${coverage_test_info} (${capture_test_err})")
endif()

message(STATUS "Merging baseline and test coverage data")
if(EXISTS "${coverage_base_info}")
  # lcov 2.x on some hosts mishandles absolute --output-file paths (ENOENT on write).
  execute_process(
    COMMAND "${LCOV_BIN}" --add-tracefile "coverage.base.info" --add-tracefile "coverage.test.info"
      --output-file "coverage.total.info"
      --ignore-errors "${LCOV_IGNORE_MERGE}"
    WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
    RESULT_VARIABLE merge_result
    OUTPUT_VARIABLE merge_out
    ERROR_VARIABLE merge_err
  )
  if(NOT merge_result EQUAL 0)
    message(FATAL_ERROR "Failed to merge coverage tracefiles: ${merge_err}")
  endif()
else()
  message(STATUS "Using test tracefile only (no baseline)")
  execute_process(
    COMMAND "${CMAKE_COMMAND}" -E copy "coverage.test.info" "coverage.total.info"
    WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
    RESULT_VARIABLE merge_result
    ERROR_VARIABLE merge_err
  )
  if(NOT merge_result EQUAL 0)
    message(FATAL_ERROR "Failed to stage coverage tracefile: ${merge_err}")
  endif()
endif()

string(REPLACE ";" " " exclude_patterns_log "${COVERAGE_EXCLUDE_PATTERNS}")
message(STATUS "Filtering coverage data with patterns: ${exclude_patterns_log}")
# Build argv explicitly; unquoted ${COVERAGE_EXCLUDE_PATTERNS} in COMMAND can mis-expand on some CMake versions.
set(_lcov_remove_cmd "${LCOV_BIN}" --remove "coverage.total.info")
foreach(_exclude_pattern IN LISTS COVERAGE_EXCLUDE_PATTERNS)
  list(APPEND _lcov_remove_cmd "${_exclude_pattern}")
endforeach()
list(APPEND _lcov_remove_cmd --output-file "${COVERAGE_INFO}" --ignore-errors "${LCOV_IGNORE_REMOVE}")
execute_process(
  COMMAND ${_lcov_remove_cmd}
  WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
  RESULT_VARIABLE filter_result
  OUTPUT_VARIABLE filter_out
  ERROR_VARIABLE filter_err
)
if(NOT filter_result EQUAL 0)
  message(FATAL_ERROR "Failed to filter coverage data: ${filter_err}")
endif()

execute_process(
  COMMAND "${LCOV_BIN}" --summary "${COVERAGE_INFO}" --rc branch_coverage=1
  WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
  RESULT_VARIABLE summary_result
  OUTPUT_VARIABLE summary_out
  ERROR_VARIABLE summary_err
)
if(NOT summary_result EQUAL 0)
  message(FATAL_ERROR "Failed to summarize coverage: ${summary_err}")
endif()

file(WRITE "${coverage_summary_file}" "${summary_out}")

string(REGEX MATCH "lines\\.+: ([0-9]+\\.[0-9]+|[0-9]+)%" lines_match "${summary_out}")
if(NOT lines_match)
  message(FATAL_ERROR "Unable to parse line coverage from lcov summary:\n${summary_out}")
endif()
set(coverage_percent "${CMAKE_MATCH_1}")

message(STATUS "Coverage summary written to ${coverage_summary_file}")
message(STATUS "TOTAL_COVERAGE=${coverage_percent}%")

if(COVERAGE_ENABLE_HTML)
  find_program(GENHTML_BIN genhtml REQUIRED)
  message(STATUS "Generating HTML report")
  execute_process(
    COMMAND "${GENHTML_BIN}" --legend --function-coverage --branch-coverage --quiet
      "${COVERAGE_INFO}"
      --prefix "${PROJECT_SOURCE_DIR}"
      --output-directory "${COVERAGE_HTML_FOLDER}"
    WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
    RESULT_VARIABLE html_result
    OUTPUT_VARIABLE html_out
    ERROR_VARIABLE html_err
  )
  if(NOT html_result EQUAL 0)
    message(FATAL_ERROR "Failed to generate HTML coverage report: ${html_err}")
  endif()
  message(STATUS "Coverage report generated at ${coverage_html_dir}/index.html")
endif()
