# Create executable
project(optimization_utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(OptimizationUtils STATIC AbcUtils.cpp AbcUtils.h YosysUtils.cpp YosysUtils.h StandartUtil.h AbcCommands.h)
set_target_properties(OptimizationUtils PROPERTIES PUBLIC_HEADER optimization_utils/*.h)
