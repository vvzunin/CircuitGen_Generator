#pragma once

#include <memory>
#include <string>
#include <vector>

#include <CircuitGenGenerator/export.hpp>

class OrientedGraph;

namespace CircuitGenGenerator {

CIRCUITGENGENERATOR_EXPORT
std::vector<std::pair<std::string, std::vector<std::shared_ptr<OrientedGraph>>>>
    runGenerationFromJsonForGraph(std::string json_path);
CIRCUITGENGENERATOR_EXPORT
std::vector<std::pair<std::string, std::vector<std::string>>>
    runGenerationFromJsonForPath(std::string json_path);
CIRCUITGENGENERATOR_EXPORT void runGenerationFromJson(std::string json_path);

}  // namespace CircuitGenGenerator
