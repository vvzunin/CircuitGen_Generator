#include <gtest/gtest.h>
#include "../optimization_utils/AbcUtils.h"

TEST(GetStatsTest, ErrorWithInvalidLibraryName) {
  AbcUtils util;
  std::string libName = "incorrect_libname.lib";
  std::string libPath = "../../../libs";
  auto result = util.getStats("correct_filename.v", libName,
    "../../test_data/OpitmizationUtilits", libPath);
  std::string errorText = "Incorrect read: Cannot open input file \""
    + libPath + "/" + libName + "\". \n\n";
  std::string errorResult = result.commandsOutput["error"];

  EXPECT_EQ(errorResult, errorText);
}

TEST(GetStatsTest, ErrorWithInvalidFileName) {
  AbcUtils util;
  auto result = util.getStats("correct_filename.v", "sky130.lib",
    "../../test_data/OpitmizationUtilits", "../../../libs");
  std::string readFlag = result.commandsOutput["fileRead"];

  EXPECT_EQ(readFlag, "true");

  result = util.getStats("incorrect_filename.v", "sky130.lib",
    "../../test_data/OpitmizationUtilits", "../../../libs");
  readFlag = result.commandsOutput["fileRead"];

  EXPECT_EQ(readFlag, "false");
}

TEST(GetStatsTest, ErrorWithInvalidFilePath) {
  AbcUtils util;
  auto result = util.getStats("correct_filename.v", "sky130.lib",
    "../../test_data/OpitmizationUtilits", "../../../libs");
  std::string readFlag = result.commandsOutput["fileRead"];

  EXPECT_EQ(readFlag, "true");

  result = util.getStats("correct_filename.v", "sky130.lib",
    "incorrect_filepath", "../../../libs");
  readFlag = result.commandsOutput["fileRead"];

  EXPECT_EQ(readFlag, "false");
}

TEST(GetStatsTest, ErrorWithInvalidLibraryPath) {
  AbcUtils util;
  std::string libPath = "incorrect_libpath";
  auto result = util.getStats("correct_filename.v", "lib130",
    "../../test_data/OpitmizationUtilits", libPath);
  std::string errorText = "Incorrect map: Warning: The network was " 
    "strashed and balanced before mapping.\nThe current library "
    "is not available.\nError: Mapping has failed.\n\n";
  std::string errorResult = result.commandsOutput["error"];

  EXPECT_EQ(errorResult, errorText);
}

