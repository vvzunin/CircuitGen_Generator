#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "SelectionParameters.hpp"
#include "SelectionsTruthTable.hpp"
#include "../ChronosomeType.hpp"

template<typename Type, typename ParametersType>
std::vector<ChronosomeType<Type, ParametersType>> SelectionType
(
  SelectionParameters i_selectionParameters,
  std::vector<ChronosomeType<Type, ParametersType>> i_population
);

template<>
inline std::vector<ChronosomeType<TruthTable, TruthTableParameters>> SelectionType
(
  SelectionParameters i_selectionParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  if (i_selectionParameters.getSelectionType() == SelectionTypes::Base)
    return SelectionsTruthTable::SelectionBase(
      i_selectionParameters,
      i_population
    );
  // default to remove warning 
  return {};
}