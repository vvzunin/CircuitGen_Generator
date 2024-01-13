# Create executable
project(abc_utils)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

set (SOURCES
  abc_utils/AbcUtils.cpp
  abc_utils/YosysUtils.cpp
)

add_library(AbcUtils AbcUtils.cpp AbcUtils.h YosysUtils.cpp YosysUtils.h StandartUtil.h)
