#pragma once

#include "baseStructures/truthTable/TruthTable.hpp"
#include "generators/genetic/chromosome/type/ChromosomeType.hpp"
#include "generators/genetic/mutations/truthTable/MutationTruthTable.hpp"
#include "generators/genetic/parents/Parents.hpp"
#include "generators/genetic/parents/parameters/ParentsParameters.hpp"
#include "generators/genetic/recombination/parameters/RecombinationParameters.hpp"
#include <ctime>
#include <vector>

namespace CG_Gen::RecombinationsTruthTable {
std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
RecombinationCrossingEachExitInTurnMany(
    RecombinationParameters i_recombinationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population);

std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
RecombinationCrossingUniform(
    RecombinationParameters i_recombinationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population);

std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
RecombinationCrossingTriadic(
    RecombinationParameters i_recombinationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population);

std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
RecombinationCrossingReducedReplacement(
    RecombinationParameters i_recombinationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population);

std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
RecombinationCrossingShuffling(
    RecombinationParameters i_recombinationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population);
// namespace end
} // namespace CG_Gen::RecombinationsTruthTable
