#include <algorithm>

#include "additional/filesTools/FilesTools.hpp"

#include <gtest/gtest.h>
namespace fs = std::filesystem;
using namespace FilesTools;
// I check the using of getDirectories and I can confirm that in test we can let
// ourselves do not care about order of directories in the vector. Full
// understanding will come after  all comments below.

// There are differences between software in terms of order of directories
// when we creating them through filesystem.
//  So we will not care about the order of directories. The elements of the
//  vectors that contain name of directories have to be the same. See below.
TEST(FileTools, OnlyDirectoriesNoFiles) {
  fs::path tmpPath =
      (fs::temp_directory_path() / "test"
      );  // Created temporary guaranteed directory to deal with
  std::string
      tmp;  // This variable exist because otherwise we will not be able push
            // tmpPath.string() to method getDirectories(Here it is going to be)
  std::fstream file;  // Created fstream variable to have the possibility to
                      // create files into temp directory to test the function
                      // on counting only directories.

  fs::create_directories(
      tmpPath / "6"
  );  // Just created directories within temporary directory . The order does
      // not matter. You will see below why
  fs::create_directories(tmpPath / "5");
  fs::create_directories(tmpPath / "4");
  fs::create_directories(tmpPath / "3");
  fs::create_directories(tmpPath / "2");
  fs::create_directories(tmpPath / "1");

  std::vector<std::string> correctVec = {
      "1",
      "2",
      "3",
      "4",
      "5",
      "6"};  // Created vector that's going to be compared
             // with the result vector we want to test

  tmp = tmpPath.string(
  );  // get the path to the current directory which contain created directories
  std::vector<std::string> resVec =
      getDirectories(tmp);  // Vector which we want to test

  std::sort(
      correctVec.begin(), correctVec.end()
  );  // If the elements of correctVec and resVec are the same
  std::sort(
      resVec.begin(), resVec.end()
  );  // after sort they are both will be equal to each other.

  EXPECT_EQ(resVec, correctVec);

  std::filesystem::remove_all(tmpPath.string()
  );  // Delete the current directory we work with.
}
TEST(FileTools, NoDirectoriesNoFiles) {
  fs::path tmpPath =
      (fs::temp_directory_path() / "anotherOne"
      );  // Created temporary guaranteed directory to deal with
  std::string tmp = tmpPath.string();
  try {
    getDirectories(tmp);  // when there is no element in directory that we
                          // pushed to getDirectories than it is going to throw
                          // exception. Here I handle that exception.
    EXPECT_EQ(0, 1);  // If the command at the line above throw exception this
                      // line will not be run and the test will not fail.
  } catch (...) {
    EXPECT_EQ(1, 1);  // To show on the console application that test was
                      // passed. We can ignore this line and just delete it. The
                      // result will not change anyway
    // but for more readability I decided to leave it.
  }
  std::filesystem::remove(tmpPath.string());  // Clean our directories.
}
TEST(FileTools, NoDirectoriesOnlyFiles) {
  fs::path tmpPath =
      (fs::temp_directory_path() / "anotherOne"
      );  // Created temporary guaranteed directory to deal with

  std::string tmp = tmpPath.string(
  );  // to prevent some errors  about rvalue to non-const lvalue and so on

  // Created ten empty txt files in the current directory to make sure that the
  // function does not count files.
  for (int i = 1; i <= 10; i++) {
    std::ofstream file;
    std::string   str = std::to_string(i)
                    + ".txt";  // Create str to prevent warning from below line
    const char* nameTxtFile(str.c_str());
    file.open((tmpPath / nameTxtFile).string()
    );  // Just create a file with name i.txt in current directory
    file.close();
  }

  try {
    getDirectories(tmp);  // when there is no element in directory that we
                          // pushed to getDirectories than it is going to throw
                          // exception. Here I handle that exception.
    EXPECT_EQ(0, 1);  // If the command at the line above throw exception this
                      // line will not be run and the test will not fail.
  } catch (...) {
    EXPECT_EQ(1, 1);  // To show on the console application that test was
                      // passed. We can ignore this line and just delete it. The
                      // result will not change anyway
    // but for more readability I decided to leave it.
  }
  std::filesystem::remove_all(tmpPath.string());  // Clean our directories.
}
TEST(FileTools, DirectoriesAndFilesExist) {
  fs::path tmpPath =
      (fs::temp_directory_path() / "test"
      );  // Created temporary guaranteed directory to deal with

  std::string
      tmp;  // This variable exist because otherwise we will not be able push
            // tmpPath.string() to method getDirectories(Here it is going to be)

  std::fstream file;  // Created fstream variable to have the possibility to
                      // create files into temp directory to test the function
                      // on counting only directories.

  fs::create_directories(
      tmpPath / "6"
  );  // Just created directories within temporary directory . The order does
      // not matter. You will see below why
  fs::create_directories(tmpPath / "5");
  fs::create_directories(tmpPath / "4");
  fs::create_directories(tmpPath / "3");
  fs::create_directories(tmpPath / "2");
  fs::create_directories(tmpPath / "1");

  std::vector<std::string> correctVec = {
      "1",
      "2",
      "3",
      "4",
      "5",
      "6"};  // Created vector that's going to be compared
             // with the result vector we want to test

  // Created ten empty txt files in the current directory to make sure that the
  // function does not count files.
  for (int i = 1; i <= 10; i++) {
    std::ofstream file;
    std::string   str =
        std::to_string(i) + ".txt";  // To prevent warning from below line
    const char* nameTxtFile(str.c_str());
    file.open((tmpPath / nameTxtFile).string()
    );  // Just create a file with name i.txt
    file.close();
  }

  tmp = tmpPath.string(
  );  // get the path to the current directory which contain created directories

  std::vector<std::string> resVec =
      getDirectories(tmp);  // Vector which we want to test

  std::sort(
      correctVec.begin(), correctVec.end()
  );  // If the elements of correctVec and resVec are the same
  std::sort(
      resVec.begin(), resVec.end()
  );  // after sort they are both will be equal to each other.

  EXPECT_EQ(resVec, correctVec);

  std::filesystem::remove_all(tmpPath.string()
  );  // Delete the current directory we work with.
}
