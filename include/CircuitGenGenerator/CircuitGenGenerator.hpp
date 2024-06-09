#pragma once

#include <string>
#include <vector>

#include <CircuitGenGenerator/export.hpp>

#include "OrientedGraph.hpp"

namespace CircuitGenGenerator {
// TODO add some other export functions
// to return void and call function, giving there a graph
// and return just void

CIRCUITGENGENERATOR_EXPORT
std::vector<std::pair<std::string, std::vector<GraphPtr>>>
    runGenerationFromJsonForGraph(std::string json_path);
CIRCUITGENGENERATOR_EXPORT
std::vector<std::pair<std::string, std::vector<std::string>>>
    runGenerationFromJsonForPath(std::string json_path);
CIRCUITGENGENERATOR_EXPORT void runGenerationFromJson(std::string json_path);
}  // namespace CircuitGenGenerator
