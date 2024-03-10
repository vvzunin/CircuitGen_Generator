#pragma once

#include <string>
#include <memory>
#include <map>
#include <utility>
#include <vector>

enum generationTypes
{
  none,
  truthTableToGraphWithoutOptimization,
  truthTableToGraphWithOptimization
};

enum LibrariesTypes
{
  SKY_LIB
};

enum Gates
{
  GateAnd,
  GateNand,
  GateOr,
  GateNor,
  GateXor,
  GateXnor,
  GateNot,
  GateBuf
};

class Settings
{
protected:
  Settings(const std::string &i_path) : d_path(i_path) {}

public:
  Settings(Settings &other) = delete;
  void operator=(const Settings &) = delete;
  static std::shared_ptr<Settings> getInstance(const std::string &i_value);
  void loadSettings();
  std::string getInstanceName() const;
  std::pair<std::string, int> getLogicOperation(const std::string &i_op);
  std::vector<Gates> getLogicOperationsKeys();
  std::pair<std::vector<bool>, std::vector<Gates>> getLogicOperationsWithGates();
  std::string fromOperationsToName(const std::string &i_op) const;
  std::string getDatasetPath() const;
  std::string getGenerationMethodPrefix(const std::string &i_s) const;
  std::string getLibraryPath() const;
  std::string getLibraryNameFromEnum(const LibrariesTypes &library) const;
  int getMaxInputs() const;
  int getMaxOutputs() const;
  std::map<std::string, std::pair<std::string, int>> getLogicOperations() const;
  std::string getPathNadezhda() const;
  std::string getNadezhdaVar(const std::string &key) const;
  std::vector<std::string> fromOperationsToHierarchy(int key) const;
  int getNumThread() const;

private:
  void SaveSettings();

  std::string d_name;
  static std::shared_ptr<Settings> d_singleton;
  std::string d_path;
  std::string d_csvdataset = "dataset.csv";
  std::string d_fileName = "settings.dat";
  std::string d_datasetPath = "./dataset";
  std::string d_libraryPath = "Generator/libs";
  // Settings d_instance;
  std::string d_pathToNadezhda = "./Generator/source/data/Nadezhda";
  std::map<std::string, std::string> d_nadezhda = {
      {"python", "python3"},
      {"resynthesis", "Nadezhda/Scripts/resynthesis_local_rewriting.pyc"},
      {"reliability", "Nadezhda/Scripts/check_reliability.pyc"},
      {"liberty", "Nadezda/Test/Nangate.lib"}};
  int d_numThreads = 4;
  std::map<std::string, std::pair<std::string, int>> d_logicOperations =
      {
          {"input", {"", 10}},
          {"output", {"=", 0}},
          {"const", {"1'b0", 9}},
          {"and", {"and", 4}},
          {"nand", {"nand", 3}},
          {"or", {"or", 2}},
          {"nor", {"nor", 1}},
          {"not", {"not", 7}},
          {"buf", {"buf", 8}},
          {"xor", {"xor", 6}},
          {"xnor", {"xnor", 5}}

  };

  std::vector<Gates> d_logicElements = {
    GateAnd,
    GateNand,
    GateOr,
    GateNor,
    GateXor,
    GateXnor,
    GateNot,
    GateBuf
  };

  std::map<int, std::vector<std::string>> d_operationsToHierarchy;
  std::map<std::string, std::string> d_operationsToName;
  int d_maxInputs = 50;
  int d_maxOutputs = 50;
};
