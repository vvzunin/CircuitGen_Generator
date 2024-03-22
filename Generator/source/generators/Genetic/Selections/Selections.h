#pragma once

#include <vector>

#include "SelectionParameters.h"

#include "../ChronosomeType.h"

/// @brief vector This is a vector of ChronosomeType objects<Type, Parameters Type>
/// 
/// 
/// <@param i_selectionParameters an object of the Selection Parameters class,
/// which contains information about the selection parameters for the combinational scheme
/// @param i_population represents a vector of 
/// ChronosomeType<Type, Parameters Type> objects, which contains a population
/// of chromosomes to which the selection method defined in the SelectionType function will be applied
/// @return This vector describes the ChronosomeType<Type, type of parameters>.

template<typename Type, typename ParametersType>
std::vector<ChronosomeType<Type, ParametersType>> SelectionType
(
  SelectionParameters i_selectionParameters,
  std::vector<ChronosomeType<Type, ParametersType>> i_population
);
