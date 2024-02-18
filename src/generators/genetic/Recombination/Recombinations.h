#pragma once

#include <vector>

#include "RecombinationParameters.h"

#include "../ChromosomeType.h"

template<typename Type, typename ParametersType>
std::vector<ChromosomeType<Type, ParametersType>> RecombinationType
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChromosomeType<Type, ParametersType>> i_population
);
