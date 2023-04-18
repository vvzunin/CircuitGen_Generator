#include <gtest/gtest.h>
#include "../Settings.cpp"

TEST(test_settings, test_default_load_settings)
{
  Settings* t = Settings::getInstance("test_default_load_settings");

  std::map<int, std::vector<std::string>> operToHierAns;
  operToHierAns[0] = {"="};
  operToHierAns[1] = {"nor"};
  operToHierAns[2] = {"or"};
  operToHierAns[3] = {"nand"};
  operToHierAns[4] = {"and"};
  operToHierAns[5] = {"xnor"};
  operToHierAns[6] = {"xor"};
  operToHierAns[7] = {"not"};
  operToHierAns[8] = {"buf"};
  operToHierAns[9] = {"1'b"};
  operToHierAns[10] = {""};

  std::map<std::string, std::string> operToNameAns;

  operToNameAns[""] = "input";
  operToNameAns["="] = "output";
  operToNameAns["1'b"] = "const";
  operToNameAns["and"] = "and";
  operToNameAns["nand"] = "nand";
  operToNameAns["or"] = "or";
  operToNameAns["nor"] = "nor";
  operToNameAns["not"] = "not";
  operToNameAns["buf"] = "buf";
  operToNameAns["xor"] = "xor";
  operToNameAns["xnor"] = "xnor";

  for (const auto& [key, value] : operToHierAns)
  {
    EXPECT_EQ(value, t->fromOperationsToHierarchy(key));
  }

  for (const auto& [key, value] : operToNameAns)
  {
    EXPECT_EQ(value, t->fromOperationsToName(key));
  }
}
