cmake_minimum_required(VERSION 3.14)

project(CircuitGenGeneratorExamples CXX)

include(../cmake/checks.cmake)
include(../cmake/folders.cmake)

if(PROJECT_IS_TOP_LEVEL)
  find_package(CircuitGenGenerator REQUIRED)
endif()

add_custom_target(run-examples)

function(add_example NAME)
  add_executable("${NAME}" "${NAME}.cpp")
  target_link_libraries("${NAME}" PRIVATE CircuitGenGenerator::CircuitGenGenerator)
  # target_compile_features("${NAME}" PRIVATE cxx_std_17)
  add_custom_target("run_${NAME}" COMMAND "${NAME}" VERBATIM)
  add_dependencies("run_${NAME}" "${NAME}")
  add_dependencies(run-examples "run_${NAME}")
endfunction()

# JSON path baked at configure time so examples work from any working directory.
function(add_json_example NAME JSON_RELATIVE)
  add_executable("${NAME}" "example_run_preset_json.cpp")
  target_link_libraries("${NAME}" PRIVATE CircuitGenGenerator::CircuitGenGenerator)
  set(_json_path "${CMAKE_CURRENT_SOURCE_DIR}/json/${JSON_RELATIVE}")
  target_compile_definitions("${NAME}" PRIVATE
                             "CIRCUITGEN_EXAMPLE_JSON_FILE=\"${_json_path}\"")
  add_custom_target("run_${NAME}" COMMAND "${NAME}" VERBATIM)
  add_dependencies("run_${NAME}" "${NAME}")
  add_dependencies(run-examples "run_${NAME}")
endfunction()

function(add_for_graph_example NAME JSON_RELATIVE)
  add_executable("${NAME}" "example_run_json_for_graph.cpp")
  target_link_libraries("${NAME}" PRIVATE CircuitGenGenerator::CircuitGenGenerator)
  set(_json_path "${CMAKE_CURRENT_SOURCE_DIR}/json/${JSON_RELATIVE}")
  target_compile_definitions("${NAME}" PRIVATE
                             "CIRCUITGEN_EXAMPLE_JSON_FILE=\"${_json_path}\"")
  add_custom_target("run_${NAME}" COMMAND "${NAME}" VERBATIM)
  add_dependencies("run_${NAME}" "${NAME}")
  add_dependencies(run-examples "run_${NAME}")
endfunction()

add_example(empty_example)
add_example(example_print_version)

add_json_example(example_run_comparison_json sampleComparison.json)
add_json_example(example_run_truth_table_json sampleTruthTable.json)
add_json_example(example_run_parity_json sampleParity.json)

add_for_graph_example(example_run_json_for_graph sampleTruthTable.json)

add_folders(Example)
