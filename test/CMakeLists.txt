cmake_minimum_required(VERSION 3.14)

project(CircuitGenGeneratorTests LANGUAGES CXX)

include(ExternalProject)
include(FetchContent)

FetchContent_Declare(
  gtest

  # Url for googletest download.
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(gtest)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

# ---- Tests ----

configure_file(
  ../easylogging++.conf
  easylogging++.conf
  COPYONLY
)

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

function(add_new_test name folders)
  add_executable(
    CircuitGenGenerator_test_${name}
    src/${folders}/${name}.cpp
  )

  target_link_libraries(
    CircuitGenGenerator_test_${name}
    PRIVATE
      GTest::gtest_main
      ${EXTERNAL_LIBS}
      CircuitGenGenerator::CircuitGenGenerator
      CircuitGenGraph::CircuitGenGraph
      easylogging++
  )

  target_compile_features(CircuitGenGenerator_test_${name} PRIVATE cxx_std_17)

  target_include_directories(
    CircuitGenGenerator_test_${name} ${warning_guard}
    PUBLIC
      "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
      "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
  )
  add_test(NAME ${name} COMMAND CircuitGenGenerator_test_${name})
endfunction()

add_new_test(AuxiliaryMethodsTests "additional")
add_new_test(FilesToolsTests "additional/filesTools")
add_new_test(TruthTableTests "baseStructures/truthTable")
# add_new_test(CircuitTests "circuit")
add_new_test(DataBaseGeneratorTests "database")
add_new_test(SimpleGeneratorsTests "generators/simple")
add_new_test(SettingsTests "settings")
add_new_test(GeneticParametersTests "generators/Genetic")
add_new_test(MutationParametersTests "generators/Genetic/Mutations")
add_new_test(MutationTruthTableTests "generators/Genetic/Mutations")
add_new_test(ParentsParametersTests "generators/Genetic/Parents")
add_new_test(ParentsTruthTableTests "generators/Genetic/Parents")
add_new_test(RecombinationsTests "generators/Genetic/Recombination")
add_new_test(RecombinationParametersTests "generators/Genetic/Recombination")
add_new_test(RecombinationTruthTableTests "generators/Genetic/Recombination")

add_folders(Test)