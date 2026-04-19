/**
 * @file example_run_preset_json.cpp
 * @brief Запуск генерации из JSON (путь задаётся CMake: CIRCUITGEN_EXAMPLE_JSON_FILE).
 */
#include <CircuitGenGenerator/CircuitGenGenerator.hpp>
#include <easyloggingpp/easylogging++.h>
#include <iostream>
#include <string>

#ifndef CIRCUITGEN_EXAMPLE_JSON_FILE
#  error CIRCUITGEN_EXAMPLE_JSON_FILE must be set by CMake for this target
#endif

INITIALIZE_EASYLOGGINGPP

auto main() -> int {
  const std::string jsonPath{CIRCUITGEN_EXAMPLE_JSON_FILE};
  std::cout << "Running generation from: " << jsonPath << '\n';
  CircuitGenGenerator::runGenerationFromJson(jsonPath);
  return 0;
}
