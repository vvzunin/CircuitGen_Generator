# Create executable
project(abc_utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

set (SOURCES
  abc_utils/AbcUtils.cpp
  abc_utils/YosysUtils.cpp
)

add_library(AbcUtils AbcUtils.cpp AbcUtils.h YosysUtils.cpp YosysUtils.h StandartUtil.h)
set_target_properties(OptimizationUtils PROPERTIES PUBLIC_HEADER abc_utils/*.h)