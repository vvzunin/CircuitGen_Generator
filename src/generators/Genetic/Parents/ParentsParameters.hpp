#pragma once

#include <cstdint>
#include <map>
#include <string>

namespace CG_Gen {

enum ParentsTypes { Panmixia, Inbringing, Outbrinding, Tournament, Roulette };

static const std::map<std::string, ParentsTypes> ParentsType2Name = {
  {"Panmixia", Panmixia},
  {"Inbringing", Inbringing},
  {"Outbrinding", Outbrinding},
  {"Tournament", Tournament},
  {"Roulette", Roulette}
};

class ParentsParameters {
public:
  void setParentsType(ParentsTypes i_parentsTypes);
  ParentsTypes getParentsType() const;
  void setTournamentNumber(int32_t i_tournamentNumber);
  int32_t getTournamentNumber() const;
  bool operator==(const ParentsParameters &r) const;

private:
  int32_t d_tournamentNumber = 2;
  ParentsTypes d_parentsType = ParentsTypes::Panmixia;
};

} // namespace CG_Gen
