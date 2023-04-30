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

void GenerationParameters::setMutationParameters( MutationTypes i_mutationType, const double i_probabilityGen, const int i_exchangeType, const double i_probabilityTruthTable)
{
  MutationParameters MP;
  MP.setMutationType(i_mutationType);
  MP.setProbabilityGen(i_probabilityGen);
  MP.setExchangeType(i_exchangeType);
  MP.setProbabilityTruthTable(i_probabilityTruthTable);
  d_geneticParameters.setMutationParameters(MP);
}

void GenerationParameters::setSelectionParameters (const SelectionTypes i_selectionType, const int i_numOfSurvivors)
{
  SelectionParameters SP;
  SP.setSelectionType(i_selectionType);
  SP.setNumOfSurvivors(i_numOfSurvivors);
  d_geneticParameters.setSelectionParameters(SP);
}
