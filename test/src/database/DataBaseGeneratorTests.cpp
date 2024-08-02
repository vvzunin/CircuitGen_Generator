#include <algorithm>
#include <filesystem>
#include <string>

#include "database/DataBaseGenerator.hpp"

#include <gtest/gtest.h>

#include "additional/filesTools/FilesTools.hpp"
#include "circuit/Circuit.hpp"
#include "easylogging++Init.hpp"

std::vector<std::string> getJsons(std::string& path) {
  std::vector<std::string> names = FilesTools::getDirectories(path);
  std::sort(names.begin(), names.end());
  std::vector<std::string> jsons;
  for (const auto& name : names) {
    if (!std::filesystem::is_empty(path + "/" + name)) {
      std::string json = path + "/" + name + "/" + name + ".json";
      if (std::filesystem::exists(json))
        jsons.push_back(json);
    }
  }
  return jsons;
}

TEST(GenerateDataBaseFromRandomTruthTable, EqualWithTheSameSeeds) {
  std::string mainDir = "dataset";
  std::string dir     = "FromRandomTruthTable";

  struct by_hash {
    bool operator()(GraphPtr a, GraphPtr b) const {
      return a->calculateHash() < b->calculateHash();
    }
  };

  GenerationParameters gParams1(dir, "1", 1, 1, 1);
  gParams1.setCNFT(true);
  DataBaseGeneratorParameters dbParams1(
      1, 4, 1, 5, 1, FromRandomTruthTable, gParams1
  );
  DataBaseGenerator generator1(dbParams1);
  auto              part1 = generator1.generateTypeForGraph(dbParams1).second;
  std::sort(part1.begin(), part1.end(), by_hash());

  GenerationParameters gParams2(dir, "2", 1, 1, 1);
  gParams2.setCNFT(true);
  DataBaseGeneratorParameters dbParams2(
      1, 4, 1, 5, 1, FromRandomTruthTable, gParams2
  );
  DataBaseGenerator generator2(dbParams2);
  auto              part2 = generator2.generateTypeForGraph(dbParams2).second;
  std::sort(part2.begin(), part2.end(), by_hash());

  // receive all json files
  // std::string       dir1  = mainDir + "/" + dir + "/" + "1";
  // std::string       dir2  = mainDir + "/" + dir + "/" + "2";
  // std::vector<std::string> jsons1 = getJsons(dir1);
  // std::vector<std::string> jsons2 = getJsons(dir2);
  // ASSERT_EQ(jsons1.empty(), false);
  // ASSERT_EQ(jsons1.size(), jsons2.size());

  // for (int i = 0; i < jsons1.size(); ++i) {
  //   EXPECT_EQ(
  //       FilesTools::loadStringFile(jsons1[i]),
  //       FilesTools::loadStringFile(jsons2[i])
  //   );
  // }

  for (size_t i = 0; i < part1.size(); ++i) {
    EXPECT_EQ(part1[i]->calculateHash(), part2[i]->calculateHash());
  }

  GenerationParameters gParams3("FromRandomTruthTable", "3", 1, 1, 1);
  gParams3.setCNFT(true);
  DataBaseGeneratorParameters dbParams3(
      2, 6, 2, 6, 1, FromRandomTruthTable, gParams3
  );
  DataBaseGenerator generator3(dbParams3);
  auto              part3 = generator3.generateTypeForGraph(dbParams3).second;
  std::sort(part3.begin(), part3.end(), by_hash());

  GenerationParameters gParams4("FromRandomTruthTable", "4", 1, 1, 1);
  gParams4.setCNFT(true);
  DataBaseGeneratorParameters dbParams4(
      2, 6, 2, 6, 1, FromRandomTruthTable, gParams4
  );
  DataBaseGenerator generator4(dbParams4);
  auto              part4 = generator4.generateTypeForGraph(dbParams4).second;
  std::sort(part4.begin(), part4.end(), by_hash());

  // dir1   = mainDir + "/" + dir + "/" + "3";
  // dir2   = mainDir + "/" + dir + "/" + "4";
  // jsons1 = getJsons(dir1);
  // jsons2 = getJsons(dir2);
  // ASSERT_EQ(jsons1.empty(), false);
  // ASSERT_EQ(jsons1.size(), jsons2.size());

  for (size_t i = 0; i < part3.size(); ++i) {
    EXPECT_EQ(part3[i]->calculateHash(), part4[i]->calculateHash());
  }
  std::filesystem::remove_all(mainDir + "/" + dir);
}

