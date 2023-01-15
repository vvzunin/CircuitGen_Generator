
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

private:
  int d_tournamentNumber = 2;
  ParentsTypes d_parentsType = ParentsTypes::Panmixia;
};
