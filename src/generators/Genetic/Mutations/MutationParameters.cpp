/**
 * @file MutationParameters.cpp
 * @author Vladimir Zunin <vzunin@hse.ru>
 * @author Чернявских Илья Игоревич <fuuulkrum7@gmail.com>
 * @author Fuuulkrum7 <ilka747428@gmail.com>
 * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
 * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
 * @author Asdfds1 <ziazetdinov@list.ru>
 */

#include <tuple>

#include "MutationParameters.hpp"

namespace CG_Gen {

void MutationParameters::setMutationType(MutationTypes i_mutationType) {
  d_mutationType = i_mutationType;
}

void MutationParameters::setProbabilityGen(double i_probabilityGen) {
  d_probabilityGen = i_probabilityGen;
}

void MutationParameters::setExchangeType(int32_t i_exchangeType) {
  d_exchangeType = i_exchangeType;
}

void MutationParameters::setProbabilityTruthTable(
    double i_probabilityTruthTable) {
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

bool MutationParameters::operator==(const MutationParameters &r) const {
  return std::tie(d_mutationType, d_probabilityGen, d_exchangeType,
                  d_probabilityTruthTable) ==
         std::tie(r.d_mutationType, r.d_probabilityGen, r.d_exchangeType,
                  r.d_probabilityTruthTable);
}

} // namespace CG_Gen
