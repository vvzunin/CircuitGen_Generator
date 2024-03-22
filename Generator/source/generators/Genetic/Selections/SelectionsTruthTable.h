#pragma once

#include "../../TruthTable.h"
#include "../ChronosomeType.h"

/// @brief vector a vector of 
/// ChronosomeType objects<Truth Table, Truth Table Parameters>, which represents
/// selected chromosomes based on a specific selection method
/// @param i_selectionParameters an object of the Selection Parameters class, which
/// contains information about the selection parameters for the combinational scheme
/// @param i_population a vector of
/// ChronosomeType objects<TruthTable, Truth Table Parameters>, which contains a
/// population of chromosomes for applying the selection method
/// @return a vector of ChronosomeType objects<Truth Table, Truth Table Parameters>,
/// which represents selected chromosomes based on a specific selection method

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> SelectionBase(
  SelectionParameters i_selectionParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);
