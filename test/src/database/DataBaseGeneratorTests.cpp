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
  GenerationParameters gParams1("FromRandomTruthTable", "1", 1, 1, 1);
  gParams1.setCNFT(true);
  DataBaseGeneratorParameters dbParams1(
      1, 4, 1, 5, 1, FromRandomTruthTable, gParams1
  );
  DataBaseGenerator generator1(dbParams1);
  generator1.generateType(dbParams1);

  GenerationParameters gParams2("FromRandomTruthTable", "2", 1, 1, 1);
  gParams2.setCNFT(true);
  DataBaseGeneratorParameters dbParams2(
      1, 4, 1, 5, 1, FromRandomTruthTable, gParams2
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

  GenerationParameters gParams3("FromRandomTruthTable", "3", 1, 1, 1);
  gParams3.setCNFT(true);
  DataBaseGeneratorParameters dbParams3(
      2, 6, 2, 6, 3, FromRandomTruthTable, gParams3
  );
  DataBaseGenerator generator3(dbParams3);
  generator3.generateType(dbParams3);

  GenerationParameters gParams4("FromRandomTruthTable", "4", 1, 1, 1);
  gParams4.setCNFT(true);
  DataBaseGeneratorParameters dbParams4(
      2, 6, 2, 6, 3, FromRandomTruthTable, gParams4
  );
  DataBaseGenerator generator4(dbParams4);
  generator4.generateType(dbParams4);

  path1     = "dataset/FromRandomTruthTable/3/";
  path2     = "dataset/FromRandomTruthTable/4/";
  fileCount = countFilesInDirectory(path1);
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
  std::filesystem::remove_all("dataset/FromRandomTruthTable");
}

TEST(GenerateDataBaseRandLevel, EqualWithTheSameSeeds) {
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

  std::string path1     = "dataset/RandLevel/1/";
  std::string path2     = "dataset/RandLevel/2/";
  int         fileCount = countFilesInDirectory(path1);
  for (int i = 0; i < fileCount; ++i) {
    std::string str1 = FilesTools::loadStringFile(
        path1 + "CCGRCG" + std::to_string(i) + "/CCGRCG" + std::to_string(i)
        + ".json"
    );
    std::string str2 = FilesTools::loadStringFile(
        path2 + "CCGRCG" + std::to_string(i) + "/CCGRCG" + std::to_string(i)
        + ".json"
    );
    EXPECT_EQ(str1, str2);
  }

  GenerationParameters gParams3("RandLevel", "3", 1, 1, 1);
  gParams3.setRandLevelParameters(1, 10, 1, 10);
  DataBaseGeneratorParameters dbParams3(2, 6, 2, 6, 4, RandLevel, gParams3);
  DataBaseGenerator           generator3(dbParams3);
  generator1.generateType(dbParams3);

  GenerationParameters gParams4("RandLevel", "4", 1, 1, 1);
  gParams4.setRandLevelParameters(1, 10, 1, 10);
  DataBaseGeneratorParameters dbParams4(2, 6, 2, 6, 4, RandLevel, gParams4);
  DataBaseGenerator           generator4(dbParams4);
  generator2.generateType(dbParams4);

  path1     = "dataset/RandLevel/3/";
  path2     = "dataset/RandLevel/4/";
  fileCount = countFilesInDirectory(path1);
  for (int i = 0; i < fileCount; ++i) {
    std::string str1 = FilesTools::loadStringFile(
        path1 + "CCGRCG" + std::to_string(i) + "/CCGRCG" + std::to_string(i)
        + ".json"
    );
    std::string str2 = FilesTools::loadStringFile(
        path2 + "CCGRCG" + std::to_string(i) + "/CCGRCG" + std::to_string(i)
        + ".json"
    );
    EXPECT_EQ(str1, str2);
  }
  std::filesystem::remove_all("dataset/RandLevel");
}

// Circuits have defferent hashes
// TEST(generateDataBaseNumOperations, EqualWithTheSameSeeds) {
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

//   std::filesystem::remove_all("dataset/NumOperations");
// }

TEST(GenerateDataBaseRandLevelExperimental, EqualWithTheSameSeeds) {
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

  std::string path1     = "dataset/RandLevelExperimental/1/";
  std::string path2     = "dataset/RandLevelExperimental/2/";
  int         fileCount = countFilesInDirectory(path1);
  for (int i = 0; i < fileCount; ++i) {
    std::string str1 = FilesTools::loadStringFile(
        path1 + "CCGRCGE" + std::to_string(i) + "/CCGRCGE" + std::to_string(i)
        + ".json"
    );
    std::string str2 = FilesTools::loadStringFile(
        path2 + "CCGRCGE" + std::to_string(i) + "/CCGRCGE" + std::to_string(i)
        + ".json"
    );
    EXPECT_EQ(str1, str2);
  }

  GenerationParameters gParams3("RandLevelExperimental", "3", 1, 1, 1);
  gParams3.setRandLevelParameters(2, 10, 2, 10);
  DataBaseGeneratorParameters dbParams3(
      2, 7, 2, 7, 3, RandLevelExperimental, gParams3
  );
  DataBaseGenerator generator3(dbParams3);
  generator3.generateType(dbParams3);

  GenerationParameters gParams4("RandLevelExperimental", "4", 1, 1, 1);
  gParams4.setRandLevelParameters(2, 10, 2, 10);
  DataBaseGeneratorParameters dbParams4(
      2, 7, 2, 7, 3, RandLevelExperimental, gParams4
  );
  DataBaseGenerator generator4(dbParams4);
  generator4.generateType(dbParams4);

  path1     = "dataset/RandLevelExperimental/3/";
  path2     = "dataset/RandLevelExperimental/4/";
  fileCount = countFilesInDirectory(path1);
  for (int i = 0; i < fileCount; ++i) {
    std::string str1 = FilesTools::loadStringFile(
        path1 + "CCGRCGE" + std::to_string(i) + "/CCGRCGE" + std::to_string(i)
        + ".json"
    );
    std::string str2 = FilesTools::loadStringFile(
        path2 + "CCGRCGE" + std::to_string(i) + "/CCGRCGE" + std::to_string(i)
        + ".json"
    );
    EXPECT_EQ(str1, str2);
  }
  std::filesystem::remove_all("dataset/RandLevelExperimental");
}
