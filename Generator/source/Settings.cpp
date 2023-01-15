#include <fstream>
#include <iostream>

#include "Settings.h"

Settings::Settings()
{
  for (const auto &[key, value] : d_logicOperations) {
    int i = value.second;
    if (d_operationsToHierarchy.find(i) == d_operationsToHierarchy.end()) 
      d_operationsToHierarchy[i] = {};
    d_operationsToHierarchy[i].push_back(value.first);
  }

  for (const auto &[key, value] : d_logicOperations)
    d_operationsToName[value.first] = key;
}

void Settings::loadSettings() {
  std::ifstream readFile(d_fileName);

  readFile >> d_csvdataset >> d_fileName >> d_datasetPath >> d_pathToNadezhda;

  int nadezhdaPathsCount;
  readFile >> nadezhdaPathsCount;
  for (int i = 0; i < nadezhdaPathsCount; ++i) 
  {
    std::string tool, path;
    readFile >> tool >> path;
    d_nadezhda[tool] = path;
  }

  readFile >> d_numThreads;

  int logicOperationCount;
  readFile >> logicOperationCount;
  for (int i = 0; i < logicOperationCount; ++i) {
    std::string operation, operationName, operationId;
    readFile >> operation >> operationName >> operationId;
    d_logicOperations[operation] = {operationName, std::stoi(operationId)};
  }

  int operationHierarchyCount;
  readFile >> operationHierarchyCount;
  for (int i = 0; i < operationHierarchyCount; ++i) {
    int operationId, operationHierarchyCount;
    std::vector<std::string> operations;
    readFile >> operationId >> operationHierarchyCount;
    
    std::string operation;
    for (int j = 0; j < operationHierarchyCount; ++j) {
      readFile >> operation;
      operations.push_back(operation);
    }
    d_operationsToHierarchy[operationId] = operations;
  }

  int operationsCount;
  readFile >> operationsCount;
  for (int i = 0; i < operationsCount; ++i) {
    std::string fromName, toName;
    readFile >> fromName >> toName;
    d_operationsToName[fromName] = toName;
  }

  readFile >> d_maxInputs >> d_maxOutputs;
}

std::pair<std::string, int> Settings::getLogicOperation(const std::string& i_op)
{
  return d_logicOperations.at(i_op);
}

std::vector<std::string> Settings::getLogicOperationsKeys()
{
  std::vector<std::string> res;
  for (const auto &[key, value] : d_logicOperations)
   res.push_back(key);

  return res;
}

std::string Settings::fromOperationsToName(const std::string& i_op) const
{
  return d_operationsToName.at(i_op);
}

void Settings::SaveSettings() {
  std::ofstream writeFile(d_fileName);
  writeFile << d_csvdataset << ' ' << d_fileName << ' ' << d_datasetPath << ' ' << 
    d_pathToNadezhda << std::endl;
  
  writeFile << d_nadezhda.size() << std::endl;
  for (const auto &[key, value] : d_nadezhda)
    writeFile << key << ' ' << value << std::endl;
  
  writeFile << d_numThreads << std::endl;

  writeFile << d_logicOperations.size() << std::endl;
  for (const auto &[key, value] : d_logicOperations)
    writeFile << key << ' ' << value.first << ' ' << value.second << std::endl;

  writeFile << d_operationsToHierarchy.size() << std::endl;
  for (const auto &[key, value] : d_operationsToHierarchy) {
    writeFile << key << ' ' << value.size() << std::endl;
    for (const auto& operation : value) 
      writeFile << operation << ' ' ;
    writeFile << std::endl;
  }

  writeFile << d_operationsToName.size() << std::endl;
  for (const auto &[key, value] : d_operationsToName)
    writeFile << key << ' ' << value << std::endl;

  writeFile << d_maxInputs << ' ' << d_maxOutputs << std::endl;
}

std::string Settings::getDatasetPath() const
{
  return d_datasetPath;
}

std::string Settings::getGenerationMethodPrefix(const std::string& i_s) const
{
  if (i_s == "FromRandomTruthTable")
    return "ftt";
  if (i_s == "RandLevel")
    return "rl";
  if (i_s == "NumOperation")
    return "nop";
  if (i_s == "Genetic")
    return "gen";

  std::cout << "UNDEFINED METHOD PREFIX << " << i_s << std::endl;

  return "ftt";
}
