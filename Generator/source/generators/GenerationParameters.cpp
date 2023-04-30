#include <vector>

#include "GenerationParameters.h"

void GenerationParameters::setRecombinationParameters( ParentsTypes i_parentsType, const int i_tournamentSize, RecombinationTypes i_recombinationType, const int i_refPoints, const double i_maskProbability, const int i_recombinationNumber)
{
  RecombinationParameters RP;
  RP.setParentsParameters(i_parentsType, i_tournamentSize);
  RP.setRefPoints(i_refPoints);
  RP.setRecombinationParameters(i_recombinationNumber);
  RP.setRecombinationType(i_recombinationType);
  RP.setMaskProbability(i_maskProbability);
  d_geneticParameters.setRecombinationParameters(RP);
}

