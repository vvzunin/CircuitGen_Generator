#include <gtest/gtest.h>
#include "../AuxiliaryMethods.h"

TEST(test_aux_methods, test_remove_spaces_without_spaces)
{
  std::string answer = "word";
  EXPECT_EQ(answer, AuxMethods::removeSpaces(answer));
}

TEST(test_aux_methods, test_read_empty_file)
{
  std::string answer = "";
  std::string path = "../../test_data/AuxMethods/test_empty_file.txt";

  EXPECT_EQ(answer, AuxMethods::readAllFile(path));
}

TEST(test_aux_methods, test_read_one_line)
{
  std::string answer = "one line";
  std::string path = "../../test_data/AuxMethods/one_line_file.txt";

  EXPECT_EQ(answer, AuxMethods::readAllFile(path));
}

TEST(test_aux_methods, test_read_two_lines)
{
  std::string answer = "one line\ntwo line";
  std::string path = "../../test_data/AuxMethods/test_two_lines.txt";

  EXPECT_EQ(answer, AuxMethods::readAllFile(path));
}

TEST(test_aux_methods, test_read_one_line_with_tab)
{
  std::string answer = "one\ttab";
  std::string path = "../../test_data/AuxMethods/test_one_line_with_tab.txt";

  EXPECT_EQ(answer, AuxMethods::readAllFile(path));
}

TEST(test_aux_methods, test_read_two_line_with_tab)
{
  std::string answer = "this\tis 2 lines\nthis is\tsecond line";
  std::string path = "../../test_data/AuxMethods/test_two_line_with_tab.txt";

  EXPECT_EQ(answer, AuxMethods::readAllFile(path));
}

TEST(test_aux_methods, test_read_non_existent_file)
{
  std::string answer = "";
  std::string path = "../../test_data/AuxMethods/bla_bla_bla.txt";

  EXPECT_THROW(AuxMethods::readAllFile(path), std::runtime_error);
}


