#pragma once

#include "../../TruthTable.h"
#include "../ChronosomeType.h"

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> SelectionBase(
  SelectionParameters i_selectionParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);
