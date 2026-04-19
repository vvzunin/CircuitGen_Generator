#include "CircuitGenGenerator/info.hpp"
#include "additional/auxiliaryMethods/AuxiliaryMethods.hpp"
#include "database/dataBaseGenerator/DataBaseGenerator.hpp"
#include "database/dataBaseGeneratorParameters/DataBaseGeneratorParameters.hpp"
#include "generators/GenerationParameters.hpp"
#include "generators/genetic/chromosome/Chromosome.hpp"
#include "generators/genetic/mutations/parameters/MutationParameters.hpp"
#include "generators/genetic/parents/parameters/ParentsParameters.hpp"
#include "generators/genetic/recombination/parameters/RecombinationParameters.hpp"
#include "generators/genetic/selections/parameters/SelectionParameters.hpp"
#include "settings/Settings.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <getopt.h>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <unistd.h>
#include <vector>

// #include "CircuitGenGenerator/CircuitGenGenerator.hpp"
#include <CircuitGenGraph/OrientedGraph.hpp>

using namespace std::chrono;
using namespace CG_Gen;

bool check(const nlohmann::json &i_data, const std::string &i_param,
           bool isExit = true) {
  if (!i_data.contains(i_param)) {
    std::cerr << "JSON file doesn't contains " + i_param + "!" << std::endl;
    if (isExit)
      std::exit(1);
    return false;
  }
  return true;
}

template<typename Type>
Type readWithCheck(const nlohmann::json &i_data, const std::string &i_param,
                   Type i_default, bool isExit = false) {
  if (!i_data.contains(i_param)) {
    std::cerr << "JSON file doesn't contains " + i_param + "!" << std::endl;
    if (isExit)
      std::exit(1);
    return i_default;
  }
  return static_cast<Type>(i_data[i_param]);
}

template<typename Type>
Type readEnumWithCheck(const nlohmann::json &i_data, const std::string &i_param,
                       const std::map<std::string, Type> &values_map) {
  if (!i_data.contains(i_param)) {
    std::cerr << "JSON file doesn't contains " + i_param + "!" << std::endl;
    std::exit(1);
  }
  const std::string valStr = static_cast<std::string>(i_data[i_param]);
  if (values_map.find(valStr) == values_map.end()) {
    std::cerr << "Unsupported type for parameter " << i_param << std::endl;
    exit(1);
  }
  return values_map.at(valStr);
}

GenerationParameters *
getBasicParameters(const nlohmann::json &i_data, GenerationTypes &i_type,
                   int &i_minInputs, int &i_maxInputs, int &i_minOutputs,
                   int &i_maxOutputs, int &i_repeats, bool &i_convertToBasis) {
  const std::string name = "GenerationParameters";
  check(i_data, name);
  int seed = readWithCheck<int>(i_data[name], "seed", -1);
  AuxMethods::setRandSeed(seed == -1 ? static_cast<unsigned>(std::time(0))
                                     : static_cast<unsigned>(seed));
  i_minInputs = readWithCheck<int>(i_data[name], "min_in", 1);
  i_maxInputs = readWithCheck<int>(i_data[name], "max_in", 1);
  i_minOutputs = readWithCheck<int>(i_data[name], "min_out", 1);
  i_maxOutputs = readWithCheck<int>(i_data[name], "max_out", 1);
  i_repeats = readWithCheck<int>(i_data[name], "repeat_n", 1);

  i_convertToBasis =
      readWithCheck<bool>(i_data[name], "convert_to_basis", false);

  // Считывание информации по логичсеким элементам.
  std::map<std::string, std::vector<int>> gatesInputsInfo;

  if (check(i_data[name], "gates_inputs_info")) {
    for (auto gate: i_data[name]["gates_inputs_info"].items()) {
      std::vector<int> gatesNumber =
          static_cast<std::vector<int>>(gate.value());

      // sorting data. It's important for fast generator work
      if (!gatesNumber.empty()) {
        std::sort(gatesNumber.begin(), gatesNumber.end());

        gatesInputsInfo[gate.key()] = gatesNumber;
      }
    }
  }

  // get generation type
  i_type = readEnumWithCheck(i_data[name], "type_of_generation",
                             GenerationTypes2Name);

  GenerationParameters *gp;

  bool isExit = false;
  if (readWithCheck<bool>(i_data["OutputParameters"], "create_id_directories",
                          false))
    isExit = true;
  std::string datasetId = readWithCheck<std::string>(i_data["OutputParameters"],
                                                     "dataset_id", "0", isExit);
  int requestIdSTR =
      readWithCheck<int>(i_data["OutputParameters"], "id", 0, isExit);
  std::string requestId = std::to_string(requestIdSTR);

  // for GraphML
  bool makeGraphMLClassic = readWithCheck<bool>(i_data["OutputParameters"],
                                                "make_graphml_classic", false);
  bool makeGraphMLPseudo = readWithCheck<bool>(
      i_data["OutputParameters"], "make_graphml_pseudo_abc_d", false);
  bool makeGraphMLOpen = readWithCheck<bool>(i_data["OutputParameters"],
                                             "make_graphml_open_abc_d", false);
  bool makeDot =
      readWithCheck<bool>(i_data["OutputParameters"], "make_dot", false);

  gp =
      new GenerationParameters(datasetId, requestId, i_minInputs, i_minOutputs,
                               i_repeats, makeGraphMLClassic, makeGraphMLPseudo,
                               makeGraphMLOpen, makeDot, i_convertToBasis);
  gp->setGatesInputInfo(gatesInputsInfo);

  return gp;
}

