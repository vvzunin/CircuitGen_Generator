#include <algorithm>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <limits>
#include <vector>

#include "DataBaseGenerator.hpp"

#include <additional/AuxiliaryMethods.hpp>
#include <additional/filesTools/FilesTools.hpp>
#include <baseStructures/Parser.hpp>
#include <baseStructures/truthTable/TruthTable.hpp>
#include <circuit/Circuit.hpp>
#include <circuit/CircuitParameters.hpp>
#include <CircuitGenGenerator/ThreadPool.hpp>
#include <generators/Genetic/GeneticParameters.h>
#include <generators/Genetic/GenGenerator.h>
#include <generators/simple/SimpleGenerators.hpp>

using namespace std::chrono;
using namespace Threading;

void DataBaseGenerator::runGeneratorByDefault(
    const DataBaseGeneratorParameters& i_dbgp,
    uint8_t                            parallel,
    bool                               createIdDirectories
) {
  GenerationTypes gt = i_dbgp.getGenerationType();
  std::function<void(const GenerationParameters&)> generator =
      getGenerateMethod(gt);
  // TODO: make normal code
  std::string dir = d_settings->getDatasetPath();

  if (createIdDirectories)
    dir += "/" + i_dbgp.getGenerationParameters().getName() + "/"
         + i_dbgp.getGenerationParameters().getRequestId();
  // Creating nested directories
  std::filesystem::create_directories(dir);

  d_mainPath = dir + "/";
  d_dirCount = 0;

  if (std::filesystem::is_directory(dir)) {
    for (const auto item : FilesTools::getDirectories(dir)) {
      std::string s0  = item;
      auto        pos = s0.find(d_settings->getGenerationMethodPrefix(gt));

      if (pos == std::string::npos)
        continue;

      s0.replace(pos, d_settings->getGenerationMethodPrefix(gt).size(), "");

      auto jk = std::min(s0.find("_"), s0.find("."));
      if (jk == std::string::npos) {
        jk = s0.size();
      }

      s0         = s0.substr(0, jk);

      d_dirCount = std::max(
          d_dirCount,
          std::stoi(s0) + 1
      );  // TODO: in general code n is int32, is it really need?
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

  for (int i = i_dbgp.getMinInputs(); i <= i_dbgp.getMaxInputs(); ++i) {
    for (int j = i_dbgp.getMinOutputs(); j <= i_dbgp.getMaxOutputs(); ++j) {
      auto iter = seeds.begin();
      d_parameters.setInputs(i);
      d_parameters.setOutputs(j);

      if (parallel > 1) {
        for (int tt = 0; tt < i_dbgp.getEachIteration(); ++tt) {
          d_parameters.setIteration(tt);
          d_parameters.setName(
              d_settings->getGenerationMethodPrefix(gt)
              + AuxMethods::intToStringWithZeroes(d_dirCount)
          );

          GenerationParameters param = d_parameters.getGenerationParameters();
          param.setSeed(*iter + i + j);

          auto runGenerator = [generator, param]() { generator(param); };

          pool.submit(runGenerator);

          ++d_dirCount;
          ++iter;
        }
      } else {
        for (int tt = 0; tt < i_dbgp.getEachIteration(); ++tt) {
          // TODO: it is that Rustam told about iteration?
          d_parameters.setIteration(tt);
          d_parameters.setName(
              d_settings->getGenerationMethodPrefix(gt)
              + AuxMethods::intToStringWithZeroes(d_dirCount)
          );

          GenerationParameters param = d_parameters.getGenerationParameters();
          param.setSeed(*iter);

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
    const DataBaseGeneratorParameters& i_dbgp,
    uint8_t                            parallel,
    bool                               createIdDirectories
) {
  d_type = ReturnType::GRAPH;

  runGeneratorByDefault(i_dbgp, parallel, createIdDirectories);

  return std::make_pair(d_mainPath, d_generatedGraphs);
}

ResultPath DataBaseGenerator::generateTypeForPath(
    const DataBaseGeneratorParameters& i_dbgp,
    uint8_t                            parallel,
    bool                               createIdDirectories
) {
  d_type = ReturnType::PATH;

  runGeneratorByDefault(i_dbgp, parallel, createIdDirectories);

  return std::make_pair(d_mainPath, d_generatedGraphsNames);
}

void DataBaseGenerator::generateTypeDefault(
    const DataBaseGeneratorParameters& i_dbgp,
    uint8_t                            parallel,
    bool                               createIdDirectories
) {
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
    const GenerationParameters& i_param
) {
  TruthTable       tt(i_param.getInputs(), i_param.getOutputs(), 0.0);

  SimpleGenerators tftt(i_param.getSeed());
  tftt.setGatesInputsInfo(i_param.getGatesInputsInfo());

  std::vector<GraphPtr> allGraphs;

  GraphPtr              graph;
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

  for (auto curGraph : allGraphs) {
    Circuit c(curGraph);
    c.setTable(tt);
    c.setPath(d_mainPath);
    c.setCircuitName(curGraph->getName());
    c.generate(i_param.getMakeGraphML());

    addDataToReturn(curGraph);
  }
}

void DataBaseGenerator::generateDataBaseRandLevel(
    const GenerationParameters& i_param
) {
  SimpleGenerators generator(i_param.getSeed());
  generator.setGatesInputsInfo(i_param.getGatesInputsInfo());

  GraphPtr graph = generator.generatorRandLevel(
      i_param.getRandLevel().getMinLevel(),
      i_param.getRandLevel().getMaxLevel(),
      i_param.getRandLevel().getMinElements(),
      i_param.getRandLevel().getMaxElements(),
      i_param.getInputs(),
      i_param.getOutputs()
  );

  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseRandLevelExperimental(
    const GenerationParameters& i_param
) {
  SimpleGenerators generator(i_param.getSeed());
  generator.setGatesInputsInfo(i_param.getGatesInputsInfo());

  auto     start = high_resolution_clock::now();
  GraphPtr graph = generator.generatorRandLevelExperimental(
      i_param.getRandLevel().getMinLevel(),
      i_param.getRandLevel().getMaxLevel(),
      i_param.getRandLevel().getMinElements(),
      i_param.getRandLevel().getMaxElements(),
      i_param.getInputs(),
      i_param.getOutputs()
  );

  auto    stop     = high_resolution_clock::now();
  auto    duration = duration_cast<microseconds>(stop - start);
  // std::clog << "Time taken on experimental: " << duration.count()
  //           << " microseconds" << std::endl;

  // std::clog << "Update started\n";
  Circuit c(graph);
  // std::clog << "Update ended\n";
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());

  c.generate(i_param.getMakeGraphML());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseNumOperations(
    const GenerationParameters& i_param
) {
  SimpleGenerators generator(i_param.getSeed());
  generator.setGatesInputsInfo(i_param.getGatesInputsInfo());

  std::vector<std::pair<std::string, GraphPtr>> circs;
  circs.push_back(
      {"NumOperation",
       generator.generatorNumOperation(
           i_param.getInputs(),
           i_param.getOutputs(),
           i_param.getNumOperations().getLogicOpers(),
           i_param.getNumOperations().getLeaveEmptyOut()
       )}
  );

  for (auto [name, graph] : circs) {
    Circuit c(graph);
    c.setPath(d_mainPath);
    c.setCircuitName(i_param.getName());
    c.generate(i_param.getMakeGraphML());

    addDataToReturn(graph);
  }
  // TODO: remake all generates to return value and call graphToVerilog
}

void DataBaseGenerator::generateDataBaseGenetic(
    const GenerationParameters& i_param
) {
  i_param.getGenetic().setInputs(i_param.getInputs());
  i_param.getGenetic().setOutputs(i_param.getOutputs());

  GeneticGenerator<TruthTable, TruthTableParameters> gg(
      GeneticParameters(i_param.getGenetic()),
      {i_param.getInputs(), i_param.getOutputs()},
      d_mainPath
  );
  gg.generate();
  // TODO make function return graphs
}

void DataBaseGenerator::generateDataBaseSummator(
    const GenerationParameters& i_param
) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  int      bits        = i_param.getInputs();
  bool     overflowIn  = i_param.getSummator().getOverFlowIn();
  bool     overflowOut = i_param.getSummator().getOverFlowOut();
  bool     minus       = i_param.getSummator().getMinus();
  GraphPtr graph = sg.generatorSummator(bits, overflowIn, overflowOut, minus);
  Circuit  c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseComparison(
    const GenerationParameters& i_param
) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  int      i_bits   = i_param.getInputs();
  bool     compare0 = i_param.getComparison().getCompare0();
  bool     compare1 = i_param.getComparison().getCompare1();
  bool     compare2 = i_param.getComparison().getCompare2();
  GraphPtr graph = sg.generatorComparison(i_bits, compare0, compare1, compare2);
  Circuit  c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseEncoder(
    const GenerationParameters& i_param
) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  int      i_bits = i_param.getInputs();
  GraphPtr graph  = sg.generatorEncoder(i_bits);
  Circuit  c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseParity(
    const GenerationParameters& i_param
) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  int      bits  = i_param.getInputs();
  GraphPtr graph = sg.generatorParity(bits);
  Circuit  c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseSubtractor(
    const GenerationParameters& i_param
) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  GraphPtr graph = sg.generatorSubtractor(
      i_param.getInputs(),
      i_param.getSubtractor().getOverFlowIn(),
      i_param.getSubtractor().getOverFlowOut(),
      i_param.getSubtractor().getSub()
  );
  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseMultiplexer(
    const GenerationParameters& i_param
) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  int      i_bits = i_param.getInputs();
  GraphPtr graph  = sg.generatorMultiplexer(i_bits);
  Circuit  c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseDemultiplexer(
    const GenerationParameters& i_param
) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  int      i_bits = i_param.getOutputs();
  GraphPtr graph  = sg.generatorDemultiplexer(i_bits);
  Circuit  c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseMultiplier(
    const GenerationParameters& i_param
) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  GraphPtr graph = sg.generatorMultiplier(i_param.getInputs());
  Circuit  c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseDecoder(
    const GenerationParameters& i_param
) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  GraphPtr graph = sg.generatorDecoder(i_param.getInputs());
  Circuit  c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());

  addDataToReturn(graph);
}

void DataBaseGenerator::generateDataBaseALU(const GenerationParameters& i_param
) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  GraphPtr graph = sg.generatorALU(
      i_param.getInputs(),
      i_param.getOutputs(),
      i_param.getALU().getALL(),
      i_param.getALU().getSUM(),
      i_param.getALU().getSUB(),
      i_param.getALU().getNSUM(),
      i_param.getALU().getNSUB(),
      i_param.getALU().getMULT(),
      i_param.getALU().getCOM(),
      i_param.getALU().getAND(),
      i_param.getALU().getNAND(),
      i_param.getALU().getOR(),
      i_param.getALU().getNOR(),
      i_param.getALU().getXOR(),
      i_param.getALU().getXNOR(),
      i_param.getALU().getCNF(),
      i_param.getALU().getRNL(),
      i_param.getALU().getNUMOP(),
      i_param.getALU().getminLevel(),
      i_param.getALU().getmaxLevel(),
      i_param.getALU().getminElement(),
      i_param.getALU().getmaxElement(),
      i_param.getALU().getm(),
      i_param.getALU().getLeaveEmptyOut()
  );
  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());

  addDataToReturn(graph);
}

// maybe this method should be rewritten using map with GenerationTypes and
// FuncAlias
std::function<void(const GenerationParameters&)>
    DataBaseGenerator::getGenerateMethod(const GenerationTypes i_methodType) {
  using FuncAlias = void (DataBaseGenerator::*)(const GenerationParameters&);
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