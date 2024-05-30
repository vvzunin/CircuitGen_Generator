#pragma once

#include <ctime>
#include <vector>

#include <baseStructures/truthTable/TruthTable.hpp>

#include "../ChronosomeType.hpp"
#include "../Mutations/MutationTruthTable.hpp"
#include "../Parents/Parents.hpp"
#include "../Parents/ParentsParameters.hpp"
#include "RecombinationParameters.hpp"

namespace RecombinationsTruthTable {
std::vector<ChronosomeType<TruthTable, TruthTableParameters>>
    RecombinationCrossingEachExitInTurnMany(
        RecombinationParameters i_recombinationParameters,
        std::vector<ChronosomeType<TruthTable, TruthTableParameters>>
            i_population
    );

std::vector<ChronosomeType<TruthTable, TruthTableParameters>>
    RecombinationCrossingUniform(
        RecombinationParameters i_recombinationParameters,
        std::vector<ChronosomeType<TruthTable, TruthTableParameters>>
            i_population
    );

std::vector<ChronosomeType<TruthTable, TruthTableParameters>>
    RecombinationCrossingTriadic(
        RecombinationParameters i_recombinationParameters,
        std::vector<ChronosomeType<TruthTable, TruthTableParameters>>
            i_population
    );

std::vector<ChronosomeType<TruthTable, TruthTableParameters>>
    RecombinationCrossingReducedReplacement(
        RecombinationParameters i_recombinationParameters,
        std::vector<ChronosomeType<TruthTable, TruthTableParameters>>
            i_population
    );

std::vector<ChronosomeType<TruthTable, TruthTableParameters>>
    RecombinationCrossingShuffling(
        RecombinationParameters i_recombinationParameters,
        std::vector<ChronosomeType<TruthTable, TruthTableParameters>>
            i_population
    );
// namespace end
}  // namespace RecombinationsTruthTable