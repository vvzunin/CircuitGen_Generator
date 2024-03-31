#include "generatorAPI.h"

#include <additional/AuxiliaryMethods.h>
#include <database/DataBaseGenerator.h>
#include <database/DataBaseGeneratorParameters.h>
#include <generators/GenerationParameters.h>
#include <getopt.h>
#include <settings/Settings.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

using namespace std::chrono;

void runGenerationFromJson(std::string json_path) {
  std::ifstream f(json_path);
  nlohmann::json DATA = nlohmann::json::parse(f);
  // Read all json objects in json file.
  for (auto it = DATA.begin(); it != DATA.end(); it++) {
    nlohmann::json data = *it;

    // Проверка на наличие типа генерации. Если его нет, то завершаем программу.
    if (!data.contains("type_of_generation")) {
      std::cerr << "No generation type!" << std::endl;
      return;
    }

    // Задаем сид рандомизации.
    AuxMethods::setRandSeed(!data.contains("seed") || data["seed"] == -1
                                ? static_cast<unsigned>(std::time(0))
                                : static_cast<unsigned>(data["seed"]));

    // Задаем основные параметры генерации
    GenerationTypes gt;
    if (data["type_of_generation"] == "From Random Truth Table")
      gt = GenerationTypes::FromRandomTruthTable;
    else if (data["type_of_generation"] == "Rand Level")
      gt = GenerationTypes::RandLevel;
    else if (data["type_of_generation"] == "Rand Level Experimental")
      gt = GenerationTypes::RandLevelExperimental;
    else if (data["type_of_generation"] == "Num Operation")
      gt = GenerationTypes::NumOperation;
    else if (data["type_of_generation"] == "Summator")
      gt = GenerationTypes::Summator;
    else if (data["type_of_generation"] == "Comparison")
      gt = GenerationTypes::Comparison;  
    else if (data["type_of_generation"] == "Subtractor")
      gt = GenerationTypes::Subtractor;
    else if (data["type_of_generation"] == "Demultiplexer")
      gt = GenerationTypes::Demultiplexer;
    // else if (data["type_of_generation"] == "Genetic")
    //   gt = GenerationTypes::Genetic;
    else {
      std::cerr << "Unsupported generation type" << std::endl;
      return;
    }

    std::string datasetId = data.contains("dataset_id")
                                ? static_cast<std::string>(data["dataset_id"])
                                : "0";

    int requestIdINT = data.contains("id") ? (int)data["id"] : 0;

    std::string requestId = std::to_string(requestIdINT);

    int minInputs = 1;
    int maxInputs = 1;
    int minOutputs = 1;
    int maxOutputs = 1;
    int repeats = 1;

    if (data.contains("min_in")) {
      minInputs = data["min_in"];
    } else {
      std::clog << "min_in is not in json" << std::endl;
    }
    if (data.contains("max_in")) {
      maxInputs = data["max_in"];
    } else {
      std::clog << "max_in is not in json" << std::endl;
    }
    if (data.contains("min_out")) {
      minOutputs = data["min_out"];
    } else {
      std::clog << "min_out is not in json" << std::endl;
    }
    if (data.contains("max_out")) {
      maxOutputs = data["max_out"];
    } else {
      std::clog << "max_out is not in json" << std::endl;
    }
    if (data.contains("repeat_n")) {
      repeats = data["repeat_n"];
    } else {
      std::clog << "repeat_n is not in json" << std::endl;
    }

    // this is for ABC
    bool calculateStatsAbc = data.contains("calculate_stats_abc")
                                 ? (bool)data["calculate_stats_abc"]
                                 : false;
    bool makeOptimizedFiles = data.contains("make_optimized_files")
                                  ? (bool)data["make_optimized_files"]
                                  : false;
    std::string libraryName =
        data.contains("library_name") ? (std::string)data["library_name"] : "";
    bool makeBench =
        data.contains("make_bench") ? (bool)data["make_bench"] : false;

    // and this is for Yosys
    bool makeFirrtl =
        data.contains("make_firrtl") ? (bool)data["make_firrtl"] : false;

    // Считывание информации по логичсеким элементам.
    std::map<std::string, std::vector<int>> gatesInputsInfo;

    if (data.contains("gates_inputs_info")) {
      for (auto gate : data["gates_inputs_info"].items()) {
        std::vector<int> gatesNumber =
            static_cast<std::vector<int>>(gate.value());

        // if vector is empty (suddenly), we add default gates number
        if (!(int)gatesNumber.size()) gatesNumber.push_back(2);
        // else sorting data. It's important for fast generator work
        else
          std::sort(gatesNumber.begin(), gatesNumber.end());

        gatesInputsInfo[gate.key()] = gatesNumber;
      }
    } else {
      // default init data
      gatesInputsInfo["and"] = {2};
      gatesInputsInfo["nand"] = {2};
      gatesInputsInfo["or"] = {2};
      gatesInputsInfo["nor"] = {2};
      gatesInputsInfo["xor"] = {2};
      gatesInputsInfo["xnor"] = {2};
    }

    // TODO:: make function that return DataBaseGeneratorParameters from json
    // Recording of json data to gp
    GenerationParameters gp(datasetId, requestId, minInputs, minOutputs,
                            repeats, libraryName, calculateStatsAbc,
                            makeOptimizedFiles, makeFirrtl, makeBench);

    gp.setGatesInputInfo(gatesInputsInfo);
    // ------------------------------------------------------------------------

    // Основные параметры для From Random Truth Table
    if (data["type_of_generation"] == "From Random Truth Table") {
      if (!(data.contains("CNFF") || data.contains("CNFT"))) {
        std::cerr << "Parameters for selected generation type is not set."
                  << std::endl;
        return;
      }
      gp.setCNFF(data.contains("CNFF") ? (bool)data["CNFF"] : false);
      gp.setCNFT(data.contains("CNFT") ? (bool)data["CNFT"] : false);
    }

    // Основные параметры для Rand Level
    if (static_cast<std::string>(data["type_of_generation"])
            .find("Rand Level") != std::string::npos) {
      if (!(data.contains("max_level") || data.contains("max_elem")))
        std::clog << "Parameters for selected generation type is not set. "
                     "Parameters sets to default."
                  << std::endl;

      int minLevel = data.contains("min_level") ? (int)data["min_level"] : 0;
      int maxLevel = data.contains("max_level") ? (int)data["max_level"] : 0;
      int minElement = data.contains("min_elem") ? (int)data["min_elem"] : 0;
      int maxElement = data.contains("max_elem") ? (int)data["max_elem"] : 0;
      gp.setRandLevelParameters(minLevel, maxLevel, minElement, maxElement);
    }

    // Основные параметры для Num Operation
    if (data["type_of_generation"] == "Num Operation") {
      std::vector<std::string> v = {"num_and", "num_nand", "num_or",
                                    "num_not", "num_nor",  "num_buf",
                                    "num_xor", "num_xnor"};

      std::map<std::string, Gates> stringToGate = {
          {"and", Gates::GateAnd}, {"nand", Gates::GateNand},
          {"or", Gates::GateOr},   {"nor", Gates::GateNor},
          {"not", Gates::GateNot}, {"buf", Gates::GateBuf},
          {"xor", Gates::GateXor}, {"xnor", Gates::GateXnor}};

      std::map<Gates, int> m;

      for (auto &el : data.items()) {
        if (std::find(v.begin(), v.end(), el.key()) != v.end()) {
          m.insert({stringToGate[el.key().substr(4, 10)], el.value()});
        }
      }

      bool LeaveEmptyOut = false;
      if (data.contains("leave_empty_out"))
        LeaveEmptyOut = data["leave_empty_out"];
      else
        std::clog << "LeaveEmptyOut is not set." << std::endl;

      gp.setNumOperationParameters(m, LeaveEmptyOut);
    }



    if (static_cast<std::string>(data["type_of_generation"])
                  .find("Subtractor") != std::string::npos) {
        if (!(data.contains("overflowIn") || data.contains("overflowOut") || data.contains("sub")))
            std::clog << "Parameters for selected generation type is not set. "
                           "Parameters sets to default."<< std::endl;

        bool overflowIn = data.contains("overflowIn") ? (bool)data["overflowIn"] : false;
        bool overflowOut = data.contains("overflowOut") ? (bool)data["overflowOut"] : false;
        bool sub = data.contains("sub") ? (bool)data["sub"] : false;
        gp.setSubtractorParameters(overflowIn, overflowOut, sub);
    }

    if (static_cast<std::string>(data["type_of_generation"])
                  .find("Summator") != std::string::npos) {
        if (!(data.contains("overflowIn") || data.contains("overflowOut") || data.contains("minus")))
            std::clog << "Parameters for selected generation type is not set. "
                           "Parameters sets to default."<< std::endl;

        bool overflowIn = data.contains("overflowIn") ? (bool)data["overflowIn"] : false;
        bool overflowOut = data.contains("overflowOut") ? (bool)data["overflowOut"] : false;
        bool minus = data.contains("minus") ? (bool)data["minus"] : false;
        gp.setSummatorParameters(overflowIn, overflowOut, minus);
    }

    if (static_cast<std::string>(data["type_of_generation"])
                  .find("Comparison") != std::string::npos) {
        if (!(data.contains("=") || data.contains("<") || data.contains(">")))
            std::clog << "Parameters for selected generation type is not set. "
                           "Parameters sets to default."<< std::endl;

        bool compare0 = data.contains("=") ? (bool)data["="] : false;
        bool compare1 = data.contains("<") ? (bool)data["<"] : false;
        bool compare2 = data.contains(">") ? (bool)data[">"] : false;
        gp.setComparisonParameters(compare0, compare1, compare2);
    }
    // Основные параметры для Genetic
    // if (data["type_of_generation"] == "Genetic")
    // {

    //   int numOfSurv = 1;
    //   if (data.contains("surv_num"))
    //     int numOfSurv = data["surv_num"];
    //   else
    //     std::clog << "Parameter surv_num is not set." << std::endl;

    //   MutationTypes mType;
    //   if (data.contains("mut_type"))
    //   {
    //     std::string mutType = data["mut_type"];

    //     if (mutType == "Binary")
    //       mType = MutationTypes::Binary;
    //     else if (mutType == "Density")
    //       mType = MutationTypes::Density;
    //     else if (mutType == "AccessionDel")
    //       mType = MutationTypes::AccessionDel;
    //     else if (mutType == "InsertDel")
    //       mType = MutationTypes::InsertDel;
    //     else if (mutType == "Exchange")
    //       mType = MutationTypes::Exchange;
    //     else if (mutType == "Delete")
    //       mType = MutationTypes::Delete;
    //     else
    //     {
    //       std::cerr << "Unsupported mutType." << std::endl;
    //       return;
    //     }
    //   }
    //   else
    //   {
    //     std::cerr << "Parameters for mutType is not set." << std::endl;
    //     return;
    //   }

    //   double mutChance = 0.5;
    //   if (data.contains("mut_chance"))
    //     mutChance = data["mut_chance"];
    //   else
    //     std::clog << "Parameter mutChance is not set." << std::endl;

    //   int exchangeType = 0;
    //   if (data.contains("swap_type"))
    //     exchangeType = data["swap_type"];
    //   else
    //     std::clog << "Parameter swap_type is not set." << std::endl;

    //   double outRatio = 1.0;
    //   if (data.contains("out_ratio"))
    //     outRatio = data["out_ratio"];
    //   else
    //     std::clog << "Parameter out_ratio is not set." << std::endl;

    //   double probabilityTruthTable = 1.0;
    //   if (data.contains("ratio_in_table"))
    //     probabilityTruthTable = data["ratio_in_table"];
    //   else
    //     std::clog << "Parameter ratio_in_table is not set." << std::endl;

    //   int recNum = 1;
    //   if (data.contains("rec_num"))
    //     recNum = data["rec_num"];
    //   else
    //     std::clog << "Parameter rec_num is not set." << std::endl;

    //   int refPoints = 1;
    //   if (data.contains("ref_points"))
    //     refPoints = data["ref_points"];
    //   else
    //     std::clog << "Parameter ref_points is not set." << std::endl;

    //   int tourSize = 1;
    //   if (data.contains("tour_size"))
    //     tourSize = data["tour_size"];
    //   else
    //     std::clog << "Parameter tour_size is not set." << std::endl;

    //   std::string selectionTypeParent = data["selection_type_parent"];
    //   ParentsTypes selecTypeParent;
    //   if (selectionTypeParent == "Panmixia")
    //     selecTypeParent = ParentsTypes::Panmixia;
    //   else if (selectionTypeParent == "Inbringing")
    //     selecTypeParent = ParentsTypes::Inbringing;
    //   else if (selectionTypeParent == "Outbrinding")
    //     selecTypeParent = ParentsTypes::Outbrinding;
    //   else if (selectionTypeParent == "Tournament")
    //     selecTypeParent = ParentsTypes::Tournament;
    //   else if (selectionTypeParent == "Roulette")
    //     selecTypeParent = ParentsTypes::Roulette;
    //   else
    //   {
    //     std::cerr << "Unsupported selectionTypeParent." << std::endl;
    //     return;
    //   }

    //   std::string recombinationType = data["playback_type"];
    //   RecombinationTypes recombType;
    //   if (recombinationType == "CrossingEachExitInTurnMany")
    //     recombType = RecombinationTypes::CrossingEachExitInTurnMany;
    //   else if (recombinationType == "CrossingUniform")
    //     recombType = RecombinationTypes::CrossingUniform;
    //   else if (recombinationType == "CrossingTriadic")
    //     recombType = RecombinationTypes::CrossingTriadic;
    //   else if (recombinationType == "CrossingReducedReplacement")
    //     recombType = RecombinationTypes::CrossingReducedReplacement;
    //   else if (recombinationType == "CrossingShuffling")
    //     recombType = RecombinationTypes::CrossingShuffling;
    //   else
    //   {
    //     std::cerr << "Unsupported recombinationType." << std::endl;
    //     return;
    //   }

    //   double maskProb = 1.0;
    //   if (data.contains("mask_prob"))
    //     maskProb = data["mask_prob"];
    //   else
    //     std::clog << "Parameter mask_prob is not set." << std::endl;

    //   int populationSize = 1;
    //   if (data.contains("population_size"))
    //     populationSize = data["population_size"];
    //   else
    //     std::clog << "Parameter population_size is not set." << std::endl;

    //   int numOfCycles = 1;
    //   if (data.contains("cycles"))
    //     numOfCycles = data["cycles"];
    //   else
    //     std::clog << "Parameter cycles is not set." << std::endl;

    //   std::string selectionType = data["selection_type"];
    //   SelectionTypes selType;
    //   if (selectionType == "Base")
    //     selType = SelectionTypes::Base;

    //   int survNum = data["surv_num"];

    //   gp.setPopulationSize(populationSize);
    //   gp.setNumOfCycles(numOfCycles);
    //   gp.setRecombinationParameters(selecTypeParent, tourSize, recombType,
    //   refPoints, maskProb, recNum); gp.setMutationParameters(mType,
    //   mutChance, exchangeType, probabilityTruthTable);
    //   gp.setSelectionParameters(selType, survNum);
    //   gp.setKeyEndProcessIndex(outRatio);
    //   // gp.setGeneticParameters(numOfSurv, mutType, mutChance, swapType,
    //   ratioInTable, recNum, refPoints, tourSize, selectionTypeParent);
    // }

    DataBaseGeneratorParameters dbgp(minInputs, maxInputs, minOutputs,
                                     maxOutputs, repeats, gt, gp);

    DataBaseGenerator generator(dbgp);

    auto start = high_resolution_clock::now();

    // Запускаем генерацию с учетом многопоточности и создания поддерикторий
    generator.generateType(
        dbgp, data.contains("multithread") ? (bool)data["multithread"] : false,
        data.contains("create_id_directories")
            ? (bool)data["create_id_directories"]
            : true);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::clog << "Time taken: " << duration.count() << " microseconds"
              << std::endl;
  }
}