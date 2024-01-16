# Create executable
project(circuit)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(Circuit SHARED Circuit.cpp Circuit.h)
target_include_directories(Circuit PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(Circuit PUBLIC AbcUtils)
