#include <gtest/gtest.h>

#include "easylogging++Init.hpp"
#include "generators/Genetic/Recombination/RecombinationsTruthTable.hpp"

std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
    createPopulation(int numIndividuals, int inputSize, int outputSize) {
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> population;
  for (int i = 0; i < numIndividuals; ++i) {
    std::vector<std::vector<bool>> table(
        inputSize, std::vector<bool>(outputSize)
    );
    for (int j = 0; j < inputSize; ++j) {
      for (int k = 0; k < outputSize; ++k) {
        table[j][k] = rand() % 2;
      }
    }
    TruthTable tt(inputSize, outputSize, table);
    ChromosomeType<TruthTable, TruthTableParameters> chr(
        "ind" + std::to_string(i + 1), tt
    );
    population.push_back(chr);
  }
  return population;
}

TEST(RecombinationTruthTableTest, RecombinationCrossingEachExitInTurnMany) {
  RecombinationParameters params;
  params.setRecombinationType(RecombinationTypes::CrossingEachExitInTurnMany);
  params.setRefPoints(2);
  params.setRecombinationParameters(2);
  auto population = createPopulation(5, 3, 2);

  auto newPopulation =
      RecombinationsTruthTable::RecombinationCrossingEachExitInTurnMany(
          params, population
      );

  ASSERT_EQ(newPopulation.size(), 2);
  ASSERT_NE(population, newPopulation);
}

TEST(RecombinationTruthTableTest, RecombinationCrossingUniform) {
  RecombinationParameters params;
  params.setRecombinationType(RecombinationTypes::CrossingUniform);
  params.setMaskProbability(0.5);
  params.setRecombinationParameters(2);
  auto population    = createPopulation(5, 3, 2);

  auto newPopulation = RecombinationsTruthTable::RecombinationCrossingUniform(
      params, population
  );

  ASSERT_EQ(newPopulation.size(), 2);
  ASSERT_NE(population, newPopulation);
}

TEST(RecombinationTruthTableTest, RecombinationCrossingTriadic) {
  RecombinationParameters params;
  params.setRecombinationType(RecombinationTypes::CrossingTriadic);
  params.setMaskProbability(0.5);
  params.setRecombinationParameters(2);
  auto population    = createPopulation(5, 3, 2);

  auto newPopulation = RecombinationsTruthTable::RecombinationCrossingTriadic(
      params, population
  );

  ASSERT_EQ(newPopulation.size(), 0);
}

TEST(RecombinationTruthTableTest, RecombinationCrossingShuffling) {
  RecombinationParameters params;
  params.setRecombinationType(RecombinationTypes::CrossingShuffling);
  params.setRecombinationParameters(2);
  auto population    = createPopulation(5, 3, 2);

  auto newPopulation = RecombinationsTruthTable::RecombinationCrossingShuffling(
      params, population
  );

  ASSERT_EQ(newPopulation.size(), 2);
  ASSERT_NE(population, newPopulation);
}
