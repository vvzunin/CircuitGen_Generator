#include "generators/simple/SimpleGenerators.hpp"

#include <gtest/gtest.h>

TEST(CnfFromTruthTableTest, EqualWithTheSameParametrs) {
  SimpleGenerators generator1 = SimpleGenerators(1);
  SimpleGenerators generator2 = SimpleGenerators(1);
  SimpleGenerators generator3 = SimpleGenerators(2);
  SimpleGenerators generator4 = SimpleGenerators(2);

  TruthTable       table =
      TruthTable {1, 1, std::vector<std::vector<bool>>({{1}, {1}})};
  GraphPtr    graphPtr1 = generator1.cnfFromTruthTable(table, true);
  GraphPtr    graphPtr2 = generator2.cnfFromTruthTable(table, true);
  std::string str1      = graphPtr1->calculateHash();
  std::string str2      = graphPtr2->calculateHash();
  EXPECT_EQ(str1, str2);
  graphPtr1 = generator3.cnfFromTruthTable(table, true);
  graphPtr2 = generator4.cnfFromTruthTable(table, true);
  str1      = graphPtr1->calculateHash(true);
  str2      = graphPtr2->calculateHash(true);
  EXPECT_EQ(str1, str2);

  table =
      TruthTable {1, 1, std::vector<std::vector<bool>>({{1}, {1}, {1}, {0}})};
  graphPtr1 = generator1.cnfFromTruthTable(table, false);
  graphPtr2 = generator2.cnfFromTruthTable(table, true);
  str1      = graphPtr1->calculateHash(true);
  str2      = graphPtr2->calculateHash(true);
  EXPECT_EQ(str1, str2);
  graphPtr1 = generator3.cnfFromTruthTable(table, true);
  graphPtr2 = generator4.cnfFromTruthTable(table, true);
  str1      = graphPtr1->calculateHash(true);
  str2      = graphPtr2->calculateHash(true);
  EXPECT_EQ(str1, str2);

  table = TruthTable {
      1, 1, std::vector<std::vector<bool>>({{1, 1}, {1, 1}, {1, 1}, {0, 0}})};
  graphPtr1 = generator1.cnfFromTruthTable(table, true);
  graphPtr2 = generator2.cnfFromTruthTable(table, true);
  str1      = graphPtr1->calculateHash(true);
  str2      = graphPtr2->calculateHash(true);
  EXPECT_EQ(str1, str2);
  graphPtr1 = generator3.cnfFromTruthTable(table, true);
  graphPtr2 = generator4.cnfFromTruthTable(table, true);
  str1      = graphPtr1->calculateHash(true);
  str2      = graphPtr2->calculateHash(true);
  EXPECT_EQ(str1, str2);
}

