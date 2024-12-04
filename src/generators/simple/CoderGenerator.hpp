#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class CoderGenerator : public SimpleGenerator {
public:
  CoderGenerator();
  CoderGenerator(uint_fast32_t i_seed);
  CoderGenerator(const GenerationParameters& i_param);

  GraphPtr generatorEncoder(uint32_t i_bits);
  GraphPtr generatorDecoder(uint32_t i_bits);

  GraphPtr generatorEncoder(const GenerationParameters &i_param);
  GraphPtr generatorDecoder(const GenerationParameters &i_param);

  GraphPtr generatorEncoder();
  GraphPtr generatorDecoder();
};
