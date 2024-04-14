#include <filesystem>
#include <regex>
#include <string>

#include "database/DataBaseGenerator.hpp"

#include <gtest/gtest.h>

#include "additional/filesTools/FilesTools.hpp"
#include "circuit/Circuit.hpp"

std::string unifySchemas(const std::string& schema) {
  // Регулярное выражение для поиска индексов после символа '_'
  std::regex  indexRegex("_\\d+");

  // Формат для замены индексов
  std::string replacement = "_INDEX";

  // Замена всех индексов на общий формат
  std::string unifiedSchema =
      std::regex_replace(schema, indexRegex, replacement);

  return unifiedSchema;
}

// TEST(GenerateDataBaseFromRandomTruthTable, EqualWithTheSameSeeds) {
//   std::filesystem::remove_all("dataset/FromRandomTruthTable");
//   GenerationParameters gParams1("FromRandomTruthTable", "1", 5, 5, 1);
//   gParams1.setCNFT(true);
//   DataBaseGeneratorParameters dbParams1(
//       1, 5, 1, 5, 1, FromRandomTruthTable, gParams1
//   );
//   DataBaseGenerator generator1(dbParams1);
//   generator1.generateType(dbParams1);

//   GenerationParameters gParams2("FromRandomTruthTable", "2", 5, 5, 1);
//   gParams2.setCNFT(true);
//   DataBaseGeneratorParameters dbParams2(
//       1, 5, 1, 5, 1, FromRandomTruthTable, gParams2
//   );
//   DataBaseGenerator generator2(dbParams2);
//   generator2.generateType(dbParams2);
// }

TEST(GenerateDataBaseRandLevel, EqualWithTheSameSeeds) {
  std::filesystem::remove_all("dataset/RandLevel");
  GenerationParameters gParams1("RandLevel", "1", 5, 5, 1);
  gParams1.setRandLevelParameters(1, 5, 1, 5);
  DataBaseGeneratorParameters dbParams1(1, 5, 1, 5, 1, RandLevel, gParams1);
  DataBaseGenerator           generator1(dbParams1);
  generator1.generateType(dbParams1);

  GenerationParameters gParams2("RandLevel", "2", 5, 5, 1);
  gParams2.setRandLevelParameters(1, 5, 1, 5);
  DataBaseGeneratorParameters dbParams2(1, 5, 1, 5, 1, RandLevel, gParams2);
  DataBaseGenerator           generator2(dbParams2);
  generator2.generateType(dbParams2);

  // 0
  int         count = 0;
  std::string str1  = FilesTools::loadStringFile(
      "dataset/RandLevel/1/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  std::string str2 = FilesTools::loadStringFile(
      "dataset/RandLevel/2/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 1
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevel/1/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevel/2/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 2
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevel/1/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevel/2/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 3
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevel/1/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevel/2/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 4
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevel/1/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevel/2/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 5
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevel/1/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevel/2/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 6
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevel/1/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevel/2/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 7
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevel/1/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevel/2/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 8
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevel/1/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevel/2/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 9
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevel/1/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevel/2/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 10
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevel/1/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevel/2/CCGRCG" + std::to_string(count) + "/CCGRCG"
      + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));
}

TEST(generateDataBaseNumOperations, EqualWithTheSameSeeds) {
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

  // 0
  int         count = 0;
  std::string str1  = FilesTools::loadStringFile(
      "dataset/NumOperations/1/CCGRVC" + std::to_string(count) + "/CCGRVC"
      + std::to_string(count) + ".v"
  );
  std::string str2 = FilesTools::loadStringFile(
      "dataset/NumOperations/2/CCGRVC" + std::to_string(count) + "/CCGRVC"
      + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 1
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/NumOperations/1/CCGRVC" + std::to_string(count) + "/CCGRVC"
      + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/NumOperations/2/CCGRVC" + std::to_string(count) + "/CCGRVC"
      + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  //   // 2
  //   count++;
  //   str1 = FilesTools::loadStringFile(
  //       "dataset/NumOperations/1/CCGRVC" + std::to_string(count) + "/CCGRVC"
  //       + std::to_string(count) + ".v"
  //   );
  //   str2 = FilesTools::loadStringFile(
  //       "dataset/NumOperations/2/CCGRVC" + std::to_string(count) + "/CCGRVC"
  //       + std::to_string(count) + ".v"
  //   );
  //   EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));
}

TEST(GenerateDataBaseRandLevelExperimental, EqualWithTheSameSeeds) {
  std::filesystem::remove_all("dataset/RandLevelExperimental");
  GenerationParameters gParams1("RandLevelExperimental", "1", 5, 5, 1);
  gParams1.setRandLevelParameters(1, 5, 1, 5);
  DataBaseGeneratorParameters dbParams1(
      1, 5, 1, 5, 1, RandLevelExperimental, gParams1
  );
  DataBaseGenerator generator1(dbParams1);
  generator1.generateType(dbParams1);

  GenerationParameters gParams2("RandLevelExperimental", "2", 5, 5, 1);
  gParams2.setRandLevelParameters(1, 5, 1, 5);
  DataBaseGeneratorParameters dbParams2(
      1, 5, 1, 5, 1, RandLevelExperimental, gParams2
  );
  DataBaseGenerator generator2(dbParams2);
  generator2.generateType(dbParams2);

  // 0
  int         count = 0;
  std::string str1  = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/1/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  std::string str2 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/2/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 1
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/1/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/2/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 2
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/1/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/2/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 3
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/1/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/2/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 4
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/1/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/2/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 5
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/1/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/2/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 6
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/1/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/2/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 7
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/1/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/2/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 8
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/1/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/2/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 9
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/1/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/2/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));

  // 10
  count++;
  str1 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/1/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  str2 = FilesTools::loadStringFile(
      "dataset/RandLevelExperimental/2/CCGRCGE" + std::to_string(count)
      + "/CCGRCGE" + std::to_string(count) + ".v"
  );
  EXPECT_EQ(unifySchemas(str1), unifySchemas(str2));
}
