#include "generators/simple/SimpleGenerators.hpp"

#include <gtest/gtest.h>

#include "easylogging++Init.hpp"

// CNF
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

// RnadLevel
TEST(GeneratorRandLevelTest, EqualWithTheSameParametrs) {
  std::map<std::string, std::vector<int32_t>> gatesInfo = {
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

// RandLevelExperimental
TEST(GeneratorRandLevelExperimentalTest, EqualWithTheSameParametrs) {
  std::map<std::string, std::vector<int32_t>> gatesInfo = {
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
  graphPtr1 = generator1.generatorRandLevelExperimental(1, 6, 1, 6, 4, 4);
  graphPtr2 = generator2.generatorRandLevelExperimental(1, 6, 1, 6, 4, 4);
  str1      = graphPtr1->calculateHash();
  str2      = graphPtr2->calculateHash();
  EXPECT_EQ(str1, str2);
  graphPtr1 = generator3.generatorRandLevelExperimental(1, 6, 1, 6, 4, 4);
  graphPtr2 = generator4.generatorRandLevelExperimental(1, 6, 1, 6, 4, 4);
  str1      = graphPtr1->calculateHash();
  str2      = graphPtr2->calculateHash();
  EXPECT_EQ(str1, str2);
}

// NumOperations
TEST(GeneratorNumOperationsTest, EqualWithTheSameParametrs) {
  SimpleGenerators         generator1 = SimpleGenerators(1);
  SimpleGenerators         generator2 = SimpleGenerators(1);
  SimpleGenerators         generator3 = SimpleGenerators(2);
  SimpleGenerators         generator4 = SimpleGenerators(2);

  std::map<Gates, int32_t> logicOper  = {
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

TEST(GeneratorParityTest, EqualToEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorParity(2);
  GraphPtr         graph_2 = S_gen_2.generatorParity(2);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1 = S_gen_1.generatorParity(10);
  graph_2 = S_gen_2.generatorParity(10);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
}
TEST(GeneratorParityTest, DifferentToEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorParity(2);
  GraphPtr         graph_2 = S_gen_2.generatorParity(3);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1 = S_gen_1.generatorParity(10);
  graph_2 = S_gen_2.generatorParity(11);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
}
// TEST(GeneratorParityTest, NumOfElements)
// {
//     SimpleGenerators S_gen_1(1);
//     SimpleGenerators S_gen_2(1);
//     int bits = 2;
//     GraphPtr graph_1 = S_gen_1.generatorParity(bits);
//     GraphPtr graph_2 = S_gen_2.generatorParity(3);
//     int expectedVerticesCount = (1 << bits) + bits + 1;  // 2^bits (все
//     возможные комбинации) + bits (входы) + 1 (выход)
//     EXPECT_EQ(graph_1->sumFullSize(), expectedVerticesCount);
// }
// Comparison
TEST(GeneratorComparisonTest, EqualToEachOver) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorComparison(2, true, false, false);
  GraphPtr         graph_2 = S_gen_2.generatorComparison(2, true, false, false);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1 = S_gen_1.generatorComparison(10, false, false, true);
  graph_2 = S_gen_2.generatorComparison(10, false, false, true);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
}
TEST(GeneratorComparisonTest, DifferentFromEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorComparison(4, true, false, false);
  GraphPtr         graph_2 = S_gen_2.generatorComparison(5, true, false, false);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1 = S_gen_1.generatorComparison(4, false, true, false);
  graph_2 = S_gen_2.generatorComparison(4, true, false, false);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
}
TEST(GeneratorComparisonTest, GraphSizeTest) {
  uint32_t         bits = 1;
  SimpleGenerators generator;
  GraphPtr graph = generator.generatorComparison(bits, true, false, false);

  ASSERT_NE(graph, nullptr);

  size_t expectedVertexCount = 8;
  EXPECT_EQ(graph->sumFullSize(), expectedVertexCount);
  // graph->~OrientedGraph();
}
// Decoder
TEST(GeneratorDecoderTest, EqualToEachOver) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorDecoder(2);
  GraphPtr         graph_2 = S_gen_2.generatorDecoder(2);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1 = S_gen_1.generatorDecoder(10);
  graph_2 = S_gen_2.generatorDecoder(10);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
}
TEST(GeneratorDecoderTest, DifferentFromEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorDecoder(4);
  GraphPtr         graph_2 = S_gen_2.generatorDecoder(5);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1 = S_gen_1.generatorDecoder(10);
  graph_2 = S_gen_2.generatorDecoder(2);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
}
// Summator
TEST(GeneratorSummatorTest, EqualToEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorSummator(2, true, false, false);
  GraphPtr         graph_2 = S_gen_2.generatorSummator(2, true, false, false);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1 = S_gen_1.generatorSummator(10, false, true, true);
  graph_2 = S_gen_2.generatorSummator(10, false, true, true);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
}
TEST(GeneratorSummatorTest, DifferentFromEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorSummator(4, true, false, false);
  GraphPtr         graph_2 = S_gen_2.generatorSummator(5, true, false, false);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1 = S_gen_1.generatorSummator(10, true, false, false);
  graph_2 = S_gen_2.generatorSummator(10, false, true, true);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
}
TEST(GeneratorSummatorTest, NumOfElements) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  uint32_t         bits = 1;
  GraphPtr graph_1      = S_gen_1.generatorSummator(bits, false, false, false);
  EXPECT_EQ(graph_1->sumFullSize(), 6);
  bits             = 4;
  GraphPtr graph_2 = S_gen_2.generatorSummator(bits, false, false, false);
  EXPECT_EQ(graph_2->sumFullSize(), 30);
}

// Encoder
TEST(GeneratorEncoderTest, EqualToEachOver) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorEncoder(2);
  GraphPtr         graph_2 = S_gen_2.generatorEncoder(2);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1 = S_gen_1.generatorEncoder(10);
  graph_2 = S_gen_2.generatorEncoder(10);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
}
TEST(GeneratorEncoderTest, DifferentFromEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorEncoder(4);
  GraphPtr         graph_2 = S_gen_2.generatorEncoder(5);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1 = S_gen_1.generatorEncoder(10);
  graph_2 = S_gen_2.generatorEncoder(2);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
}
// Subtractor
TEST(GeneratorSubtractorTest, EqualToEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorSubtractor(2, true, false, false);
  GraphPtr         graph_2 = S_gen_2.generatorSubtractor(2, true, false, false);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1 = S_gen_1.generatorSubtractor(10, false, true, true);
  graph_2 = S_gen_2.generatorSubtractor(10, false, true, true);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
}
TEST(GeneratorSubtractorTest, DifferentFromEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorSubtractor(4, true, false, false);
  GraphPtr         graph_2 = S_gen_2.generatorSubtractor(5, true, false, false);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1 = S_gen_1.generatorSubtractor(10, true, false, false);
  graph_2 = S_gen_2.generatorSubtractor(10, false, true, true);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
}
// Multiplexer
TEST(GeneratorMultiplexerTest, EqualToEachOver) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorMultiplexer(2);
  GraphPtr         graph_2 = S_gen_2.generatorMultiplexer(2);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1 = S_gen_1.generatorMultiplexer(10);
  graph_2 = S_gen_2.generatorMultiplexer(10);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
}
TEST(GeneratorMultiplexerTest, DifferentFromEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorMultiplexer(4);
  GraphPtr         graph_2 = S_gen_2.generatorMultiplexer(5);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1 = S_gen_1.generatorMultiplexer(10);
  graph_2 = S_gen_2.generatorMultiplexer(2);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
}

