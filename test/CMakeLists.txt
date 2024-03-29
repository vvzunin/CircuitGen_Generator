cmake_minimum_required(VERSION 3.14)

project(CircuitGenGeneratorTests LANGUAGES CXX)


include(ExternalProject)
include(FetchContent)

# Get googletest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(CircuitGenGenerator REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

set(SOURCES_TEST
  src/additional/AuxiliaryMethodsTests.cpp
  src/additional/filesTools/FilesToolsTests.cpp
  src/settings/SettingsTests.cpp
)

add_executable(CircuitGenGenerator_test ${SOURCES_TEST})
target_link_libraries(CircuitGenGenerator_test PRIVATE CircuitGenGenerator::CircuitGenGenerator)
target_compile_features(CircuitGenGenerator_test PRIVATE cxx_std_17)

add_test(NAME CircuitGenGenerator_test COMMAND CircuitGenGenerator_test)

# ---- End-of-file commands ----

add_folders(Test)
