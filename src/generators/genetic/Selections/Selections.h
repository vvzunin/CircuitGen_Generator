#pragma once

#include <vector>

#include "SelectionParameters.h"

#include "../ChromosomeType.h"

template<typename Type, typename ParametersType>
std::vector<ChromosomeType<Type, ParametersType>> SelectionType
(
  SelectionParameters i_selectionParameters,
  std::vector<ChromosomeType<Type, ParametersType>> i_population
);
