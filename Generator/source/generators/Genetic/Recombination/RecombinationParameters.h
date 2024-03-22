#pragma once

#include "../Parents/ParentsParameters.h"

enum RecombinationTypes
{
  CrossingEachExitInTurnMany, // relative to several reference points
  CrossingUniform, //
  CrossingTriadic,
  CrossingReducedReplacement,
  CrossingShuffling
};

/// class RecombinationParameters
/// @param d_recombinationType Stores the recombination type. This enumeration (RecombinationTypes) represents the various recombination methods used in genetic algorithms, for example, "single-point crossover", "multipoint crossover", "uniform crossover" ***
/// @param d_parentsParameters Stores the parameters of the parents (parents parameters). This is an object of the Parent's Parameters class, which probably contains information about the selection of parents for the recombination process, for example, the type of parent selection and the size of the tournament
/// @param d_refPoints Stores the number of reference points for multipoint recombination. This value is used in some multipoint crossover methods to determine the number of points at which genetic material is exchanged between parents***
/// @param d_maskProbability Stores the probability of masking (mask probability) for uniform crossover. This value represents the probability of using a gene from one of the parents when performing a uniform crossover
/// @param d_recombinationNumber Stores the number of recombinations (recombination number). This value indicates how many times the recombination process will be performed when using the recombination operator***
/// 
/// */

class RecombinationParameters
{
public:

  /// @brief getRecombinationType returns the current type of recombination
  /// @return type of recombination from enum RecombinationTypes
  /// */

  RecombinationTypes getRecombinationType() const;

  /// @brief getParentsParameters returns the current parameters of the parents
  /// @return parent parameters
  /// */

  ParentsParameters getParentsParameters() const;

  /// @brief getRefPoints returns the current number of recombination points
  /// @return an integer value representing the number of recombination points
  /// */

  int getRefPoints() const;

  /// @brief setRefPoints sets the number of recombination points
  /// @param i_refPoints An integer value representing the number of recombination points to be set
  /// */

  void setRefPoints(int i_refPoints);

  /// @brief getMaskProbability returns the current probability of using the
  /// mask during recombination
  /// @return a double precision floating point number representing the
  /// probability of using a mask
  /// */

  double getMaskProbability() const;

  /// @brief setRecombinationParameters sets the recombination parameters
  /// @param i_rp an integer value representing the recombination parameters
  /// to be set
  /// */

  void setRecombinationParameters(int i_rp);

  /// @brief getRecombinationParameters returns the current recombination parameters
  /// @return The current value of the variable d_recombinationNumber,
  /// representing the recombination parameters

  int getRecombinationParameters() const;
  bool operator== (const RecombinationParameters& r) const;

  /// @brief setMaskProbability sets the probability of using a mask during recombination
  /// @param i_maskProbability representing a new probability of using a mask during recombination
  /// */

  void setMaskProbability(double i_maskProbability);

  /// @brief setParentsParameters sets the parameters of the parents for the recombination process
  /// @param i_parentsType The ParentsTypes enumeration, representing the type of parents
  /// @param i_tournamentSize An integer value representing the size of the
  /// tournament, if the parent type is tournament selection

  void setParentsParameters(ParentsTypes i_parentsType, const int i_tournamentSize);

  /// @brief setRecombinationType sets the type of recombination
  /// @param i_recombinationType a Recombination Types enumeration representing the type of recombination that needs to be set***
  /// *

  void setRecombinationType(RecombinationTypes i_recombinationType);
private:
  RecombinationTypes d_recombinationType = RecombinationTypes::CrossingEachExitInTurnMany;
  ParentsParameters d_parentsParameters = ParentsParameters();
  int d_refPoints = 1;
  double d_maskProbability = 0.5;
  int d_recombinationNumber = 1;
};