void setFromTruthTable(const nlohmann::json &i_data,
                       GenerationParameters *i_gp) {
  std::string name = "FromRandomTruthTable";
  // Основные параметры для From Random Truth Table
  check(i_data, name);
  bool cnff = readWithCheck<bool>(i_data[name], "CNFF", false);
  bool cnft = readWithCheck<bool>(i_data[name], "CNFT", false);
  bool zhegalkin = readWithCheck<bool>(i_data[name], "Zhegalkin", false);
  if (!(cnff || cnft || zhegalkin)) {
    std::cerr << "Parameters for selected generation type is not set."
              << std::endl;
    exit(1);
  }
  i_gp->setCNFF(cnff);
  i_gp->setCNFT(cnft);
  i_gp->setZhegalkin(zhegalkin);
}

void setRandLevel(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "RandLevel";
  check(i_data, name);
  const auto minLevel = readWithCheck<int>(i_data[name], "min_level", 1);
  const auto maxLevel = readWithCheck<int>(i_data[name], "max_level", 1);
  const auto minElem = readWithCheck<int>(i_data[name], "min_elem", 1);
  const auto maxElem = readWithCheck<int>(i_data[name], "max_elem", 1);

  i_gp->setRandLevelParameters(minLevel, maxLevel, minElem, maxElem);
}

void setRandLevelExperimental(const nlohmann::json &i_data,
                              GenerationParameters *i_gp) {
  std::string name = "RandLevelExperimental";
  check(i_data, name);
  const auto minLevel = readWithCheck<int>(i_data[name], "min_level", 1);
  const auto maxLevel = readWithCheck<int>(i_data[name], "max_level", 1);
  const auto minElem = readWithCheck<int>(i_data[name], "min_elem", 1);
  const auto maxElem = readWithCheck<int>(i_data[name], "max_elem", 1);

  i_gp->setRandLevelParameters(minLevel, maxLevel, minElem, maxElem);
}

void setNumOperation(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "NumOperation";
  check(i_data, name);

  bool LeaveEmptyOut =
      readWithCheck<bool>(i_data[name], "leave_empty_out", false);

  std::map<std::string, Gates> mapping = {
      {"num_and", Gates::GateAnd}, {"num_nand", Gates::GateNand},
      {"num_or", Gates::GateOr},   {"num_not", Gates::GateNot},
      {"num_nor", Gates::GateNor}, {"num_buf", Gates::GateBuf},
      {"num_xor", Gates::GateXor}, {"num_xnor", Gates::GateXnor},
  };

  std::map<Gates, int> m;

  for (const auto &[key, val]: mapping) {
    const int count = readWithCheck<int>(i_data[name], key, 1);
    m[val] = count;
  }

  i_gp->setNumOperationParameters(m, LeaveEmptyOut);
}

void setComparison(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "Comparison";
  check(i_data, name);

  const bool equal = readWithCheck<bool>(i_data[name], "equal", false);
  const bool less = readWithCheck<bool>(i_data[name], "less", false);
  const bool more = readWithCheck<bool>(i_data[name], "more", false);

  i_gp->setComparisonParameters(equal, less, more);
}

void setSummator(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "Summator";
  check(i_data, name);

  const bool overflowIn =
      readWithCheck<bool>(i_data[name], "overflowIn", false);
  const bool overflowOut =
      readWithCheck<bool>(i_data[name], "overflowOut", false);
  const bool minus = readWithCheck<bool>(i_data[name], "minus", false);

  i_gp->setSummatorParameters(overflowIn, overflowOut, minus);
}

