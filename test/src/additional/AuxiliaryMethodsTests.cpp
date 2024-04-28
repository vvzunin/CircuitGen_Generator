#include <algorithm>
#include <utility>

#include "additional/AuxiliaryMethods.hpp"

#include <gtest/gtest.h>

TEST(test_aux_methods, test_remove_spaces_without_spaces) {
  std::string answer = "word";
  EXPECT_EQ(answer, AuxMethods::removeSpaces(answer));
}

TEST(test_aux_methods, test_read_empty_file) {
  std::string answer = "";
  std::string path =
      "src/additional/testData_AuxiliaryMethodsTests/"
      "test_empty_file.txt";

  EXPECT_EQ(answer, AuxMethods::readAllFile(path));
}

TEST(test_aux_methods, test_read_one_line) {
  std::string answer = "one line";
  std::string path =
      "src/additional/testData_AuxiliaryMethodsTests/"
      "one_line_file.txt";

  EXPECT_EQ(answer, AuxMethods::readAllFile(path));
}

TEST(test_aux_methods, test_read_two_lines) {
  std::string answer = "one line\ntwo line";
  std::string path =
      "src/additional/testData_AuxiliaryMethodsTests/"
      "test_two_lines.txt";

  EXPECT_EQ(answer, AuxMethods::readAllFile(path));
}

TEST(test_aux_methods, test_read_one_line_with_tab) {
  std::string answer = "one\ttab";
  std::string path =
      "src/additional/testData_AuxiliaryMethodsTests/"
      "test_one_line_with_tab.txt";

  EXPECT_EQ(answer, AuxMethods::readAllFile(path));
}

TEST(test_aux_methods, test_read_two_line_with_tab) {
  std::string answer = "this\tis 2 lines\nthis is\tsecond line";
  std::string path =
      "src/additional/testData_AuxiliaryMethodsTests/"
      "test_two_line_with_tab.txt";

  EXPECT_EQ(answer, AuxMethods::readAllFile(path));
}

TEST(test_aux_methods, test_read_non_existent_file) {
  std::string answer = "";
  std::string path =
      "src/additional/testData_AuxiliaryMethodsTests/"
      "bla_bla_bla.txt";

  EXPECT_THROW(AuxMethods::readAllFile(path), std::runtime_error);
}

using namespace AuxMethods;

TEST(TestAuxiliaryRemoveSpaces, NormalTest) {
  // Created  instances of std::string which going to be input for removeSpaces.
  std::string normalInput1 = "abcd  a";
  std::string normalInput2 = "a    v";
  std::string normalInput3 = "   a";
  std::string normalInput4 = " a1  2  3";
  // EXPECT_EQ(ActualResult , expectedResult):
  EXPECT_EQ(removeSpaces(normalInput1), "abcda");
  EXPECT_EQ(removeSpaces(normalInput2), "av");
  EXPECT_EQ(removeSpaces(normalInput3), "a");
  EXPECT_EQ(removeSpaces(normalInput4), "a123");
}

TEST(
    TestAuxiliaryRemoveSpaces,
    RemoveSpacesDeleteAllSpacesWhenTheStringHasOnlySpaces
)  // By special input I mean string that have only spaces or string that have
   // nothing and so on
{
  std::string OnlySpaces = "                          ";
  EXPECT_EQ(
      (removeSpaces(OnlySpaces)).size(), 0
  );  // If string contain only spaces so that output string have to have no
      // symbols => the size of the string equals to 0
}

TEST(
    TestAuxiliaryRemoveSpaces,
    RemoveSpacesDoesNothingWithStringHasNoSpaces
)  // By special input I mean string that have only spaces or string that have
   // nothing and so on
{
  std::string NoSpaces = "StringWithoutSpaces";
  EXPECT_EQ(
      NoSpaces, removeSpaces(NoSpaces)
  );  // If there no spaces in the string so that it must not be changed after
      // removeSpaces;
}

