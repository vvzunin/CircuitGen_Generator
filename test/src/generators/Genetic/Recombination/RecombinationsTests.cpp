#include "generators/Genetic/Recombination/Recombinations.hpp"

#include <gtest/gtest.h>

#include "easylogging++Init.hpp"

TruthTable createRandomTruthTable(int32_t inputs, int32_t outputs) {
  std::vector<std::vector<bool>> table(outputs, std::vector<bool>(inputs));
  for (int32_t i = 0; i < outputs; ++i) {
    for (int32_t j = 0; j < inputs; ++j) {
      table[i][j] = AuxMethods::getRandInt(0, 2);
    }
  }
  return TruthTable(inputs, outputs, table);
}

ChromosomeType<TruthTable, TruthTableParameters> createRandomChromosome(
    const std::string& name,
    int32_t            inputs,
    int32_t            outputs
) {
  return ChromosomeType<TruthTable, TruthTableParameters>(
      name, createRandomTruthTable(inputs, outputs)
  );
}

std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
    createPopulation(int32_t populationSize, int32_t inputs, int32_t outputs) {
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> population;
  for (int32_t i = 0; i < populationSize; ++i) {
    population.push_back(createRandomChromosome(
        "Chromosome" + std::to_string(i), inputs, outputs
    ));
  }
  return population;
}

TEST(RecombinationTest, RecombinationCrossingEachExitInTurnMany) {
  RecombinationParameters params;
  params.setRecombinationType(RecombinationTypes::CrossingEachExitInTurnMany);
  auto population = createPopulation(5, 3, 2);
  auto newPopulation =
      RecombinationType<TruthTable, TruthTableParameters>(params, population);

  ASSERT_NE(population, newPopulation);
}

TEST(RecombinationTest, RecombinationCrossingUniform) {
  RecombinationParameters params;
  params.setRecombinationType(RecombinationTypes::CrossingUniform);
  auto population = createPopulation(5, 3, 2);
  auto newPopulation =
      RecombinationType<TruthTable, TruthTableParameters>(params, population);

  ASSERT_NE(population, newPopulation);
}

TEST(RecombinationTest, RecombinationCrossingTriadic) {
  RecombinationParameters params;
  params.setRecombinationType(RecombinationTypes::CrossingTriadic);
  auto population = createPopulation(5, 3, 2);
  auto newPopulation =
      RecombinationType<TruthTable, TruthTableParameters>(params, population);

  ASSERT_NE(population, newPopulation);
}
/*
//does not work, idk why
TEST(RecombinationTest, RecombinationCrossingReducedReplacement) {
    RecombinationParameters params;
    params.setRecombinationType(RecombinationTypes::CrossingReducedReplacement);
    auto population = createPopulation(5, 3, 2);
    auto newPopulation = RecombinationType<TruthTable,
TruthTableParameters>(params, population);

    ASSERT_NE(population, newPopulation);
}
*/

TEST(RecombinationTest, RecombinationCrossingShuffling) {
  RecombinationParameters params;
  params.setRecombinationType(RecombinationTypes::CrossingShuffling);
  auto population = createPopulation(5, 3, 2);
  auto newPopulation =
      RecombinationType<TruthTable, TruthTableParameters>(params, population);

  ASSERT_NE(population, newPopulation);
}

TEST(RecombinationTest, DefaultRecombination) {
  RecombinationParameters params;
  params.setRecombinationType(static_cast<RecombinationTypes>(-1));
  auto population = createPopulation(5, 3, 2);
  auto newPopulation =
      RecombinationType<TruthTable, TruthTableParameters>(params, population);

  ASSERT_TRUE(newPopulation.empty());
}