#include <additional/filesTools/FilesTools.h>
#include <additional/threadPool/ThreadPool.h>
#include <baseStructures/Parser.h>
#include <baseStructures/truthTable/TruthTable.h>
#include <circuits/Circuit.h>
#include <circuits/CircuitsParameters.h>
#include <generators/simple/SimpleGenerators.h>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <limits>
#include <vector>
// #include <generators/Genetic/GenGenerator.h>
// #include <generators/Genetic/GeneticParameters.h>
#include <additional/AuxiliaryMethods.h>

#include "DataBaseGenerator.h"

using namespace std::chrono;
using namespace Threading;

void DataBaseGenerator::generateType(const DataBaseGeneratorParameters &i_dbgp,
                                     bool parallel, bool createIdDirectories) {
  std::string s = i_dbgp.getGenerationTypeString();
  std::function<void(const GenerationParameters &)> generator =
      getGenerateMethod(s);
  // TODO: make normal code
  std::string dir = d_settings->getDatasetPath();

  if (createIdDirectories)
    dir += "/" + i_dbgp.getGenerationParameters().getName() + "/" +
           i_dbgp.getGenerationParameters().getRequestId();
  // Creating nested directories
  std::filesystem::create_directories(dir);

  d_mainPath = dir + "/";
  d_dirCount = 0;
  // std::cout << "Inside of generateType: " << std::endl;
  // std::cout << "dir = " << dir << std::endl;
  // std::cout << "i_dbgp.getGenerationParameters().getRequestId() returned: "
  // << i_dbgp.getGenerationParameters().getRequestId() << std::endl; std::cout
  // << "i_dbgp.getMaxInputs() returned: " << i_dbgp.getMaxInputs() <<
  // std::endl; std::cout << "i_dbgp.getMinInputs() returned: " <<
  // i_dbgp.getMinInputs() << std::endl; std::cout << "i_dbgp.getMaxOutputs()
  // returned: " << i_dbgp.getMaxOutputs() << std::endl; std::cout <<
  // "i_dbgp.getMinOutsputs() returned: " << i_dbgp.getMinOutputs() <<
  // std::endl;
  if (std::filesystem::is_directory(dir)) {
    for (const auto item : FilesTools::getDirectories(dir)) {
      std::string s0 = item;
      auto pos = s0.find(d_settings->getGenerationMethodPrefix(s));

      if (pos == std::string::npos) continue;

      s0.replace(pos, d_settings->getGenerationMethodPrefix(s).size(), "");

      auto jk = std::min(s0.find("_"), s0.find("."));
      if (jk == std::string::npos) {
        jk = s0.size();
      }

      s0 = s0.substr(0, jk);

      d_dirCount = std::max(
          d_dirCount,
          std::stoi(s0) +
              1);  // TODO: in general code n is int32, is it really need?
    }
  }

  std::vector<std::uint_fast32_t> seeds(i_dbgp.getEachIteration());

  auto randGeneratorLambda = []() {
    return AuxMethods::getRandInt(0, INT_MAX);
  };
  // we create int sequence, wich would give us diffetent seeds for each repeat
  std::generate(seeds.begin(), seeds.end(), randGeneratorLambda);

  ThreadPool pool(d_settings->getNumThread());

  for (int i = i_dbgp.getMinInputs(); i <= i_dbgp.getMaxInputs(); ++i) {
    for (int j = i_dbgp.getMinOutputs(); j <= i_dbgp.getMaxOutputs(); ++j) {
      auto iter = seeds.begin();
      d_parameters.setInputs(i);
      d_parameters.setOutputs(j);

      if (parallel) {
        for (int tt = 0; tt < i_dbgp.getEachIteration(); ++tt) {
          d_parameters.setIteration(tt);
          d_parameters.setName(d_settings->getGenerationMethodPrefix(s) +
                               std::to_string(d_dirCount));

          GenerationParameters param = d_parameters.getGenerationParameters();
          param.setSeed(*iter);

          auto runGenerator = [generator, param]() { generator(param); };

          pool.submit(runGenerator);

          ++d_dirCount;
          ++iter;
        }

        pool.wait();
      } else {
        for (int tt = 0; tt < i_dbgp.getEachIteration(); ++tt) {
          // TODO: it is that Rustam told about iteration?
          d_parameters.setIteration(tt);
          d_parameters.setName(d_settings->getGenerationMethodPrefix(s) +
                               std::to_string(d_dirCount));

          GenerationParameters param = d_parameters.getGenerationParameters();
          param.setSeed(*iter);

          generator(param);

          ++d_dirCount;
          ++iter;
        }
      }
    }
  }
}

