#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class ParityGenerator : public SimpleGenerator {
public:
  ParityGenerator();
  ParityGenerator(uint_fast32_t i_seed);
  ParityGenerator(const GenerationParameters& i_param);

  GraphPtr generatorParity(uint32_t i_bits);
};