TEST(GenerateDataBaseRandLevel, EqualWithTheSameSeeds) {
  std::string          mainDir = "dataset";
  std::string          dir     = "RandLevel";

  GenerationParameters gParams1(dir, "1", 1, 1, 1);
  gParams1.setRandLevelParameters(1, 5, 1, 5);
  DataBaseGeneratorParameters dbParams1(1, 5, 1, 5, 1, RandLevel, gParams1);
  DataBaseGenerator           generator1(dbParams1);
  generator1.generateTypeDefault(dbParams1);

  GenerationParameters gParams2(dir, "2", 1, 1, 1);
  gParams2.setRandLevelParameters(1, 5, 1, 5);
  DataBaseGeneratorParameters dbParams2(1, 5, 1, 5, 1, RandLevel, gParams2);
  DataBaseGenerator           generator2(dbParams2);
  generator2.generateTypeDefault(dbParams2);

  std::string              dir1   = mainDir + "/" + dir + "/" + "1";
  std::string              dir2   = mainDir + "/" + dir + "/" + "2";
  std::vector<std::string> jsons1 = getJsons(dir1);
  std::vector<std::string> jsons2 = getJsons(dir2);
  ASSERT_EQ(jsons1.empty(), false);
  ASSERT_EQ(jsons1.size(), jsons2.size());

  for (size_t i = 0; i < jsons1.size(); ++i) {
    EXPECT_EQ(
        FilesTools::loadStringFile(jsons1[i]),
        FilesTools::loadStringFile(jsons2[i])
    );
  }

  GenerationParameters gParams3(dir, "3", 1, 1, 1);
  gParams3.setRandLevelParameters(1, 10, 1, 10);
  DataBaseGeneratorParameters dbParams3(2, 6, 2, 6, 4, RandLevel, gParams3);
  DataBaseGenerator           generator3(dbParams3);
  generator1.generateTypeDefault(dbParams3);

  GenerationParameters gParams4(dir, "4", 1, 1, 1);
  gParams4.setRandLevelParameters(1, 10, 1, 10);
  DataBaseGeneratorParameters dbParams4(2, 6, 2, 6, 4, RandLevel, gParams4);
  DataBaseGenerator           generator4(dbParams4);
  generator2.generateTypeDefault(dbParams4);

  dir1   = mainDir + "/" + dir + "/" + "3";
  dir2   = mainDir + "/" + dir + "/" + "4";
  jsons1 = getJsons(dir1);
  jsons2 = getJsons(dir2);
  ASSERT_EQ(jsons1.empty(), false);
  ASSERT_EQ(jsons1.size(), jsons2.size());

  for (size_t i = 0; i < jsons1.size(); ++i) {
    EXPECT_EQ(
        FilesTools::loadStringFile(jsons1[i]),
        FilesTools::loadStringFile(jsons2[i])
    );
  }
  std::filesystem::remove_all(mainDir + "/" + dir);
}

