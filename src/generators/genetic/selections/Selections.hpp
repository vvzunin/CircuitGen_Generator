#pragma once

#include "generators/genetic/selections/parameters/SelectionParameters.hpp"
#include <generators/genetic/chromosome/type/ChromosomeType.hpp>
#include <generators/genetic/selections/SelectionsTruthTable.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace CG_Gen {

template<typename Type, typename ParametersType>
std::vector<ChromosomeType<Type, ParametersType>>
SelectionType(SelectionParameters i_selectionParameters,
              std::vector<ChromosomeType<Type, ParametersType>> i_population);

template<>
inline std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
SelectionType(SelectionParameters i_selectionParameters,
              std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
                  i_population) {
  if (i_selectionParameters.getSelectionType() == SelectionTypes::Base)
    return SelectionsTruthTable::SelectionBase(i_selectionParameters,
                                               i_population);
  // default to remove warning
  return {};
}

} // namespace CG_Gen
