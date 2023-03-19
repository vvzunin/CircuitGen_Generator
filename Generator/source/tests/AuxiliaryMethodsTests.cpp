#include <gtest/gtest.h>
#include "../AuxiliaryMethods.h"

TEST(test_aux_methods, test_remove_spaces_without_spaces)
{
  std::string ans = "word";
  EXPECT_EQ(ans, AuxMethods::removeSpaces(ans));
}