// Circuits have different hashes
TEST(generateDataBaseNumOperations, EqualWithTheSameSeeds) {
  std::string          mainDir   = "dataset";
  std::string          dir       = "NumOperations";

  std::map<Gates, int> logicOper = {
      {Gates::GateAnd, 5},
      {Gates::GateOr, 5},
      {Gates::GateNot, 6},
      {Gates::GateNor, 6},
      {Gates::GateNand, 1},
      {Gates::GateXnor, 9},
      {Gates::GateXor, 12}};
  GenerationParameters gParams1(dir, "1", 5, 5, 1);
  gParams1.setNumOperationParameters(logicOper, false);
  DataBaseGeneratorParameters dbParams1(1, 5, 1, 5, 1, NumOperation, gParams1);
  DataBaseGenerator           generator1(dbParams1);
  generator1.generateTypeDefault(dbParams1);

  GenerationParameters gParams2(dir, "2", 5, 5, 1);
  gParams2.setNumOperationParameters(logicOper, false);
  DataBaseGeneratorParameters dbParams2(1, 5, 1, 5, 1, NumOperation, gParams2);
  DataBaseGenerator           generator2(dbParams2);
  generator2.generateTypeDefault(dbParams2);

  // receive all json files
  std::string              dir1   = mainDir + "/" + dir + "/" + "1";
  std::string              dir2   = mainDir + "/" + dir + "/" + "2";
  std::vector<std::string> jsons1 = getJsons(dir1);
  std::vector<std::string> jsons2 = getJsons(dir2);
  ASSERT_EQ(jsons1.empty(), false);
  ASSERT_EQ(jsons1.size(), jsons2.size());

  for (int i = 0; i < jsons1.size(); ++i) {
    EXPECT_EQ(
        FilesTools::loadStringFile(jsons1[i]),
        FilesTools::loadStringFile(jsons2[i])
    );
  }

  std::filesystem::remove_all(mainDir + "/" + dir);
}

TEST(GenerateDataBaseRandLevelExperimental, EqualWithTheSameSeeds) {
  std::string          mainDir = "dataset";
  std::string          dir     = "RandLevelExperimental";

  GenerationParameters gParams1(dir, "1", 5, 5, 1);
  gParams1.setRandLevelParameters(1, 5, 1, 5);
  DataBaseGeneratorParameters dbParams1(
      1, 5, 1, 5, 1, RandLevelExperimental, gParams1
  );
  DataBaseGenerator generator1(dbParams1);
  generator1.generateTypeDefault(dbParams1);

  GenerationParameters gParams2(dir, "2", 5, 5, 1);
  gParams2.setRandLevelParameters(1, 5, 1, 5);
  DataBaseGeneratorParameters dbParams2(
      1, 5, 1, 5, 1, RandLevelExperimental, gParams2
  );
  DataBaseGenerator generator2(dbParams2);
  generator2.generateTypeDefault(dbParams2);

  // receive all json files
  std::string              dir1   = mainDir + "/" + dir + "/" + "1";
  std::string              dir2   = mainDir + "/" + dir + "/" + "2";
  std::vector<std::string> jsons1 = getJsons(dir1);
  std::vector<std::string> jsons2 = getJsons(dir2);
  ASSERT_EQ(jsons1.empty(), false);
  ASSERT_EQ(jsons1.size(), jsons2.size());

  for (size_t i = 0; i < jsons1.size(); ++i) {
    EXPECT_EQ(
        FilesTools::loadStringFile(jsons1[i]),
        FilesTools::loadStringFile(jsons2[i])
    );
  }

  GenerationParameters gParams3(dir, "3", 1, 1, 1);
  gParams3.setRandLevelParameters(2, 10, 2, 10);
  DataBaseGeneratorParameters dbParams3(
      2, 7, 2, 7, 3, RandLevelExperimental, gParams3
  );
  DataBaseGenerator generator3(dbParams3);
  generator3.generateTypeDefault(dbParams3);

  GenerationParameters gParams4(dir, "4", 1, 1, 1);
  gParams4.setRandLevelParameters(2, 10, 2, 10);
  DataBaseGeneratorParameters dbParams4(
      2, 7, 2, 7, 3, RandLevelExperimental, gParams4
  );
  DataBaseGenerator generator4(dbParams4);
  generator4.generateTypeDefault(dbParams4);

  dir1   = mainDir + "/" + dir + "/" + "3";
  dir2   = mainDir + "/" + dir + "/" + "4";
  jsons1 = getJsons(dir1);
  jsons2 = getJsons(dir2);
  ASSERT_EQ(jsons1.empty(), false);
  ASSERT_EQ(jsons1.size(), jsons2.size());

  for (size_t i = 0; i < jsons1.size(); ++i) {
    EXPECT_EQ(
        FilesTools::loadStringFile(jsons1[i]),
        FilesTools::loadStringFile(jsons2[i])
    );
  }
  std::filesystem::remove_all(mainDir + "/" + dir);
}
