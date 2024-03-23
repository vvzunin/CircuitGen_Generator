#pragma once

#include <vector>

#include "RecombinationParameters.h"

#include "../ChronosomeType.h"

/// @brief RecombinationType TO DO: Description!!!
/// @param i_recombinationParameters An object of the Recombination
/// Parameters class that contains information about the type of recombination***
/// 
/// @param i_population vector std::vector<ChronosomeType<Type, Parameters Type>>,
/// containing a population of chromosomes. Each element of the vector represents
/// a chromosome of a certain type Type with the corresponding ParametersType
/// parameters.
/// @return vector std::vector<ChronosomeType<Type, Parameters Type>>, which
/// represents a new population of chromosomes after applying the selected
/// recombination method
/// */

template<typename Type, typename ParametersType>
std::vector<ChronosomeType<Type, ParametersType>> RecombinationType
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChronosomeType<Type, ParametersType>> i_population
);
