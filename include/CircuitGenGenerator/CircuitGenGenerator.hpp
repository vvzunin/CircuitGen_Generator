#pragma once

#include <CircuitGenGenerator/export.hpp>
#include <CircuitGenGenerator/info.hpp>
#include <memory>
#include <string>
#include <vector>

class OrientedGraph;

namespace CircuitGenGenerator {

CIRCUITGENGENERATOR_EXPORT
std::vector<std::pair<std::string, std::vector<std::shared_ptr<OrientedGraph>>>>
runGenerationFromJsonForGraph(std::string json_path);
CIRCUITGENGENERATOR_EXPORT
std::vector<std::pair<std::string, std::vector<std::string>>>
runGenerationFromJsonForPath(std::string json_path);
CIRCUITGENGENERATOR_EXPORT void runGenerationFromJson(std::string json_path);
CIRCUITGENGENERATOR_EXPORT std::string getVersion() {
  return CircuitGen_Generator_version;
}

} // namespace CircuitGenGenerator