void DataBaseGenerator::generateDataBaseFromRandomTruthTable(
    const GenerationParameters &i_param) {
  TruthTable tt(i_param.getInputs(), i_param.getOutputs(), 0.0);

  SimpleGenerators tftt;
  tftt.setGatesInputsInfo(i_param.getGatesInputsInfo());

  std::vector<std::pair<std::string, std::vector<std::string>>> circs;

  if (i_param.getCNF().getCNFT())
    circs.push_back({"CNFT", tftt.cnfFromTruthTable(tt, true)});

  if (i_param.getCNF().getCNFF())
    circs.push_back({"CNFF", tftt.cnfFromTruthTable(tt, false)});

  for (const auto &[name, expr] : circs) {
    Parser pCNFT(expr);
    pCNFT.parseAll();

    OrientedGraph graph = pCNFT.getGraph();
    graph.setName(i_param.getName() + "_" + name);

    Circuit c(&graph, expr);
    c.setTable(tt);
    c.setPath(d_mainPath);
    c.setCircuitName(i_param.getName() + "_" + name);
    c.generate();
  }
}

void DataBaseGenerator::generateDataBaseRandLevel(
    const GenerationParameters &i_param) {
  SimpleGenerators generator(i_param.getSeed());
  generator.setGatesInputsInfo(i_param.getGatesInputsInfo());

  OrientedGraph graph =
      generator.generatorRandLevel(i_param.getRandLevel().getMinLevel(),
                                   i_param.getRandLevel().getMaxLevel(),
                                   i_param.getRandLevel().getMinElements(),
                                   i_param.getRandLevel().getMaxElements(),
                                   i_param.getInputs(), i_param.getOutputs());

  Circuit c(&graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate();
}

void DataBaseGenerator::generateDataBaseRandLevelExperimental(
    const GenerationParameters &i_param) {
  SimpleGenerators generator(i_param.getSeed());
  generator.setGatesInputsInfo(i_param.getGatesInputsInfo());

  auto start = high_resolution_clock::now();
  OrientedGraph graph = generator.generatorRandLevelExperimental(
      i_param.getRandLevel().getMinLevel(),
      i_param.getRandLevel().getMaxLevel(),
      i_param.getRandLevel().getMinElements(),
      i_param.getRandLevel().getMaxElements(), i_param.getInputs(),
      i_param.getOutputs());

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::clog << "Time taken on experimental: " << duration.count()
            << " microseconds" << std::endl;

  std::clog << "Update started\n";
  Circuit c(&graph);
  std::clog << "Update ended\n";
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());

  c.generate();
}

void DataBaseGenerator::generateDataBaseNumOperations(
    const GenerationParameters &i_param) {
  SimpleGenerators generator(i_param.getSeed());
  generator.setGatesInputsInfo(i_param.getGatesInputsInfo());

  std::vector<std::pair<std::string, OrientedGraph>> circs;
  circs.push_back(
      {"NumOperation", generator.generatorNumOperation(
                           i_param.getInputs(), i_param.getOutputs(),
                           i_param.getNumOperations().getLogicOpers(),
                           i_param.getNumOperations().getLeaveEmptyOut())});

  for (auto [name, graph] : circs) {
    Circuit c(&graph);
    c.setPath(d_mainPath);
    c.setCircuitName(i_param.getName());
    c.generate();
  }
  // TODO: remake all generates to return value and call graphToVerilog
}

void DataBaseGenerator::generateDataBaseGenetic(
    const GenerationParameters &i_param) {
  // i_param.getGenetic().setInputs(i_param.getInputs());
  // i_param.getGenetic().setOutputs(i_param.getOutputs());

  // GeneticGenerator<TruthTable, TruthTableParameters>
  // gg(GeneticParameters(i_param.getGenetic()),
  //                                                       {i_param.getInputs(),
  //                                                       i_param.getOutputs()},
  //                                                       d_mainPath);
  // gg.generate();
}

