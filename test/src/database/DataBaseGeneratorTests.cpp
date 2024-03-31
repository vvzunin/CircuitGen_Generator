#include <gtest/gtest.h>
#include <filesystem>

#include "database/DataBaseGenerator.h"
#include "database/DataBaseGeneratorParameters.h"

/*
TEST(GenerateDataBaseFromRandomTruthTable, EqualWithTheSameSeeds) {
  GenerationParameters gParams("FromRandomTruthTable", "1", 4, 4, 8,"Generator/libs/sky130.lib", true, true, true, true);
  DataBaseGeneratorParameters dbParams(1, 4, 1, 4, 8, FromRandomTruthTable, gParams);
  DataBaseGenerator generator(dbParams);
  generator.generateType(dbParams);
  std::filesystem::remove_all("dataset/RandLevel");
}*/

/*TEST(GenerateDataBaseRandLevel, EqualWithTheSameSeeds) {
  GenerationParameters gParams1("RandLevel", "1", 5, 5, 8);
  DataBaseGeneratorParameters dbParams1(2, 6, 2, 6, 1, RandLevel, gParams1);
  DataBaseGenerator generator1(dbParams1);
  generator1.generateType(dbParams1);
}*/

/*TEST(generateDataBaseNumOperations, EqualWithTheSameSeeds) {
  GenerationParameters gParams1("NumOperations", "1", 6, 6, 8);
  DataBaseGeneratorParameters dbParams1(2, 6, 2, 6, 1, NumOperation, gParams1);
  DataBaseGenerator generator1(dbParams1);
  generator1.generateType(dbParams1);
}*/