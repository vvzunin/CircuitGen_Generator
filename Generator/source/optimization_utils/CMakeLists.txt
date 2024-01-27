# Set minimum version of cmake
cmake_minimum_required(VERSION 3.13)

# Create executable
project(optimization_utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(MAIN_LIBRARY OptimizationUtils)

# Needed to build library.
set(BUILD_LIBRARY True)

OPTION(GENERATOR_DEBUG "Extended debug printing" OFF)
option(BUILD_SHARED_PROJECT_LIBS "Build using shared libraries" ON)

set(SOURCES
    AbcUtils.cpp
    AbcUtils.h
    YosysUtils.cpp
    YosysUtils.h
    StandartUtil.h
    UtilsCommands.h
)
set(public_headers
    AbcUtils.h
    YosysUtils.h
    StandartUtil.h
)

add_library(${MAIN_LIBRARY} SHARED EXCLUDE_FROM_ALL ${SOURCES})

set_target_properties(${MAIN_LIBRARY} PROPERTIES PUBLIC_HEADER "${public_headers}")
target_include_directories(${MAIN_LIBRARY} PRIVATE .)
set_property(TARGET ${MAIN_LIBRARY} PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET ${MAIN_LIBRARY} PROPERTY OUTPUT_NAME ${MAIN_LIBRARY})
