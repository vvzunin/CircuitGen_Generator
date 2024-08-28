#include <algorithm>
#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <additional/AuxiliaryMethods.hpp>
#include <database/DataBaseGenerator.hpp>
#include <database/DataBaseGeneratorParameters.hpp>
#include <generators/GenerationParameters.hpp>
#include <getopt.h>
#include <nlohmann/json.hpp>
#include <settings/Settings.hpp>
#include <unistd.h>

#include "CircuitGenGenerator/export.hpp"

using namespace std::chrono;

bool check(const nlohmann::json &i_data, const std::string& i_param, bool isExit = true) {
  if (!i_data.contains(i_param)) {
    std::cerr << "JSON file doesn't contains " + i_param + "!" << std::endl;
    if (isExit)
      std::exit(1);
    return false;
  }
  return true;
}

template<typename Type>
Type readWithCheck(const nlohmann::json &i_data, const std::string& i_param, Type i_default, bool isExit = false) {
  if (!i_data.contains(i_param)) {
    std::cerr << "JSON file doesn't contains " + i_param + "!" << std::endl;
    if (isExit)
      std::exit(1);
    return i_default;
  } else {
    return static_cast<Type>(i_data[i_param]);
  }
}

/// @brief Method for setting main output settings.
/// @param data Parsed json fields for one generation type.
/// @param gp Base GenerationParameters as a result of method.
void setOutputParameters(const nlohmann::json &data, GenerationParameters *gp) {
  bool isExit = false;
  if (readWithCheck<bool>(data["OutputParameters"], "create_id_directories", false))
    isExit = true;
  std::string datasetId    = readWithCheck<std::string>(data["OutputParameters"], "dataset_id", "0", isExit);
  int requestIdINT = readWithCheck<int>(data["OutputParameters"], "id", 0, isExit);
  std::string requestId    = std::to_string(requestIdINT);
  
  // for GraphML
  bool makeGraphML = readWithCheck<bool>(data["OutputParameters"], "make_graphml", false);

  // Recording of json data to gp
  gp = new GenerationParameters(
      datasetId,
      requestId,
      makeGraphML
  );
}

void setFromTruthTable(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "FromRandomTruthTable";
  // Основные параметры для From Random Truth Table
  check(data, name);
  bool cnff = readWithCheck<bool>(data[name], "CNFF", false);
  bool cnft = readWithCheck<bool>(data[name], "CNFT", false);
  bool zhegalkin = readWithCheck<bool>(data[name], "Zhegalkin", false);
  if (!(cnff || cnft || zhegalkin)) {
    std::cerr << "Parameters for selected generation type is not set."
              << std::endl;
    exit(1);
  }
  gp->setCNFF(cnff);
  gp->setCNFT(cnft);
  gp->setZhegalkin(zhegalkin);  
}

void setRandLevel(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "RandLevel";
  check(data, name);
  gp->setRandLevelParameters(
    readWithCheck<int>(data[name], "min_level", 1),
    readWithCheck<int>(data[name], "max_level", 1),
    readWithCheck<int>(data[name], "min_elem", 1),
    readWithCheck<int>(data[name], "max_elem", 1));
}

void setRandLevelExperimental(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "RandLevelExperimental";
  check(data, name);
  gp->setRandLevelParameters(
    readWithCheck<int>(data[name], "min_level", 1),
    readWithCheck<int>(data[name], "max_level", 1),
    readWithCheck<int>(data[name], "min_elem", 1),
    readWithCheck<int>(data[name], "max_elem", 1));
}

void setNumOperation(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "NumOperation";
  check(data, name);

  std::vector<std::string> v = {
      "num_and",
      "num_nand",
      "num_or",
      "num_not",
      "num_nor",
      "num_buf",
      "num_xor",
      "num_xnor"
  };

  std::map<std::string, Gates> stringToGate = {
      {"and", Gates::GateAnd},
      {"nand", Gates::GateNand},
      {"or", Gates::GateOr},
      {"nor", Gates::GateNor},
      {"not", Gates::GateNot},
      {"buf", Gates::GateBuf},
      {"xor", Gates::GateXor},
      {"xnor", Gates::GateXnor}
  };

  std::map<Gates, int> m;

  for (auto& el : data[name].items()) {
    if (std::find(v.begin(), v.end(), el.key()) != v.end()) {
      m.insert({stringToGate[el.key().substr(4, 10)], el.value()});
    }
  }

  bool LeaveEmptyOut = readWithCheck<bool>(data[name], "leave_empty_out", false);
  gp->setNumOperationParameters(m, LeaveEmptyOut);
}

