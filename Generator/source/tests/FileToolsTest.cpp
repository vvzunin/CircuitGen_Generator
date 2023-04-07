#include<iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include <gtest/gtest.h>
#include "../FileTools.h"
namespace fs = std::filesystem;
using namespace FilesTools;
std::vector<std::string> getDirectories(std::string& path)
{
   
    std::vector<std::string> res;

    for (const auto& file : std::filesystem::directory_iterator(path))
    {
        if (std::filesystem::is_directory(path))
            res.push_back(file.path().string());
    }
    return res;
}

TEST(FileToolsTest, NormalTest)
{
    fs::path tmpPath = fs::temp_directory_path();//Created temporary guaranted directory to deal with
    std::string tmp; // This variable exist because otherwise we will not be able push tmpPath.string() to method getDirectories(Here it is gonna be)
    std::fstream file; // Created fstream variable to have the possibility to create files into temp directory to test the fucntion on counting only directories.

    fs::create_directories(tmpPath / "first");// Just created directories into temporary directory 
    fs::create_directories(tmpPath / "second");
    fs::create_directories(tmpPath / "third");
    fs::create_directories(tmpPath / "fourth");
    fs::create_directories(tmpPath / "fifth");
    fs::create_directories(tmpPath / "sixth");

    std::vector<std::string> correctVec = { 
        (tmpPath / "first").string() , (tmpPath / "second").string()
        , (tmpPath / "third").string() , (tmpPath / "fourth").string()
        , (tmpPath / "fifth").string() , (tmpPath / "sixth").string() }; // Created vector that's gonna be compared with vector we wanna test 
    
    tmp = tmpPath.string();
    std::vector<std::string> resVec = getDirectories(tmp);// Vector which we wanna test 

    EXPECT_EQ(correctVec, resVec);

    // Created ten empty txt files in the current directory to make sure that the function does not count files.
    for (int i = 1; i <= 10; i++)
    {
        std::ofstream file;// WARNING!!!
        std::string str = std::to_string(i) + ".txt";//To prevent warning from below line
        const char* nameTxtFile(str.c_str());
        file.open((tmpPath / nameTxtFile).string());
        file.close();
    }

    EXPECT_EQ(correctVec, resVec); // check

    // Now we gonna delete first two directories , add two directories and  correct our correctVec so that it will be suitable ot real situation
    fs::remove(tmpPath / "first");
    fs::remove(tmpPath / "second");
    //Here we add two directories
    fs::create_directories(tmpPath / "seventh");
    fs::create_directories(tmpPath / "eighth");
    //Here we update our correctVec
    correctVec.erase(correctVec.begin(), correctVec.begin() + 2);
    correctVec.insert(correctVec.end(), { (tmpPath / "seventh").string() , (tmpPath / "eigth").string() });
    tmp = tmpPath.string();
    resVec = getDirectories(tmp);// Update resVec

    EXPECT_EQ(correctVec, resVec); // check

    // Now we again gonna delete first three directories , add four directories and  correct our correctVec so that it will be suitable ot real situation
    fs::remove(tmpPath / "third");
    fs::remove(tmpPath / "fourth");
    fs::remove(tmpPath / "fifth");
    fs::create_directories(tmpPath / "ninth");
    fs::create_directories(tmpPath / "tenth");
    fs::create_directories(tmpPath / "eleventh");
    fs::create_directories(tmpPath / "twelfth");

    correctVec.erase(correctVec.begin(), correctVec.begin() + 3);
    correctVec.insert(correctVec.end(), { ( tmpPath / "ninth" ).string() , (tmpPath / "tenth").string()  , 
        (tmpPath / "eleventh").string() , (tmpPath / "twelfth").string() });
    tmp = tmpPath.string();
    resVec = getDirectories(tmp);// Update resVec

    EXPECT_EQ(correctVec, resVec);// final check



}
