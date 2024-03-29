cmake_minimum_required(VERSION 3.19)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(cmake/prelude.cmake)

project(
    CircuitGen_Generator
    VERSION 0.1.0
    DESCRIPTION "Program for circuits dataset generation"
    HOMEPAGE_URL "https://github.com/vvzunin/CircuitGen_Generator"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----
option(CircuitGen_Generator_USE_EXTERNAL_JSON "Use an external JSON library" ON)
add_subdirectory(lib)

# Check if pthreads is installed; adjust compiler/linker options
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Add all subdirectories for the project.

add_subdirectory(src)

include_directories(src)


# ---- Declare executable ----
set(MAIN_LIBRARY cgen)

add_executable(CircuitGen_Generator_exe src/main.cpp)
add_executable(CircuitGen_Generator::exe ALIAS CircuitGen_Generator_exe)

set_property(TARGET CircuitGen_Generator_exe PROPERTY OUTPUT_NAME CircuitGen_Generator)

target_compile_features(CircuitGen_Generator_exe PRIVATE cxx_std_17)

target_link_libraries(CircuitGen_Generator_exe PRIVATE cgen)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT CircuitGen_Generator_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of CircuitGen_Generator"
  )
endif()

include(cmake/dev-mode.cmake)
