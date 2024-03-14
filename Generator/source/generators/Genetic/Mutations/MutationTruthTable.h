#pragma once

#include <vector>

#include "../../TruthTable.h"
#include "../ChronosomeType.h"

/// @brief MutationTable This method takes an i_table matrix containing Boolean values and the probability of i_probability. He then iterates over each element of the matrix and, according to a given probability, reverses its value using a random number
/// @param i_table A matrix of Boolean values that needs to be mutated
/// @param i_probability The probability of mutation of each element of the matrix. This value should be in the range from 0 to 1 and represents the probability of each element changing to the opposite value
/// @return a mutated matrix of Boolean values of type std::vector<std::vector<bool>>
/// */

std::vector<std::vector<bool>> MutationTable(std::vector<std::vector<bool>> i_table,
                                            double i_probability);

/// @brief MutationBinary This method returns a vector of ChronosomeType<TruthTable, Truth Table Parameters> objects containing mutated chromosomes
/// @param i_mutationParameters An object of the Mutation Parameters type containing mutation parameters
/// @param i_population A vector of ChronosomeType<TruthTable, Truth Table Parameters> objects representing a population.
/// @return vector of ChronosomeType<TruthTable, Truth Table Parameters> objects containing mutated chromosomes
/// */

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationBinary(
  MutationParameters i_mutationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);

/// @brief MutationDensity The method performs a mutation operation for a population of individuals in a genetic algorithm.
/// @param i_mutationParameters Mutation parameters, which may include information about the probability of mutation or other settings***
/// @param i_population The vector of individuals to be mutated.
/// std::vector<ChronosomeType<TruthTable, Truth Table Parameters>>: Vector of mutated individuals.
/// */

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationDensity(
  MutationParameters i_mutationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);


/// @brief MutationAccessionDel The method implements a mutation of the "join/delete" type for binary strings
/// @param i_mutationParameters Mutation parameters, which may contain information about the probability of mutation or other settings***
/// @param i_population The vector of individuals to be mutated
/// @return std::vector<ChronosomeType<TruthTable, Truth Table Parameters>>: Mutated population of individuals
/// */


std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationAccessionDel(
  MutationParameters i_mutationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);

/// @brief MutationInsertDel The method implements an insert/delete mutation for binary strings
/// @param i_mutationParameters Mutation parameters, which may contain information about the probability of mutation or other settings***
/// @param i_population The vector of individuals to be mutated
/// @return std::vector<ChronosomeType<TruthTable, Truth Table Parameters>>: Mutated population of individuals
/// */

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationInsertDel(
  MutationParameters i_mutationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);

/// @brief MutationExchange The method implements an "exchange" type mutation for binary strings
/// @param i_mutationParameters Mutation parameters, which may contain information about the type of exchange and the probability of mutation***
/// @parma i_population The vector of individuals to be mutated.
/// @return std::vector<ChronosomeType<TruthTable, Truth Table Parameters>>: Mutated population of individuals
/// */

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationExchange(
  MutationParameters i_mutationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);

/// @brief MutationDelete This method is a mutation operation in genetic algorithms aimed at removing random elements from binary strings in a population
/// @param i_mutationParameters Mutation parameters, which may contain information about the probability of mutation and the probability of deletion of a particular element.
/// @param i_population The vector of individuals to be mutated
/// @return std::vector<ChronosomeType<TruthTable, Truth Table Parameters>>: Mutated population of individuals.
/// */

// TO DO: why do I need 2 copies?

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationDelete(
  MutationParameters i_mutationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);

/// @brief MutationDelete The method is a mutation operation in genetic algorithms aimed at randomly removing elements from binary strings in a population
/// @param i_mutationParameters Mutation parameters, which may contain information about the probability of mutation and the probability of deletion of a particular element
/// @param i_population The vector of individuals to be mutated.
/// @return std::vector<ChronosomeType<TruthTable, Truth Table Parameters>>: Mutated population of individuals
/// */


std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationDelete(
  MutationParameters i_mutationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
);
