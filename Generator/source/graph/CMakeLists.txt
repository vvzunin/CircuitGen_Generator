project(graph)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(GraphVertex SHARED GraphVertex.cpp GraphVertex.h)
add_library(OrientedGraph SHARED OrientedGraph.cpp OrientedGraph.h)

target_include_directories(GraphVertex PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(OrientedGraph PUBLIC ${CMAKE_SOURCE_DIR})
