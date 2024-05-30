#pragma once

#include <vector>

#include "RecombinationParameters.hpp"
#include "../ChronosomeType.hpp"
#include "../Parents/ParentsParameters.hpp"
#include <baseStructures/truthTable/TruthTable.hpp>
#include "../Parents/Parents.hpp"
#include "../Mutations/MutationTruthTable.hpp"
#include <ctime>

namespace RecombinationsTruthTable
{
std::vector<ChronosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingEachExitInTurnMany
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingUniform
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingTriadic
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingReducedReplacement
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingShuffling
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);
//namespace end
}