// Demultiplexer
TEST(GeneratorDemultiplexerTest, EqualToEachOver) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorDemultiplexer(2);
  GraphPtr         graph_2 = S_gen_2.generatorDemultiplexer(2);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1 = S_gen_1.generatorDemultiplexer(10);
  graph_2 = S_gen_2.generatorDemultiplexer(10);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
}
TEST(GeneratorDemultiplexerTest, DifferentFromEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorDemultiplexer(4);
  GraphPtr         graph_2 = S_gen_2.generatorDemultiplexer(5);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1 = S_gen_1.generatorDemultiplexer(10);
  graph_2 = S_gen_2.generatorDemultiplexer(2);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
}
// Multiplier
TEST(GeneratorMultiplierTest, EqualToEachOver) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  ;
  GraphPtr    graph_1 = S_gen_1.generatorMultiplier(2);
  GraphPtr    graph_2 = S_gen_2.generatorMultiplier(2);
  std::string str1    = graph_1->calculateHash();
  std::string str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1 = S_gen_1.generatorMultiplier(10);
  graph_2 = S_gen_2.generatorMultiplier(10);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
}
TEST(GeneratorMultiplierTest, DifferentFromEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorMultiplier(4);
  GraphPtr         graph_2 = S_gen_2.generatorMultiplier(5);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
}
