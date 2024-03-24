cmake_minimum_required(VERSION 3.14)

project(CircuitGenGeneratorTests LANGUAGES CXX)


include(ExternalProject)
include(FetchContent)

# Get googletest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

<<<<<<< HEAD
include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Set sources ----
foreach (src ${SOURCES})
  list(APPEND NEW_SOURCES "../${src}")
endforeach(src ${SOURCES})

message(${NEW_SOURCES})

# ---- Tests ----

# Test AuxiliaryMethodsTests

configure_file(
  src/additional/testData_AuxiliaryMethodsTests/one_line_file.txt
  src/additional/testData_AuxiliaryMethodsTests/one_line_file.txt
  COPYONLY)

configure_file(
  src/additional/testData_AuxiliaryMethodsTests/test_empty_file.txt
  src/additional/testData_AuxiliaryMethodsTests/test_empty_file.txt
  COPYONLY)

configure_file(
  src/additional/testData_AuxiliaryMethodsTests/test_one_line_with_tab.txt
  src/additional/testData_AuxiliaryMethodsTests/test_one_line_with_tab.txt
  COPYONLY)

configure_file(
  src/additional/testData_AuxiliaryMethodsTests/test_two_line_with_tab.txt
  src/additional/testData_AuxiliaryMethodsTests/test_two_line_with_tab.txt
    COPYONLY)

configure_file(
  src/additional/testData_AuxiliaryMethodsTests/test_two_lines.txt
  src/additional/testData_AuxiliaryMethodsTests/test_two_lines.txt
  COPYONLY)

add_executable(CircuitGenGenerator_test_AuxiliaryMethodsTests src/additional/AuxiliaryMethodsTests.cpp ${NEW_SOURCES})

target_link_libraries(CircuitGenGenerator_test_AuxiliaryMethodsTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_compile_features(CircuitGenGenerator_test_AuxiliaryMethodsTests PRIVATE cxx_std_17)
target_include_directories(
  CircuitGenGenerator_test_AuxiliaryMethodsTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
=======
add_executable(${PROJECT_NAME}
  ##src/additional/filesTools/FilesToolsTests.cpp
  ##src/additional/AuxiliaryMethodsTests.cpp

  #src/baseStructers/graph/GraphVertexTests.cpp
  #src/baseStructers/graph/OrientedGraphTests.cpp
  #src/baseStructers/graph/OrientedGraphSysTests.cpp
  ##src/baseStructers/truthTable/TruthTableTests.cpp 

  #src/circuits/CircuitTests.cpp

  #src/database/DataBaseGeneratorTests.cpp

  src/generators/simple/SimpleGeneratorsTests.cpp 

  ##src/settings/SettingsTests.cpp

  #AbcUtilsTests.cpp
  #YosysUtilsTests.cpp
>>>>>>> 442514d5a (commit before pull)
)
add_test(NAME AuxiliaryMethodsTests COMMAND CircuitGenGenerator_test_AuxiliaryMethodsTests)

# Test FilesToolsTests
add_executable(CircuitGenGenerator_test_FilesToolsTests src/additional/filesTools/FilesToolsTests.cpp ${NEW_SOURCES})

<<<<<<< HEAD
target_link_libraries(CircuitGenGenerator_test_FilesToolsTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_compile_features(CircuitGenGenerator_test_FilesToolsTests PRIVATE cxx_std_17)
target_include_directories(
  CircuitGenGenerator_test_FilesToolsTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
=======
DataBaseGenerator
AuxiliaryMethods 
Circuit 
#Reliability
SimpleGenerator
TruthTable 
OrientedGraph 
#GeneticParameters
#MutationParameters 
#RecombinationParameters 
#SelectionParameters 
#ParentsParameters 
#GraphVertex 
FilesTools 
Settings 
#OptimizationUtils 
ThreadPool 
Parser

nlohmann_json::nlohmann_json
gtest
gtest_main
>>>>>>> 442514d5a (commit before pull)
)
add_test(NAME FilesToolsTests COMMAND CircuitGenGenerator_test_FilesToolsTests)

# Test SettingsTests
add_executable(CircuitGenGenerator_test_SettingsTests src/settings/SettingsTests.cpp ${NEW_SOURCES})

target_link_libraries(CircuitGenGenerator_test_SettingsTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_compile_features(CircuitGenGenerator_test_SettingsTests PRIVATE cxx_std_17)
target_include_directories(
  CircuitGenGenerator_test_SettingsTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME SettingsTests COMMAND CircuitGenGenerator_test_SettingsTests)

# ---- End-of-file commands ----

add_folders(Test)
