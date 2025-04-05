#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <CircuitGenGraph/OrientedGraph.hpp>

#include <additional/AuxiliaryMethods.hpp>
#include <database/DataBaseGenerator.hpp>
#include <database/DataBaseGeneratorParameters.hpp>
#include <generators/GenerationParameters.hpp>
#include <getopt.h>
#include <nlohmann/json.hpp>
#include <settings/Settings.hpp>
#include <unistd.h>

#include "generators/Genetic/Chromosome.hpp"
#include "generators/Genetic/Mutations/MutationParameters.hpp"
#include "generators/Genetic/Parents/ParentsParameters.hpp"
#include "generators/Genetic/Recombination/RecombinationParameters.hpp"
#include "generators/Genetic/Selections/SelectionParameters.hpp"

using namespace std::chrono;

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

GenerationParameters *getBasicParameters(const nlohmann::json &i_data,
                                         GenerationTypes &i_type,
                                         int &i_minInputs, int &i_maxInputs,
                                         int &i_minOutputs, int &i_maxOutputs,
                                         int &i_repeats) {
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

  // if gates_inputs_info in json was empty or there was no such data in json
  if (!gatesInputsInfo.size()) {
    // default init data
    gatesInputsInfo["and"] = {2};
    gatesInputsInfo["nand"] = {2};
    gatesInputsInfo["or"] = {2};
    gatesInputsInfo["nor"] = {2};
    gatesInputsInfo["xor"] = {2};
    gatesInputsInfo["xnor"] = {2};
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

  gp = new GenerationParameters(datasetId, requestId, i_minInputs, i_minOutputs,
                                i_repeats, makeGraphMLClassic,
                                makeGraphMLPseudo, makeGraphMLOpen, makeDot);
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

  for(const auto &[key, val]: mapping) {
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
      readEnumWithCheck<GenotypeParametersTypes>(i_data[name], "chromosome_type", GenotypeParametersType2Name);
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

DataBaseGeneratorParameters *
setGenerationParameters(const nlohmann::json &i_data) {
  GenerationTypes gt;
  int minInputs, maxInputs;
  int minOutputs, maxOutputs;
  int repeats;
  GenerationParameters *gp = getBasicParameters(
      i_data, gt, minInputs, maxInputs, minOutputs, maxOutputs, repeats);

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

    auto start = high_resolution_clock::now();

    generator.generateTypeForGraph(*dbgp, threads, createDirs);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::clog << "Time taken: " << duration.count() << " microseconds"
              << std::endl;
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