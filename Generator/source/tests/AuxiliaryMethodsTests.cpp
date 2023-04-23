#include <gtest/gtest.h>
#include <utility>
#include <algorithm>
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

using namespace AuxMethods;

TEST(TestAuxiliaryRemoveSpaces, NormalTest)
{
	//Created  instances of std::string which gonna be input for removeSpaces.
	std::string normalInput1 = "abcd  a";
	std::string normalInput2 = "a    v";
	std::string normalInput3 = "   a";
	std::string normalInput4 = " a1  2  3";
	//EXPECT_EQ(ActualResult , expectedResult):
	EXPECT_EQ(removeSpaces(normalInput1), "abcda");
	EXPECT_EQ(removeSpaces(normalInput2), "av");
	EXPECT_EQ(removeSpaces(normalInput3), "a");
	EXPECT_EQ(removeSpaces(normalInput4), "a123");
}

TEST(TestAuxiliaryRemoveSpaces, RemoveSpacesDeleteAllSpacesWhenTheStringHasOnlySpaces)//By special input I mean string that have only spaces or string that have nothing and so on
{
	std::string OnlySpaces = "                          ";
	EXPECT_EQ((removeSpaces(OnlySpaces)).size(), 0);// If string contain only spaces so that output string have to have no symbols => the size of the string equals to 0

}

