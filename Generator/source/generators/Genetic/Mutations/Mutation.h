#pragma once

#include <vector>

#include "MutationParameters.h"
#include "../ChronosomeType.h"

/// @brief MutationType TO DO:
/// @param i_mutationParameters Mutation parameters, which may include information about the probability of mutation, type of mutation, and other settings
/// @param i_population The vector of individuals on which the mutation will be performed
/// @return std::vector<ChronosomeType<Type, Parameters Type>>: Mutated population of individuals
/// */

template<typename Type, typename ParametersType>
std::vector<ChronosomeType<Type, ParametersType>> MutationType(
  MutationParameters i_mutationParameters,
  std::vector<ChronosomeType<Type, ParametersType>> i_population
);
