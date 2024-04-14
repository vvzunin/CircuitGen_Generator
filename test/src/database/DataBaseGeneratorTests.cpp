#include <filesystem>
#include <regex>
#include <string>

#include "database/DataBaseGenerator.hpp"

#include <gtest/gtest.h>

#include "additional/filesTools/FilesTools.hpp"
#include "circuit/Circuit.hpp"

int countFilesInDirectory(const std::string& directoryPath) {
  int fileCount = 0;
  for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
    if (std::filesystem::is_directory(entry)) {
      ++fileCount;
    }
  }
  return fileCount;
}

TEST(GenerateDataBaseFromRandomTruthTable, EqualWithTheSameSeeds) {
  std::filesystem::remove_all("dataset/FromRandomTruthTable");
  GenerationParameters gParams1("FromRandomTruthTable", "1", 1, 1, 1);
  gParams1.setCNFT(true);
  DataBaseGeneratorParameters dbParams1(
      1, 2, 1, 5, 1, FromRandomTruthTable, gParams1
  );
  DataBaseGenerator generator1(dbParams1);
  generator1.generateType(dbParams1);

  GenerationParameters gParams2("FromRandomTruthTable", "2", 1, 1, 1);
  gParams2.setCNFT(true);
  DataBaseGeneratorParameters dbParams2(
      1, 2, 1, 5, 1, FromRandomTruthTable, gParams2
  );
  DataBaseGenerator generator2(dbParams2);
  generator2.generateType(dbParams2);

  std::string path1     = "dataset/FromRandomTruthTable/1/";
  std::string path2     = "dataset/FromRandomTruthTable/2/";
  int         fileCount = countFilesInDirectory(path1);
  for (int i = 2; i < fileCount; ++i) {
    std::string str1 = FilesTools::loadStringFile(
        path1 + "CCGRTT" + std::to_string(i) + "_CNFT" + "/CCGRTT"
        + std::to_string(i) + "_CNFT" + ".json"
    );
    std::string str2 = FilesTools::loadStringFile(
        path2 + "CCGRTT" + std::to_string(i) + "_CNFT" + "/CCGRTT"
        + std::to_string(i) + "_CNFT" + ".json"
    );
    EXPECT_EQ(str1, str2);
  }
}

// TEST(GenerateDataBaseRandLevel, EqualWithTheSameSeeds) {
//   std::filesystem::remove_all("dataset/RandLevel");
//   GenerationParameters gParams1("RandLevel", "1", 5, 5, 1);
//   gParams1.setRandLevelParameters(1, 5, 1, 5);
//   DataBaseGeneratorParameters dbParams1(1, 5, 1, 5, 1, RandLevel, gParams1);
//   DataBaseGenerator           generator1(dbParams1);
//   generator1.generateType(dbParams1);

//   GenerationParameters gParams2("RandLevel", "2", 5, 5, 1);
//   gParams2.setRandLevelParameters(1, 5, 1, 5);
//   DataBaseGeneratorParameters dbParams2(1, 5, 1, 5, 1, RandLevel, gParams2);
//   DataBaseGenerator           generator2(dbParams2);
//   generator2.generateType(dbParams2);

//   std::string path1     = "dataset/RandLevel/1/";
//   std::string path2     = "dataset/RandLevel/2/";
//   int         fileCount = countFilesInDirectory(path1);
//   for (int i = 0; i < fileCount; ++i) {
//     std::string str1 = FilesTools::loadStringFile(
//         path1 + "CCGRCG" + std::to_string(i) + "/CCGRCG" + std::to_string(i)
//         + ".json"
//     );
//     std::string str2 = FilesTools::loadStringFile(
//         path2 + "CCGRCG" + std::to_string(i) + "/CCGRCG" + std::to_string(i)
//         + ".json"
//     );
//     EXPECT_EQ(str1, str2);
//   }
// }

// TEST(generateDataBaseNumOperations, EqualWithTheSameSeeds) {
//   std::filesystem::remove_all("dataset/NumOperations");
//   GenerationParameters gParams1("NumOperations", "1", 5, 5, 1);
//   std::map<Gates, int> logicOper = {
//       {Gates::GateAnd, 5},
//       {Gates::GateOr, 5},
//       {Gates::GateNot, 6},
//       {Gates::GateNor, 6},
//       {Gates::GateNand, 1},
//       {Gates::GateXnor, 9},
//       {Gates::GateXor, 12}};
//   gParams1.setNumOperationParameters(logicOper, false);
//   DataBaseGeneratorParameters dbParams1(1, 5, 1, 5, 1, NumOperation,
//   gParams1); DataBaseGenerator           generator1(dbParams1);
//   generator1.generateType(dbParams1);

//   GenerationParameters gParams2("NumOperations", "2", 5, 5, 1);
//   gParams2.setNumOperationParameters(logicOper, false);
//   DataBaseGeneratorParameters dbParams2(1, 5, 1, 5, 1, NumOperation,
//   gParams2); DataBaseGenerator           generator2(dbParams2);
//   generator2.generateType(dbParams2);
// }

// TEST(GenerateDataBaseRandLevelExperimental, EqualWithTheSameSeeds) {
//   std::filesystem::remove_all("dataset/RandLevelExperimental");
//   GenerationParameters gParams1("RandLevelExperimental", "1", 5, 5, 1);
//   gParams1.setRandLevelParameters(1, 5, 1, 5);
//   DataBaseGeneratorParameters dbParams1(
//       1, 5, 1, 5, 1, RandLevelExperimental, gParams1
//   );
//   DataBaseGenerator generator1(dbParams1);
//   generator1.generateType(dbParams1);

//   GenerationParameters gParams2("RandLevelExperimental", "2", 5, 5, 1);
//   gParams2.setRandLevelParameters(1, 5, 1, 5);
//   DataBaseGeneratorParameters dbParams2(
//       1, 5, 1, 5, 1, RandLevelExperimental, gParams2
//   );
//   DataBaseGenerator generator2(dbParams2);
//   generator2.generateType(dbParams2);

//   std::string path1     = "dataset/RandLevelExperimental/1/";
//   std::string path2     = "dataset/RandLevelExperimental/2/";
//   int         fileCount = countFilesInDirectory(path1);
//   for (int i = 0; i < fileCount; ++i) {
//     std::string str1 = FilesTools::loadStringFile(
//         path1 + "CCGRCGE" + std::to_string(i) + "/CCGRCGE" +
//         std::to_string(i)
//         + ".json"
//     );
//     std::string str2 = FilesTools::loadStringFile(
//         path2 + "CCGRCGE" + std::to_string(i) + "/CCGRCGE" +
//         std::to_string(i)
//         + ".json"
//     );
//     EXPECT_EQ(str1, str2);
//   }
// }
