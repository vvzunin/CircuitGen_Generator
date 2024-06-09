#include <tuple>

#include "MutationParameters.hpp"

void MutationParameters::setMutationType(MutationTypes i_mutationType) {
  d_mutationType = i_mutationType;
}

void MutationParameters::setProbabilityGen(double i_probabilityGen) {
  d_probabilityGen = i_probabilityGen;
}

void MutationParameters::setExchangeType(int32_t i_exchangeType) {
  d_exchangeType = i_exchangeType;
}

void MutationParameters::setProbabilityTruthTable(double i_probabilityTruthTable
) {
  d_probabilityTruthTable = i_probabilityTruthTable;
}

MutationTypes MutationParameters::getMutationType() const {
  return d_mutationType;
}

double MutationParameters::getProbabilityGen() const {
  return d_probabilityGen;
}

int32_t MutationParameters::getExchangeType() const {
  return d_exchangeType;
}

double MutationParameters::getProbabilityTruthTable() const {
  return d_probabilityTruthTable;
}

bool MutationParameters::operator==(const MutationParameters& r) const {
  return std::tie(
             d_mutationType,
             d_probabilityGen,
             d_exchangeType,
             d_probabilityTruthTable
         )
      == std::tie(
             r.d_mutationType,
             r.d_probabilityGen,
             r.d_exchangeType,
             r.d_probabilityTruthTable
      );
}
