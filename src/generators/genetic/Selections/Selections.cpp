#include <vector>
#include <iostream>
#include <string>

#include "Selections.h"


template<typename Type, typename ParametersType>
std::vector<ChromosomeType<Type, ParametersType>> RecombinationType
(
  SelectionParameters i_selectionParameters,
  std::vector<ChromosomeType<Type, ParametersType>> i_population
)
{
  if (i_selectionParameters.getSelectionType() == SelectionTypes::Base)
    return SelectionBase(
      i_selectionParameters,
      i_population
    );
}
