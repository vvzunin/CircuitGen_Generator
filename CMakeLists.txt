# Минимальная версия CMake для сборки
cmake_minimum_required(VERSION 3.26)

project(
  CircuitGenGenerator
  VERSION 1.3.1
  DESCRIPTION "Program for circuits generation"
  HOMEPAGE_URL "https://hub.mos.ru/circuitgen/CircuitGen_Generator"
  LANGUAGES CXX
)

list(APPEND PROJECT_SUPPORTED_SYSTEMS "Linux")

# ------------------------------------------------------------------------------
# Options
# ------------------------------------------------------------------------------

option(CircuitGenGenerator_ENABLE_LINTING
  "Create formatting targets for CircuitGenGenerator"
  OFF
)

option(CircuitGenGenerator_ENABLE_SPELL_CHECK
  "Create spell-check targets for CircuitGenGenerator"
  OFF
)

option(CircuitGenGenerator_ENABLE_CLANG_TIDY
  "Run clang-tidy during build"
  OFF
)

option(CircuitGenGenerator_DEVELOPER_MODE
  "Enable developer mode"
  OFF
)

option(CircuitGenGenerator_BUILD_EXAMPLES
  "Build CircuitGenGenerator examples"
  OFF
)

option(CircuitGenGenerator_BUILD_ALL_TESTS
  "Build tests for CircuitGenGenerator and its dependencies"
  OFF
)

option(BUILD_MCSS_DOCS
  "Build documentation using Doxygen and m.css"
  OFF
)

option(ENABLE_COVERAGE
  "Enable coverage support separate from CTest's"
  OFF
)

# Prefix for auxiliary targets if lint/spell targets are enabled.
set(PROJECT_TARGET_PREFIX CircuitGenGenerator)

# ------------------------------------------------------------------------------
# Internal CMake modules
# ------------------------------------------------------------------------------

include("${CMAKE_CURRENT_LIST_DIR}/cmake/utils.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/checks.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/folders.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/variables.cmake")

if(PROJECT_IS_TOP_LEVEL)
  include("${CMAKE_CURRENT_LIST_DIR}/cmake/lint-targets.cmake")
  include("${CMAKE_CURRENT_LIST_DIR}/cmake/spell-targets.cmake")
endif()

include("${CMAKE_CURRENT_LIST_DIR}/cmake/CMakeGraphVizOptions.cmake")

include(GNUInstallDirs)
include(CheckIPOSupported)
include(ExternalProject)
include(FetchContent)

check_ipo_supported(RESULT ipo_supported)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${ipo_supported})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_if_undefined(
  CircuitGenGenerator_INSTALL_CMAKEDIR
  "${CMAKE_INSTALL_LIBDIR}/cmake/CircuitGenGenerator-${PROJECT_VERSION}"
  CACHE STRING
  "Install path for CircuitGenGenerator package-related CMake files"
)

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET default)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)

include(CTest)

# ------------------------------------------------------------------------------
# CircuitGenGraph dependency
# ------------------------------------------------------------------------------

list(APPEND external_targets CircuitGenGraph)

set(ORIENTED_GRAPH CircuitGenGraph)

# Disable optional functionality of CircuitGenGraph before FetchContent.
set(CircuitGenGraph_ENABLE_LINTING OFF CACHE BOOL "" FORCE)
set(CircuitGenGraph_ENABLE_SPELL_CHECK OFF CACHE BOOL "" FORCE)
set(CircuitGenGraph_ENABLE_CLANG_TIDY OFF CACHE BOOL "" FORCE)

# Save current BUILD_TESTING value.
set(_CGG_BUILD_TESTING "${BUILD_TESTING}")

# Disable dependency tests unless all tests were explicitly requested.
if(NOT CircuitGenGenerator_BUILD_ALL_TESTS)
  set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
endif()

