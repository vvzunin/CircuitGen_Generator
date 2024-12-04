#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class NumOperationsGenerator : public SimpleGenerator {
public:
  NumOperationsGenerator();
  NumOperationsGenerator(uint_fast32_t i_seed);
  NumOperationsGenerator(const GenerationParameters& i_param);

  GraphPtr generatorNumOperation(
      uint32_t                 i_input,
      uint32_t                 i_output,
      std::map<Gates, int32_t> i_logicOper,
      bool                     i_leaveEmptyOut = true
  );

  GraphPtr generatorNumOperation(const GenerationParameters &i_param);
  GraphPtr generatorNumOperation();
};