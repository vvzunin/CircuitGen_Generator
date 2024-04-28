#pragma once

enum GenotypeParametersTypes
{
  TruthTableEnum
};

template<typename T>
class Chronosome
{
public:
  virtual void generateRandom(T i_gp) = 0;
};
