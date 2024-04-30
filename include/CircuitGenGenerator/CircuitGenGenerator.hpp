#pragma once

#include <string>
#include <vector>

#include <CircuitGenGenerator/export.hpp>
#include <CircuitGenGenerator/OrientedGraph.hpp>

namespace CircuitGenGenerator {
CIRCUITGENGENERATOR_EXPORT std::vector<std::pair<std::string, std::vector<GraphPtr>>>
                           runGenerationFromJson(std::string json_path);
}
