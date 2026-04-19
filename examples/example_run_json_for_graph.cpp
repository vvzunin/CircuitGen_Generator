/**
 * @file example_run_json_for_graph.cpp
 * @brief runGenerationFromJsonForGraph: пакеты схем в памяти (путь к JSON задаётся
 *        CMake: CIRCUITGEN_EXAMPLE_JSON_FILE).
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
  const auto batches =
      CircuitGenGenerator::runGenerationFromJsonForGraph(jsonPath);
  std::cout << "Batches: " << batches.size() << '\n';
  for (const auto &batch: batches) {
    std::cout << "  id=" << batch.first
              << " graphs=" << batch.second.size() << '\n';
  }
  return 0;
}
