#pragma once

#include <vector>

#include "MutationParameters.h"
#include "../ChronosomeTypes.h"

template<typename Type, typename ParametersType>
class Mutations
{
public:
  std::vector<ChronosomeType<Type, ParametersType>> MutationType(
    MutationParameters i_mutationParameters,
    std::vector<ChronosomeType<Type, ParametersType>> i_population
  );


private:
  
};
