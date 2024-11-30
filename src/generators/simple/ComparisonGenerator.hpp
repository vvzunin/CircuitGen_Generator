#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class ComparisonGenerator : public SimpleGenerator {
public:
  ComparisonGenerator();
  ComparisonGenerator(uint_fast32_t i_seed);
  ComparisonGenerator(const GenerationParameters& i_param);

  GraphPtr generatorComparison(
      uint32_t i_bits,
      bool     compare0,
      bool     compare1,
      bool     compare2
  );
};