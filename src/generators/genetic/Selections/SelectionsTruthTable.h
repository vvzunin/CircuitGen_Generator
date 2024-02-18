#pragma once

#include "../../TruthTable.h"
#include "../ChromosomeType.h"

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> SelectionBase(
  SelectionParameters i_selectionParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);
