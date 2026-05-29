#include <gtest/gtest.h>

#include "additional/tempProjectDir/TempProjectDir.hpp"
#include "easylogging++Init.hpp"
#include "fstream"
#include <filesystem>

using namespace CG_Gen;

const std::filesystem::path currentDirectory =
    std::filesystem::current_path() / "src" / "additional" / "tempProjectDir";
const std::filesystem::path testDirectory = currentDirectory / "testTempDir";

TEST(TemporaryDirectory, createSubdirectoryTest) {
  auto tempDir =
      std::make_unique<TempProjectDir>(testDirectory, currentDirectory);
  std::string subDirectoryName = "testSubDirectory";
  std::filesystem::path result = tempDir->createSubDirectory(subDirectoryName);

  auto createdDirPath = testDirectory / "testSubDirectory";
  EXPECT_EQ(result, createdDirPath);
  EXPECT_TRUE(std::filesystem::exists(createdDirPath) &&
              std::filesystem::is_directory(createdDirPath));
}

TEST(TemporaryDirectory, copyFileTest) {
  auto tempDir =
      std::make_unique<TempProjectDir>(testDirectory, currentDirectory);
  std::filesystem::path emptyFilePath =
      currentDirectory / "testData" / "test_empty.txt";
  std::filesystem::path notEmptyFilePath =
      currentDirectory / "testData" / "test_not_empty.txt";

  std::ifstream emptyFile(emptyFilePath);
  std::string emptyFileContent;
  if (emptyFile.is_open()) {
    std::getline(emptyFile, emptyFileContent);
  }
  emptyFile.close();

  std::ifstream notEmptyFile(notEmptyFilePath);
  std::string notEmptyFileContent;
  std::stringstream buffer;
  if (notEmptyFile.is_open()) {
    buffer << notEmptyFile.rdbuf();
    notEmptyFileContent = buffer.str();
  }
  notEmptyFile.close();

  std::filesystem::path emptyFileCopied = testDirectory / "empty.txt";
  std::filesystem::path notEmptyFileCopied = testDirectory / "not_empty.txt";

  bool emptyRes = tempDir->copyFile(emptyFilePath, emptyFileCopied);
  bool notEmptyRes = tempDir->copyFile(notEmptyFilePath, notEmptyFileCopied);

  ASSERT_TRUE(emptyRes);
  ASSERT_TRUE(notEmptyRes);

  std::ifstream copiedEmpty(emptyFileCopied);
  std::string copiedEmptyContent;
  if (copiedEmpty.is_open()) {
    std::getline(copiedEmpty, copiedEmptyContent);
  }
  copiedEmpty.close();

  std::ifstream copiedNotEmpty(notEmptyFileCopied);
  buffer.str("");
  buffer.clear();
  std::string copiedNotEmptyContent;
  if (copiedNotEmpty.is_open()) {
    buffer << copiedNotEmpty.rdbuf();
    copiedNotEmptyContent = buffer.str();
  }
  copiedNotEmpty.close();

  ASSERT_EQ(emptyFileContent, copiedEmptyContent);
  ASSERT_EQ(notEmptyFileContent, copiedNotEmptyContent);
}

TEST(TemporaryDirectory, createFileTest) {
  auto tempDir =
      std::make_unique<TempProjectDir>(testDirectory, currentDirectory);
  std::string newFileName = "newFile.txt";
  std::string content = "Content example";

  bool result = tempDir->createFile(newFileName, content);
  ASSERT_TRUE(result);

  auto newFilePath = testDirectory / newFileName;

  std::ifstream newFile(newFilePath);
  std::string newFileContent;
  if (newFile.is_open()) {
    std::getline(newFile, newFileContent);
  }
  newFile.close();

  ASSERT_EQ(content, newFileContent);
}