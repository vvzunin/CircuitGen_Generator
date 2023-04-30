#pragma once

enum ParentsTypes{
  Panmixia,
  Inbringing,
  Outbrinding,
  Tournament,
  Roulette
};

class ParentsParameters {
public:
  void setParentsType(ParentsTypes i_parentsTypes);
  ParentsTypes getParentsType() const;
  void setTournamentNumber(const int i_tournamentNumber);
  int getTournamentNumber() const;
  bool operator== (const ParentsParameters& r) const;

private:
  int d_tournamentNumber = 2;
  ParentsTypes d_parentsType = ParentsTypes::Panmixia;
};
