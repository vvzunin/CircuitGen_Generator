#include "generators/simple/SimpleGenerators.hpp"

#include <gtest/gtest.h>

// CNF RandLevel NumOperations was made in branch tests

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
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
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
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
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
  GraphPtr graph_1 = S_gen_1.generatorComparison(2, true, false, false);
  GraphPtr graph_2 = S_gen_2.generatorComparison(2, true, false, false);
  std::string str1 = graph_1->calculateHash();
  std::string str2 = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1 = S_gen_1.generatorComparison(10, false, false, true);
  graph_2 = S_gen_2.generatorComparison(10, false, false, true);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
}
TEST(GeneratorComparisonTest, DifferentFromEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr graph_1 = S_gen_1.generatorComparison(4, true, false, false);
  GraphPtr graph_2 = S_gen_2.generatorComparison(5, true, false, false);
  std::string str1 = graph_1->calculateHash();
  std::string str2 = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1 = S_gen_1.generatorComparison(4, false, true, false);
  graph_2 = S_gen_2.generatorComparison(4, true, false, false);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
}
TEST(GeneratorComparisonTest, GraphSizeTest) {
  int              bits = 1;
  SimpleGenerators generator;
  GraphPtr graph = generator.generatorComparison(bits, true, false, false);

  ASSERT_NE(graph, nullptr);

  int expectedVertexCount = 8;
  EXPECT_EQ(graph->sumFullSize(), expectedVertexCount);
  graph->~OrientedGraph();
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
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
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
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
}
// Summator
TEST(GeneratorSummatorTest, EqualToEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr    graph_1 = S_gen_1.generatorSummator(2, true, false, false);
  GraphPtr    graph_2 = S_gen_2.generatorSummator(2, true, false, false);
  std::string str1    = graph_1->calculateHash();
  std::string str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1 = S_gen_1.generatorSummator(10, false, true, true);
  graph_2 = S_gen_2.generatorSummator(10, false, true, true);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
}
TEST(GeneratorSummatorTest, DifferentFromEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr    graph_1 = S_gen_1.generatorSummator(4, true, false, false);
  GraphPtr    graph_2 = S_gen_2.generatorSummator(5, true, false, false);
  std::string str1    = graph_1->calculateHash();
  std::string str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1 = S_gen_1.generatorSummator(10, true, false, false);
  graph_2 = S_gen_2.generatorSummator(10, false, true, true);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
}
TEST(GeneratorSummatorTest, NumOfElements) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  int              bits = 1;
  GraphPtr         graph_1 =
      S_gen_1.generatorSummator(bits, false, false, false);
  EXPECT_EQ(graph_1->sumFullSize(), 6);
  bits = 4;
  GraphPtr graph_2 =
      S_gen_2.generatorSummator(bits, false, false, false);
  EXPECT_EQ(graph_2->sumFullSize(), 30);
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
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
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
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
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
}
// Subtractor
TEST(GeneratorSubtractorTest, EqualToEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr graph_1 = S_gen_1.generatorSubtractor(2, true, false, false);
  GraphPtr graph_2 = S_gen_2.generatorSubtractor(2, true, false, false);
  std::string str1 = graph_1->calculateHash();
  std::string str2 = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1 = S_gen_1.generatorSubtractor(10, false, true, true);
  graph_2 = S_gen_2.generatorSubtractor(10, false, true, true);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_TRUE(str1 == str2);
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
}
TEST(GeneratorSubtractorTest, DifferentFromEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr graph_1 = S_gen_1.generatorSubtractor(4, true, false, false);
  GraphPtr graph_2 = S_gen_2.generatorSubtractor(5, true, false, false);
  std::string str1 = graph_1->calculateHash();
  std::string str2 = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1 = S_gen_1.generatorSubtractor(10, true, false, false);
  graph_2 = S_gen_2.generatorSubtractor(10, false, true, true);
  str1    = graph_1->calculateHash();
  str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
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
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
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
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
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
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
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
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
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
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
}
TEST(GeneratorMultiplierTest, DifferentFromEachOther) {
  SimpleGenerators S_gen_1(1);
  SimpleGenerators S_gen_2(1);
  GraphPtr         graph_1 = S_gen_1.generatorMultiplier(4);
  GraphPtr         graph_2 = S_gen_2.generatorMultiplier(5);
  std::string      str1    = graph_1->calculateHash();
  std::string      str2    = graph_2->calculateHash();
  EXPECT_FALSE(str1 == str2);
  graph_1->~OrientedGraph();
  graph_2->~OrientedGraph();
}
