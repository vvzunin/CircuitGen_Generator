# Create executable
project(circuit)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

set (SOURCES
  ../Settings.cpp
  ../FilesTools.cpp
  circuits/Circuit.cpp
)

add_library(Circuit Circuit.cpp Circuit.h)
