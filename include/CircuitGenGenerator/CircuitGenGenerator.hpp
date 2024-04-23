#pragma once

#include <string>

#include <CircuitGenGenerator/export.hpp>
#include <database/DataBaseGeneratorParameters.hpp>

namespace CircuitGenGenerator {
CIRCUITGENGENERATOR_EXPORT void runGenerationFromJson(std::string json_path);
CIRCUITGENGENERATOR_EXPORT void runGenerationFromDbgp(
    DataBaseGeneratorParameters dbgp,
    bool                        multithread           = false,
    bool                        create_id_directories = true
);
}  // namespace CircuitGenGenerator