void setGenetic(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "Genetic";
  check(data, name);

  int numOfSurv = readWithCheck<int>(data[name], "surv_num", 1);

  // MutationTypes mType;
  // if (data.contains("mut_type"))
  // {
  //   std::string mutType = data["mut_type"];

  //   if (mutType == "Binary")
  //     mType = MutationTypes::Binary;
  //   else if (mutType == "Density")
  //     mType = MutationTypes::Density;
  //   else if (mutType == "AccessionDel")
  //     mType = MutationTypes::AccessionDel;
  //   else if (mutType == "InsertDel")
  //     mType = MutationTypes::InsertDel;
  //   else if (mutType == "Exchange")
  //     mType = MutationTypes::Exchange;
  //   else if (mutType == "Delete")
  //     mType = MutationTypes::Delete;
  //   else
  //   {
  //     std::cerr << "Unsupported mutType." << std::endl;
  //     return;
  //   }
  // }
  // else
  // {
  //   std::cerr << "Parameters for mutType is not set." << std::endl;
  //   return;
  // }

  // double mutChance = 0.5;
  // if (data.contains("mut_chance"))
  //   mutChance = data["mut_chance"];
  // else
  //   std::clog << "Parameter mutChance is not set." << std::endl;

  // int exchangeType = 0;
  // if (data.contains("swap_type"))
  //   exchangeType = data["swap_type"];
  // else
  //   std::clog << "Parameter swap_type is not set." << std::endl;

  // double outRatio = 1.0;
  // if (data.contains("out_ratio"))
  //   outRatio = data["out_ratio"];
  // else
  //   std::clog << "Parameter out_ratio is not set." << std::endl;

  // double probabilityTruthTable = 1.0;
  // if (data.contains("ratio_in_table"))
  //   probabilityTruthTable = data["ratio_in_table"];
  // else
  //   std::clog << "Parameter ratio_in_table is not set." << std::endl;

  // int recNum = 1;
  // if (data.contains("rec_num"))
  //   recNum = data["rec_num"];
  // else
  //   std::clog << "Parameter rec_num is not set." << std::endl;

  // int refPoints = 1;
  // if (data.contains("ref_points"))
  //   refPoints = data["ref_points"];
  // else
  //   std::clog << "Parameter ref_points is not set." << std::endl;

  // int tourSize = 1;
  // if (data.contains("tour_size"))
  //   tourSize = data["tour_size"];
  // else
  //   std::clog << "Parameter tour_size is not set." << std::endl;

  // std::string selectionTypeParent = data["selection_type_parent"];
  // ParentsTypes selecTypeParent;
  // if (selectionTypeParent == "Panmixia")
  //   selecTypeParent = ParentsTypes::Panmixia;
  // else if (selectionTypeParent == "Inbringing")
  //   selecTypeParent = ParentsTypes::Inbringing;
  // else if (selectionTypeParent == "Outbrinding")
  //   selecTypeParent = ParentsTypes::Outbrinding;
  // else if (selectionTypeParent == "Tournament")
  //   selecTypeParent = ParentsTypes::Tournament;
  // else if (selectionTypeParent == "Roulette")
  //   selecTypeParent = ParentsTypes::Roulette;
  // else
  // {
  //   std::cerr << "Unsupported selectionTypeParent." << std::endl;
  //   return;
  // }

  // std::string recombinationType = data["playback_type"];
  // RecombinationTypes recombType;
  // if (recombinationType == "CrossingEachExitInTurnMany")
  //   recombType = RecombinationTypes::CrossingEachExitInTurnMany;
  // else if (recombinationType == "CrossingUniform")
  //   recombType = RecombinationTypes::CrossingUniform;
  // else if (recombinationType == "CrossingTriadic")
  //   recombType = RecombinationTypes::CrossingTriadic;
  // else if (recombinationType == "CrossingReducedReplacement")
  //   recombType = RecombinationTypes::CrossingReducedReplacement;
  // else if (recombinationType == "CrossingShuffling")
  //   recombType = RecombinationTypes::CrossingShuffling;
  // else
  // {
  //   std::cerr << "Unsupported recombinationType." << std::endl;
  //   return;
  // }

  // double maskProb = 1.0;
  // if (data.contains("mask_prob"))
  //   maskProb = data["mask_prob"];
  // else
  //   std::clog << "Parameter mask_prob is not set." << std::endl;

  // int populationSize = 1;
  // if (data.contains("population_size"))
  //   populationSize = data["population_size"];
  // else
  //   std::clog << "Parameter population_size is not set." << std::endl;

  // int numOfCycles = 1;
  // if (data.contains("cycles"))
  //   numOfCycles = data["cycles"];
  // else
  //   std::clog << "Parameter cycles is not set." << std::endl;

  // std::string selectionType = data["selection_type"];
  // SelectionTypes selType;
  // if (selectionType == "Base")
  //   selType = SelectionTypes::Base;

  // int survNum = data["surv_num"];

  // gp.setPopulationSize(populationSize);
  // gp.setNumOfCycles(numOfCycles);
  // gp.setRecombinationParameters(selecTypeParent, tourSize, recombType,
  // refPoints, maskProb, recNum);
  // gp.setMutationParameters(mType, mutChance, exchangeType, probabilityTruthTable);
  // gp.setSelectionParameters(selType, survNum);
  // gp.setKeyEndProcessIndex(outRatio);
  // gp.setGeneticParameters(numOfSurv, mutType, mutChance, swapType,
  // ratioInTable, recNum, refPoints, tourSize, selectionTypeParent);
}

