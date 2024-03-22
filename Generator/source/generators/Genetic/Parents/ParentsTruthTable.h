#pragma once

#include "../../TruthTable.h"
#include "../ChronosomeType.h"

/// @brief GetHemming This function calculates the Hamming distance between
/// each element of the i_population vector and the bit string represented
/// as a binary mask based on the value of i_t. The Hamming distance between
/// two bit strings is defined as the number of positions in which the
/// corresponding bits are different.
/// P.S. Perhaps the calculation of the hamming distance is implemented
/// incorrectly!!!
/// @param i_t An integer value that defines the threshold value for searching
/// for bit strings with a Hamming distance less than or equal to i_t
/// @param i_population A vector of objects of the
/// ChronosomeType<Truth Table, Truth Table Parameters> type containing bit
/// strings for which the Hamming distance from the bit string represented
/// as a binary mask must be calculated
/// @return A vector of integers containing the Hamming distances between
/// the bit strings from the input vector i_population and the bit string
/// represented as a binary mask based on the value i_t

std::vector<int> GetHemming(int i_t,
                            std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population);

/// @brief ParentsPanmixia This method implements the selection of parents for
/// a mixed (panmixia) reproduction scheme in a genetic algorithm. It randomly
/// selects two different parents from a population of bit strings
/// @param i_parentsParameters An object of the Parentparameters class containing
/// parameters for selecting parents.
/// P.S. It is not used in this implementation!!!
/// @param i_population a vector of
/// ChronosomeType objects<TruthTable, Truth Table Parameters> containing bit
/// strings from which the parents will be selected
/// @return A vector containing the indices of two selected different parents
/// from the population

std::vector<int> ParentsPanmixia(
  ParentsParameters i_parentsParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);

/// @brief ParentsInbrinding This function selects one parent randomly from the
/// population and selects the second parent in such a way that it is the
/// closest neighbor (by the smallest Hamming distance) to the first parent
/// @param i_parentsParameters An object of the Parentparameters class
/// containing parameters for selecting parents
/// P.S. It is not used in this implementation!!!
/// @param i_population A vector of
/// ChronosomeType objects<TruthTable, Truth Table Parameters> containing
/// bit strings from which the parents will be selected
/// @return A vector containing the indexes of two selected parents from the
/// population. The first element of the vector is the index of the first
/// parent, and the second element is the index of the second parent
/// */

std::vector<int> ParentsInbrinding(
  ParentsParameters i_parentsParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);

/// @brief ParentsOutbrinding implements an approach to choosing parents,
/// known as outbreeding
/// @param i_parentsParameters An object of the Parentparameters class
/// containing parameters for selecting parents.
/// P.S. It is not used in this implementation!!!
/// @param i_population a vector of
/// ChronosomeType objects<TruthTable, Truth Table Parameters> containing
/// bit strings from which the parents will be selected
/// @return A vector containing the indices of two selected parents from
/// the population. The first element of the vector is the index of the first
/// parent, and the second element is the index of the second parent
/// */

std::vector<int> ParentsOutbrinding(
  ParentsParameters i_parentsParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);

// TO DO: There is no function body!!!

std::vector<int> ParentTournament(
  ParentsParameters i_parentsParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);

/// @brief ParentsRoulette implements an approach to choosing parents using the
/// roulette method. In this case, this function simply delegates the parents'
/// choice to another Parent's Tournament function, which probably implements
/// the parents' tournament choice ***
/// @param i_parentsParameters An object of the Parentparameters class
/// containing parameters for selecting parents
/// P.S. It is not used in this implementation!!!
/// @param i_population A vector of
/// ChronosomeType objects<TruthTable, Truth Table Parameters> containing
/// bit strings from which the parents will be selected
/// @return A vector containing the indices of two selected parents from the
/// population
/// */

std::vector<int> ParentsRoulette(
  ParentsParameters i_parentsParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);
