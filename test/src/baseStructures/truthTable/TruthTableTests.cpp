#include <vector>

#include "baseStructures/truthTable/TruthTable.hpp"

#include <gtest/gtest.h>

#include "easylogging++Init.hpp"

TEST(EqualOperationOfTruthTable, EqualToEachOther) {
  TruthTable firstTable =
      TruthTable {1, 1, std::vector<std::vector<bool>>({{1}, {1}})};
  TruthTable secondTable =
      TruthTable {1, 1, std::vector<std::vector<bool>>({{1}, {1}})};
  EXPECT_EQ(firstTable, secondTable);
  firstTable =
      TruthTable {2, 1, std::vector<std::vector<bool>>({{1}, {1}, {1}, {0}})};
  secondTable =
      TruthTable {2, 1, std::vector<std::vector<bool>>({{1}, {1}, {1}, {0}})};
  EXPECT_EQ(firstTable, secondTable);
  firstTable = TruthTable {
      2, 2, std::vector<std::vector<bool>>({{1, 1}, {1, 1}, {1, 1}, {0, 0}})};
  secondTable = TruthTable {
      2, 2, std::vector<std::vector<bool>>({{1, 1}, {1, 1}, {1, 1}, {0, 0}})};
  EXPECT_EQ(firstTable, secondTable);
}

TEST(EqualOperationOfTruthTable, DifferentFromEachOther) {
  TruthTable firstTable =
      TruthTable {1, 1, std::vector<std::vector<bool>>({{1}, {1}})};
  TruthTable secondTable =
      TruthTable {1, 1, std::vector<std::vector<bool>>({{1}, {0}})};
  EXPECT_FALSE(firstTable == secondTable);
  firstTable = TruthTable {
      3,
      1,
      std::vector<std::vector<bool>>({{1}, {1}, {1}, {0}, {1}, {1}, {1}, {0}})};
  secondTable = TruthTable {
      3,
      1,
      std::vector<std::vector<bool>>({{1}, {1}, {1}, {0}, {1}, {1}, {1}, {1}})};
  EXPECT_FALSE(firstTable == secondTable);
  firstTable  = TruthTable {1, 1, std::vector<std::vector<bool>>({{0}, {0}})};
  secondTable = TruthTable {1, 1, std::vector<std::vector<bool>>({{1}, {1}})};
  EXPECT_FALSE(firstTable == secondTable);
}

TEST(ConvToBinaryOfTruthTable, NormalTest) {
  TruthTable table =
      TruthTable {1, 1, std::vector<std::vector<bool>>({{1}, {1}})};
  EXPECT_EQ(table.convToBinary(), std::vector<std::vector<bool>>({{0}, {1}}));
  table =
      TruthTable {2, 1, std::vector<std::vector<bool>>({{1}, {0}, {0}, {0}})};
  EXPECT_EQ(
      table.convToBinary(),
      std::vector<std::vector<bool>>({{0, 0}, {0, 1}, {1, 0}, {1, 1}})
  );
  table = TruthTable {3, 1, std::vector<std::vector<bool>>({})};
  EXPECT_EQ(
      table.convToBinary(),
      std::vector<std::vector<bool>>(
          {{0, 0, 0},
           {0, 0, 1},
           {0, 1, 0},
           {0, 1, 1},
           {1, 0, 0},
           {1, 0, 1},
           {1, 1, 0},
           {1, 1, 1}}
      )
  );
}

TEST(ConstructorForTruthTableWithVector, CorrectSize) {
  EXPECT_EQ((TruthTable {1, 1, std::vector<std::vector<bool>> {}}).size(), 2);
}

TEST(ConstructorForTruthTableWithVector, CorrectInput) {
  EXPECT_EQ(
      (TruthTable {1, 1, std::vector<std::vector<bool>> {}}).getInput(), 1
  );
}

TEST(ConstructorForTruthTableWithVector, CorrectOutput) {
  EXPECT_EQ(
      (TruthTable {1, 1, std::vector<std::vector<bool>> {}}).getOutput(), 1
  );
}

TEST(ConstructorForTruthTableWithVector, CorrectVector) {
  EXPECT_EQ(
      (TruthTable {1, 1, std::vector<std::vector<bool>>({{1}, {1}})}
      ).getOutTable(),
      std::vector<std::vector<bool>>({{1}, {1}})
  );
}

TEST(ConstructorForTruthTableWithDouble, CorrectSize) {
  EXPECT_EQ((TruthTable {1, 1, 0.3}).size(), 2);
}

TEST(ConstructorForTruthTableWithDouble, CorrectInput) {
  EXPECT_EQ((TruthTable {1, 1, 0.5}).getInput(), 1);
}

TEST(ConstructorForTruthTableWithDouble, CorrectOutput) {
  EXPECT_EQ((TruthTable {1, 1, 0.1}).getOutput(), 1);
}

TEST(ConstructorForTruthTableWithDouble, CorrectSizeOfVector) {
  EXPECT_EQ((TruthTable {1, 1, 0.2}).getOutTable().size(), 2);
}

TEST(GenerateTableOfTruthTable, CorrectSizeOfVector) {
  TruthTable example = TruthTable {1, 2, 0.2};
  example.generateTable();
  EXPECT_EQ(example.getOutTable().size(), 2);
  for (int32_t i = 0; i < 2; i++) {
    EXPECT_EQ(example.getOutTable()[i].size(), 2);
  }
}