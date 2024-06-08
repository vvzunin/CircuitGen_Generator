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

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

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
)
add_test(NAME AuxiliaryMethodsTests COMMAND CircuitGenGenerator_test_AuxiliaryMethodsTests)

# Test FilesToolsTests
add_executable(CircuitGenGenerator_test_FilesToolsTests src/additional/filesTools/FilesToolsTests.cpp ${NEW_SOURCES})

target_link_libraries(CircuitGenGenerator_test_FilesToolsTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_compile_features(CircuitGenGenerator_test_FilesToolsTests PRIVATE cxx_std_17)
target_include_directories(
  CircuitGenGenerator_test_FilesToolsTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME FilesToolsTests COMMAND CircuitGenGenerator_test_FilesToolsTests)

# Test GraphVertexConstantTests
add_executable(CircuitGenGenerator_test_GraphVertexConstantTests src/baseStructures/graph/GraphVertexConstantTests.cpp ${NEW_SOURCES})

target_link_libraries(CircuitGenGenerator_test_GraphVertexConstantTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_compile_features(CircuitGenGenerator_test_GraphVertexConstantTests PRIVATE cxx_std_17)
target_include_directories(
  CircuitGenGenerator_test_GraphVertexConstantTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME GraphVertexConstantTests COMMAND CircuitGenGenerator_test_GraphVertexConstantTests)

# Test GraphVertexGatesTests
add_executable(CircuitGenGenerator_test_GraphVertexGatesTests src/baseStructures/graph/GraphVertexGatesTests.cpp ${NEW_SOURCES})

target_link_libraries(CircuitGenGenerator_test_GraphVertexGatesTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_compile_features(CircuitGenGenerator_test_GraphVertexGatesTests PRIVATE cxx_std_17)
target_include_directories(
 CircuitGenGenerator_test_GraphVertexGatesTests ${warning_guard}
   PUBLIC
   "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME GraphVertexGatesTests COMMAND CircuitGenGenerator_test_GraphVertexGatesTests)

# Test GraphVertexInputTests
add_executable(CircuitGenGenerator_test_GraphVertexInputTests src/baseStructures/graph/GraphVertexInputTests.cpp ${NEW_SOURCES})

target_link_libraries(CircuitGenGenerator_test_GraphVertexInputTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_compile_features(CircuitGenGenerator_test_GraphVertexInputTests PRIVATE cxx_std_17)
target_include_directories(
 CircuitGenGenerator_test_GraphVertexInputTests ${warning_guard}
   PUBLIC
   "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME GraphVertexInputTests COMMAND CircuitGenGenerator_test_GraphVertexInputTests)

# Test GraphVertexOutputTests
add_executable(CircuitGenGenerator_test_GraphVertexOutputTests src/baseStructures/graph/GraphVertexOutputTests.cpp ${NEW_SOURCES})

target_link_libraries(CircuitGenGenerator_test_GraphVertexOutputTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_compile_features(CircuitGenGenerator_test_GraphVertexOutputTests PRIVATE cxx_std_17)
target_include_directories(
  CircuitGenGenerator_test_GraphVertexOutputTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME GraphVertexOutputTests COMMAND CircuitGenGenerator_test_GraphVertexOutputTests)

# Test GraphVertexSubGraphTests
add_executable(CircuitGenGenerator_test_GraphVertexSubGraphTests src/baseStructures/graph/GraphVertexSubGraphTests.cpp ${NEW_SOURCES})

target_link_libraries(CircuitGenGenerator_test_GraphVertexSubGraphTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_compile_features(CircuitGenGenerator_test_GraphVertexSubGraphTests PRIVATE cxx_std_17)
target_include_directories(
  CircuitGenGenerator_test_GraphVertexSubGraphTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME GraphVertexSubGraphTests COMMAND CircuitGenGenerator_test_GraphVertexSubGraphTests)


# # Test OrientedGrahTests
# add_executable(CircuitGenGenerator_test_OrientedGraphTests src/baseStructures/graph/OrientedGraphTests.cpp ${NEW_SOURCES})

# target_link_libraries(CircuitGenGenerator_test_OrientedGraphTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
# target_compile_features(CircuitGenGenerator_test_OrientedGraphTests PRIVATE cxx_std_17)
# target_include_directories(
#   CircuitGenGenerator_test_OrientedGraphTests ${warning_guard}
#     PUBLIC
#     "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
# )
# add_test(NAME OrientedGraphTests COMMAND CircuitGenGenerator_test_OrientedGraphTests)

# Test TruthTableTests
add_executable(CircuitGenGenerator_test_TruthTableTests src/baseStructures/truthTable/TruthTableTests.cpp ${NEW_SOURCES})

target_link_libraries(CircuitGenGenerator_test_TruthTableTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_compile_features(CircuitGenGenerator_test_TruthTableTests PRIVATE cxx_std_17)
target_include_directories(
  CircuitGenGenerator_test_TruthTableTests ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME TruthTableTests COMMAND CircuitGenGenerator_test_TruthTableTests)

# # Test CircuitTests
# add_executable(CircuitGenGenerator_test_CircuitTests src/circuit/CircuitTests.cpp ${NEW_SOURCES})

# target_link_libraries(CircuitGenGenerator_test_CircuitTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
# target_compile_features(CircuitGenGenerator_test_CircuitTests PRIVATE cxx_std_17)
# target_include_directories(
#  CircuitGenGenerator_test_CircuitTests ${warning_guard}
#    PUBLIC
#    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
# )
# add_test(NAME CircuitTests COMMAND CircuitGenGenerator_test_CircuitTests)

# Test DataBaseGeneratorTests
add_executable(CircuitGenGenerator_test_DataBaseGeneratorTests src/database/DataBaseGeneratorTests.cpp ${NEW_SOURCES})

target_link_libraries(CircuitGenGenerator_test_DataBaseGeneratorTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_compile_features(CircuitGenGenerator_test_DataBaseGeneratorTests PRIVATE cxx_std_17)
target_include_directories(
 CircuitGenGenerator_test_DataBaseGeneratorTests ${warning_guard}
   PUBLIC
   "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)
add_test(NAME DataBaseGeneratorsTests COMMAND CircuitGenGenerator_test_DataBaseGeneratorTests)

# Test SimpleGeneratorsTests
add_executable(CircuitGenGenerator_test_SimpleGeneratorsTests src/generators/simple/SimpleGeneratorsTests.cpp ${NEW_SOURCES})

target_link_libraries(CircuitGenGenerator_test_SimpleGeneratorsTests PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_compile_features(CircuitGenGenerator_test_SimpleGeneratorsTests PRIVATE cxx_std_17)
target_include_directories(
 CircuitGenGenerator_test_SimpleGeneratorsTests ${warning_guard}
   PUBLIC
   "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"  
)
add_test(NAME SimpleGeneratorsTests COMMAND CircuitGenGenerator_test_SimpleGeneratorsTests)

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
