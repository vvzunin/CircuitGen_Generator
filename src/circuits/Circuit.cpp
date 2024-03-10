#include <cmath>
#include <mutex>
#include <cstdio>
#include <thread>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>

#include "Circuit.h"
#include <additional/filesTools/FilesTools.h>
#include <additional/AuxiliaryMethods.h>
#include <baseStructures/graph/enums.h>

Circuit::Circuit(OrientedGraph *const i_graph, const std::vector<std::string> &i_logExpressions)
{
  d_graph = i_graph;
  std::clog << "Graph moved, update begins" << std::endl;
  d_graph->updateLevels();
  d_logExpressions = i_logExpressions;
}

void Circuit::computeHash()
{
  std::stringstream stream;
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_numInputs << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_numConstants << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_numOutputs << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_maxLevel << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_numEdges << '\n';

  for (auto [key, value] : d_circuitParameters.d_numElementsOfEachType)
    stream << "\t\t\"" << key << "\": " << value << '\n';

  for (auto [key, value] : d_circuitParameters.d_numEdgesOfEachType)
    stream << "\t\t\"" << key.first << "-" << key.second << "\": " << value << '\n';

  {
    // TODO: write logic of get SHA256
  }
}

void Circuit::updateCircuitsParameters()
{
  if (d_graph->isEmptyFull())
    return;

  d_graph->updateLevels();
  std::clog << "Update ended, norm. calc started" << std::endl;

  d_circuitParameters.d_name = d_circuitName;

  std::vector<GraphVertexBase *> inputs = d_graph->getVerticesByType(VertexTypes::input);
  std::vector<GraphVertexBase *> constants = d_graph->getVerticesByType(VertexTypes::constant);
  std::vector<GraphVertexBase *> outputs = d_graph->getVerticesByType(VertexTypes::output);

  d_circuitParameters.d_numInputs = inputs.size();
  d_circuitParameters.d_numConstants = constants.size();
  d_circuitParameters.d_numOutputs = outputs.size();

  d_circuitParameters.d_maxLevel = d_graph->getMaxLevel();

  d_circuitParameters.d_numEdges = 0;
  // TODO: Добавить корректную реализацию
  // for (const auto &row : d_graph->getAdjacencyMatrixReference())
  //     for (auto el : row)
  //         if (el)
  //             d_circuitParameters.d_numEdges++;

  d_circuitParameters.d_numElementsOfEachType.clear();
  // const std::vector<GraphVertex> &gv = d_graph->getVerticesReference();

  for (const auto &[key, value] : d_settings->getLogicOperations())
    d_circuitParameters.d_numElementsOfEachType[key] = 0;
  // TODO: Добавить корректную реализацию
  // for (const auto &v : gv)
  //     for (const auto &[key, value] : d_settings->getLogicOperations())
  //         if (v.getOperation() == key)
  //             d_circuitParameters.d_numElementsOfEachType[v.getOperation()]++;

  d_circuitParameters.d_numEdgesOfEachType.clear();
  // TODO: Добавить корректную реализацию
  // for (const auto &[key1, value1] : d_settings->getLogicOperations())
  //     for (const auto &[key2, vluae2] : d_settings->getLogicOperations())
  //         if (key1 != "output" && key2 != "input")
  //             d_circuitParameters.d_numEdgesOfEachType[std::make_pair(key1, key2)] = 0;

  // for (int i = 0; i < gv.size(); ++i)
  //     for (int j = 0; j < gv.size(); ++j)
  //         if (d_graph->getAdjacencyMatrix(i, j))
  //             d_circuitParameters.d_numEdgesOfEachType[std::make_pair(gv[i].getOperation(), gv[j].getOperation())]++;

  computeHash();
}

bool Circuit::graphToVerilog(const std::string &i_path, bool i_pathExists)
{
  // TODO: Переделать
  // if (d_graph->empty())
    //     return false;

    // d_graph->numberVerticesCorrectly();


  /* if (!i_pathExists) // TODO: work with directory
         if (!FilesTools::isDirectoryExists(std::filesystem::current_path().string() + i_path))
             std::filesystem::create_directory(i_path);
     */

  // static std::string filename;
  
  // filename = d_path + "/" + d_circuitName + ".v";

  // d_graph->toVerilog(filename);

  return true;
}

