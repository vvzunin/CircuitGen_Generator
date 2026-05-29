cmake_minimum_required(VERSION 3.14)

project(CircuitGenGeneratorTests LANGUAGES CXX)

include(ExternalProject)
include(FetchContent)

FetchContent_Declare(
  gtest

  # Url for googletest download.
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG v1.17.0
)
# Do not pollute product install with test framework artifacts.
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(INSTALL_GMOCK OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)
add_folders(Libraries gtest)

include(../cmake/checks.cmake)
include(../cmake/folders.cmake)

option(CircuitGenGenerator_TESTS_ENABLE_ASAN "Enable AddressSanitizer for tests" ON)
if(CircuitGenGenerator_TESTS_ENABLE_ASAN AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
endif()

# ---- Tests ----

configure_file(
  ../easylogging++.conf
  easylogging++.conf
  COPYONLY
)

function(add_new_test name folders targets)
  set(test_target "CircuitGenGenerator_test_${name}")
  add_executable(
    ${test_target}
    src/${folders}/${name}.cpp
  )

  target_link_libraries(
    ${test_target}
    PRIVATE
      GTest::gtest_main
      Threads::Threads
      # CircuitGenGenerator::CircuitGenGenerator
      CircuitGenGraph::CircuitGenGraph
      easylogging++

      ${targets}
  )

  # target_compile_features(${test_target} PRIVATE cxx_std_17)

  target_include_directories(
    ${test_target} ${warning_guard}
    PUBLIC
      "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
      "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
  )
  add_test(NAME ${name} COMMAND ${test_target})
endfunction()

function (add_files pathFrom)
  if (ARGC GREATER_EQUAL 2)
    set(pathTo ${ARGV1})
  else()
    set(pathTo ${pathFrom})
  endif()
  configure_file(
    ${pathFrom}
    ${pathTo}
    COPYONLY
  )

endfunction()

add_new_test(AuxiliaryMethodsTests        "additional/auxiliaryMethods"                 auxiliaryMethods)
add_files(src/additional/auxiliaryMethods/testData/one_line_file.txt)
add_files(src/additional/auxiliaryMethods/testData/test_empty_file.txt)
add_files(src/additional/auxiliaryMethods/testData/test_one_line_with_tab.txt)
add_files(src/additional/auxiliaryMethods/testData/test_two_line_with_tab.txt)
add_files(src/additional/auxiliaryMethods/testData/test_two_lines.txt)

add_new_test(FilesToolsTests              "additional/filesTools"                       filesTools)
add_new_test(TruthTableTests              "baseStructures/truthTable"                   truthTable)
add_new_test(CircuitTests                 "circuit"                                     circuit)
add_new_test(DataBaseGeneratorTests       "database"                                    dataBase)
add_new_test(MutationParametersTests      "generators/genetic/mutations/parameters"     geneticMutationParameters)
add_new_test(MutationTruthTableTests      "generators/genetic/mutations/truthTable"     geneticMutationTruthTable)
add_new_test(GeneticParametersTests       "generators/genetic/parameters"               geneticParameters)
add_new_test(ParentsTruthTableTests       "generators/genetic/parents"                  geneticParents)
add_new_test(ParentsParametersTests       "generators/genetic/parents/parameters"       geneticParents;geneticParentsParameters)
add_new_test(RecombinationsTests          "generators/genetic/recombination"            geneticRecombination)
add_new_test(RecombinationParametersTests "generators/genetic/recombination/parameters" geneticRecombinationParameters)
add_new_test(RecombinationTruthTableTests "generators/genetic/recombination/truthTable" geneticRecombinationsTruthTable)
add_new_test(SimpleGeneratorsTests        "generators/simple"                           simpleGenerators)
add_new_test(SettingsTests                "settings"                                    settings)
add_new_test(TempProjectDirTests          "additional/tempProjectDir"                   tempProjectDir)
add_new_test(ChiselProjectTests           "chiselModule/chiselProject"                  chiselProject)
add_files(src/chiselModule/testData_ChiselModule/no_main.scala)
add_files(src/chiselModule/testData_ChiselModule/with_main.scala)
add_files(src/additional/tempProjectDir/testData/test_empty.txt)
add_files(src/additional/tempProjectDir/testData/test_not_empty.txt)

add_folders(Test)