project(generator)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(Genetic)

set (SOURCES
  ../Settings.cpp
  generators/TruthTable.cpp
)

add_library(TruthTable TruthTable.cpp TruthTable.h)
