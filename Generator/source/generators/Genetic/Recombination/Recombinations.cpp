#include <vector>
#include <iostream>
#include <string>

#include "Recombinations.h"


template<typename Type, typename ParametersType>
std::vector<ChronosomeType<Type, ParametersType>> RecombinationType
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChronosomeType<Type, ParametersType>> i_population
)
{
  if (i_recombinationParameters.getRecombinationType() == RecombinationTypes::CrossingEachExitInTurnMany)
    return RecombinationCrossingEachExitInTurnMany(
      i_recombinationParameters,
      i_population
    );
  else if (i_recombinationParameters.getRecombinationType() == RecombinationTypes::CrossingUniform)
    return RecombinationCrossingUniform(
      i_recombinationParameters,
      i_population
    );
  else if (i_recombinationParameters.getRecombinationType() == RecombinationTypes::CrossingTriadic)
    return RecombinationCrossingTriadic(
      i_recombinationParameters,
      i_population
    );
  else if (i_recombinationParameters.getRecombinationType() == RecombinationTypes::CrossingReducedReplacement)
    return RecombinationCrossingReducedReplacement(
      i_recombinationParameters,
      i_population
    );
  else if (i_recombinationParameters.getRecombinationType() == RecombinationTypes::CrossingShuffling)
    return RecombinationCrossingShuffling(
      i_recombinationParameters,
      i_population
    );
}
