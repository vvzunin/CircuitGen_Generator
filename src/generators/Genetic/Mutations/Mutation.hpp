#pragma once

#include <vector>

#include "../ChromosomeType.hpp"
#include "MutationParameters.hpp"
#include "MutationTruthTable.hpp"

template<typename Type, typename ParametersType>
std::vector<ChromosomeType<Type, ParametersType>>
MutationType(MutationParameters i_mutationParameters,
             std::vector<ChromosomeType<Type, ParametersType>> i_population);
template<>
std::vector<ChromosomeType<TruthTable, TruthTableParameters>> MutationType(
    MutationParameters i_mutationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population);
