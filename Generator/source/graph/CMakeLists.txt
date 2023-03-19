# Create executable
project(graph)

set(CMAKE_VERBOSE_MAKEFILE ON)

set (SOURCES
  ../Settings.cpp
  graph/GraphVertex.cpp
)

add_library(graph GraphVertex.cpp GraphVertex.h)
