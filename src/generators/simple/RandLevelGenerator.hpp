#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class RandLevelGenerator : public SimpleGenerator {
public:
  RandLevelGenerator();
  RandLevelGenerator(uint_fast32_t i_seed);
  RandLevelGenerator(const GenerationParameters& i_param);

  GraphPtr generatorRandLevel(
      uint32_t i_minLevel,
      uint32_t i_maxLevel,
      uint32_t i_minElements,
      uint32_t i_maxElements,
      uint32_t i_inputs,
      uint32_t i_outputs
  );

  GraphPtr generatorRandLevelExperimental(
        uint32_t i_minLevel,
        uint32_t i_maxLevel,
        uint32_t i_minElements,
        uint32_t i_maxElements,
        uint32_t i_inputs,
        uint32_t i_outputs
    );
};
