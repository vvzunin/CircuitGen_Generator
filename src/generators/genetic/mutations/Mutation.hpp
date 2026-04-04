#pragma once

#include "generators/genetic/chromosome/type/ChromosomeType.hpp"
#include "generators/genetic/mutations/parameters/MutationParameters.hpp"
#include "generators/genetic/mutations/truthTable/MutationTruthTable.hpp"
#include <vector>

namespace CG_Gen {

template<typename Type, typename ParametersType>
std::vector<ChromosomeType<Type, ParametersType>>
MutationType(MutationParameters i_mutationParameters,
             std::vector<ChromosomeType<Type, ParametersType>> i_population);
template<>
std::vector<ChromosomeType<TruthTable, TruthTableParameters>> MutationType(
    MutationParameters i_mutationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population);

} // namespace CG_Gen
