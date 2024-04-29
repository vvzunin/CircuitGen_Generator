#pragma once

#include <string>

#include <CircuitGenGenerator/export.hpp>
#include <database/DataBaseGenerator.hpp>

namespace CircuitGenGenerator {
CIRCUITGENGENERATOR_EXPORT Result runGenerationFromJson(std::string json_path);
}
