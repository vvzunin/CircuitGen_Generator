#pragma once

enum ParentsTypes{
  Panmixia,
  Inbringing,
  Outbrinding,
  Tournament,
  Roulette
};

/// class ParentsParameters
/// @param d_tournamentNumber Stores the number of participants in the tournament (tournament number) for the method of selecting parents using the tournament. This value indicates how many individuals will be selected from the population to participate in the tournament, from which the winner for the parent pair will be selected
/// @param d_parentsType Stores the parents type for the genetic algorithm. This enumeration (ParentsTypes) represents various methods of choosing parents, such as random selection, tournament selection, rating selection, etc.
/// 
/// */

class ParentsParameters {
public:

  /// @brief setParentsType The method is designed to set the type of parent selection
  /// @param i_parentsTypes An enumeration of the ParentsTypes type, representing the
  /// new type of parent selection that needs to be set
  /// */

  void setParentsType(ParentsTypes i_parentsTypes);
  ParentsTypes getParentsType() const;

  /// @brief setTournamentNumber The method is designed to get the current type of parent selection
  /// @param i_tournamentNumber The number of participants in the tournament when using the tournament parent selection
  /// */

  void setTournamentNumber(int i_tournamentNumber);

  /// @brief getTournamentNumber The method is designed to get the current value of the number of participants in the tournament
  /// @return an integer value representing the current number of participants in the tournament
  /// */

  int getTournamentNumber() const;
  bool operator== (const ParentsParameters& r) const;

private:
  int d_tournamentNumber = 2;
  ParentsTypes d_parentsType = ParentsTypes::Panmixia;
};
