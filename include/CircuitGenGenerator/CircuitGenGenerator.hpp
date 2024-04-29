#pragma once

#include <string>
#include <vector>

#include <CircuitGenGenerator/export.hpp>
#include <database/DataBaseGenerator.hpp>

namespace CircuitGenGenerator {
CIRCUITGENGENERATOR_EXPORT std::vector<Result> runGenerationFromJson(std::string json_path);
}