void setMultiplier(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "Multiplier";
  check(i_data, name, false);
}

void setSubtractor(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "Subtractor";
  check(i_data, name);

  const bool overflowIn =
      readWithCheck<bool>(i_data[name], "overflowIn", false);
  const bool overflowOut =
      readWithCheck<bool>(i_data[name], "overflowOut", false);
  const bool sub = readWithCheck<bool>(i_data[name], "sub", false);

  i_gp->setSubtractorParameters(overflowIn, overflowOut, sub);
}

void setMultiplexer(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "Multiplexer";
  check(i_data, name, false);
}

void setDemultiplexer(const nlohmann::json &i_data,
                      GenerationParameters *i_gp) {
  std::string name = "Demultiplexer";
  check(i_data, name, false);
}

void setEncoder(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "Encoder";
  check(i_data, name, false);
}

void setDecoder(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "Decoder";
  check(i_data, name, false);
}

void setGenetic(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "Genetic";
  check(i_data, name);

  const int32_t populationSize =
      readWithCheck<int32_t>(i_data[name], "population_size", 1);
  const int32_t numOfCycles = readWithCheck<int32_t>(i_data[name], "cycles", 1);
  const ParentsTypes selecTypeParent = readEnumWithCheck<ParentsTypes>(
      i_data[name], "selection_type_parent", ParentsType2Name);
  const int32_t tourSize = readWithCheck<int32_t>(i_data[name], "tour_size", 1);
  const RecombinationTypes recombinationType =
      readEnumWithCheck<RecombinationTypes>(i_data[name], "playback_type",
                                            RecombinationType2Name);
  const int32_t refPoints =
      readWithCheck<int32_t>(i_data[name], "ref_points", 1);
  const double maskProb = readWithCheck<double>(i_data[name], "mask_prob", 1.0);
  const int32_t recNum = readWithCheck<int32_t>(i_data[name], "rec_num", 1);

  // currently not used
  [[maybe_unused]] const GenotypeParametersTypes chromosomeType =
      readEnumWithCheck<GenotypeParametersTypes>(
          i_data[name], "chromosome_type", GenotypeParametersType2Name);
  [[maybe_unused]] const int32_t exchangeType =
      readWithCheck<int32_t>(i_data[name], "swap_type", 1);
  [[maybe_unused]] const double mutationChance =
      readWithCheck<double>(i_data[name], "mut_chance", 0.5);
  [[maybe_unused]] const MutationTypes mutationType =
      readEnumWithCheck<MutationTypes>(i_data[name], "mut_type",
                                       MutationType2Name);
  [[maybe_unused]] const double outRatio =
      readWithCheck<double>(i_data[name], "out_ratio", 1.0);
  [[maybe_unused]] const double probabilityTruthTable =
      readWithCheck<double>(i_data[name], "ratio_in_table", 1.0);
  [[maybe_unused]] const SelectionTypes selType =
      readEnumWithCheck<SelectionTypes>(i_data[name], "selection_type",
                                        SelectionType2Name);
  [[maybe_unused]] const int32_t survNum =
      readWithCheck<int32_t>(i_data[name], "surv_num", 1);

  i_gp->setPopulationSize(populationSize);
  i_gp->setNumOfCycles(numOfCycles);
  i_gp->setRecombinationParameters(selecTypeParent, tourSize, recombinationType,
                                   refPoints, maskProb, recNum);
}

void setParity(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "Parity";
  check(i_data, name, false);
}

void setALU(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "ALU";
  check(i_data, name);

  const bool ALL = readWithCheck<bool>(i_data[name], "ALL", false);
  const bool AND = readWithCheck<bool>(i_data[name], "AND", false);
  const bool NAND = readWithCheck<bool>(i_data[name], "NAND", false);
  const bool OR = readWithCheck<bool>(i_data[name], "OR", false);
  const bool NOR = readWithCheck<bool>(i_data[name], "NOR", false);
  const bool XOR = readWithCheck<bool>(i_data[name], "XOR", false);
  const bool XNOR = readWithCheck<bool>(i_data[name], "XNOR", false);
  const bool SUM = readWithCheck<bool>(i_data[name], "SUM", false);
  const bool NSUM = readWithCheck<bool>(i_data[name], "NSUM", false);
  const bool MULT = readWithCheck<bool>(i_data[name], "MULT", false);
  const bool SUB = readWithCheck<bool>(i_data[name], "SUB", false);
  const bool NSUB = readWithCheck<bool>(i_data[name], "NSUB", false);
  const bool COM = readWithCheck<bool>(i_data[name], "COM", false);
  const bool CNF = readWithCheck<bool>(i_data[name], "CNF", false);
  const bool RNL = readWithCheck<bool>(i_data[name], "RNL", false);
  const bool NUM_OP = readWithCheck<bool>(i_data[name], "NUM_OP", false);

  const int min_level = readWithCheck<int>(i_data[name], "min_level", 1);
  const int max_level = readWithCheck<int>(i_data[name], "max_level", 1);
  const int min_elem = readWithCheck<int>(i_data[name], "min_elem", 1);
  const int max_elem = readWithCheck<int>(i_data[name], "max_elem", 1);
  const bool leave_empty_out =
      readWithCheck<bool>(i_data[name], "leave_empty_out", false);

  // not initialized now
  std::map<Gates, int32_t> m;

  i_gp->setALUParameters(ALL, SUM, SUB, NSUM, NSUB, MULT, COM, AND, NAND, OR,
                         NOR, XOR, XNOR, CNF, RNL, NUM_OP, min_level, max_level,
                         min_elem, max_elem, m, leave_empty_out);
}

