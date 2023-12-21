#pragma once

#include <vector>

#include "SelectionParameters.h"

#include "../ChronosomeType.h"

template<typename Type, typename ParametersType>
std::vector<ChronosomeType<Type, ParametersType>> SelectionType
(
  SelectionParameters i_selectionParameters,
  std::vector<ChronosomeType<Type, ParametersType>> i_population
);
