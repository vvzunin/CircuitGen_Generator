#include "generators/Genetic/GeneticParameters.hpp"

#include <gtest/gtest.h>

#include "easylogging++Init.hpp"

TEST(GeneticParametersTest, ConstructorTest) {
  GeneticParameters gp(5, 3);
  EXPECT_EQ(gp.getInputs(), 5);
  EXPECT_EQ(gp.getOutputs(), 3);
}

TEST(GeneticParametersTest, GetAndSetInputs) {
  GeneticParameters gp(0, 0);
  gp.setInputs(4);
  EXPECT_EQ(gp.getInputs(), 4);
}

TEST(GeneticParametersTest, GetAndSetOutputs) {
  GeneticParameters gp(0, 0);
  gp.setOutputs(2);
  EXPECT_EQ(gp.getOutputs(), 2);
}

TEST(GeneticParametersTest, GetAndSetKeyEndProcessIndex) {
  GeneticParameters gp(0, 0);
  gp.setKeyEndProcessIndex(0.75);
  EXPECT_EQ(gp.getKeyEndProcessIndex(), 0.75);
}

TEST(GeneticParametersTest, GetAndSetNumOfCycles) {
  GeneticParameters gp(0, 0);
  gp.setNumOfCycles(50);
  EXPECT_EQ(gp.getNumOfCycles(), 50);
}

TEST(GeneticParametersTest, GetAndSetSelectionParameters) {
  GeneticParameters   gp(0, 0);
  SelectionParameters sp;
  gp.setSelectionParameters(sp);
  EXPECT_EQ(gp.getSelectionParameters(), sp);
}

TEST(GeneticParametersTest, GetAndSetRecombinationParameters) {
  GeneticParameters       gp(0, 0);
  RecombinationParameters rp;
  gp.setRecombinationParameters(rp);
  EXPECT_EQ(gp.getRecombinationParameters(), rp);
}

TEST(GeneticParametersTest, GetAndSetMutationParameters) {
  GeneticParameters  gp(0, 0);
  MutationParameters mp;
  gp.setMutationParameters(mp);
  EXPECT_EQ(gp.getMutationParameters(), mp);
}

TEST(OrientedGraphParametersTest, GetMaxLevelAndElementsTest) {
  OrientedGraphParameters ogp;
  EXPECT_EQ(ogp.getMaxLevel(), 0);
  EXPECT_EQ(ogp.getMaxElements(), 0);
}

TEST(OrientedGraphParametersTest, EmptyTest) {
  OrientedGraphParameters ogp;
  EXPECT_TRUE(ogp.empty());
}

TEST(TruthTableParametersTest, ConstructorTest) {
  TruthTableParameters ttp(3, 2);
  EXPECT_EQ(ttp.getInputs(), 3);
  EXPECT_EQ(ttp.getOutputs(), 2);
  EXPECT_EQ(ttp.size(), 8);  // 2^3 = 8
}

TEST(TruthTableParametersTest, CopyConstructorTest) {
  GeneticParameters    gp(4, 1);
  TruthTableParameters ttp(gp);
  EXPECT_EQ(ttp.getInputs(), 4);
  EXPECT_EQ(ttp.getOutputs(), 1);
}

TEST(TruthTableParametersTest, EqualityOperatorTest) {
  TruthTableParameters ttp1(3, 2);
  TruthTableParameters ttp2(3, 2);
  EXPECT_TRUE(ttp1 == ttp2);

  ttp2.setInputs(4);
  EXPECT_FALSE(ttp1 == ttp2);
}