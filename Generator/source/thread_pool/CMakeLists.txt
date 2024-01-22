# Create executable
project(thread_pool)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(ThreadPool SHARED ThreadPool.cpp ThreadPool.h UnboundedMPMCQueue.h)
set_target_properties(ThreadPool PROPERTIES PUBLIC_HEADER thread_pool/*.h)
