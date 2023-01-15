#pragma once

#include "../Parents/ParentsParameters.h"

enum RecombinationTypes
{
  CrossingEachExitInTurnMany, // relative to several reference points
  CrossingUniform, //
  CrossingTriadic,
  CrossingReducedReplacement,
  CorssingShuffling
};

class RecombinationParameters
{
public:
  ParentsParameters getParentsParameters() const
  {
    return d_parentsParameters;
  }

  double getMaskProbability() const
  {
    return d_maskProbability;
  }

  void setRecombinationParameters(int i_rp)
  {
    d_recombinationNumber = i_rp;
  }

  int getRecombinationParameters() const
  {
    return d_recombinationNumber;
  }

private:
  RecombinationTypes d_recombinationType = RecombinationTypes::CrossingEachExitInTurnMany;
  ParentsParameters d_parentsParameters = ParentsParameters();
  int d_refPoints = 1;
  double d_maskProbability = 0.5;
  int d_recombinationNumber = 1;
};
