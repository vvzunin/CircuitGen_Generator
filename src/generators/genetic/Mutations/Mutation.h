#pragma once

#include <vector>

#include "MutationParameters.h"
#include "../ChromosomeType.h"

template<typename Type, typename ParametersType>
std::vector<ChromosomeType<Type, ParametersType>> MutationType(
  MutationParameters i_mutationParameters,
  std::vector<ChromosomeType<Type, ParametersType>> i_population
);
