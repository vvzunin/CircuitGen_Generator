#include "generators/Genetic/Mutations/MutationParameters.hpp"

#include <gtest/gtest.h>

#include "easylogging++Init.hpp"

TEST(MutationParametersTest, SetAndGetMutationType) {
  MutationParameters params;
  params.setMutationType(MutationTypes::Density);
  EXPECT_EQ(params.getMutationType(), MutationTypes::Density);
}

TEST(MutationParametersTest, SetAndGetProbabilityGen) {
  MutationParameters params;
  double             probGen = 0.5;
  params.setProbabilityGen(probGen);
  EXPECT_DOUBLE_EQ(params.getProbabilityGen(), probGen);
}

TEST(MutationParametersTest, SetAndGetExchangeType) {
  MutationParameters params;
  int32_t            exchangeType = 2;
  params.setExchangeType(exchangeType);
  EXPECT_EQ(params.getExchangeType(), exchangeType);
}

TEST(MutationParametersTest, SetAndGetProbabilityTruthTable) {
  MutationParameters params;
  double             probTruthTable = 0.7;
  params.setProbabilityTruthTable(probTruthTable);
  EXPECT_DOUBLE_EQ(params.getProbabilityTruthTable(), probTruthTable);
}

TEST(MutationParametersTest, EqualityOperator) {
  MutationParameters params1;
  params1.setMutationType(MutationTypes::Exchange);
  params1.setProbabilityGen(0.5);
  params1.setExchangeType(2);
  params1.setProbabilityTruthTable(0.7);

  MutationParameters params2;
  params2.setMutationType(MutationTypes::Exchange);
  params2.setProbabilityGen(0.5);
  params2.setExchangeType(2);
  params2.setProbabilityTruthTable(0.7);

  EXPECT_TRUE(params1 == params2);
}

TEST(MutationParametersTest, InequalityOperator) {
  MutationParameters params1;
  params1.setMutationType(MutationTypes::Exchange);
  params1.setProbabilityGen(0.5);
  params1.setExchangeType(2);
  params1.setProbabilityTruthTable(0.7);

  MutationParameters params2;
  params2.setMutationType(MutationTypes::Binary);
  params2.setProbabilityGen(0.5);
  params2.setExchangeType(2);
  params2.setProbabilityTruthTable(0.7);

  EXPECT_FALSE(params1 == params2);
}