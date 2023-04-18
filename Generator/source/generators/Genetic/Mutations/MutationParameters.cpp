#include <tuple>

#include "MutationParameters.h"

MutationTypes MutationParameters::getMutationType() const
{
  return d_mutationType;
}

double MutationParameters::getProbabilityGen() const
{
  return d_probabilityGen;
}

int MutationParameters::getExchangeType() const
{
  return d_exchangeType;
}

double MutationParameters::getProbabilityTruthTable() const
{
  return d_probabilityTruthTable;
}

bool MutationParameters::operator== (const MutationParameters& r) const
{
  return std::tie(d_mutationType, d_probabilityGen, d_exchangeType, d_probabilityTruthTable) == std::tie(r.d_mutationType, r.d_probabilityGen, r.d_exchangeType, r.d_probabilityTruthTable);
}
