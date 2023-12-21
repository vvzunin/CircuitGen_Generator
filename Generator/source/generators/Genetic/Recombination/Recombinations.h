#pragma once

#include <vector>

#include "RecombinationParameters.h"

#include "../ChronosomeType.h"

template<typename Type, typename ParametersType>
std::vector<ChronosomeType<Type, ParametersType>> RecombinationType
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChronosomeType<Type, ParametersType>> i_population
);
