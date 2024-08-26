cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
  CircuitGen_Generator
  VERSION 1.3.0
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

include(ExternalProject)
include(FetchContent)

set(ORIENTED_GRAPH CircuitGenGraph)

FetchContent_Declare(
  ${ORIENTED_GRAPH}
  GIT_REPOSITORY https://github.com/vvzunin/CircuitGen_Graph
  GIT_TAG v1.2.0
)
FetchContent_MakeAvailable(${ORIENTED_GRAPH})

set(PUBLIC_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/CircuitGenGenerator/export.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/CircuitGenGenerator/CircuitGenGenerator.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/CircuitGenGenerator/ThreadPool.hpp
)

set(SOURCES
  src/additional/AuxiliaryMethods.cpp
  src/additional/filesTools/FilesTools.cpp
  src/additional/threadPool/ThreadPool.cpp
  src/baseStructures/Parser.cpp
  src/baseStructures/truthTable/TruthTable.cpp
  src/circuit/Circuit.cpp
  src/database/DataBaseGenerator.cpp
  src/database/DataBaseGeneratorParameters.cpp
  src/generators/simple/SimpleGenerators.cpp
  src/generators/Genetic/GeneticParameters.cpp
  src/generators/Genetic/GenGenerator.hpp
  src/generators/Genetic/Chromosome.hpp
  src/generators/Genetic/ChromosomeType.hpp
  src/generators/Genetic/Selections/Selections.hpp
  src/generators/Genetic/Selections/SelectionParameters.cpp
  src/generators/Genetic/Selections/SelectionsTruthTable.hpp
  src/generators/Genetic/Recombination/Recombinations.hpp
  src/generators/Genetic/Recombination/RecombinationParameters.cpp
  src/generators/Genetic/Recombination/RecombinationsTruthTable.cpp
  src/generators/Genetic/Parents/Parents.hpp
  src/generators/Genetic/Parents/ParentsParameters.cpp
  src/generators/Genetic/Parents/ParentsTruthTable.hpp
  src/generators/Genetic/Mutations/Mutation.cpp
  src/generators/Genetic/Mutations/MutationParameters.cpp
  src/generators/Genetic/Mutations/MutationTruthTable.cpp
  src/settings/Settings.cpp
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" 
  FILES 
  src/CircuitGenGenerator.cpp 
  ${SOURCES}
)

add_library(
  CircuitGenGenerator_lib
)
add_library(CircuitGenGenerator::CircuitGenGenerator ALIAS CircuitGenGenerator_lib)

if(NOT TARGET easylogging++)
  add_library(
    easylogging++ STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/easyloggingpp/easylogging++.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/easyloggingpp/easylogging++.h
  )
endif()

configure_file(
  easylogging++.conf
  easylogging++.conf
  COPYONLY
)

include(cmake/utils.cmake)
include(GNUInstallDirs)

set_if_undefined(CircuitGenGenerator_INSTALL_CMAKEDIR
  "${CMAKE_INSTALL_LIBDIR}/cmake/CircuitGenGenerator-${PROJECT_VERSION}" CACHE STRING
  "Install path for CircuitGenGenerator package-related CMake files")

if(DEFINED CircuitGenGenerator_SHARED_LIBS)
  set(BUILD_SHARED_LIBS ${CircuitGenGenerator_SHARED_LIBS})
endif()

option(CircuitGenGenerator_BUILD_EXAMPLES "Build CircuitGenGenerator examples" OFF)

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET default)
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
  VERSION "${PROJECT_VERSION}"
  SOVERSION "${PROJECT_VERSION_MAJOR}"
  EXPORT_NAME CircuitGenGenerator
  OUTPUT_NAME CircuitGenGenerator
  PUBLIC_HEADER "${PUBLIC_HEADERS}"
)

list(APPEND PUBLIC_HEADERS
  "${CMAKE_CURRENT_BINARY_DIR}/include/CircuitGenGenerator/${export_file_name}")

include(CMakePackageConfigHelpers)

target_link_libraries(
  CircuitGenGenerator_lib PRIVATE 
  ${EXTERNAL_LIBS} 
  CircuitGenGraph::CircuitGenGraph
  PUBLIC
  easylogging++
)

target_sources(CircuitGenGenerator_lib 
  PRIVATE 
  src/CircuitGenGenerator.cpp ${SOURCES}
)

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

include_directories("${CMAKE_SOURCE_DIR}/include")
# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)
target_include_directories(CircuitGenGenerator_lib
  PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
  PRIVATE
  "src"  
)

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

install(TARGETS CircuitGenGenerator_lib easylogging++
  EXPORT CircuitGenGenerator_export
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

# ---- Declare executable ----
add_executable(CircuitGenGenerator_exe src/main.cpp)
add_executable(CircuitGenGenerator::exe ALIAS CircuitGenGenerator_exe)

set_property(TARGET CircuitGenGenerator_exe PROPERTY OUTPUT_NAME CircuitGenGenerator)

target_compile_features(CircuitGenGenerator_exe PRIVATE cxx_std_17)

target_link_libraries(
  CircuitGenGenerator_exe
  PRIVATE
    CircuitGenGenerator::CircuitGenGenerator
    easylogging++
)

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
