#pragma once

#include <ctime>
#include <vector>

#include <baseStructures/truthTable/TruthTable.hpp>

#include "../ChromosomeType.hpp"
#include "../Mutations/MutationTruthTable.hpp"
#include "../Parents/Parents.hpp"
#include "../Parents/ParentsParameters.hpp"
#include "RecombinationParameters.hpp"

namespace RecombinationsTruthTable {
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
} // namespace RecombinationsTruthTable