void setSummator(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "Summator";
  check(data, name);

  gp->setSummatorParameters(
    readWithCheck<bool>(data[name], "overflowIn", false),
    readWithCheck<bool>(data[name], "overflowOut", false),
    readWithCheck<bool>(data[name], "minus", false)
  );
}

void setSubtractor(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "Subtractor";
  check(data, name);

  gp->setSubtractorParameters(
    readWithCheck<bool>(data[name], "overflowIn", false),
    readWithCheck<bool>(data[name], "overflowOut", false),
    readWithCheck<bool>(data[name], "sub", false)
  );
}

void setComparison(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "Comparison";
  check(data, name);

  gp->setComparisonParameters(
    readWithCheck<bool>(data[name], "=", false),
    readWithCheck<bool>(data[name], "<", false),
    readWithCheck<bool>(data[name], ">", false)
  );
}

void setEncoder(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "Encoder";
  check(data, name, false);
}

void setDecoder(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "Decoder";
  check(data, name, false);
}

void setMultiplexer(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "Multiplexer";
  check(data, name, false);
}

void setDemultiplexer(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "Demultiplexer";
  check(data, name, false);
}

void setMultiplier(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "Multiplier";
  check(data, name, false);
}

void setParity(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "Parity";
  check(data, name, false);
}

void setALU(const nlohmann::json &data, GenerationParameters *gp) {
  std::string name = "ALU";
  check(data, name);

  std::vector<std::string> v = {
      "num_and",
      "num_nand",
      "num_or",
      "num_not",
      "num_nor",
      "num_buf",
      "num_xor",
      "num_xnor"
  };

  std::map<std::string, Gates> stringToGate = {
      {"and", Gates::GateAnd},
      {"nand", Gates::GateNand},
      {"or", Gates::GateOr},
      {"nor", Gates::GateNor},
      {"not", Gates::GateNot},
      {"buf", Gates::GateBuf},
      {"xor", Gates::GateXor},
      {"xnor", Gates::GateXnor}
  };

  std::map<Gates, int> m;

  for (auto& el : data[name].items()) {
    if (std::find(v.begin(), v.end(), el.key()) != v.end()) {
      m.insert({stringToGate[el.key().substr(4, 10)], el.value()});
    }
  }

  gp->setALUParameters(
    readWithCheck<bool>(data[name], "ALL", false),
    readWithCheck<bool>(data[name], "SUM", false),
    readWithCheck<bool>(data[name], "SUB", false),
    readWithCheck<bool>(data[name], "NSUM", false),
    readWithCheck<bool>(data[name], "NSUB", false),
    readWithCheck<bool>(data[name], "MULT", false),
    readWithCheck<bool>(data[name], "COM", false),
    readWithCheck<bool>(data[name], "AND", false),
    readWithCheck<bool>(data[name], "NAND", false),
    readWithCheck<bool>(data[name], "OR", false),
    readWithCheck<bool>(data[name], "NOR", false),
    readWithCheck<bool>(data[name], "XOR", false),
    readWithCheck<bool>(data[name], "XNOR", false),
    readWithCheck<bool>(data[name], "CNF", false),
    readWithCheck<bool>(data[name], "RNL", false),
    readWithCheck<bool>(data[name], "NUM_OP", false),
    readWithCheck<int>(data[name], "minLevel", false),
    readWithCheck<int>(data[name], "maxLevel", false),
    readWithCheck<int>(data[name], "minElement", false),
    readWithCheck<int>(data[name], "maxElement", false),
    m,
    readWithCheck<bool>(data[name], "LeaveEmptyOut", false)
  );
}

