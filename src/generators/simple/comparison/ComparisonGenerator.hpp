#pragma once
#include <generators/simple/simple/SimpleGenerator.hpp>

namespace CG_Gen {

using namespace CG_Graph;

class ComparisonGenerator : public SimpleGenerator {
public:
  ComparisonGenerator();
  ComparisonGenerator(uint_fast32_t i_seed);
  ComparisonGenerator(const GenerationParameters &i_param);

  GraphPtr generatorComparison(uint32_t i_bits, bool compare0, bool compare1,
                               bool compare2);
  GraphPtr generatorComparison(const GenerationParameters &i_param);
  GraphPtr generatorComparison();
};

} // namespace CG_Gen
