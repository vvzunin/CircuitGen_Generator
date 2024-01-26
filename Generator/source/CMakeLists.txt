# Set minimum version of cmake
cmake_minimum_required(VERSION 3.13)

# Define project name, version and description
project(CircuitsGenerator 
  VERSION 0.1.0
  DESCRIPTION "Programm for circuits dataset generation"
  HOMEPAGE_URL https://github.com/vvzunin/CAD_CombinationalCircuits
  LANGUAGES CXX
)

# Add path for .cmake files. Needed for "include" directive.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Big section with some variables to define
# Define variables for coverege
set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
# Define main cmake project settings
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_INIT} -std=c++11 -fPIC")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")
set(CMAKE_BUILD_TYPE Debug)
# Define folder for external libraries
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
# Define name of final file.
set(MAIN_TARGET circuitgen)
set(MAIN_LIBRARY cgen)
# Needed to build library.
set(BUILD_LIBRARY True)

OPTION(GENERATOR_DEBUG "Extended debug printing" OFF)

# Configuration file.
configure_file(config.h.in config.h)

option(BUILD_SHARED_PROJECT_LIBS "Build using shared libraries" ON)

include(ExternalProject)
include(FetchContent)

# Get json
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

# Get googletest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# The compilation options.
# add_compile_options(-g3 -Wall -Wignored-qualifiers -DYYERROR_VERBOSE)

# Add all subdirectories for the project.
add_subdirectory(AuxiliaryMethods)
add_subdirectory(circuits)
add_subdirectory(DataBase)
add_subdirectory(filesTools)
add_subdirectory(generators)
add_subdirectory(graph)
add_subdirectory(optimization_utils)
add_subdirectory(reliability)
add_subdirectory(settings)
add_subdirectory(thread_pool)

add_subdirectory(tests)

# Set all libraries, using in project.
set(PROJECT_LIBS
  # Internal libraries
  GraphVertex
  OrientedGraph
  TruthTable
  Reliability
  Circuit
  AuxiliaryMethods
  FilesTools
  Settings
  OptimizationUtils
  ThreadPool
  DataBaseGenerator

  # External libraries
  nlohmann_json::nlohmann_json
)

# Add source files
set(SOURCES
  settings/Settings.cpp
  AuxiliaryMethods/AuxiliaryMethods.cpp
  filesTools/FilesTools.cpp  
  generators/Genetic/Parents/ParentsParameters.cpp
  generators/Genetic/Recombination/RecombinationParameters.cpp
  generators/Genetic/Mutations/MutationParameters.cpp
  generators/Genetic/Selections/SelectionParameters.cpp
  generators/Genetic/GeneticParameters.cpp
  generators/GenerationParameters.cpp
  graph/GraphVertex.cpp
  graph/OrientedGraph.cpp
  reliability/Reliability.cpp
  optimization_utils/AbcUtils.cpp
  optimization_utils/YosysUtils.cpp
  thread_pool/ThreadPool.cpp
  generators/TruthTable.cpp
  generators/Genetic/Chronosome.cpp
  generators/Genetic/ChronosomeType.cpp
  circuits/Circuit.cpp
  generators/Parser.cpp
  generators/SimpleGenerators.cpp
  generators/Genetic/GenGenerator.cpp
  DataBase/DataBaseGenerator.cpp
  DataBase/DataBaseGeneratorParameters.cpp
  generatorAPI.cpp
  main.cpp
)

# Create executable
add_executable(${MAIN_TARGET} ${SOURCES})

# Add all internal libraries in the project
target_link_libraries(${MAIN_TARGET} ${PROJECT_LIBS})

# Check if pthreads is installed; adjust compiler/linker options
find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(${MAIN_TARGET} PUBLIC "-lpthread")
endif()
if(CMAKE_THREAD_PROJECT_LIBS_INIT)
  target_link_libraries(${MAIN_TARGET} "${CMAKE_THREAD_PROJECT_LIBS_INIT}")
endif()




# Link to shared library
function(gen_properties target visibility)
    target_include_directories(${target} ${visibility} ${CMAKE_CURRENT_SOURCE_DIR} )
    target_link_libraries(${target} ${visibility} ${PROJECT_LIBS})
endfunction()

add_library(${MAIN_LIBRARY} SHARED EXCLUDE_FROM_ALL ${SOURCES})
gen_properties(${MAIN_LIBRARY} PRIVATE)

set(public_headers
    generatorAPI.h
)

set_target_properties(${MAIN_LIBRARY} PROPERTIES PUBLIC_HEADER "${public_headers}")

set_property(TARGET ${MAIN_LIBRARY} PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET ${MAIN_LIBRARY} PROPERTY OUTPUT_NAME ${MAIN_LIBRARY})