/// @brief Method for setting main generation parameters.
/// @param data Parsed json fields for one generation type.
/// @return DataBaseGeneratorParameters pointer
DataBaseGeneratorParameters* setGenerationParameters(const nlohmann::json &data) {

  check(data, "GenerationParameters");
  // Setting Randomization seed.
  int seed = readWithCheck<int>(data["GenerationParameters"], "seed", -1);
  AuxMethods::setRandSeed(
    seed == -1
    ? static_cast<unsigned>(std::time(0))
    : static_cast<unsigned>(seed)
  );

  int         minInputs    = readWithCheck<int>(data["GenerationParameters"], "min_in", 1);
  int         maxInputs    = readWithCheck<int>(data["GenerationParameters"], "max_in", 1);
  int         minOutputs   = readWithCheck<int>(data["GenerationParameters"], "min_out", 1);
  int         maxOutputs   = readWithCheck<int>(data["GenerationParameters"], "max_out", 1);
  int         repeats      = readWithCheck<int>(data["GenerationParameters"], "repeat_n", 1);

  // Считывание информации по логичсеким элементам.
  std::map<std::string, std::vector<int>> gatesInputsInfo;

  if (check(data["GenerationParameters"], "gates_inputs_info")) {
    for (auto gate : data["GenerationParameters"]["gates_inputs_info"].items()) {
      std::vector<int> gatesNumber =
          static_cast<std::vector<int>>(gate.value());

      // sorting data. It's important for fast generator work
      if (gatesNumber.size()) {
        std::sort(gatesNumber.begin(), gatesNumber.end());

        gatesInputsInfo[gate.key()] = gatesNumber;
      }
    }
  }
  // if gates_inputs_info in json was empty or there was no such data in json
  if (!gatesInputsInfo.size()) {
    // default init data
    gatesInputsInfo["and"]  = {2};
    gatesInputsInfo["nand"] = {2};
    gatesInputsInfo["or"]   = {2};
    gatesInputsInfo["nor"]  = {2};
    gatesInputsInfo["xor"]  = {2};
    gatesInputsInfo["xnor"] = {2};
  }

  GenerationParameters *gp;
  setOutputParameters(data, gp);

  // Setting generation type.
  GenerationTypes gt;
  std::string s = readWithCheck<std::string>(data["GenerationParameters"], "type_of_generation", "", true);
  if (s == "From Random Truth Table") {
    gt = GenerationTypes::FromRandomTruthTable;
    setFromTruthTable(data, gp);
  }
  if (s == "Rand Level") {
    gt = GenerationTypes::RandLevel;
    setRandLevel(data, gp);
  } else if (s == "Rand Level Experimental") {
    gt = GenerationTypes::RandLevelExperimental;
    setRandLevelExperimental(data, gp);
  } else if (s == "Num Operation") {
    gt = GenerationTypes::NumOperation;
    setNumOperation(data, gp);
  } else if (s == "Genetic") {
    gt = GenerationTypes::Genetic;
    setGenetic(data, gp);
  } else if (s == "Summator") {
    gt = GenerationTypes::Summator;
    setSummator(data, gp);
  } else if (s == "Subtractor") {
    gt = GenerationTypes::Subtractor;
    setSubtractor(data, gp);
  } else if (s == "Comparison") {
    gt = GenerationTypes::Comparison;
    setComparison(data, gp);
  } else if (s == "Encoder") {
    gt = GenerationTypes::Encoder;
    setEncoder(data, gp);
  } else if (s == "Decoder") {
    gt = GenerationTypes::Decoder;
    setDecoder(data, gp);
  } else if (s == "Multiplexer") {
    gt = GenerationTypes::Multiplexer;
    setMultiplexer(data, gp);
  } else if (s == "Demultiplexer") {
    gt = GenerationTypes::Demultiplexer;
    setDemultiplexer(data, gp);
  } else if (s == "Multiplier") {
    gt = GenerationTypes::Multiplier;
    setMultiplier(data, gp);
  } else if (s == "Parity") {
    gt = GenerationTypes::Parity;
    setParity(data, gp);
  } else if (s == "ALU") {
    gt = GenerationTypes::ALU;
    setALU(data, gp);
  } else {
    std::cerr << "Unsupported generation type" << std::endl;
    exit(1);
  }

  gp->setGatesInputInfo(gatesInputsInfo);

  DataBaseGeneratorParameters* dbgp = new DataBaseGeneratorParameters(minInputs, maxInputs, minOutputs,
                                     maxOutputs, repeats, gt, *gp);
  return dbgp;
}

