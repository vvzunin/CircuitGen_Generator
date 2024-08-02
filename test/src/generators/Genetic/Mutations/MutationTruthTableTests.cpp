#include "generators/Genetic/Mutations/MutationTruthTable.hpp"

#include <gtest/gtest.h>

#include "easylogging++Init.hpp"

TEST(MutationTruthTableTest, MutationTable) {
  std::vector<std::vector<bool>> table = {
      {true, false, true}, {false, true, false}, {true, true, false}};
  double probability  = 0.5;

  auto   mutatedTable = MutationTruthTable::MutationTable(table, probability);

  ASSERT_EQ(mutatedTable.size(), table.size());
  ASSERT_EQ(mutatedTable[0].size(), table[0].size());
}

TEST(MutationTruthTableTest, MutationBinary) {
  MutationParameters params;
  params.setProbabilityGen(0.5);
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> population;

  TruthTable                                       table(2, 2, 0.5);
  ChromosomeType<TruthTable, TruthTableParameters> Chromosome("Test", table);
  population.push_back(Chromosome);

  auto mutatedPopulation =
      MutationTruthTable::MutationBinary(params, population);

  ASSERT_EQ(mutatedPopulation.size(), population.size());
  ASSERT_NE(
      mutatedPopulation[0].getChromosomeType().getOutTable(),
      table.getOutTable()
  );
}

TEST(MutationTruthTableTest, MutationDensity) {
  MutationParameters params;
  params.setProbabilityGen(0.5);
  params.setProbabilityTruthTable(0.5);
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> population;

  TruthTable                                       table(2, 2, 0.5);
  ChromosomeType<TruthTable, TruthTableParameters> Chromosome("Test", table);
  population.push_back(Chromosome);

  auto mutatedPopulation =
      MutationTruthTable::MutationDensity(params, population);

  ASSERT_EQ(mutatedPopulation.size(), population.size());
  ASSERT_NE(
      mutatedPopulation[0].getChromosomeType().getOutTable(),
      table.getOutTable()
  );
}

TEST(MutationTruthTableTest, MutationAccessionDel) {
  MutationParameters params;
  params.setProbabilityGen(0.5);
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> population;

  TruthTable                                       table(2, 2, 0.5);
  ChromosomeType<TruthTable, TruthTableParameters> Chromosome("Test", table);
  population.push_back(Chromosome);

  auto mutatedPopulation =
      MutationTruthTable::MutationAccessionDel(params, population);

  ASSERT_EQ(mutatedPopulation.size(), population.size());
  ASSERT_NE(
      mutatedPopulation[0].getChromosomeType().getOutTable(),
      table.getOutTable()
  );
}

TEST(MutationTruthTableTest, MutationInsertDel) {
  MutationParameters params;
  params.setProbabilityGen(0.5);
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> population;

  TruthTable                                       table(2, 2, 0.5);
  ChromosomeType<TruthTable, TruthTableParameters> Chromosome("Test", table);
  population.push_back(Chromosome);

  auto mutatedPopulation =
      MutationTruthTable::MutationInsertDel(params, population);

  ASSERT_EQ(mutatedPopulation.size(), population.size());
  ASSERT_NE(
      mutatedPopulation[0].getChromosomeType().getOutTable(),
      table.getOutTable()
  );
}

// Работает только если изменить в MutationTruthTable
// int32_t k = AuxMethods::getRandInt(1, size - 2) на эту строку (меняются
// значения в скобках)
/*
TEST(MutationTruthTableTest, MutationExchange) {
    MutationParameters params;
    params.setProbabilityGen(0.5);
    params.setExchangeType(1);
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> population;
    TruthTable table(2, 2, 0.5);
    std::vector<std::vector<bool>> originalTable = table.getOutTable();
    ChromosomeType<TruthTable, TruthTableParameters> Chromosome("Test", table);
    population.push_back(Chromosome);
    auto mutatedPopulation = MutationTruthTable::MutationExchange(params,
population); ASSERT_EQ(mutatedPopulation.size(), population.size()); auto
mutatedTable = mutatedPopulation[0].getChromosomeType().getOutTable(); bool
mutationOccurred = mutatedTable != originalTable; ASSERT_TRUE(mutationOccurred);
}
*/

TEST(MutationTruthTableTest, MutationDelete) {
  MutationParameters params;
  params.setProbabilityGen(0.5);
  params.setProbabilityTruthTable(0.5);
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> population;

  TruthTable                                       table(2, 2, 0.5);
  ChromosomeType<TruthTable, TruthTableParameters> Chromosome("Test", table);
  population.push_back(Chromosome);

  auto mutatedPopulation =
      MutationTruthTable::MutationDelete(params, population);

  ASSERT_EQ(mutatedPopulation.size(), population.size());
  ASSERT_NE(
      mutatedPopulation[0].getChromosomeType().getOutTable(),
      table.getOutTable()
  );
}