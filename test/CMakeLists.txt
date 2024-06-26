cmake_minimum_required(VERSION 3.14)

project(CircuitGenGeneratorTests LANGUAGES CXX)


include(ExternalProject)
include(FetchContent)

# Get googletest
# FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY https://github.com/google/googletest
#   GIT_TAG v1.14.0
# )

# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

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

add_executable(CircuitGenGenerator_test_AuxiliaryMethodsTests src/additional/AuxiliaryMethodsTests.cpp)

target_link_libraries(CircuitGenGenerator_test_AuxiliaryMethodsTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(CircuitGenGenerator_test_AuxiliaryMethodsTests 
  PRIVATE CircuitGenGenerator::CircuitGenGenerator CircuitGenGraph::CircuitGenGraph)

target_compile_features(CircuitGenGenerator_test_AuxiliaryMethodsTests PRIVATE cxx_std_17)
target_include_directories(
  CircuitGenGenerator_test_AuxiliaryMethodsTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME AuxiliaryMethodsTests COMMAND CircuitGenGenerator_test_AuxiliaryMethodsTests)

# Test FilesToolsTests
add_executable(CircuitGenGenerator_test_FilesToolsTests src/additional/filesTools/FilesToolsTests.cpp)

target_link_libraries(CircuitGenGenerator_test_FilesToolsTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(CircuitGenGenerator_test_FilesToolsTests PRIVATE 
PRIVATE CircuitGenGenerator::CircuitGenGenerator CircuitGenGraph::CircuitGenGraph)

target_include_directories(
  CircuitGenGenerator_test_FilesToolsTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME FilesToolsTests COMMAND CircuitGenGenerator_test_FilesToolsTests)

# Test TruthTableTests
add_executable(CircuitGenGenerator_test_TruthTableTests src/baseStructures/truthTable/TruthTableTests.cpp)

target_link_libraries(CircuitGenGenerator_test_TruthTableTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(CircuitGenGenerator_test_TruthTableTests PRIVATE 
PRIVATE CircuitGenGenerator::CircuitGenGenerator CircuitGenGraph::CircuitGenGraph)

target_include_directories(
  CircuitGenGenerator_test_TruthTableTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME TruthTableTests COMMAND CircuitGenGenerator_test_TruthTableTests)

# # Test CircuitTests
# add_executable(CircuitGenGenerator_test_CircuitTests src/circuit/CircuitTests.cpp)

# target_link_libraries(CircuitGenGenerator_test_CircuitTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
# target_compile_features(CircuitGenGenerator_test_CircuitTests PRIVATE cxx_std_17)
# target_include_directories(
#  CircuitGenGenerator_test_CircuitTests ${warning_guard}
#    PUBLIC
#    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
# )
# add_test(NAME CircuitTests COMMAND CircuitGenGenerator_test_CircuitTests)

# Test DataBaseGeneratorTests
add_executable(CircuitGenGenerator_test_DataBaseGeneratorTests src/database/DataBaseGeneratorTests.cpp)

target_link_libraries(CircuitGenGenerator_test_DataBaseGeneratorTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(CircuitGenGenerator_test_DataBaseGeneratorTests 
  PRIVATE CircuitGenGenerator::CircuitGenGenerator CircuitGenGraph::CircuitGenGraph)
target_include_directories(
 CircuitGenGenerator_test_DataBaseGeneratorTests ${warning_guard}
   PUBLIC
   "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME DataBaseGeneratorsTests COMMAND CircuitGenGenerator_test_DataBaseGeneratorTests)

# Test SimpleGeneratorsTests
add_executable(CircuitGenGenerator_test_SimpleGeneratorsTests src/generators/simple/SimpleGeneratorsTests.cpp)

target_link_libraries(CircuitGenGenerator_test_SimpleGeneratorsTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(CircuitGenGenerator_test_SimpleGeneratorsTests 
  PRIVATE CircuitGenGenerator::CircuitGenGenerator CircuitGenGraph::CircuitGenGraph)

target_include_directories(
 CircuitGenGenerator_test_SimpleGeneratorsTests ${warning_guard}
   PUBLIC
   "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"  
)
add_test(NAME SimpleGeneratorsTests COMMAND CircuitGenGenerator_test_SimpleGeneratorsTests)

# Test SettingsTests
add_executable(CircuitGenGenerator_test_SettingsTests src/settings/SettingsTests.cpp)

target_link_libraries(CircuitGenGenerator_test_SettingsTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(CircuitGenGenerator_test_SettingsTests 
  PRIVATE CircuitGenGenerator::CircuitGenGenerator CircuitGenGraph::CircuitGenGraph)

target_include_directories(
  CircuitGenGenerator_test_SettingsTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME SettingsTests COMMAND CircuitGenGenerator_test_SettingsTests)

# Test MutationParametersTests
add_executable(CircuitGenGenerator_test_MutationParametersTests src/generators/Genetic/Mutations/MutationParametersTests.cpp)

target_link_libraries(CircuitGenGenerator_test_MutationParametersTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(CircuitGenGenerator_test_MutationParametersTests 
  PRIVATE CircuitGenGenerator::CircuitGenGenerator CircuitGenGraph::CircuitGenGraph)

target_include_directories(
  CircuitGenGenerator_test_MutationParametersTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME MutationParametersTests COMMAND CircuitGenGenerator_test_MutationParametersTests)

# Test GeneticParametersTests
add_executable(CircuitGenGenerator_test_GeneticParametersTests src/generators/Genetic/GeneticParametersTests.cpp)

target_link_libraries(CircuitGenGenerator_test_GeneticParametersTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(CircuitGenGenerator_test_GeneticParametersTests 
  PRIVATE CircuitGenGenerator::CircuitGenGenerator CircuitGenGraph::CircuitGenGraph)

target_include_directories(
  CircuitGenGenerator_test_GeneticParametersTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME GeneticParametersTests COMMAND CircuitGenGenerator_test_GeneticParametersTests)

# Test MutationTruthTableTests
add_executable(CircuitGenGenerator_test_MutationTruthTableTests src/generators/Genetic/Mutations/MutationTruthTableTests.cpp)

target_link_libraries(CircuitGenGenerator_test_MutationTruthTableTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(CircuitGenGenerator_test_MutationTruthTableTests 
  PRIVATE CircuitGenGenerator::CircuitGenGenerator CircuitGenGraph::CircuitGenGraph)

target_include_directories(
  CircuitGenGenerator_test_MutationTruthTableTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME MutationTruthTableTests COMMAND CircuitGenGenerator_test_MutationTruthTableTests)

# Test ParentsParametersTests
add_executable(CircuitGenGenerator_test_ParentsParametersTests src/generators/Genetic/Parents/ParentsParametersTests.cpp)

target_link_libraries(CircuitGenGenerator_test_ParentsParametersTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(CircuitGenGenerator_test_ParentsParametersTests 
  PRIVATE CircuitGenGenerator::CircuitGenGenerator CircuitGenGraph::CircuitGenGraph)

target_include_directories(
  CircuitGenGenerator_test_ParentsParametersTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME ParentsParametersTests COMMAND CircuitGenGenerator_test_ParentsParametersTests)

# Test ParentsTruthTableTests
add_executable(CircuitGenGenerator_test_ParentsTruthTableTests src/generators/Genetic/Parents/ParentsTruthTableTests.cpp)

target_link_libraries(CircuitGenGenerator_test_ParentsTruthTableTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(CircuitGenGenerator_test_ParentsTruthTableTests 
  PRIVATE CircuitGenGenerator::CircuitGenGenerator CircuitGenGraph::CircuitGenGraph)

target_include_directories(
  CircuitGenGenerator_test_ParentsTruthTableTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME ParentsTruthTableTests COMMAND CircuitGenGenerator_test_ParentsTruthTableTests)

# Test RecombinationsTests
add_executable(CircuitGenGenerator_test_RecombinationsTests src/generators/Genetic/Recombination/RecombinationsTests.cpp)

target_link_libraries(CircuitGenGenerator_test_RecombinationsTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(CircuitGenGenerator_test_RecombinationsTests 
  PRIVATE CircuitGenGenerator::CircuitGenGenerator CircuitGenGraph::CircuitGenGraph)

target_include_directories(
  CircuitGenGenerator_test_RecombinationsTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME RecombinationsTests COMMAND CircuitGenGenerator_test_RecombinationsTests)

# Test RecombinationParametersTests
add_executable(CircuitGenGenerator_test_RecombinationParametersTests src/generators/Genetic/Recombination/RecombinationParametersTests.cpp)

target_link_libraries(CircuitGenGenerator_test_RecombinationParametersTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(CircuitGenGenerator_test_RecombinationParametersTests 
  PRIVATE CircuitGenGenerator::CircuitGenGenerator CircuitGenGraph::CircuitGenGraph)

target_include_directories(
  CircuitGenGenerator_test_RecombinationParametersTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME RecombinationParametersTests COMMAND CircuitGenGenerator_test_RecombinationParametersTests)

# Test RecombinationTruthTableTests
add_executable(CircuitGenGenerator_test_RecombinationTruthTableTests src/generators/Genetic/Recombination/RecombinationTruthTableTests.cpp)

target_link_libraries(CircuitGenGenerator_test_RecombinationTruthTableTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(CircuitGenGenerator_test_RecombinationTruthTableTests 
  PRIVATE CircuitGenGenerator::CircuitGenGenerator CircuitGenGraph::CircuitGenGraph)

target_include_directories(
  CircuitGenGenerator_test_RecombinationTruthTableTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME RecombinationTruthTableTests COMMAND CircuitGenGenerator_test_RecombinationTruthTableTests)
# ---- End-of-file commands ----

add_folders(Test)