TEST(TestAuxiliarySortDictByValue, NormalTest) {
  // Just created some maps that going to be input for  sortDictByValue
  std::map<std::string, int> normalInput1 = {
      {"0", 0}, {"1", 1}, {"2", 2}, {"3", 3}};
  std::map<std::string, int> normalInput2 = {
      {"0", 110}, {"1", 10}, {"2", 20}, {"3", 3}};
  std::map<std::string, int> normalInput3 = {
      {"0", 1100}, {"1", 1}, {"2", 1}, {"3", 33}};
  // Here I created vector correctAnswer which I will use to compare with the
  // result of sortDictByValue
  std::vector<std::pair<std::string, int>> correctAnswer;
  // Here I fill the vector with expected from sortDictByValue(testDict1, false)
  // data
  correctAnswer.push_back({"3", 3});
  correctAnswer.push_back({"2", 2});
  correctAnswer.push_back({"1", 1});
  correctAnswer.push_back({"0", 0});
  // Here I check the equality of the expected data and the data that I have
  // from sortDictByValue
  EXPECT_EQ(correctAnswer, sortDictByValue(normalInput1, false));
  std::reverse(
      correctAnswer.begin(), correctAnswer.end()
  );  // reverse it because now I going to check the result of
      // sortDictByValue(testDict1, true) when up == true
  EXPECT_EQ(correctAnswer, sortDictByValue(normalInput1, true));
  correctAnswer.clear();  // Make it clear to fill it again with data which I
                          // expected from sortDictByValue(testDict2, true)
  // Below just repetition the same logic as above
  correctAnswer.push_back({"3", 3});
  correctAnswer.push_back({"1", 10});
  correctAnswer.push_back({"2", 20});
  correctAnswer.push_back({"0", 110});
  EXPECT_EQ(correctAnswer, sortDictByValue(normalInput2, true));
  std::reverse(correctAnswer.begin(), correctAnswer.end());
  EXPECT_EQ(correctAnswer, sortDictByValue(normalInput2, false));

  correctAnswer.clear();
  correctAnswer.push_back({"1", 1});
  correctAnswer.push_back({"2", 1});
  correctAnswer.push_back({"3", 33});
  correctAnswer.push_back({"0", 1100});
  EXPECT_EQ(correctAnswer, sortDictByValue(normalInput3, true));
  std::reverse(correctAnswer.begin(), correctAnswer.end());
  EXPECT_EQ(correctAnswer, sortDictByValue(normalInput3, false));
}

TEST(
    TestAuxiliarySortDictByValue,
    SortDictByValueReturnEmptyVectorWhenThereEmptyDictionary
) {
  // Just created a map that going to be input for  sortDictByValue
  std::map<std::string, int> EmptyMap = {};
  EXPECT_EQ(
      0, (sortDictByValue(EmptyMap, true)).size()
  );  // Check to make sure that output of sortDictByValue(testDict1, true) has
      // nothing
  EXPECT_EQ(
      0, (sortDictByValue(EmptyMap, false)).size()
  );  // Check to make sure that output of sortDictByValue(testDict1, false) has
      // nothing
}

TEST(TestAuxiliarySortDictByValue, WhenThereTheSameValuesInDictionary) {
  // Just created a map that's going to be input for  sortDictByValue
  std::map<std::string, int> TheSameElements = {
      {"1", 1}, {"2", 1}, {"3", 1}, {"4", 1}, {"5", 1}};
  // Here I created vector correctAnswer which I will use to compare with the
  // result of sortDictByValue
  std::vector<std::pair<std::string, int>> correctAnswer;
  // Here I fill the vector with expected from sortDictByValue(testDict1, false)
  // data
  correctAnswer.push_back({"1", 1});
  correctAnswer.push_back({"2", 1});
  correctAnswer.push_back({"3", 1});
  correctAnswer.push_back({"4", 1});
  correctAnswer.push_back({"5", 1});
  EXPECT_EQ(
      correctAnswer, sortDictByValue(TheSameElements, true)
  );  // No matter true or false second input of sortDictByValue the answer msut
      // be the same
}