void setMealyMoore(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "MealyMoore";
  check(i_data, name);

  const bool genType = readWithCheck<bool>(i_data[name], "gen_type", false);
  const uint32_t numStates =
      readWithCheck<uint32_t>(i_data[name], "num_states", 0);
  const bool saveDOT_mmg =
      readWithCheck<bool>(i_data[name], "save_dot_mmg", false);

  i_gp->setMealyMooreParameters(genType, numStates, saveDOT_mmg);
}

void setDotToGraph(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "DotToGraph";
  check(i_data, name);

  const bool GenTypeDot =
      readWithCheck<bool>(i_data[name], "gen_type_dot", false);
  const std::string DotPath =
      readWithCheck<std::string>(i_data[name], "dotpath", "./dataset/21/3");

  i_gp->setDotToGraphParameters(GenTypeDot, DotPath);
}

void setCascade(const nlohmann::json &i_data, GenerationParameters *i_gp) {
  std::string name = "Cascade";
  check(i_data, name);

  const uint32_t MaxNumStates =
      readWithCheck<uint32_t>(i_data[name], "max_num_states", 1);
  const uint32_t MinNumStates =
      readWithCheck<uint32_t>(i_data[name], "min_num_states", 1);
  const uint32_t NumAutomaton =
      readWithCheck<uint32_t>(i_data[name], "num_automatons", 1);

  i_gp->setCascadeParameters(MaxNumStates, MinNumStates, NumAutomaton);
}

DataBaseGeneratorParameters *
setGenerationParameters(const nlohmann::json &i_data) {
  GenerationTypes gt;
  int minInputs, maxInputs;
  int minOutputs, maxOutputs;
  int repeats;
  bool convertToBasis;
  GenerationParameters *gp =
      getBasicParameters(i_data, gt, minInputs, maxInputs, minOutputs,
                         maxOutputs, repeats, convertToBasis);

  // Setting generation type.
  switch (gt) {
    case GenerationTypes::FromRandomTruthTable: {
      setFromTruthTable(i_data, gp);
      break;
    }
    case GenerationTypes::RandLevel: {
      setRandLevel(i_data, gp);
      break;
    }
    case GenerationTypes::RandLevelExperimental: {
      setRandLevelExperimental(i_data, gp);
      break;
    }
    case GenerationTypes::NumOperation: {
      setNumOperation(i_data, gp);
      break;
    }
    case GenerationTypes::Comparison: {
      setComparison(i_data, gp);
      break;
    }
    case GenerationTypes::Summator: {
      setSummator(i_data, gp);
      break;
    }
    case GenerationTypes::Multiplier: {
      setMultiplier(i_data, gp);
      break;
    }
    case GenerationTypes::Subtractor: {
      setSubtractor(i_data, gp);
      break;
    }
    case GenerationTypes::Multiplexer: {
      setMultiplexer(i_data, gp);
      break;
    }
    case GenerationTypes::Demultiplexer: {
      setDemultiplexer(i_data, gp);
      break;
    }
    case GenerationTypes::Encoder: {
      setEncoder(i_data, gp);
      break;
    }
    case GenerationTypes::Decoder: {
      setDecoder(i_data, gp);
      break;
    }
    case GenerationTypes::Genetic: {
      setGenetic(i_data, gp);
      break;
    }
    case GenerationTypes::Parity: {
      setParity(i_data, gp);
      break;
    }
    case GenerationTypes::ALU: {
      setALU(i_data, gp);
      break;
    }
    case GenerationTypes::MealyMoore: {
      setMealyMoore(i_data, gp);
      break;
    }
    case GenerationTypes::DotToGraph: {
      setDotToGraph(i_data, gp);
      break;
    }
    case GenerationTypes::Cascade: {
      setCascade(i_data, gp);
      break;
    }
  }

  DataBaseGeneratorParameters *dbgp = new DataBaseGeneratorParameters(
      minInputs, maxInputs, minOutputs, maxOutputs, repeats, gt, *gp);

  auto instance = Settings::getInstance("CircuitGenGenerator");

  if (check(i_data["OutputParameters"], "dataset_path")) {
    const auto path =
        static_cast<std::string>(i_data["OutputParameters"]["dataset_path"]);
    instance->setDatasetPath(path);
  }

  return dbgp;
}

