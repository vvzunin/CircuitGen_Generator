#pragma once

#include <vector>

#include "../ChronosomeType.hpp"
#include "MutationParameters.hpp"
#include "MutationTruthTable.hpp"

template<typename Type, typename ParametersType>
std::vector<ChronosomeType<Type, ParametersType>> MutationType(
    MutationParameters                                i_mutationParameters,
    std::vector<ChronosomeType<Type, ParametersType>> i_population
);
template<>
std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationType(
    MutationParameters i_mutationParameters,
    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);
