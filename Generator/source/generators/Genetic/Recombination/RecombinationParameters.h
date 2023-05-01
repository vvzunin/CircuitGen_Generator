#pragma once

#include "../Parents/ParentsParameters.h"

enum RecombinationTypes
{
  CrossingEachExitInTurnMany, // relative to several reference points
  CrossingUniform, //
  CrossingTriadic,
  CrossingReducedReplacement,
  CrossingShuffling
};

class RecombinationParameters
{
public:
  RecombinationTypes getRecombinationType() const;
  ParentsParameters getParentsParameters() const;
  int getRefPoints() const;
  void setRefPoints(int i_refPoints);
  double getMaskProbability() const;
  void setRecombinationParameters(int i_rp);
  int getRecombinationParameters() const;
  bool operator== (const RecombinationParameters& r) const;
  void setMaskProbability(double i_maskProbability);
  void setParentsParameters(ParentsTypes i_parentsType, const int i_tournamentSize);
  void setRecombinationType(RecombinationTypes i_recombinationType);
private:
  RecombinationTypes d_recombinationType = RecombinationTypes::CrossingEachExitInTurnMany;
  ParentsParameters d_parentsParameters = ParentsParameters();
  int d_refPoints = 1;
  double d_maskProbability = 0.5;
  int d_recombinationNumber = 1;
};
