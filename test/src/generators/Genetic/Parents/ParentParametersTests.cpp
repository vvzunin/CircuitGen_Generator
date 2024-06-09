#include <gtest/gtest.h>

#include "generators/Genetic/Parents/Parents.hpp"

TEST(ParentsParametersTest, SetAndGetParentsType) {
  ParentsParameters params;
  params.setParentsType(ParentsTypes::Tournament);
  ASSERT_EQ(params.getParentsType(), ParentsTypes::Tournament);

  params.setParentsType(ParentsTypes::Roulette);
  ASSERT_EQ(params.getParentsType(), ParentsTypes::Roulette);
}

TEST(ParentsParametersTest, SetAndGetTournamentNumber) {
  ParentsParameters params;
  params.setTournamentNumber(5);
  ASSERT_EQ(params.getTournamentNumber(), 5);

  params.setTournamentNumber(10);
  ASSERT_EQ(params.getTournamentNumber(), 10);
}