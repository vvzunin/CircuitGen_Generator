#include "generators/simple/SimpleGenerators.hpp"

#include <gtest/gtest.h>

TEST(CnfFromTruthTableTest, EqualWithTheSameParametrs) {
  SimpleGenerators firstGenerator  = SimpleGenerators(1);
  SimpleGenerators secondGenerator = SimpleGenerators(1);
  SimpleGenerators thirdGenerator  = SimpleGenerators(2);
  SimpleGenerators fourthGenerator = SimpleGenerators(2);

  TruthTable       table =
      TruthTable {1, 1, std::vector<std::vector<bool>>({{1}, {1}})};
  std::shared_ptr<OrientedGraph> firstGraph =
      firstGenerator.cnfFromTruthTable(table, true);
  std::shared_ptr<OrientedGraph> secondGraph =
      secondGenerator.cnfFromTruthTable(table, true);
  std::string str1 = firstGraph->calculateHash();
  std::string str2 = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);
  firstGraph  = thirdGenerator.cnfFromTruthTable(table, true);
  secondGraph = fourthGenerator.cnfFromTruthTable(table, true);
  str1        = firstGraph->calculateHash(true);
  str2        = secondGraph->calculateHash(true);
  EXPECT_EQ(str1, str2);

  //   table =
  //       TruthTable {2, 1, std::vector<std::vector<bool>>({{1}, {1}, {1},
  //       {0}})};
  //   firstGraph  = firstGenerator.cnfFromTruthTable(table, true);
  //   secondGraph = secondGenerator.cnfFromTruthTable(table, true);
  //   str1        = firstGraph->calculateHash(true);
  //   str2        = secondGraph->calculateHash(true);
  //   EXPECT_EQ(str1, str2);
  //   firstGraph  = thirdGenerator.cnfFromTruthTable(table, true);
  //   secondGraph = fourthGenerator.cnfFromTruthTable(table, true);
  //   str1        = firstGraph->calculateHash(true);
  //   str2        = secondGraph->calculateHash(true);
  //   EXPECT_EQ(str1, str2);

  //   table = TruthTable {
  //       2, 2, std::vector<std::vector<bool>>({{1, 1}, {1, 1}, {1, 1}, {0,
  //       0}})};
  //   firstGraph  = firstGenerator.cnfFromTruthTable(table, true);
  //   secondGraph = secondGenerator.cnfFromTruthTable(table, true);
  //   str1        = firstGraph->calculateHash(true);
  //   str2        = secondGraph->calculateHash(true);
  //   EXPECT_EQ(str1, str2);
  //   firstGraph  = thirdGenerator.cnfFromTruthTable(table, true);
  //   secondGraph = fourthGenerator.cnfFromTruthTable(table, true);
  //   str1        = firstGraph->calculateHash(true);
  //   str2        = secondGraph->calculateHash(true);
  //   EXPECT_EQ(str1, str2);
}

TEST(GeneratorRandLevelTest, EqualWithTheSameParametrs) {
  std::map<std::string, std::vector<int>> gatesInfo = {
      {"and", {2, 4, 8}},
      {"nand", {2, 4, 8}},
      {"or", {2, 8}},
      {"nor", {16, 4, 8}},
      {"xor", {2, 8, 4}},
      {"xnor", {2, 16, 8}}};

  SimpleGenerators firstGenerator = SimpleGenerators(1);
  firstGenerator.setGatesInputsInfo(gatesInfo);
  SimpleGenerators secondGenerator = SimpleGenerators(1);
  secondGenerator.setGatesInputsInfo(gatesInfo);
  SimpleGenerators thirdGenerator = SimpleGenerators(2);
  thirdGenerator.setGatesInputsInfo(gatesInfo);
  SimpleGenerators fourthGenerator = SimpleGenerators(2);
  fourthGenerator.setGatesInputsInfo(gatesInfo);

  std::shared_ptr<OrientedGraph> firstGraph =
      firstGenerator.generatorRandLevel(1, 3, 1, 3, 3, 3);
  std::shared_ptr<OrientedGraph> secondGraph =
      secondGenerator.generatorRandLevel(1, 3, 1, 3, 3, 3);
  std::string str1 = firstGraph->calculateHash();
  std::string str2 = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);
  firstGraph  = thirdGenerator.generatorRandLevel(1, 3, 1, 3, 3, 3);
  secondGraph = fourthGenerator.generatorRandLevel(1, 3, 1, 3, 3, 3);
  str1        = firstGraph->calculateHash();
  str2        = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);

  firstGraph  = firstGenerator.generatorRandLevel(2, 6, 2, 6, 4, 4);
  secondGraph = secondGenerator.generatorRandLevel(2, 6, 2, 6, 4, 4);
  str1        = firstGraph->calculateHash();
  str2        = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);
  firstGraph  = thirdGenerator.generatorRandLevel(2, 6, 2, 6, 4, 4);
  secondGraph = fourthGenerator.generatorRandLevel(2, 6, 2, 6, 4, 4);
  str1        = firstGraph->calculateHash();
  str2        = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);
}

