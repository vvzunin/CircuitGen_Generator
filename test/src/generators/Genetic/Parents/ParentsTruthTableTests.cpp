#include "generators/Genetic/Parents/ParentsTruthTable.hpp"

#include <gtest/gtest.h>

#include "easylogging++Init.hpp"

TruthTable createRandomTruthTable(int32_t inputs, int32_t outputs) {
  std::vector<std::vector<bool>> table(
      static_cast<std::vector<std::vector<bool>>::size_type>(outputs),
      std::vector<bool>(static_cast<std::vector<bool>::size_type>(inputs))
  );
  for (int32_t i = 0; i < outputs; ++i) {
    for (int32_t j = 0; j < inputs; ++j) {
      table[static_cast<std::vector<std::vector<bool>>::size_type>(i)]
           [static_cast<std::vector<bool>::size_type>(j)] =
               AuxMethods::getRandInt(0, 2);
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

TEST(ParentsTruthTableTest, GetHemming) {
  auto population    = createPopulation(5, 3, 2);
  auto hemmingResult = GetHemming(0, population);

  ASSERT_EQ(hemmingResult.size(), population.size() - 1);

  for (const auto& index : hemmingResult) {
    ASSERT_NE(index, 0);
  }
}

TEST(ParentsTruthTableTest, ParentsPanmixia) {
  ParentsParameters params;
  auto              population = createPopulation(5, 3, 2);
  auto              parents    = ParentsPanmixia(params, population);

  ASSERT_EQ(parents.size(), 2);
  ASSERT_NE(parents[0], parents[1]);
}

TEST(ParentsTruthTableTest, ParentsInbrinding) {
  ParentsParameters params;
  auto              population = createPopulation(5, 3, 2);
  auto              parents    = ParentsInbrinding(params, population);

  ASSERT_EQ(parents.size(), 2);
  ASSERT_NE(parents[0], parents[1]);
}

TEST(ParentsTruthTableTest, ParentsOutbrinding) {
  ParentsParameters params;
  auto              population = createPopulation(5, 3, 2);
  auto              parents    = ParentsOutbrinding(params, population);

  ASSERT_EQ(parents.size(), 2);
  ASSERT_NE(parents[0], parents[1]);
}

TEST(ParentsTruthTableTest, ParentsTournament) {
  ParentsParameters params;
  params.setTournamentNumber(3);
  auto population = createPopulation(5, 3, 2);
  auto parents    = ParentsTournament(params, population);

  ASSERT_EQ(parents.size(), 2);
  ASSERT_NE(parents[0], parents[1]);
}

TEST(ParentsTruthTableTest, ParentsRoulette) {
  ParentsParameters params;
  auto              population = createPopulation(5, 3, 2);
  auto              parents    = ParentsRoulette(params, population);

  ASSERT_EQ(parents.size(), 2);
  ASSERT_NE(parents[0], parents[1]);
}