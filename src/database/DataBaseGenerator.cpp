#include <algorithm>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <limits>
#include <vector>
#include <limits.h> // INT_MAX

#include "DataBaseGenerator.hpp"

#include <additional/AuxiliaryMethods.hpp>
#include <additional/filesTools/FilesTools.hpp>
#include <baseStructures/Parser.hpp>
#include <baseStructures/truthTable/TruthTable.hpp>
#include <circuit/Circuit.hpp>
#include <circuit/CircuitParameters.hpp>
#include <CircuitGenGenerator/ThreadPool.hpp>

using namespace std::chrono;
using namespace Threading;

void DataBaseGenerator::runGeneratorByDefault(
    const DataBaseGeneratorParameters &i_dbgp, uint8_t parallel,
    bool createIdDirectories) {
  GenerationTypes gt = i_dbgp.getGenerationType();
  std::function<void(const GenerationParameters &)> generator =
      getGenerateMethod(gt);
  // TODO: make normal code
  std::string dir = d_settings->getDatasetPath();

  if (createIdDirectories)
    dir += "/" + i_dbgp.getGenerationParameters().getName() + "/" +
           i_dbgp.getGenerationParameters().getRequestId();
  // Creating nested directories
  std::filesystem::create_directories(dir);

  d_mainPath = dir + "/";
  d_dirCount = 0;

  if (std::filesystem::is_directory(dir)) {
    for (const auto item: FilesTools::getDirectories(dir)) {
      std::string s0 = item;
      auto pos = s0.find(d_settings->getGenerationMethodPrefix(gt));

      if (pos == std::string::npos)
        continue;

      s0.replace(pos, d_settings->getGenerationMethodPrefix(gt).size(), "");

      auto jk = std::min(s0.find("_"), s0.find("."));
      if (jk == std::string::npos) {
        jk = s0.size();
      }

      s0 = s0.substr(0, jk);
      d_dirCount = std::max(
          d_dirCount,
          std::stoi(s0) +
              1); // TODO: in general code n is int32, is it really need?
    }
  }

  std::vector<std::uint_fast32_t> seeds(i_dbgp.getEachIteration());

  d_randGenerator.setSeed(AuxMethods::getRandSeed());

  auto randGeneratorLambda = [&]() {
    return d_randGenerator.getRandInt(0, INT_MAX);
  };
  // we create int sequence, which would give us diffetent seeds for each repeat
  std::generate(seeds.begin(), seeds.end(), randGeneratorLambda);

  ThreadPool pool(parallel);

  for (int32_t i = i_dbgp.getMinInputs(); i <= i_dbgp.getMaxInputs(); ++i) {
    for (int32_t j = i_dbgp.getMinOutputs(); j <= i_dbgp.getMaxOutputs(); ++j) {
      auto iter = seeds.begin();
      d_parameters.setInputs(i);
      d_parameters.setOutputs(j);

      if (parallel > 1) {
        for (int32_t tt = 0; tt < i_dbgp.getEachIteration(); ++tt) {
          d_parameters.setIteration(tt);
          d_parameters.setName(d_settings->getGenerationMethodPrefix(gt) +
                               AuxMethods::intToStringWithZeroes(d_dirCount));

          GenerationParameters param = d_parameters.getGenerationParameters();
          param.setSeed(*iter + i + j);

          auto runGenerator = [generator, param]() { generator(param); };

          pool.submit(runGenerator);

          ++d_dirCount;
          ++iter;
        }
      } else {
        for (int32_t tt = 0; tt < i_dbgp.getEachIteration(); ++tt) {
          // TODO: it is that Rustam told about iteration?
          d_parameters.setIteration(tt);
          d_parameters.setName(d_settings->getGenerationMethodPrefix(gt) +
                               AuxMethods::intToStringWithZeroes(d_dirCount));

          GenerationParameters param = d_parameters.getGenerationParameters();
          param.setSeed(*iter + i + j);

          generator(param);

          ++d_dirCount;
          ++iter;
        }
      }
    }
  }
  pool.wait();
}

ResultGraph DataBaseGenerator::generateTypeForGraph(
    const DataBaseGeneratorParameters &i_dbgp, uint8_t parallel,
    bool createIdDirectories) {
  d_type = ReturnType::GRAPH;

  runGeneratorByDefault(i_dbgp, parallel, createIdDirectories);

  return std::make_pair(d_mainPath, d_generatedGraphs);
}

ResultPath DataBaseGenerator::generateTypeForPath(
    const DataBaseGeneratorParameters &i_dbgp, uint8_t parallel,
    bool createIdDirectories) {
  d_type = ReturnType::PATH;

  runGeneratorByDefault(i_dbgp, parallel, createIdDirectories);

  return std::make_pair(d_mainPath, d_generatedGraphsNames);
}

void DataBaseGenerator::generateTypeDefault(
    const DataBaseGeneratorParameters &i_dbgp, uint8_t parallel,
    bool createIdDirectories) {
  d_type = ReturnType::DEFAULT;

  runGeneratorByDefault(i_dbgp, parallel, createIdDirectories);
}

void DataBaseGenerator::addDataToReturn(GraphPtr graph) {
  d_resWrite.lock();
  switch (d_type) {
    case ReturnType::GRAPH:
      d_generatedGraphs.push_back(graph);
      break;
    case ReturnType::PATH:
      d_generatedGraphsNames.push_back(graph->getName());
      break;
    default:
      break;
  }
  d_resWrite.unlock();
}

void DataBaseGenerator::processCircuit(std::shared_ptr<OrientedGraph> graph,
                                       const TruthTable &tt,
                                       const GenerationParameters &i_param,
                                       const std::string name) {

  Circuit c(graph);
  c.setTable(tt);
  c.setPath(d_mainPath);
  if (name.empty())
    c.setCircuitName(i_param.getName());
  else
    c.setCircuitName(name);
  c.generate(i_param.getMakeGraphMLClassic(),
             i_param.getMakeGraphMLPseudoABCD(),
             i_param.getMakeGraphMLOpenABCD());

  addDataToReturn(graph);
}

void DataBaseGenerator::processCircuit(std::shared_ptr<OrientedGraph> graph,
                                       const GenerationParameters &i_param,
                                       const std::string name) {
  Circuit c(graph);
  c.setPath(d_mainPath);
  if (name.empty())
    c.setCircuitName(i_param.getName());
  else
    c.setCircuitName(name);
  c.generate(i_param.getMakeGraphMLClassic(),
             i_param.getMakeGraphMLPseudoABCD(),
             i_param.getMakeGraphMLOpenABCD());

  addDataToReturn(graph);
}

// maybe this method should be rewritten using map with GenerationTypes and
// FuncAlias
std::function<void(const GenerationParameters &)>
DataBaseGenerator::getGenerateMethod(const GenerationTypes i_methodType) {
  using FuncAlias = void (DataBaseGenerator::*)(const GenerationParameters &);
  FuncAlias generateMethodFunc = nullptr;

  generateMethodFunc = &DataBaseGenerator::generateDataBase;

  return std::bind(generateMethodFunc, this, std::placeholders::_1);
}