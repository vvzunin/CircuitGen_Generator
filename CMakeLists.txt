cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    CircuitGenGenerator
    VERSION 0.1.0
    DESCRIPTION "Program for circuits dataset generation"
    HOMEPAGE_URL "https://github.com/vvzunin/CircuitGen_Generator"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

add_subdirectory(lib)
include_directories(lib)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# ---- Declare library ----

set(
  PROJECT_LIBS
  # Internal libraries
  additional
  baseStructures
  Circuit
  DataBaseGenerator  
)

set(
  EXTERNAL_LIBS
  # External libraries
  Threads::Threads
)

set(SOURCES
  src/additional/AuxiliaryMethods.cpp
  src/additional/filesTools/FilesTools.cpp
  src/additional/threadPool/ThreadPool.cpp
  src/api/generatorAPI.cpp
  src/baseStructures/graph/GraphVertexBase.cpp  
  src/baseStructures/graph/GraphVertexConstant.cpp
  src/baseStructures/graph/GraphVertexInput.cpp
  src/baseStructures/graph/GraphVertexGates.cpp
  src/baseStructures/graph/GraphVertexOutput.cpp
  src/baseStructures/graph/OrientedGraph.cpp  
  src/baseStructures/Parser.cpp
  src/baseStructures/truthTable/TruthTable.cpp
  src/circuit/Circuit.cpp
  src/database/DataBaseGenerator.cpp
  src/database/DataBaseGeneratorParameters.cpp
  src/generators/simple/SimpleGenerators.cpp
  src/settings/Settings.cpp
)

add_library(
    CircuitGenGenerator_lib OBJECT
    ${SOURCES}
)
add_library(CircuitGenGenerator::CircuitGenGenerator ALIAS CircuitGenGenerator_lib)

include(GenerateExportHeader)
generate_export_header(
  CircuitGenGenerator_lib
    BASE_NAME CircuitGenGenerator
    EXPORT_FILE_NAME export/CircuitGenGenerator/CircuitGenGenerator_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

set(BUILD_SHARED_LIBS NO)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(CircuitGenGenerator_lib PUBLIC CIRCUITGENGENERATOR_STATIC_DEFINE)
endif()

set_target_properties(
  CircuitGenGenerator_lib PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME CircuitGenGenerator
    OUTPUT_NAME CircuitGenGenerator
    PUBLIC_HEADER src/api/generatorAPI.h
)

target_include_directories(
  CircuitGenGenerator_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
  CircuitGenGenerator_lib SYSTEM
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_link_libraries(CircuitGenGenerator_lib PRIVATE ${EXTERNAL_LIBS})

target_include_directories(
    CircuitGenGenerator_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)

target_compile_features(CircuitGenGenerator_lib PUBLIC cxx_std_17)

# ---- Declare executable ----

add_executable(CircuitGenGenerator_exe src/main.cpp)
add_executable(CircuitGenGenerator::exe ALIAS CircuitGenGenerator_exe)

set_property(TARGET CircuitGenGenerator_exe PROPERTY OUTPUT_NAME CircuitGenGenerator)

target_compile_features(CircuitGenGenerator_exe PRIVATE cxx_std_17)

target_link_libraries(CircuitGenGenerator_exe PRIVATE CircuitGenGenerator_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${CircuitGenGenerator_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
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

include(cmake/dev-mode.cmake)