TEST(GeneratorRandLevelTest, EqualWithTheSameParametrs) {
  std::map<std::string, std::vector<int>> gatesInfo = {
      {"and", {2, 4, 8}},
      {"nand", {2, 4, 8}},
      {"or", {2, 8}},
      {"nor", {16, 4, 8}},
      {"xor", {2, 8, 4}},
      {"xnor", {2, 16, 8}}};

  SimpleGenerators generator1 = SimpleGenerators(1);
  generator1.setGatesInputsInfo(gatesInfo);
  SimpleGenerators generator2 = SimpleGenerators(1);
  generator2.setGatesInputsInfo(gatesInfo);
  SimpleGenerators generator3 = SimpleGenerators(2);
  generator3.setGatesInputsInfo(gatesInfo);
  SimpleGenerators generator4 = SimpleGenerators(2);
  generator4.setGatesInputsInfo(gatesInfo);

  std::shared_ptr<OrientedGraph> graphPtr1 =
      generator1.generatorRandLevel(1, 3, 1, 3, 3, 3);
  std::shared_ptr<OrientedGraph> graphPtr2 =
      generator2.generatorRandLevel(1, 3, 1, 3, 3, 3);
  std::string str1 = graphPtr1->calculateHash(true);
  std::string str2 = graphPtr2->calculateHash(true);
  EXPECT_EQ(str1, str2);
  graphPtr1 = generator3.generatorRandLevel(1, 3, 1, 3, 3, 3);
  graphPtr2 = generator4.generatorRandLevel(1, 3, 1, 3, 3, 3);
  str1      = graphPtr1->calculateHash(true);
  str2      = graphPtr2->calculateHash(true);
  EXPECT_EQ(str1, str2);

  graphPtr1 = generator1.generatorRandLevel(2, 6, 2, 6, 4, 4);
  graphPtr2 = generator2.generatorRandLevel(2, 6, 2, 6, 4, 4);
  str1      = graphPtr1->calculateHash(true);
  str2      = graphPtr2->calculateHash(true);
  EXPECT_EQ(str1, str2);
  graphPtr1 = generator3.generatorRandLevel(2, 6, 2, 6, 4, 4);
  graphPtr2 = generator4.generatorRandLevel(2, 6, 2, 6, 4, 4);
  str1      = graphPtr1->calculateHash(true);
  str2      = graphPtr2->calculateHash(true);
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

  SimpleGenerators generator1 = SimpleGenerators(1);
  generator1.setGatesInputsInfo(gatesInfo);
  SimpleGenerators generator2 = SimpleGenerators(1);
  generator2.setGatesInputsInfo(gatesInfo);
  SimpleGenerators generator3 = SimpleGenerators(2);
  generator3.setGatesInputsInfo(gatesInfo);
  SimpleGenerators generator4 = SimpleGenerators(2);
  generator4.setGatesInputsInfo(gatesInfo);

  std::shared_ptr<OrientedGraph> graphPtr1 =
      generator1.generatorRandLevelExperimental(1, 3, 1, 3, 3, 3);
  std::shared_ptr<OrientedGraph> graphPtr2 =
      generator2.generatorRandLevelExperimental(1, 3, 1, 3, 3, 3);
  std::string str1 = graphPtr1->calculateHash(true);
  std::string str2 = graphPtr2->calculateHash(true);
  EXPECT_EQ(str1, str2);
  graphPtr1 = generator3.generatorRandLevelExperimental(1, 3, 1, 3, 3, 3);
  graphPtr2 = generator4.generatorRandLevelExperimental(1, 3, 1, 3, 3, 3);
  str1      = graphPtr1->calculateHash(true);
  str2      = graphPtr2->calculateHash(true);
  EXPECT_EQ(str1, str2);

  //-error
  // graphPtr1 = generator1.generatorRandLevelExperimental(1, 6, 1, 6, 4, 4);
  // graphPtr2 = generator2.generatorRandLevelExperimental(1, 6, 1, 6, 4, 4);
  // str1      = graphPtr1->calculateHash();
  // str2      = graphPtr2->calculateHash();
  // EXPECT_EQ(str1, str2);
  // graphPtr1 = generator3.generatorRandLevelExperimental(1, 6, 1, 6, 4, 4);
  // graphPtr2 = generator4.generatorRandLevelExperimental(1, 6, 1, 6, 4, 4);
  // str1      = graphPtr1->calculateHash();
  // str2      = graphPtr2->calculateHash();
  // EXPECT_EQ(str1, str2);
}