TEST(GeneratorRandLevelExperimentalTest, EqualWithTheSameParametrs) {
  std::map<std::string, std::vector<int>> gatesInfo = {
      {"and", {2, 4, 8}},
      {"nand", {2, 4, 8}},
      {"or", {2, 8}},
      {"nor", {16, 4, 8}},
      {"xor", {2, 8, 4}},
      {"xnor", {2, 16, 8}}};

  SimpleGenerators firstGenerator = SimpleGenerators(1);
  firstGenerator.setGatesInputsInfo(gatesInfo);
  SimpleGenerators secondGenerator = SimpleGenerators(1);
  secondGenerator.setGatesInputsInfo(gatesInfo);
  SimpleGenerators thirdGenerator = SimpleGenerators(2);
  thirdGenerator.setGatesInputsInfo(gatesInfo);
  SimpleGenerators fourthGenerator = SimpleGenerators(2);
  fourthGenerator.setGatesInputsInfo(gatesInfo);

  std::shared_ptr<OrientedGraph> firstGraph =
      firstGenerator.generatorRandLevelExperimental(1, 3, 1, 3, 3, 3);
  std::shared_ptr<OrientedGraph> secondGraph =
      secondGenerator.generatorRandLevelExperimental(1, 3, 1, 3, 3, 3);
  std::string str1 = firstGraph->calculateHash();
  std::string str2 = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);
  firstGraph = thirdGenerator.generatorRandLevelExperimental(1, 3, 1, 3, 3, 3);
  secondGraph =
      fourthGenerator.generatorRandLevelExperimental(1, 3, 1, 3, 3, 3);
  str1 = firstGraph->calculateHash();
  str2 = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);

  //-error
  //   firstGraph = firstGenerator.generatorRandLevelExperimental(1, 6, 1, 6, 4,
  //   4); secondGraph =
  //       secondGenerator.generatorRandLevelExperimental(1, 6, 1, 6, 4, 4);
  //   str1 = firstGraph->calculateHash();
  //   str2 = secondGraph->calculateHash();
  //   EXPECT_EQ(str1, str2);
  //   firstGraph = thirdGenerator.generatorRandLevelExperimental(1, 6, 1, 6, 4,
  //   4); secondGraph =
  //       fourthGenerator.generatorRandLevelExperimental(1, 6, 1, 6, 4, 4);
  //   str1 = firstGraph->calculateHash();
  //   str2 = secondGraph->calculateHash();
  //   EXPECT_EQ(str1, str2);
}

TEST(GeneratorNumOperationsTest, EqualWithTheSameParametrs) {
  SimpleGenerators     firstGenerator  = SimpleGenerators(1);
  SimpleGenerators     secondGenerator = SimpleGenerators(1);
  SimpleGenerators     thirdGenerator  = SimpleGenerators(2);
  SimpleGenerators     fourthGenerator = SimpleGenerators(2);

  std::map<Gates, int> logicOper       = {
      {Gates::GateAnd, 2}, {Gates::GateOr, 2}, {Gates::GateNot, 1}};
  std::shared_ptr<OrientedGraph> firstGraph =
      firstGenerator.generatorNumOperation(1, 1, logicOper, true);
  std::string str1 = firstGraph->calculateHash();
  EXPECT_EQ(str1, str1);
  std::shared_ptr<OrientedGraph> secondGraph =
      secondGenerator.generatorNumOperation(1, 1, logicOper, true);
  std::string str2 = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);
  firstGraph  = thirdGenerator.generatorNumOperation(1, 1, logicOper, true);
  secondGraph = fourthGenerator.generatorNumOperation(1, 1, logicOper, true);
  str1        = firstGraph->calculateHash();
  str2        = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);

  logicOper = {
      {Gates::GateAnd, 5},
      {Gates::GateOr, 5},
      {Gates::GateNot, 1},
      {Gates::GateNor, 1},
      {Gates::GateNand, 1},
      {Gates::GateXnor, 1},
      {Gates::GateXor, 1}};

  firstGraph  = firstGenerator.generatorNumOperation(1, 1, logicOper, true);
  secondGraph = secondGenerator.generatorNumOperation(1, 1, logicOper, true);
  str1        = firstGraph->calculateHash();
  str2        = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);

  firstGraph  = thirdGenerator.generatorNumOperation(1, 1, logicOper, true);
  secondGraph = fourthGenerator.generatorNumOperation(1, 1, logicOper, true);
  str1        = firstGraph->calculateHash();
  str2        = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);

  firstGraph  = firstGenerator.generatorNumOperation(5, 10, logicOper, true);
  secondGraph = secondGenerator.generatorNumOperation(5, 10, logicOper, true);
  str1        = firstGraph->calculateHash();
  str2        = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);

  firstGraph  = thirdGenerator.generatorNumOperation(5, 10, logicOper, true);
  secondGraph = fourthGenerator.generatorNumOperation(5, 10, logicOper, true);
  str1        = firstGraph->calculateHash();
  str2        = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);

  logicOper = {
      {Gates::GateAnd, 5},
      {Gates::GateOr, 5},
      {Gates::GateNot, 6},
      {Gates::GateNor, 6},
      {Gates::GateNand, 1},
      {Gates::GateXnor, 9},
      {Gates::GateXor, 12}};

  firstGraph  = firstGenerator.generatorNumOperation(1, 1, logicOper, false);
  secondGraph = secondGenerator.generatorNumOperation(1, 1, logicOper, false);
  str1        = firstGraph->calculateHash();
  str2        = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);

  firstGraph  = thirdGenerator.generatorNumOperation(1, 1, logicOper, false);
  secondGraph = fourthGenerator.generatorNumOperation(1, 1, logicOper, false);
  str1        = firstGraph->calculateHash();
  str2        = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);

  firstGraph  = firstGenerator.generatorNumOperation(7, 9, logicOper, false);
  secondGraph = secondGenerator.generatorNumOperation(7, 9, logicOper, false);
  str1        = firstGraph->calculateHash();
  str2        = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);

  firstGraph  = thirdGenerator.generatorNumOperation(7, 9, logicOper, false);
  secondGraph = fourthGenerator.generatorNumOperation(7, 9, logicOper, false);
  str1        = firstGraph->calculateHash();
  str2        = secondGraph->calculateHash();
  EXPECT_EQ(str1, str2);
}
