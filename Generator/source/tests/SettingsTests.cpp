#include <gtest/gtest.h>
#include "settings/Settings.cpp"
#include <string>
#include <exception>
#include <memory>
#include <fstream>
#include <filesystem>

std::string fileName = "settings.dat"; // To test LoadSettings by default. See below.
// If the d_fileName will assign to another value by default you also have to change the input of  std::filesystem::exists that placed above. 
// That's the only way to test LoadSettings when file does not exists without breaking encapsulation.


TEST(test_settings, test_default_load_settings)
{
  std::shared_ptr<Settings> t = Settings::getInstance("test_default_load_settings");

  std::map<int, std::vector<std::string>> operToHierAns;
  operToHierAns[0] = {"="};
  operToHierAns[1] = {"nor"};
  operToHierAns[2] = {"or"};
  operToHierAns[3] = {"nand"};
  operToHierAns[4] = {"and"};
  operToHierAns[5] = {"xnor"};
  operToHierAns[6] = {"xor"};
  operToHierAns[7] = {"not"};
 // operToHierAns[8] = {"buf"};
  operToHierAns[9] = {"1'b0"};
  operToHierAns[10] = {""};

  std::map<std::string, std::string> operToNameAns;

  operToNameAns[""] = "input";
  operToNameAns["="] = "output";
  operToNameAns["1'b0"] = "const";
  operToNameAns["and"] = "and";
  operToNameAns["nand"] = "nand";
  operToNameAns["or"] = "or";
  operToNameAns["nor"] = "nor";
  operToNameAns["not"] = "not";
//  operToNameAns["buf"] = "buf";
  operToNameAns["xor"] = "xor";
  operToNameAns["xnor"] = "xnor";

  for (const auto& [key, value] : operToHierAns)
  {
    EXPECT_EQ(value, t->fromOperationsToHierarchy(key));
  }

  for (const auto& [key, value] : operToNameAns)
  {
    EXPECT_EQ(value, t->fromOperationsToName(key));
  }
}

TEST(SettingsTest, defaultInitializationWithLoadSettingsWriteCorrectLogicOperation)
{
    if (!std::filesystem::exists(fileName))
    {
        std::shared_ptr<Settings> SetPtr = Settings::getInstance(" ");// Here we call implicitly loadSettings.
        // Below I gonna write down correc samples that I wanna use to compare with the output of the loadSettings
        std::map <std::string, std::pair<std::string, int>> correctLogicOperations =
        {
          {"input",  {"",     10}},
          {"output", {"=",    0}},
          {"const",  {"1'b0",  9}},
          {"and",    {"and",  4}},
          {"nand",   {"nand", 3}},
          {"or",     {"or",   2}},
          {"nor",    {"nor",  1}},
          {"not",    {"not",  7}},
     //     {"buf",    {"buf",  8}},
          {"xor",    {"xor",  6}},
          {"xnor",   {"xnor", 5}}
        };

        for (auto const& [key, val] : correctLogicOperations)
        {
            EXPECT_EQ(correctLogicOperations[key], SetPtr->getLogicOperation(key));
        }
    }
}

TEST(SettingsTest, defaultInitializationWithLoadSettingsWriteCorrectOperationsToHierarchy)
{
    if (!std::filesystem::exists(fileName))
    {
        std::shared_ptr<Settings> SetPtr = Settings::getInstance(" ");// Here we call implicitly loadSettings.
        // Below I gonna write down correc samples that I wanna use to compare with the output of the loadSettings
        std::map <int, std::vector<std::string>> correctOperationsToHierarchy =
        {
          {10,      {""}},
          {0,      {"="}},
          {9,    {"1'b0"}},
          {4,    {"and"}},
          {3,  {"nand" }},
          {2,    {"or" }},
          {1,    {"nor"}},
          {7,    {"not"}},
    //      {8,    {"buf"}},
          {6,    {"xor"}},
          {5,   {"xnor"}}
        };

        for (auto const& [key, val] : correctOperationsToHierarchy)
        {
            EXPECT_EQ(correctOperationsToHierarchy[key], SetPtr->fromOperationsToHierarchy(key));
        }
    }
}

TEST(SettingsTest, defaultInitializationWithLoadSettingsWriteCorrectOperationsToName)
{
    if (!std::filesystem::exists(fileName))
    {
        std::shared_ptr<Settings> SetPtr = Settings::getInstance(" ");// Here we call implicitly loadSettings.
        // Below I gonna write down correc samples that I wanna use to compare with the output of the loadSettings

        std::map <std::string, std::string> correctOperationsToName =
        {
            {"" , "input"},
            {"=" , "output"},
            {"1'b0" , "const"},
            {"and" , "and"},
            {"nand" , "nand"},
            {"or" , "or"},
            {"nor" , "nor"},
            {"not" , "not"},
       //     {"buf" , "buf"},
            {"xor" , "xor"},
            {"xnor" , "xnor"}
        };

        for (auto const& [key, val] : correctOperationsToName)
        {
            EXPECT_EQ(correctOperationsToName[key], SetPtr->fromOperationsToName(key));
        }
    }
}
/* This part of code is working just fine. It can be used when SaveSettings will be set as public
TEST(SettingsTest, SaveSettingsNormalTest)
{
    std::ifstream readFile(fileName);
    std::vector<std::string> BeforeSaveSettings;
    std::vector<std::string> AfterSaveSettings;
    std::shared_ptr<Settings> SetPtr = Settings::getInstance(" ");// Here we implicitely called loadSettings()
    readFile.clear();
    readFile.seekg(0);// Back to the beginnigs of the file .
    std::string str;

    SetPtr->loadSettings();// Fill file with data

    while (!readFile.eof())
    {
        readFile >> str;
        if (str != "") BeforeSaveSettings.push_back(str);//Read all data from the file to BeforeSaveSettings
        str = "";
    }

    SetPtr->SaveSettings();

    readFile.clear();
    readFile.seekg(0);// Back to the beginnigs of the file .

    while (!readFile.eof())
    {
        readFile >> str;
        if (str != "") AfterSaveSettings.push_back(str);//Read all data from the file to AfterSaveSettings
        str = "";
    }

    EXPECT_EQ(BeforeSaveSettings, AfterSaveSettings);
}*/