if(NOT DEFINED LOCAL_BUILD)
  FetchContent_Declare(
    ${ORIENTED_GRAPH}
    GIT_REPOSITORY https://hub.mos.ru/circuitgen/CircuitGen_Graph
    GIT_TAG 4a4d823
  )
else()
  FetchContent_Declare(
    ${ORIENTED_GRAPH}
    SOURCE_DIR ${LOCAL_BUILD}
  )
  message(STATUS "Using local graph build")
endif()

FetchContent_MakeAvailable(${ORIENTED_GRAPH})
add_folders(Libraries CircuitGenGraph)

# Restore BUILD_TESTING for this project.
set(BUILD_TESTING "${_CGG_BUILD_TESTING}" CACHE BOOL "" FORCE)
unset(_CGG_BUILD_TESTING)

# ------------------------------------------------------------------------------
# Other dependencies
# ------------------------------------------------------------------------------

list(APPEND external_targets Threads)
find_package(Threads REQUIRED)

find_program(CLANG_TIDY NAMES clang-tidy)
if(PROJECT_IS_TOP_LEVEL)
  option(CircuitGenGenerator_ENABLE_CLANG_TIDY "Run clang-tidy during build" ON)
endif()
if (CLANG_TIDY AND CircuitGenGenerator_ENABLE_CLANG_TIDY)
  set(GENERATOR_CLANG_TIDY
    ${CLANG_TIDY};
    -line-filter=[{"name":".hpp"},{"name":".hpp.in"},{"name":".cpp"}]
  )
elseif(CLANG_TIDY)
  message(STATUS "clang-tidy found but disabled")
else()
  message(STATUS "clang-tidy not found")
endif()
set(BUILD_TESTING_Graph OFF CACHE BOOL "" FORCE)

# ------------------------------------------------------------------------------
# Project directories
# ------------------------------------------------------------------------------

add_subdirectory(lib)
add_subdirectory(src)

include(CTest)
if(BUILD_TESTING_Generator)
  add_subdirectory(test)
endif()

# ------------------------------------------------------------------------------
# Optional documentation / coverage
# ------------------------------------------------------------------------------

if(BUILD_MCSS_DOCS)
  include(cmake/docs.cmake)
endif()

if(ENABLE_COVERAGE)
  include(cmake/coverage.cmake)
endif()

# ------------------------------------------------------------------------------
# Information
# ------------------------------------------------------------------------------

print_cmake_info(Green)
print_build_info(Green)
print_system_info(Green)

if(PROJECT_IS_TOP_LEVEL)
  print_project_info(Green)
endif()

if(NOT TARGET easylogging++)
  configure_file(
  easylogging++.conf
  "${PROJECT_BINARY_DIR}/bin/easylogging++.conf"
  COPYONLY
)
endif()
# ------------------------------------------------------------------------------
# Install rules
# ------------------------------------------------------------------------------

# ---- Install rules ----
if(NOT CMAKE_SKIP_INSTALL_RULES AND PROJECT_IS_TOP_LEVEL)
  include(cmake/install-rules.cmake)
endif()
# ------------------------------------------------------------------------------
# Examples
# ------------------------------------------------------------------------------

if(CircuitGenGenerator_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# ------------------------------------------------------------------------------
# Developer mode
# ------------------------------------------------------------------------------

if(NOT CircuitGenGenerator_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
    AUTHOR_WARNING
    "Developer mode is intended for developers of CircuitGenGenerator"
  )
endif()

if(TARGET CircuitGenGenerator_lib)
  target_compile_options(CircuitGenGenerator_lib PUBLIC -Wpedantic)
  target_compile_options(CircuitGenGenerator_lib PUBLIC -Wall)
endif()

if(TARGET CircuitGenGenerator_exe)
  target_compile_options(CircuitGenGenerator_exe PUBLIC -Wpedantic)
  target_compile_options(CircuitGenGenerator_exe PUBLIC -Wall)
endif()

add_folders(Project)