/// @brief runGeneration reads json file and runs specified generator/
/// for DotToGraph generator it reads folderpath from json and changes
/// json file for DotToGraphGenerator so it receives every .dot file in
/// folderpath. Then it runs DotToGraphGenerator for every .dot file in folder.
/// This change is for DotToGraphGenerator only.
/// @param folderPath path to a folder containing .dot files for
/// DotToGraphGenerator

void runGeneration(
    std::string i_json_path,
    std::function<void(DataBaseGenerator &, const DataBaseGeneratorParameters &,
                       uint8_t, bool)>
        i_callable) {
  std::ifstream f(i_json_path);
  nlohmann::json DATA = nlohmann::json::parse(f);
  // Read all json objects in json file.

  for (auto it = DATA.begin(); it != DATA.end(); it++) {
    nlohmann::json data = *it;

    DataBaseGeneratorParameters *dbgp = setGenerationParameters(data);

    DataBaseGenerator generator(*dbgp);

    const uint8_t threads = readWithCheck<uint8_t>(data, "multithread", 1);
    const bool createDirs = readWithCheck<bool>(data["OutputParameters"],
                                                "create_id_directories", false);

    if (dbgp->getGenerationType() == DotToGraph) {

      std::string folderPath =
          readWithCheck<std::string>(data["DotToGraph"], "dotpath", "", true);

      for (const auto &entry: std::filesystem::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".dot") {
          auto start = std::chrono::high_resolution_clock::now();

          data["DotToGraph"]["dotpath"] = entry.path().string();
          delete dbgp;
          dbgp = setGenerationParameters(data);
          DataBaseGenerator generator(*dbgp);
          i_callable(generator, *dbgp, threads, createDirs);
          auto stop = std::chrono::high_resolution_clock::now();
          auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
              stop - start);
          std::clog << "Processed file: " << entry.path()
                    << " | Time: " << duration.count() << " microseconds\n";
        }
      }
    } else {
      auto start = high_resolution_clock::now();

      i_callable(generator, *dbgp, threads, createDirs);

      auto stop = high_resolution_clock::now();
      auto duration = duration_cast<microseconds>(stop - start);
      std::clog << "Time taken: " << duration.count() << " microseconds"
                << std::endl;
    }
    delete dbgp;
  }
}

namespace CircuitGenGenerator {

std::vector<ResultGraph> runGenerationFromJsonForGraph(std::string json_path) {
  std::vector<ResultGraph> finalRes;

  auto runGeneratorForGraph =
      [&finalRes](DataBaseGenerator &generator,
                  const DataBaseGeneratorParameters &dbgp, uint8_t multithread,
                  bool create_id_directories) {
        finalRes.push_back(generator.generateTypeForGraph(
            dbgp, multithread, create_id_directories));
      };

  runGeneration(json_path, runGeneratorForGraph);
  return finalRes;
}

std::vector<ResultPath> runGenerationFromJsonForPath(std::string json_path) {
  std::vector<ResultPath> finalRes;

  auto runGeneratorForGraph =
      [&finalRes](DataBaseGenerator &generator,
                  const DataBaseGeneratorParameters &dbgp, uint8_t multithread,
                  bool create_id_directories) {
        finalRes.push_back(generator.generateTypeForPath(
            dbgp, multithread, create_id_directories));
      };

  runGeneration(json_path, runGeneratorForGraph);

  return finalRes;
}

void runGenerationFromJson(std::string json_path) {
  auto runGeneratorForGraph =
      [](DataBaseGenerator &generator, const DataBaseGeneratorParameters &dbgp,
         uint8_t multithread, bool create_id_directories) {
        generator.generateTypeDefault(dbgp, multithread, create_id_directories);
      };

  runGeneration(json_path, runGeneratorForGraph);
}
} // namespace CircuitGenGenerator
