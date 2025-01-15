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
#include <generators/Genetic/GeneticParameters.hpp>
#include <generators/Genetic/GenGenerator.hpp>
#include <generators/simple/ArithmeticGenerator.hpp>
#include <generators/simple/FromTruthTableGenerator.hpp>
#include <generators/simple/CoderGenerator.hpp>
#include <generators/simple/RandLevelGenerator.hpp>
#include <generators/simple/PlexerGenerator.hpp>
#include <generators/simple/ALUGenerator.hpp>
#include <generators/simple/ComparisonGenerator.hpp>
#include <generators/simple/NumOperationsGenerator.hpp>
#include <generators/simple/ParityGenerator.hpp>

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

void DataBaseGenerator::generateDataBaseFromRandomTruthTable(
    const GenerationParameters &i_param) {
  TruthTable tt(i_param.getInputs(), i_param.getOutputs(), 0.0);

  FromTruthTableGenerator tftt(i_param);

  std::vector<GraphPtr> allGraphs;

  GraphPtr graph;
  if (i_param.getZhegalkin().getZhegalkin()) {
    graph = tftt.zhegalkinFromTruthTable(tt);
    graph->setName(i_param.getName() + "_" + "Zhegalkin");

    allGraphs.push_back(graph);
  }
  if (i_param.getCNF().getCNFF()) {
    graph = tftt.cnfFromTruthTable(tt, !i_param.getCNF().getCNFF());
    graph->setName(i_param.getName() + "_" + "CNFF");

    allGraphs.push_back(graph);
  }
  if (i_param.getCNF().getCNFT()) {
    graph = tftt.cnfFromTruthTable(tt, i_param.getCNF().getCNFT());
    graph->setName(i_param.getName() + "_" + "CNFT");

    allGraphs.push_back(graph);
  }

  for (auto curGraph: allGraphs) {
    Circuit c(curGraph);
    c.setTable(tt);
    c.setPath(d_mainPath);
    c.setCircuitName(curGraph->getName());
    c.generate(i_param.getMakeGraphMLClassic(),
               i_param.getMakeGraphMLPseudoABCD(),
               i_param.getMakeGraphMLOpenABCD());

    addDataToReturn(curGraph);
  }
}

void DataBaseGenerator::generateDataBaseRandLevel(
    const GenerationParameters &i_param) {
  RandLevelGenerator generator(i_param);
  GraphPtr graph = generator.generatorRandLevel();

  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphMLClassic(),
             i_param.getMakeGraphMLPseudoABCD(),
             i_param.getMakeGraphMLOpenABCD());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseRandLevelExperimental(
    const GenerationParameters &i_param) {
  RandLevelGenerator generator(i_param);

  auto start = high_resolution_clock::now();
  GraphPtr graph = generator.generatorRandLevelExperimental();

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  // std::clog << "Time taken on experimental: " << duration.count()
  //           << " microseconds" << std::endl;

  // std::clog << "Update started\n";
  Circuit c(graph);
  // std::clog << "Update ended\n";
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());

  c.generate(i_param.getMakeGraphMLClassic(),
             i_param.getMakeGraphMLPseudoABCD(),
             i_param.getMakeGraphMLOpenABCD());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseNumOperations(
    const GenerationParameters &i_param) {
  NumOperationsGenerator generator(i_param);

  std::vector<std::pair<std::string, GraphPtr>> circs;
  circs.push_back({"NumOperation", generator.generatorNumOperation()});

  for (auto [name, graph]: circs) {
    Circuit c(graph);
    c.setPath(d_mainPath);
    c.setCircuitName(i_param.getName());
    c.generate(i_param.getMakeGraphMLClassic(),
               i_param.getMakeGraphMLPseudoABCD(),
               i_param.getMakeGraphMLOpenABCD());

    addDataToReturn(graph);
  }
}

void DataBaseGenerator::generateDataBaseGenetic(
    const GenerationParameters &i_param) {
  GeneticGenerator<TruthTable, TruthTableParameters> gg(
      GeneticParameters(i_param.getGenetic()),
      {i_param.getInputs(), i_param.getOutputs()}, d_mainPath,
      i_param.getName());

  const auto &population = gg.generate();
  auto graphs = gg.getGraphsFromPopulation(population);

  for (auto graph: graphs) {
    Circuit c(graph);
    c.setPath(d_mainPath);
    c.setCircuitName(graph->getName());
    c.generate(i_param.getMakeGraphMLClassic(),
               i_param.getMakeGraphMLPseudoABCD(),
               i_param.getMakeGraphMLOpenABCD());

    addDataToReturn(graph);
  }
}

