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

include("${CMAKE_CURRENT_LIST_DIR}/cmake/utils.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/checks.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/folders.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/variables.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/lint-targets.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/spell-targets.cmake")

include("${CMAKE_CURRENT_LIST_DIR}/cmake/CMakeGraphVizOptions.cmake")

include(GNUInstallDirs)
include(CheckIPOSupported)
include(ExternalProject)
include(FetchContent)

check_ipo_supported(RESULT ipo_supported)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${ipo_supported})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_if_undefined(CircuitGenGenerator_INSTALL_CMAKEDIR
  "${CMAKE_INSTALL_LIBDIR}/cmake/CircuitGenGenerator-${PROJECT_VERSION}" CACHE STRING
  "Install path for CircuitGenGenerator package-related CMake files")
set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET default)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# Подключение внешних зависимостей
list(APPEND external_targets CircuitGenGraph)

set(ORIENTED_GRAPH CircuitGenGraph)

if (NOT DEFINED LOCAL_BUILD)
  FetchContent_Declare(
    ${ORIENTED_GRAPH}
    GIT_REPOSITORY https://hub.mos.ru/circuitgen/CircuitGen_Graph
    GIT_TAG 54562f3a7e2fb6b87e14494e53043efba4c6a020
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

list(APPEND external_targets Threads)
find_package(Threads REQUIRED)

find_program(CLANG_TIDY NAMES clang-tidy)
if(PROJECT_IS_TOP_LEVEL)
  option(CircuitGenGenerator_ENABLE_CLANG_TIDY "Run clang-tidy during build" OFF)
endif()
if (CLANG_TIDY AND CircuitGenGenerator_ENABLE_CLANG_TIDY)
  set(GENERATOR_CLANG_TIDY
    ${CLANG_TIDY};
    -line-filter=[{"name":".hpp"},{"name":".hpp.in"},{"name":".cpp"}]
  )
elseif(CLANG_TIDY)
  message(STATUS "clang-tidy found but disabled (set CircuitGenGenerator_ENABLE_CLANG_TIDY=ON to enable)")
else()
  message(STATUS "clang-tidy not found")
endif()

# TODO: Добавить в код
# list(APPEND external_targets Gettext)
# find_package(Gettext REQUIRED)

add_subdirectory(lib)
add_subdirectory(src)
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
# include_directories(lib)

if(PROJECT_IS_TOP_LEVEL)
  option(CircuitGenGenerator_DEVELOPER_MODE "Enable developer mode" OFF)
  option(CircuitGenGenerator_BUILD_EXAMPLES "Build CircuitGenGenerator examples" OFF)
  option(BUILD_MCSS_DOCS "Build documentation using Doxygen and m.css" OFF)
  if(BUILD_MCSS_DOCS)
    include(cmake/docs.cmake)
  endif()
  option(ENABLE_COVERAGE "Enable coverage support separate from CTest's" ON)
  if(ENABLE_COVERAGE)
    include(cmake/coverage.cmake)
  endif()
endif()

print_cmake_info(Green)
print_build_info(Green)
print_system_info(Green)

if(PROJECT_IS_TOP_LEVEL)
  print_project_info(Green)
endif()

configure_file(
  easylogging++.conf
  "${PROJECT_BINARY_DIR}/bin/easylogging++.conf"
  COPYONLY
)

# ---- Install rules ----
if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# Examples (optional): must be registered before the developer-mode early return so that
# Release + CircuitGenGenerator_BUILD_EXAMPLES=ON can still add this subdirectory.
if(PROJECT_IS_TOP_LEVEL AND CircuitGenGenerator_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# ---- Developer mode ----
if(NOT CircuitGenGenerator_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
    AUTHOR_WARNING
    "Developer mode is intended for developers of CircuitGenGenerator"
  )
endif()

# if(ENABLE_LOGGING)
#   target_compile_definitions(CircuitGenGenerator_exe PRIVATE -DLOGGING)
# endif()

# if (DEBUG)
#   target_compile_options(CircuitGenGenerator_exe PUBLIC -fnoinline-functions)
# endif()

# if (RELEASE)
#   target_compile_options(CircuitGenGenerator_exe PUBLIC -finline-functions)
# endif()

target_compile_options(CircuitGenGenerator_lib PUBLIC -Wpedantic)
target_compile_options(CircuitGenGenerator_lib PUBLIC -Wall)
# target_compile_options(CircuitGenGenerator_lib PUBLIC -H)
# target_compile_options(threadPool PUBLIC -H)
# target_compile_options(CircuitGenGenerator_exe PUBLIC -H)
target_compile_options(CircuitGenGenerator_exe PUBLIC -Wpedantic)
target_compile_options(CircuitGenGenerator_exe PUBLIC -Wall)

add_folders(Project)