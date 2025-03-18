#pragma once

namespace CG_Gen {

enum GenotypeParametersTypes { TruthTableEnum };

template<typename T>
class Chromosome {
public:
  virtual void generateRandom(T i_gp) = 0;
};

} // namespace CG_Gen
