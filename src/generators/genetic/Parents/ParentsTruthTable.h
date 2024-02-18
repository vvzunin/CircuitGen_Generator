#pragma once

#include "../../TruthTable.h"
#include "../ChromosomeType.h"

std::vector<int> GetHemming(int i_t,
                            std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population);

std::vector<int> ParentsPanmixia(
  ParentsParameters i_parentsParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
); 

std::vector<int> ParentsInbrinding(
  ParentsParameters i_parentsParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<int> ParentsOutbrinding(
  ParentsParameters i_parentsParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<int> ParentTournament(
  ParentsParameters i_parentsParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<int> ParentsRoulette(
  ParentsParameters i_parentsParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);
