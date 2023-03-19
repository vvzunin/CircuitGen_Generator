cmake_minimum_required(VERSION 3.10.2)
project(tests)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)
add_executable(${PROJECT_NAME} SettingsTests.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC
graph
gtest
gtest_main
)
