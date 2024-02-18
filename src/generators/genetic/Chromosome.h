#pragma once

#include "GeneticParameters.h"

enum GenotypeParametersTypes
{
  TruthTableEnum
};

class Chromosome
{
public:
  virtual void generateRandom(GeneticParameters* i_gp) = 0;
};
