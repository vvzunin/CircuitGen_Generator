#include <filesystem>

#include "database/DataBaseGenerator.hpp"

#include <gtest/gtest.h>

#include "additional/filesTools/FilesTools.hpp"
#include "circuit/Circuit.hpp"

/*TEST(GenerateDataBaseFromRandomTruthTable, EqualWithTheSameSeeds) {
  std::filesystem::remove_all("dataset/FromRandomTruthTable");
  GenerationParameters gParams1("FromRandomTruthTable", "1", 5, 5, 1);
  gParams1.setCNFT(true);
  DataBaseGeneratorParameters dbParams1(
      1, 5, 1, 5, 1, FromRandomTruthTable, gParams1
  );
  DataBaseGenerator generator1(dbParams1);
  generator1.generateType(dbParams1);

  GenerationParameters gParams2("FromRandomTruthTable", "2", 5, 5, 1);
  gParams2.setCNFT(true);
  DataBaseGeneratorParameters dbParams2(
      1, 5, 1, 5, 1, FromRandomTruthTable, gParams2
  );
  DataBaseGenerator generator2(dbParams2);
  generator2.generateType(dbParams2);
}*/

/*TEST(GenerateDataBaseRandLevel, EqualWithTheSameSeeds) {
  std::filesystem::remove_all("dataset/RandLevel");
  GenerationParameters gParams1("RandLevel", "1", 5, 5, 1);
  gParams1.setRandLevelParameters(1, 5, 1, 5);
  DataBaseGeneratorParameters dbParams1(1, 5, 1, 5, 1, RandLevel, gParams1);
  DataBaseGenerator           generator1(dbParams1);
  generator1.generateType(dbParams1);
  std::string str1 =
      FilesTools::loadStringFile("dataset/RandLevel/1/CCGRCG0/CCGRCG0.v");

  GenerationParameters gParams2("RandLevel", "2", 5, 5, 1);
  gParams2.setRandLevelParameters(1, 5, 1, 5);
  DataBaseGeneratorParameters dbParams2(1, 5, 1, 5, 1, RandLevel, gParams2);
  DataBaseGenerator           generator2(dbParams2);
  generator2.generateType(dbParams2);
  std::string str2 =
      FilesTools::loadStringFile("dataset/RandLevel/2/CCGRCG0/CCGRCG0.v");
  EXPECT_EQ(str1, str2);
}*/

/*TEST(generateDataBaseNumOperations, EqualWithTheSameSeeds) {
  std::filesystem::remove_all("data/NumOperations");
  GenerationParameters gParams1("NumOperations", "1", 5, 5, 1);
  std::map<Gates, int> logicOper = {
      {Gates::GateAnd, 5},
      {Gates::GateOr, 5},
      {Gates::GateNot, 6},
      {Gates::GateNor, 6},
      {Gates::GateNand, 1},
      {Gates::GateXnor, 9},
      {Gates::GateXor, 12}};
  gParams1.setNumOperationParameters(logicOper, false);
  DataBaseGeneratorParameters dbParams1(1, 5, 1, 5, 1, NumOperation, gParams1);
  DataBaseGenerator           generator1(dbParams1);
  generator1.generateType(dbParams1);

  GenerationParameters gParams2("NumOperations", "2", 5, 5, 1);
  gParams2.setNumOperationParameters(logicOper, false);
  DataBaseGeneratorParameters dbParams2(1, 5, 1, 5, 1, NumOperation, gParams2);
  DataBaseGenerator           generator2(dbParams2);
  generator2.generateType(dbParams2);
}*/

/*TEST(GenerateDataBaseRandLevelExperimental, EqualWithTheSameSeeds) {
  std::filesystem::remove_all("dataset/RandLevelExperimental");
  GenerationParameters gParams1("RandLevelExperimental", "1", 5, 5, 1);
  gParams1.setRandLevelParameters(1, 5, 1, 5);
  DataBaseGeneratorParameters dbParams1(
      1, 5, 1, 5, 1, RandLevelExperimental, gParams1
  );
  DataBaseGenerator generator1(dbParams1);
  generator1.generateType(dbParams1);
  std::string str1 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/1/CCGRCG0/CCGRCG0.v"
  );

  GenerationParameters gParams2("RandLevelExperimental", "2", 5, 5, 1);
  gParams2.setRandLevelParameters(1, 5, 1, 5);
  DataBaseGeneratorParameters dbParams2(
      1, 5, 1, 5, 1, RandLevelExperimental, gParams2
  );
  DataBaseGenerator generator2(dbParams2);
  generator2.generateType(dbParams2);
  std::string str2 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/2/CCGRCG0/CCGRCG0.v"
  );
  EXPECT_EQ(str1, str2);
}*/
