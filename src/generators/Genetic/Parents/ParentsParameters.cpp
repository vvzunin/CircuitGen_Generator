#include <cstdint>
#include <tuple>

#include "ParentsParameters.h"

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

bool ParentsParameters::operator==(const ParentsParameters& r) const {
  return std::tuple(d_tournamentNumber, d_parentsType)
      == std::tuple(r.d_tournamentNumber, r.d_parentsType);
}
