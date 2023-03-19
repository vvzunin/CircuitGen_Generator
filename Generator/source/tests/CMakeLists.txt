cmake_minimum_required(VERSION 3.10.2)
project(tests)
SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)
add_executable(${PROJECT_NAME} AuxiliaryMethodsTests.cpp SettingsTests.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC
ParentsParameters SelectionParameters RecombinationParameters MutationParameters GeneticParameters TruthTable Reliability GraphVertex OrientedGraph AuxiliaryMethods Circuit FilesTools settings nlohmann_json::nlohmann_json
gtest
gtest_main
)