void DataBaseGenerator::GenerateDataBaseSummator(
    const GenerationParameters &i_param) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  int i_bits = i_param.getInputs();
  bool i_overflowIn = i_param.getSummator().d_OverFlowIn;
  bool i_overflowOut = i_param.getSummator().d_OverFlowOut;
  bool i_minus = i_param.getSummator().d_minus;
  OrientedGraph graph =
      sg.generatorSummator(i_bits, i_overflowIn, i_overflowOut, i_minus);
  Circuit c(&graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate();
}

void DataBaseGenerator::GenerateDataBaseComparison(
    const GenerationParameters &i_param) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  int i_bits = i_param.getInputs();
  bool i_compare0 = i_param.getComparison().d_compare0;
  bool i_compare1 = i_param.getComparison().d_compare1;
  bool i_compare2 = i_param.getComparison().d_compare2;
  OrientedGraph graph =
      sg.generatorComparison(i_bits, i_compare0, i_compare1, i_compare2);
  Circuit c(&graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate();
}

void DataBaseGenerator::GenerateDataBaseEncoder(
    const GenerationParameters &i_param) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  int bits = i_param.getInputs();
  OrientedGraph graph = sg.generatorEncoder(bits);
  Circuit c(&graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate();
}

void DataBaseGenerator::generateDataBaseSubtractor(const GenerationParameters &i_param) {
    SimpleGenerators sg(i_param.getSeed());
    sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

    OrientedGraph graph = sg.generatorSubtractor(i_param.getInputs(),
                                                 i_param.getSubtractor().getOverFlowIn(),
                                                 i_param.getSubtractor().getOverFlowOut(),
                                                 i_param.getSubtractor().getSub());
    Circuit c(&graph);
    c.setPath(d_mainPath);
    c.setCircuitName(i_param.getName());
    c.generate();
}

void DataBaseGenerator::generateDataBaseDemultiplexer(const GenerationParameters &i_param) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  int i_bits = i_param.getOutputs();
  OrientedGraph graph = sg.generatorDemultiplexer(i_bits);
  Circuit c(&graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate();
}

void DataBaseGenerator::generateDataBaseMultiplier(const GenerationParameters &i_param){
    SimpleGenerators sg(i_param.getSeed());
    sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

    OrientedGraph graph = sg.generatorMultiplier(i_param.getInputs());
    Circuit c(&graph);
    c.setPath(d_mainPath);
    c.setCircuitName(i_param.getName());
    c.generate();
}

std::function<void(const GenerationParameters &)>
DataBaseGenerator::getGenerateMethod(const std::string &i_methodName) {
  if (i_methodName == "FromRandomTruthTable")
    return std::bind(&DataBaseGenerator::generateDataBaseFromRandomTruthTable,
                     this, std::placeholders::_1);
  if (i_methodName == "RandLevel")
    return std::bind(&DataBaseGenerator::generateDataBaseRandLevel, this,
                     std::placeholders::_1);
  if (i_methodName == "RandLevelExperimental")
    return std::bind(&DataBaseGenerator::generateDataBaseRandLevelExperimental,
                     this, std::placeholders::_1);
  if (i_methodName == "NumOperation")
    return std::bind(&DataBaseGenerator::generateDataBaseNumOperations, this,
                     std::placeholders::_1);
  if (i_methodName == "Summator")
    return std::bind(&DataBaseGenerator::GenerateDataBaseSummator, this,
                     std::placeholders::_1);
  if (i_methodName == "Comparison")
    return std::bind(&DataBaseGenerator::GenerateDataBaseComparison, this,
                     std::placeholders::_1);
  if (i_methodName == "Genetic")
    return std::bind(&DataBaseGenerator::generateDataBaseGenetic, this,
                     std::placeholders::_1);
  if (i_methodName == "Subtractor")
      return std::bind(&DataBaseGenerator::generateDataBaseSubtractor, this,
                       std::placeholders::_1);
  if (i_methodName == "Demultiplexer")
    return std::bind(&DataBaseGenerator::generateDataBaseDemultiplexer, this, 
                       std::placeholders::_1);
  if (i_methodName == "Multiplier")
      return std::bind(&DataBaseGenerator::generateDataBaseMultiplier, this,
                       std::placeholders::_1);
                       
  std::cout << "UNDEFINED FUNC << " << i_methodName << std::endl;
  return std::bind(&DataBaseGenerator::generateDataBaseFromRandomTruthTable,
                   this, std::placeholders::_1);
}