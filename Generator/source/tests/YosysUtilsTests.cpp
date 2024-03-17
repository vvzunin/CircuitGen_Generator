#include <gtest/gtest.h>

#include "../optimization_utils/YosysUtils.h"

TEST (WriteFirrtlTest, ErrorWithInvalidFileName) {
  YosysUtils util;
  auto result = util.writeFirrtl("incorrect_filename.v", "aaa",
    "../../test_data/OpitmizationUtilits");
  std::string errorText = "Incorrect write_firrtl: ERROR: "
    "Can't open input file `incorrect_filename.v' for reading: "
    "No such file or directory\n\n";
  std::string errorResult = result.commandsOutput["error"];

  EXPECT_EQ(errorResult, errorText);

  std::remove("../../test_data/OpitmizationUtilits/aaa");
}

TEST (WriteFirrtlTest, ErrorWithInvalidFilePath) {
  YosysUtils util;
  auto result = util.writeFirrtl("correct_filename.v", "aaa",
    "incorrect_filepath");
  std::string errorText = "Something went wrong during files parsing "
    "in YosysUtils: \nsh: 1: cd: can't cd to incorrect_filepath\n";
  std::string errorResult = result.commandsOutput["error"];
  EXPECT_EQ(errorResult, errorText);
}
