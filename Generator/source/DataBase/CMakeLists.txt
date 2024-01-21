# Create executable
project(data_base_generator)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(DataBaseGenerator SHARED DataBaseGenerator.cpp DataBaseGenerator.h DataBaseGeneratorParameters.cpp DataBaseGeneratorParameters.h)
target_include_directories(DataBaseGenerator PUBLIC ${CMAKE_SOURCE_DIR})
