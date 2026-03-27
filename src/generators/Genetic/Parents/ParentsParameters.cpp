/**
 * @file ParentsParameters.cpp
 * @author Vladimir Zunin <vzunin@hse.ru>
 * @author Чернявских Илья Игоревич <fuuulkrum7@gmail.com>
 * @author Fuuulkrum7 <ilka747428@gmail.com>
 * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
 * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
 * @author Asdfds1 <ziazetdinov@list.ru>
 */

#include <cstdint>
#include <tuple>

#include "ParentsParameters.hpp"

namespace CG_Gen {

void ParentsParameters::setParentsType(ParentsTypes i_parentsTypes) {
  d_parentsType = i_parentsTypes;
}

ParentsTypes ParentsParameters::getParentsType() const {
  return d_parentsType;
}

void ParentsParameters::setTournamentNumber(int32_t i_tournamentNumber) {
  d_tournamentNumber = i_tournamentNumber;
}

int32_t ParentsParameters::getTournamentNumber() const {
  return d_tournamentNumber;
}

bool ParentsParameters::operator==(const ParentsParameters &r) const {
  return std::tuple(d_tournamentNumber, d_parentsType) ==
         std::tuple(r.d_tournamentNumber, r.d_parentsType);
}

} // namespace CG_Gen
