project(selection_parameters)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(SelectionParameters SHARED SelectionParameters.cpp SelectionParameters.h)
target_include_directories(SelectionParameters PUBLIC ${CMAKE_SOURCE_DIR})