void DataBaseGenerator::generateDataBaseSummator(
    const GenerationParameters &i_param) {
  ArithmeticGenerator sg(i_param);
  GraphPtr graph = sg.generatorSummator();

  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphMLClassic(),
             i_param.getMakeGraphMLPseudoABCD(),
             i_param.getMakeGraphMLOpenABCD());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseComparison(
    const GenerationParameters &i_param) {
  ComparisonGenerator sg(i_param);
  GraphPtr graph = sg.generatorComparison();

  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphMLClassic(),
             i_param.getMakeGraphMLPseudoABCD(),
             i_param.getMakeGraphMLOpenABCD());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseEncoder(
    const GenerationParameters &i_param) {
  CoderGenerator sg(i_param);
  GraphPtr graph = sg.generatorEncoder();

  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphMLClassic(),
             i_param.getMakeGraphMLPseudoABCD(),
             i_param.getMakeGraphMLOpenABCD());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseParity(
    const GenerationParameters &i_param) {
  ParityGenerator sg(i_param);
  GraphPtr graph = sg.generatorParity();

  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphMLClassic(),
             i_param.getMakeGraphMLPseudoABCD(),
             i_param.getMakeGraphMLOpenABCD());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseSubtractor(
    const GenerationParameters &i_param) {
  ArithmeticGenerator sg(i_param);
  GraphPtr graph = sg.generatorSubtractor();

  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphMLClassic(),
             i_param.getMakeGraphMLPseudoABCD(),
             i_param.getMakeGraphMLOpenABCD());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseMultiplexer(
    const GenerationParameters &i_param) {
  PlexerGenerator sg(i_param);
  GraphPtr graph = sg.generatorMultiplexer();

  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphMLClassic(),
             i_param.getMakeGraphMLPseudoABCD(),
             i_param.getMakeGraphMLOpenABCD());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseDemultiplexer(
    const GenerationParameters &i_param) {
  PlexerGenerator sg(i_param);
  GraphPtr graph = sg.generatorDemultiplexer();

  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphMLClassic(),
             i_param.getMakeGraphMLPseudoABCD(),
             i_param.getMakeGraphMLOpenABCD());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseMultiplier(
    const GenerationParameters &i_param) {
  ArithmeticGenerator sg(i_param);
  GraphPtr graph = sg.generatorMultiplier();

  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphMLClassic(),
             i_param.getMakeGraphMLPseudoABCD(),
             i_param.getMakeGraphMLOpenABCD());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseDecoder(
    const GenerationParameters &i_param) {
  CoderGenerator sg(i_param);
  GraphPtr graph = sg.generatorDecoder();

  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphMLClassic(),
             i_param.getMakeGraphMLPseudoABCD(),
             i_param.getMakeGraphMLOpenABCD());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseALU(
    const GenerationParameters &i_param) {
  ALUGenerator sg(i_param);
  GraphPtr graph = sg.generatorALU();

  // LOG(INFO) << "Generation ALU complete!";
  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  // LOG(INFO) << "Start circuit generation!";
  c.generate(i_param.getMakeGraphMLClassic(),
             i_param.getMakeGraphMLPseudoABCD(),
             i_param.getMakeGraphMLOpenABCD());

  // LOG(INFO) << "Full ALU complete!";

  addDataToReturn(graph);
}

// maybe this method should be rewritten using map with GenerationTypes and
// FuncAlias
std::function<void(const GenerationParameters &)>
DataBaseGenerator::getGenerateMethod(const GenerationTypes i_methodType) {
  using FuncAlias = void (DataBaseGenerator::*)(const GenerationParameters &);
  FuncAlias generateMethodFunc = nullptr;

  switch (i_methodType) {
    case GenerationTypes::FromRandomTruthTable:
      generateMethodFunc =
          &DataBaseGenerator::generateDataBaseFromRandomTruthTable;
      break;
    case GenerationTypes::RandLevel:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseRandLevel;
      break;
    case GenerationTypes::RandLevelExperimental:
      generateMethodFunc =
          &DataBaseGenerator::generateDataBaseRandLevelExperimental;
      break;
    case GenerationTypes::NumOperation:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseNumOperations;
      break;
    case GenerationTypes::Genetic:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseGenetic;
      break;
    case GenerationTypes::Summator:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseSummator;
      break;
    case GenerationTypes::Comparison:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseComparison;
      break;
    case GenerationTypes::Encoder:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseEncoder;
      break;
    case GenerationTypes::Subtractor:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseSubtractor;
      break;
    case GenerationTypes::Multiplexer:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseMultiplexer;
      break;
    case GenerationTypes::Demultiplexer:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseDemultiplexer;
      break;
    case GenerationTypes::Multiplier:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseMultiplier;
      break;
    case GenerationTypes::Decoder:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseDecoder;
      break;
    case GenerationTypes::Parity:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseParity;
      break;
    case GenerationTypes::ALU:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseALU;
      break;

    default:
      std::clog << "Something went wrong while getting generation method. "
                << "\"FromRandomTruthTable\" is set as generation method."
                << std::endl;
      generateMethodFunc =
          &DataBaseGenerator::generateDataBaseFromRandomTruthTable;
      break;
  }

  return std::bind(generateMethodFunc, this, std::placeholders::_1);
}