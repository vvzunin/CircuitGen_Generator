#pragma once

#include <vector>

#include "ParentsParameters.h"
#include "../ChromosomeType.h"


template<typename Type, typename ParametersType>
std::vector<int> ParentsTypesWorker(ParentsParameters i_parentsParameters,
                              std::vector<ChromosomeType<Type, ParametersType>> i_population
);
