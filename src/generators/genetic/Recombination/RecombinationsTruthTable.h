#pragma once

#include <vector>

#include "RecombinationParameters.h"
#include "../ChromosomeType.h"
#include "../Parents/ParentsParameters.h"
#include "../../TruthTable.h"

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingEachExitInTurnMany
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingUniform
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingTriadic
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingReducedReplacement
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingShuffling
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);
