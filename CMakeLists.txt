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

set(PUBLIC_HEADERS
  include/CircuitGenGenerator/export.hpp
  include/CircuitGenGenerator/CircuitGenGenerator.hpp
)

set(SOURCES
  src/additional/AuxiliaryMethods.cpp
  src/additional/filesTools/FilesTools.cpp
  src/additional/threadPool/ThreadPool.cpp
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

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES src/CircuitGenGenerator.cpp ${SOURCES})

add_library(
    CircuitGenGenerator_lib
)
add_library(CircuitGenGenerator::CircuitGenGenerator ALIAS CircuitGenGenerator_lib)

include(cmake/utils.cmake)
include(GNUInstallDirs)

set_if_undefined(CircuitGenGenerator_INSTALL_CMAKEDIR 
    "${CMAKE_INSTALL_LIBDIR}/cmake/CircuitGenGenerator-${PROJECT_VERSION}" CACHE STRING
    "Install path for CircuitGenGenerator package-related CMake files")

if(DEFINED CircuitGenGenerator_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${CircuitGenGenerator_SHARED_LIBS})
endif()

option(CircuitGenGenerator_BUILD_EXAMPLES "Build CircuitGenGenerator examples" OFF)

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)


if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(CircuitGenGenerator_lib PUBLIC CircuitGenGenerator_STATIC_DEFINE)
endif()

set(export_file_name "export_shared.hpp")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.hpp")
endif()

include(GenerateExportHeader)
generate_export_header(
  CircuitGenGenerator_lib
  BASE_NAME CircuitGenGenerator
  EXPORT_FILE_NAME include/CircuitGenGenerator/${export_file_name}
  CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

set_target_properties(
  CircuitGenGenerator_lib PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME CircuitGenGenerator
    OUTPUT_NAME CircuitGenGenerator
    PUBLIC_HEADER "${PUBLIC_HEADERS}"
)

list(APPEND PUBLIC_HEADERS
    "${CMAKE_CURRENT_BINARY_DIR}/include/CircuitGenGenerator/${export_file_name}")
# list(APPEND SOURCES
#     "${CMAKE_CURRENT_BINARY_DIR}/include/CircuitGenGenerator/${export_file_name}")

include(CMakePackageConfigHelpers)
target_sources(CircuitGenGenerator_lib PRIVATE src/CircuitGenGenerator.cpp ${SOURCES})


target_include_directories(
  CircuitGenGenerator_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
  CircuitGenGenerator_lib SYSTEM
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
)

target_include_directories(CircuitGenGenerator_lib
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(CircuitGenGenerator_lib PRIVATE ${EXTERNAL_LIBS})

target_include_directories(
    CircuitGenGenerator_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)

target_compile_features(CircuitGenGenerator_lib PUBLIC cxx_std_17)

configure_package_config_file(cmake/CircuitGenGenerator-config.cmake.in CircuitGenGenerator-config.cmake
  INSTALL_DESTINATION "${CircuitGenGenerator_INSTALL_CMAKEDIR}")

write_basic_package_version_file(CircuitGenGenerator-config-version.cmake
  COMPATIBILITY SameMajorVersion)

  install(TARGETS CircuitGenGenerator_lib EXPORT CircuitGenGenerator_export
  RUNTIME COMPONENT CircuitGenGenerator
  LIBRARY COMPONENT CircuitGenGenerator NAMELINK_COMPONENT CircuitGenGenerator-dev
  ARCHIVE COMPONENT CircuitGenGenerator-dev
  PUBLIC_HEADER COMPONENT CircuitGenGenerator-dev
      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/CircuitGenGenerator")

set(targets_file "CircuitGenGenerator-shared-targets.cmake")

if(NOT BUILD_SHARED_LIBS)
  set(targets_file "CircuitGenGenerator-static-targets.cmake")
endif()

install(EXPORT CircuitGenGenerator_export
  COMPONENT CircuitGenGenerator-dev
  FILE "${targets_file}"
  DESTINATION "${CircuitGenGenerator_INSTALL_CMAKEDIR}"
  NAMESPACE CircuitGenGenerator::)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/CircuitGenGenerator-config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/CircuitGenGenerator-config-version.cmake"
  COMPONENT CircuitGenGenerator-dev
  DESTINATION "${CircuitGenGenerator_INSTALL_CMAKEDIR}")

  if(MSVC)
    set(pdb_file "")
    set(pdb_file_destination "")

    if(BUILD_SHARED_LIBS)
        set(pdb_file "$<TARGET_PDB_FILE:CircuitGenGenerator>")
        set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
    else()
        # TARGET_PDB_FILE does not work for pdb file generated by compiler
        # during static library build, need to determine it another way
        set(pdb_file "$<TARGET_FILE_DIR:CircuitGenGenerator>/$<TARGET_FILE_PREFIX:CircuitGenGenerator>$<TARGET_FILE_BASE_NAME:CircuitGenGenerator>.pdb")
        set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
    endif()

    install(FILES "${pdb_file}"
        COMPONENT CircuitGenGenerator-dev
        CONFIGURATIONS Debug RelWithDebInfo
        DESTINATION "${pdb_file_destination}"
        OPTIONAL)
endif()

# ---- Declare executable ----

add_executable(CircuitGenGenerator_exe src/main.cpp)
add_executable(CircuitGenGenerator::exe ALIAS CircuitGenGenerator_exe)

set_property(TARGET CircuitGenGenerator_exe PROPERTY OUTPUT_NAME CircuitGenGenerator)

target_compile_features(CircuitGenGenerator_exe PRIVATE cxx_std_17)

target_link_libraries(CircuitGenGenerator_exe PRIVATE CircuitGenGenerator::CircuitGenGenerator)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${CircuitGenGenerator_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(examples)
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