bool Circuit::saveParameters(bool i_pathExists) const
{
  if (true)
  { /*
       if (!FilesTools::isDirectoryExists(std::filesystem::current_path().string() + d_path)) // TODO: make function isDirectory exists
       {
           //std::filesystem::create_directory(d_path);
       }
   */
  }

  std::string filename = d_path + "/" + d_circuitName + ".json";

  // if (std::filesystem::exists(filename))
  //     std::remove(filename.c_str());

  std::ofstream outputFile(filename);

  if (!outputFile)
    return false;

  outputFile << "{" << std::endl;

  outputFile << "\t\"name\": \"" << d_circuitParameters.d_name << "\"," << std::endl;
  outputFile << "\t\"numInputs\": \"" << d_circuitParameters.d_numInputs << "\"," << std::endl;
  outputFile << "\t\"numConstants\": \"" << d_circuitParameters.d_numConstants << "\"," << std::endl;
  outputFile << "\t\"numOutputs\": \"" << d_circuitParameters.d_numOutputs << "\"," << std::endl;
  outputFile << "\t\"maxLevel\": \"" << d_circuitParameters.d_maxLevel << "\"," << std::endl;
  outputFile << "\t\"numEdges\": \"" << d_circuitParameters.d_numEdges << "\"," << std::endl;
  outputFile << "\t\"hash_code\": \"" << d_circuitParameters.d_hashCode << "\"," << std::endl;

  outputFile << "\t\"numElementsOfEachType\": {" << std::endl;

  bool first = true;
  for (const auto &[key, value] : d_circuitParameters.d_numElementsOfEachType)
  {
    if (value != 0)
    {
      if (first)
      {
        first = false;
        outputFile << "\t\t\"" << key << "\": " << value;
      }
      else
      {
        outputFile << "," << std::endl
                   << "\t\t\"" << key << "\": " << value;
      }
    }
  }
  outputFile << std::endl;

  outputFile << "\t}," << std::endl;

  outputFile << "\t\"numEdgesOfEachType\": {" << std::endl;
  first = true;
  for (const auto &[key, value] : d_circuitParameters.d_numEdgesOfEachType)
  {
    if (value != 0)
    {
      if (first)
      {
        first = false;
        outputFile << "\t\t\"" << key.first << "-" << key.second << "\": " << value;
      }
      else
      {
        outputFile << "," << std::endl
                   << "\t\t\"" << key.first << "-" << key.second << "\": " << value;
      }
    }
  }
  outputFile << std::endl;

  outputFile << "\t}";

  return true;
}

bool Circuit::checkExistingHash() // TODO: is it really need return true when hash wrong?
{
  std::string path = FilesTools::getParentDirOf(d_path);
  if (path == "" || !std::filesystem::exists(path))
    return false;

  std::ifstream r(path);

  std::string hash = "";

  r >> hash;

  while (r >> hash)
    if (hash != d_circuitParameters.d_hashCode)
      return false; // TODO: costul

  return false;
}

bool Circuit::generate(bool i_pathExists)
{
  // creating all files in sub directories
  std::string d_path_temp = d_path + d_circuitName;
  d_path += d_circuitName + "/";

  std::filesystem::create_directories(d_path);


  // if (!i_pathExists)
  // d_path += d_circuitName;
  std::clog << "Writing verilog for " << d_circuitName << std::endl;
  if (!graphToVerilog(d_path, i_pathExists))
    return false;

  std::clog << "Writing verilog ended " << d_circuitName << std::endl;
  
  updateCircuitsParameters();
  // TODO: costul
  // if (checkExistingHash() || d_circuitParameters.d_reliability == 0 || d_circuitParameters.d_gates == 0)
  //{
  // if (!i_pathExists)
  //     std::filesystem::remove_all(d_path);
  //}
  // else
  //{
  //    std::string path = FilesTools::getParentDirOf(d_path) + "/hashCodes.txt";
  //    std::ofstream w(path, std::ios_base::out | std::ios_base::app);
  //    w << d_circuitParameters.d_hashCode;
  //}

  return true;
}

void Circuit::setTable(const TruthTable &i_tt)
{
  d_tTable = i_tt;
}

void Circuit::setPath(const std::string &i_path)
{
  d_path = i_path;
}

void Circuit::setCircuitName(const std::string &i_circName)
{
  d_circuitName = i_circName;
  d_graph->setName(i_circName);
}

std::vector<GraphVertexBase*> Circuit::getIndexOfWireName(const std::string &i_wireName)
{
  return d_graph->getVerticesByName(i_wireName);
}
