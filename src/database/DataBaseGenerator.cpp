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
#include <additional/threadPool/ThreadPool.hpp>
#include <baseStructures/Parser.hpp>
#include <baseStructures/truthTable/TruthTable.hpp>
#include <circuit/Circuit.hpp>
#include <circuit/CircuitParameters.hpp>
#include <generators/Genetic/GeneticParameters.h>
#include <generators/Genetic/GenGenerator.h>
#include <generators/simple/SimpleGenerators.hpp>

using namespace std::chrono;
using namespace Threading;

void DataBaseGenerator::generateType(
    const DataBaseGeneratorParameters& i_dbgp,
    bool                               parallel,
    bool                               createIdDirectories
) {
  std::string s = i_dbgp.getGenerationTypeString();
  std::function<void(const GenerationParameters&)> generator =
      getGenerateMethod(s);
  // TODO: make normal code
  std::string dir = d_settings->getDatasetPath();

  if (createIdDirectories)
    dir += "/" + i_dbgp.getGenerationParameters().getName() + "/"
         + i_dbgp.getGenerationParameters().getRequestId();
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
      std::string s0  = item;
      auto        pos = s0.find(d_settings->getGenerationMethodPrefix(s));

      if (pos == std::string::npos)
        continue;

      s0.replace(pos, d_settings->getGenerationMethodPrefix(s).size(), "");

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

  auto                            randGeneratorLambda = []() {
    return AuxMethods::getRandInt(0, INT_MAX);
  };
  // we create int sequence, which would give us diffetent seeds for each repeat
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
          d_parameters.setName(
              d_settings->getGenerationMethodPrefix(s)
              + AuxMethods::intToStringWithZeroes(d_dirCount)
          );

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
          d_parameters.setName(
              d_settings->getGenerationMethodPrefix(s)
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
}

void DataBaseGenerator::generateDataBaseFromRandomTruthTable(
    const GenerationParameters& i_param
) {
  TruthTable       tt(i_param.getInputs(), i_param.getOutputs(), 0.0);

  SimpleGenerators tftt;
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
}

void DataBaseGenerator::generateDataBaseComparison(
    const GenerationParameters& i_param
) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  int      bits     = i_param.getInputs();
  bool     compare0 = i_param.getComparison().getCompare0();
  bool     compare1 = i_param.getComparison().getCompare1();
  bool     compare2 = i_param.getComparison().getCompare2();
  GraphPtr graph = sg.generatorComparison(bits, compare0, compare1, compare2);
  Circuit  c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());
}

void DataBaseGenerator::generateDataBaseEncoder(
    const GenerationParameters& i_param
) {
  SimpleGenerators sg(i_param.getSeed());
  sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

  int      bits  = i_param.getInputs();
  GraphPtr graph = sg.generatorEncoder(bits);
  Circuit  c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());
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
      i_param.getALU().getCNF()
  );
  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());
}

std::function<void(const GenerationParameters&)>
    DataBaseGenerator::getGenerateMethod(const std::string& i_methodName) {
  if (i_methodName == "FromRandomTruthTable")
    return std::bind(
        &DataBaseGenerator::generateDataBaseFromRandomTruthTable,
        this,
        std::placeholders::_1
    );
  if (i_methodName == "RandLevel")
    return std::bind(
        &DataBaseGenerator::generateDataBaseRandLevel,
        this,
        std::placeholders::_1
    );
  if (i_methodName == "RandLevelExperimental")
    return std::bind(
        &DataBaseGenerator::generateDataBaseRandLevelExperimental,
        this,
        std::placeholders::_1
    );
  if (i_methodName == "NumOperation")
    return std::bind(
        &DataBaseGenerator::generateDataBaseNumOperations,
        this,
        std::placeholders::_1
    );
  if (i_methodName == "Genetic")
    return std::bind(
        &DataBaseGenerator::generateDataBaseGenetic, this, std::placeholders::_1
    );
  if (i_methodName == "Summator")
    return std::bind(
        &DataBaseGenerator::generateDataBaseSummator,
        this,
        std::placeholders::_1
    );
  if (i_methodName == "Comparison")
    return std::bind(
        &DataBaseGenerator::generateDataBaseComparison,
        this,
        std::placeholders::_1
    );
  if (i_methodName == "Encoder")
    return std::bind(
        &DataBaseGenerator::generateDataBaseEncoder, this, std::placeholders::_1
    );
  if (i_methodName == "Subtractor")
    return std::bind(
        &DataBaseGenerator::generateDataBaseSubtractor,
        this,
        std::placeholders::_1
    );
  if (i_methodName == "Multiplexer")
    return std::bind(
        &DataBaseGenerator::generateDataBaseMultiplexer,
        this,
        std::placeholders::_1
    );
  if (i_methodName == "Demultiplexer")
    return std::bind(
        &DataBaseGenerator::generateDataBaseDemultiplexer,
        this,
        std::placeholders::_1
    );
  if (i_methodName == "Multiplier")
    return std::bind(
        &DataBaseGenerator::generateDataBaseMultiplier,
        this,
        std::placeholders::_1
    );
  if (i_methodName == "Decoder")
    return std::bind(
        &DataBaseGenerator::generateDataBaseDecoder, this, std::placeholders::_1
    );
  if (i_methodName == "Parity")
    return std::bind(
        &DataBaseGenerator::generateDataBaseParity, this, std::placeholders::_1
    );
  if (i_methodName == "ALU")
    return std::bind(
        &DataBaseGenerator::generateDataBaseALU, this, std::placeholders::_1
    );

  std::cout << "UNDEFINED FUNC << " << i_methodName << std::endl;
  return std::bind(
      &DataBaseGenerator::generateDataBaseFromRandomTruthTable,
      this,
      std::placeholders::_1
  );
}