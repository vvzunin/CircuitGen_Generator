#include "generators/Genetic/Recombination/RecombinationParameters.hpp"

#include <gtest/gtest.h>

#include "easylogging++Init.hpp"

TEST(RecombinationParametersTest, DefaultConstructor) {
  RecombinationParameters params;

  ASSERT_EQ(
      params.getRecombinationType(),
      RecombinationTypes::CrossingEachExitInTurnMany
  );
  ASSERT_EQ(params.getRefPoints(), 1);
  ASSERT_DOUBLE_EQ(params.getMaskProbability(), 0.5);
  ASSERT_EQ(params.getRecombinationParameters(), 1);

  ParentsParameters defaultParentsParams;
  ASSERT_EQ(params.getParentsParameters(), defaultParentsParams);
}

TEST(RecombinationParametersTest, SetAndGetRecombinationType) {
  RecombinationParameters params;
  params.setRecombinationType(RecombinationTypes::CrossingUniform);

  ASSERT_EQ(params.getRecombinationType(), RecombinationTypes::CrossingUniform);
}

TEST(RecombinationParametersTest, SetAndGetRefPoints) {
  RecombinationParameters params;
  params.setRefPoints(5);

  ASSERT_EQ(params.getRefPoints(), 5);
}

TEST(RecombinationParametersTest, SetAndGetMaskProbability) {
  RecombinationParameters params;
  params.setMaskProbability(0.8);

  ASSERT_DOUBLE_EQ(params.getMaskProbability(), 0.8);
}

TEST(RecombinationParametersTest, SetAndGetRecombinationParameters) {
  RecombinationParameters params;
  params.setRecombinationParameters(10);

  ASSERT_EQ(params.getRecombinationParameters(), 10);
}

TEST(RecombinationParametersTest, SetAndGetParentsParameters) {
  RecombinationParameters params;
  ParentsTypes            parentType     = ParentsTypes::Tournament;
  int32_t                 tournamentSize = 3;

  params.setParentsParameters(parentType, tournamentSize);

  ParentsParameters parentsParams = params.getParentsParameters();
  ASSERT_EQ(parentsParams.getParentsType(), parentType);
  ASSERT_EQ(parentsParams.getTournamentNumber(), tournamentSize);
}

TEST(RecombinationParametersTest, EqualityOperator) {
  RecombinationParameters params1;
  RecombinationParameters params2;

  ASSERT_TRUE(params1 == params2);

  params1.setRecombinationType(RecombinationTypes::CrossingUniform);
  ASSERT_FALSE(params1 == params2);

  params2.setRecombinationType(RecombinationTypes::CrossingUniform);
  ASSERT_TRUE(params1 == params2);

  params1.setRefPoints(5);
  ASSERT_FALSE(params1 == params2);

  params2.setRefPoints(5);
  ASSERT_TRUE(params1 == params2);

  params1.setMaskProbability(0.8);
  ASSERT_FALSE(params1 == params2);

  params2.setMaskProbability(0.8);
  ASSERT_TRUE(params1 == params2);

  params1.setRecombinationParameters(10);
  ASSERT_FALSE(params1 == params2);

  params2.setRecombinationParameters(10);
  ASSERT_TRUE(params1 == params2);

  ParentsTypes parentType     = ParentsTypes::Tournament;
  int32_t      tournamentSize = 3;

  params1.setParentsParameters(parentType, tournamentSize);
  ASSERT_FALSE(params1 == params2);

  params2.setParentsParameters(parentType, tournamentSize);
  ASSERT_TRUE(params1 == params2);
}