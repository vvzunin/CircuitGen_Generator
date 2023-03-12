#pragma once

enum MutationTypes
{
  Binary,
  Density,
  AccessionDel,
  InsertDel,
  Exchange,
  Delete
};

class MutationParameters
{
public:
  MutationParameters() = default;
  MutationTypes getMutationType() const;
  double getProbabilityGen() const;
  int getExchangeType() const;
  double getProbabilityTruthTable() const;
  bool operator== (const MutationParameters& r) const;

private:
  MutationTypes d_mutationType = MutationTypes::Binary;
  double d_probabilityGen = 0.1;
  int d_exchangeType = 0;
  double d_probabilityTruthTable = 0.1;
};