void runGeneration(
    std::string json_path,
    std::function<void(
        DataBaseGenerator&,
        DataBaseGeneratorParameters&,
        uint8_t,
        bool
    )>          callable
) {
  std::ifstream  f(json_path);
  nlohmann::json DATA = nlohmann::json::parse(f);
  // Read all json objects in json file.

  for (auto it = DATA.begin(); it != DATA.end(); it++) {
    nlohmann::json data = *it;

    
    DataBaseGeneratorParameters* dbgp = setGenerationParameters(data);
    DataBaseGenerator generator;

    if (check(data, "dataset_path", false)) {
      Settings::getInstance("CircuitGenGenerator")
          ->setDatasetPath(readWithCheck<std::string>(data, "dataset_path", "dataset"));
    }

    auto    start = high_resolution_clock::now();
    
    // Запускаем генерацию с учетом многопоточности и создания поддерикторий
    callable(
        generator,
        *dbgp,
        readWithCheck<uint8_t>(data, "multithread", 1),
        readWithCheck<bool>(data["OutputParameters"], "create_id_directories", true)
    );

    auto stop     = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::clog << "Time taken: " << duration.count() << " microseconds"
              << std::endl;
  }
}

namespace CircuitGenGenerator {
std::vector<ResultGraph> runGenerationFromJsonForGraph(std::string json_path) {
  std::vector<ResultGraph> finalRes;

  auto                     runGeneratorForGraph = [&finalRes](
                                  DataBaseGenerator&                 generator,
                                  DataBaseGeneratorParameters& dbgp,
                                  uint8_t multithread,
                                  bool    create_id_directories
                              ) {
    finalRes.push_back(
        generator.generateTypeForGraph(dbgp, multithread, create_id_directories)
    );
  };

  runGeneration(json_path, runGeneratorForGraph);
  return finalRes;
}

std::vector<ResultPath> runGenerationFromJsonForPath(std::string json_path) {
  std::vector<ResultPath> finalRes;

  auto                    runGeneratorForGraph = [&finalRes](
                                  DataBaseGenerator&                 generator,
                                  DataBaseGeneratorParameters& dbgp,
                                  uint8_t multithread,
                                  bool    create_id_directories
                              ) {
    finalRes.push_back(
        generator.generateTypeForPath(dbgp, multithread, create_id_directories)
    );
  };

  runGeneration(json_path, runGeneratorForGraph);

  return finalRes;
}

void runGenerationFromJson(std::string json_path) {
  auto runGeneratorForGraph = [](DataBaseGenerator&                 generator,
                                 DataBaseGeneratorParameters& dbgp,
                                 uint8_t                            multithread,
                                 bool create_id_directories) {
    generator.generateTypeDefault(dbgp, multithread, create_id_directories);
  };

  runGeneration(json_path, runGeneratorForGraph);
}
}  // namespace CircuitGenGenerator