TEST(GeneratorNumOperationsTest, EqualWithTheSameParametrs) {
  SimpleGenerators     generator1 = SimpleGenerators(1);
  SimpleGenerators     generator2 = SimpleGenerators(1);
  SimpleGenerators     generator3 = SimpleGenerators(2);
  SimpleGenerators     generator4 = SimpleGenerators(2);

  std::map<Gates, int> logicOper  = {
      {Gates::GateAnd, 2}, {Gates::GateOr, 2}, {Gates::GateNot, 1}};
  std::shared_ptr<OrientedGraph> graphPtr1 =
      generator1.generatorNumOperation(1, 1, logicOper, true);
  std::string str1 = graphPtr1->calculateHash();
  EXPECT_EQ(str1, str1);
  std::shared_ptr<OrientedGraph> graphPtr2 =
      generator2.generatorNumOperation(1, 1, logicOper, true);
  std::string str2 = graphPtr2->calculateHash();
  EXPECT_EQ(str1, str2);
  graphPtr1 = generator3.generatorNumOperation(1, 1, logicOper, true);
  graphPtr2 = generator4.generatorNumOperation(1, 1, logicOper, true);
  str1      = graphPtr1->calculateHash();
  str2      = graphPtr2->calculateHash();
  EXPECT_EQ(str1, str2);

  logicOper = {
      {Gates::GateAnd, 5},
      {Gates::GateOr, 5},
      {Gates::GateNot, 1},
      {Gates::GateNor, 1},
      {Gates::GateNand, 1},
      {Gates::GateXnor, 1},
      {Gates::GateXor, 1}};

  graphPtr1 = generator1.generatorNumOperation(1, 1, logicOper, true);
  graphPtr2 = generator2.generatorNumOperation(1, 1, logicOper, true);
  str1      = graphPtr1->calculateHash();
  str2      = graphPtr2->calculateHash();
  EXPECT_EQ(str1, str2);

  graphPtr1 = generator3.generatorNumOperation(1, 1, logicOper, true);
  graphPtr2 = generator4.generatorNumOperation(1, 1, logicOper, true);
  str1      = graphPtr1->calculateHash();
  str2      = graphPtr2->calculateHash();
  EXPECT_EQ(str1, str2);

  graphPtr1 = generator1.generatorNumOperation(5, 10, logicOper, true);
  graphPtr2 = generator2.generatorNumOperation(5, 10, logicOper, true);
  str1      = graphPtr1->calculateHash();
  str2      = graphPtr2->calculateHash();
  EXPECT_EQ(str1, str2);

  graphPtr1 = generator3.generatorNumOperation(5, 10, logicOper, true);
  graphPtr2 = generator4.generatorNumOperation(5, 10, logicOper, true);
  str1      = graphPtr1->calculateHash();
  str2      = graphPtr2->calculateHash();
  EXPECT_EQ(str1, str2);

  logicOper = {
      {Gates::GateAnd, 5},
      {Gates::GateOr, 5},
      {Gates::GateNot, 6},
      {Gates::GateNor, 6},
      {Gates::GateNand, 1},
      {Gates::GateXnor, 9},
      {Gates::GateXor, 12}};

  graphPtr1 = generator1.generatorNumOperation(1, 1, logicOper, false);
  graphPtr2 = generator2.generatorNumOperation(1, 1, logicOper, false);
  str1      = graphPtr1->calculateHash();
  str2      = graphPtr2->calculateHash();
  EXPECT_EQ(str1, str2);

  graphPtr1 = generator3.generatorNumOperation(1, 1, logicOper, false);
  graphPtr2 = generator4.generatorNumOperation(1, 1, logicOper, false);
  str1      = graphPtr1->calculateHash();
  str2      = graphPtr2->calculateHash();
  EXPECT_EQ(str1, str2);

  graphPtr1 = generator1.generatorNumOperation(7, 9, logicOper, false);
  graphPtr2 = generator2.generatorNumOperation(7, 9, logicOper, false);
  str1      = graphPtr1->calculateHash();
  str2      = graphPtr2->calculateHash();
  EXPECT_EQ(str1, str2);

  graphPtr1 = generator3.generatorNumOperation(7, 9, logicOper, false);
  graphPtr2 = generator4.generatorNumOperation(7, 9, logicOper, false);
  str1      = graphPtr1->calculateHash();
  str2      = graphPtr2->calculateHash();
  EXPECT_EQ(str1, str2);
}
