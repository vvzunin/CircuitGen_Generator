#pragma once

#include <map>
#include <string>

namespace CG_Gen {

enum GenotypeParametersTypes { TruthTableEnum };

static const std::map<std::string, GenotypeParametersTypes>
    GenotypeParametersType2Name = {
        {"TruthTableEnum", TruthTableEnum},
};

template<typename T>
class Chromosome {
public:
  virtual void generateRandom(T i_gp) = 0;
};

} // namespace CG_Gen
