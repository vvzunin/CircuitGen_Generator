#include <tuple>

#include "RecombinationParameters.h"

void RecombinationParameters::setMaskProbability(double i_maskProbability)
{
  d_maskProbability = i_maskProbability;
}

void RecombinationParameters::setParentsParameters(ParentsTypes i_parentsType, int i_tournamentSize)
{
  d_parentsParameters.setParentsType(i_parentsType);
  d_parentsParameters.setTournamentNumber(i_tournamentSize);
}

void RecombinationParameters::setRecombinationType(RecombinationTypes i_recombinationType)
{
  d_recombinationType = i_recombinationType;
}

RecombinationTypes RecombinationParameters::getRecombinationType() const
{
  return d_recombinationType;
}

ParentsParameters RecombinationParameters::getParentsParameters() const
{
  return d_parentsParameters;
}

int RecombinationParameters::getRefPoints() const
{
  return d_refPoints;
}

void RecombinationParameters::setRefPoints(int i_refPoints)
{
  d_refPoints = i_refPoints;
}

double RecombinationParameters::getMaskProbability() const
{
  return d_maskProbability;
}

void RecombinationParameters::setRecombinationParameters(int i_rp)
{
  d_recombinationNumber = i_rp;
}

int RecombinationParameters::getRecombinationParameters() const
{
  return d_recombinationNumber;
}

bool RecombinationParameters::operator== (const RecombinationParameters& r) const
{
  return std::tie(d_recombinationType, d_parentsParameters, d_refPoints, d_maskProbability, d_recombinationNumber) == std::tie(r.d_recombinationType, r.d_parentsParameters, r.d_refPoints, r.d_maskProbability, r.d_recombinationNumber);
}
