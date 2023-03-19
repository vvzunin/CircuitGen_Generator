project(selection_parameters)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

set (SOURCES
  generators/Genetic/Selections/SelectionParameters.cpp
)

add_library(SelectionParameters SelectionParameters.cpp SelectionParameters.h)
