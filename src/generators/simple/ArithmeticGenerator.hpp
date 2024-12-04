#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class ArithmeticGenerator : public SimpleGenerator {
public:
  ArithmeticGenerator();
  ArithmeticGenerator(uint_fast32_t i_seed);
  ArithmeticGenerator(const GenerationParameters& i_param);

  GraphPtr generatorSummator(
      uint32_t i_bits,
      bool     i_overflowIn,
      bool     i_overflowOut,
      bool     i_minus
  );

  GraphPtr generatorSubtractor(
      uint32_t i_bits,
      bool     i_overflowIn,
      bool     i_overflowOut,
      bool     i_sub
  );

  GraphPtr generatorMultiplier(uint32_t i_bits);

  GraphPtr generatorSummator(const GenerationParameters &i_param);

  GraphPtr generatorSubtractor(const GenerationParameters &i_param);

  GraphPtr generatorMultiplier(const GenerationParameters &i_param);

  GraphPtr generatorSummator();

  GraphPtr generatorSubtractor();

  GraphPtr generatorMultiplier();
};
