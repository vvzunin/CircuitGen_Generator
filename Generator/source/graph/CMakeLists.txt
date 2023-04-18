project(graph)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

set (SOURCES
  ../Settings.cpp
  graph/GraphVertex.cpp
  graph/OrientedGraph.cpp
)

add_library(GraphVertex GraphVertex.cpp GraphVertex.h)
add_library(OrientedGraph OrientedGraph.cpp OrientedGraph.h)
