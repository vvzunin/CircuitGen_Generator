#include <map>
#include <array>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

#include <unistd.h>
#include <getopt.h>

#include "nlohmann/json.hpp"

#include <AuxiliaryMethods/AuxiliaryMethods.h>
#include <DataBase/DataBaseGenerator.h>
#include <generators/GenerationParameters.h>
#include <DataBase/DataBaseGeneratorParameters.h>

#include <generatorAPI.h>

using namespace std::chrono;

void runGenerationFromJson(std::string json_path)
{
  std::ifstream f(json_path);
  nlohmann::json DATA = nlohmann::json::parse(f);
  // Read all json objects in json file.
  for (auto it = DATA.begin(); it != DATA.end(); it++)
  {
    nlohmann::json data = *it;

    // Проверка на наличие типа генерации. Если его нет, то завершаем программу.
    if (!data.contains("type_of_generation"))
    {
      cerr << "No generation type!" << endl;
      return;
    }

    // Задаем сид рандомизации.
    AuxMethods::setRandSeed(
      !data.contains("seed") || data["seed"] == -1 ? 
      static_cast<unsigned>(std::time(0)) : 
      static_cast<unsigned>(data["seed"]));

    // Задаем основные параметры генерации
    GenerationTypes gt;
    if (data["type_of_generation"] == "From Random Truth Table")
      gt = GenerationTypes::FromRandomTruthTable;
    else if (data["type_of_generation"] == "Rand Level")
      gt = GenerationTypes::RandLevel;
    else if (data["type_of_generation"] == "Num Operation")
      gt = GenerationTypes::NumOperation;
    else if (data["type_of_generation"] == "Genetic")
      gt = GenerationTypes::Genetic;
    else {
      cerr << "Unsupported generation type" << endl;
      return;
    }

    std::string datasetId = "0";
    if (data.contains("dataset_id"))
      std::string datasetId = data["dataset_id"];

    std::string requestId = "0";
    if (data.contains("id"))
      std::string datasetId = data["id"];

    if (data.contains("min_in")) {
      int minInputs = data["min_in"];
      cout << "min_in is not in json" << endl;
    }
    if (data.contains("max_in")) {
      int minInputs = data["max_in"];
      cout << "max_in is not in json" << endl;
    }
    if (data.contains("min_out")) {
      int minInputs = data["min_out"];
      cout << "min_out is not in json" << endl;
    }
    if (data.contains("max_out")) {
      int minInputs = data["max_out"];
      cout << "max_out is not in json" << endl;
    }
    data["repeat_n"] = 1;
    if (data.contains("repeat_n")) {
      int minInputs = data["repeat_n"];
      cout << "repeat_n is not in json" << endl;
    }

    // this is for ABC
    bool calculateStatsAbc = 
      data.contains("calculate_stats_abc") ? 
      (bool)data["calculate_stats_abc"] : 
      false;
    bool makeOptimizedFiles = 
      data.contains("make_optimized_files") ? 
      (bool)data["make_optimized_files"] : 
      false;
    std::string libraryName = 
      data.contains("library_name") ? 
      (std::string)data["library_name"] : "";

    // Считывание информации по логичсеким элементам.
    std::map<std::string, std::vector<int>> gatesInputsInfo;

    if (data.contains("gates_inputs_info"))
    {
      for (auto gate : data["gates_inputs_info"].items())
      {
        std::vector<int> gatesNumber = static_cast<std::vector<int>>(gate.value());

        // if vector is empty (suddenly), we add default gates number
        if (!(int)gatesNumber.size())
          gatesNumber.push_back(2);
        gatesInputsInfo[gate.key()] = gatesNumber;
      }
    }
    else
    {
      // default init data
      gatesInputsInfo["and"] = {2};
      gatesInputsInfo["nand"] = {2};
      gatesInputsInfo["or"] = {2};
      gatesInputsInfo["nor"] = {2};
      gatesInputsInfo["xor"] = {2};
      gatesInputsInfo["xnor"] = {2};
    }
    gp.setGatesInputInfo(gatesInputsInfo);
    // ------------------------------------------------------------------------    

    // TODO:: make function that return DataBaseGeneratorParameters from json
    // Recording of json data to gp
    GenerationParameters gp(
        datasetId,
        requestId,
        minInputs,
        minOutputs,
        repeats,
        libraryName,
        calculateStatsAbc,
        makeOptimizedFiles);

    // ------------------------------------------------------------------------  


    // Основные параметры для From Random Truth Table
    if (data["type_of_generation"] == "From Random Truth Table") {
      if !((data.contains("CNFF") || data.contains("CNFT"))) {
        cerr << "Parameters for selected generation type is not set." << endl;
        return;
      }
      gp.setCNFF(data.contains("CNFF") ? data["CNFF"] : false);
      gp.setCNFT(data.contains("CNFT") ? data["CNFT"] : false);
    }
    
    // Основные параметры для Rand Level
    if (data["type_of_generation"] == "Rand Level") {
      if !((data.contains("max_level") || data.contains("max_elem")))
        cout << "Parameters for selected generation type is not set. Parameters sets to default." << endl;

      int maxLevel = data.contains("max_level") ? data["max_level"] : 0;
      int maxElement = data.contains("max_elem") ? data["max_elem"] : 0;
      gp.setRandLevelParameters(maxLevel, maxElement);
    }   

    // Основные параметры для Num Operation
    if (data["type_of_generation"] == "Num Operation") {
      std::map<std::string, int> m;
      std::vector<std::string> v =
          {"num_and", "num_nand", "num_or", "num_not",
          "num_nor", "num_buf", "num_xor", "num_xnor"};

      for (auto &el : data.items())
      {
        if (std::find(v.begin(), v.end(), el.key()) != v.end())
          m.insert({el.key().substr(4, 10), el.value()});
      }
      bool LeaveEmptyOut = false;
      if (data.contains("leave_empty_out"))
        LeaveEmptyOut = data["leave_empty_out"];
      else
        cout << "LeaveEmptyOut is not set." << endl;

      gp.setNumOperationParameters(m, LeaveEmptyOut);
    }

    // Основные параметры для Genetic
    if (data["type_of_generation"] == "Genetic") {
      
      int numOfSurv = 1;
      if (data.contains("surv_num"))
        int numOfSurv = data["surv_num"];
      else
        cout << "Parameter surv_num is not set." << endl;

      if (data.contains("mut_type")) {
        std::string mutType = data["mut_type"];
        MutationTypes mType;
        if (mutType == "Binary")
          mType = MutationTypes::Binary;
        else if (mutType == "Density")
          mType = MutationTypes::Density;
        else if (mutType == "AccessionDel")
          mType = MutationTypes::AccessionDel;
        else if (mutType == "InsertDel")
          mType = MutationTypes::InsertDel;
        else if (mutType == "Exchange")
          mType = MutationTypes::Exchange;
        else if (mutType == "Delete")
          mType = MutationTypes::Delete;
        else {
          cerr << "Unsupported mutType." << endl;
          return;
        }
      } else {
        cerr << "Parameters for mutType is not set." << endl;
        return;
      }

      double mutChance = 0.5;
      if (data.contains("mut_chance"))
        mutChance = data["mut_chance"];
      else
        cout << "Parameter mutChance is not set." << endl;
      
      int exchangeType = 0;
      if (data.contains("swap_type"))
        exchangeType = data["swap_type"];
      else
        cout << "Parameter swap_type is not set." << endl;

      double outRatio = 1.0;
      if (data.contains("out_ratio"))
        outRatio = data["out_ratio"];
      else
        cout << "Parameter out_ratio is not set." << endl;

      double probabilityTruthTable = 1.0;
      if (data.contains("ratio_in_table"))
        probabilityTruthTable = data["ratio_in_table"];
      else
        cout << "Parameter ratio_in_table is not set." << endl;
      
      int recNum = 1;
      if (data.contains("rec_num"))
        recNum = data["rec_num"];
      else
        cout << "Parameter rec_num is not set." << endl;

      int refPoints = 1;
      if (data.contains("ref_points"))
        refPoints = data["ref_points"];
      else
        cout << "Parameter ref_points is not set." << endl;

      int tourSize = 1;
      if (data.contains("tour_size"))
        tourSize = data["tour_size"];
      else
        cout << "Parameter tour_size is not set." << endl;

      std::string selectionTypeParent = data["selection_type_parent"];
      ParentsTypes selecTypeParent;
      if (selectionTypeParent == "Panmixia")
        selecTypeParent = ParentsTypes::Panmixia;
      else if (selectionTypeParent == "Inbringing")
        selecTypeParent = ParentsTypes::Inbringing;
      else if (selectionTypeParent == "Outbrinding")
        selecTypeParent = ParentsTypes::Outbrinding;
      else if (selectionTypeParent == "Tournament")
        selecTypeParent = ParentsTypes::Tournament;
      else if (selectionTypeParent == "Roulette")
        selecTypeParent = ParentsTypes::Roulette;
      else {
        cerr << "Unsupported selectionTypeParent." << endl;
        return;
      }

      std::string recombinationType = data["playback_type"];
      RecombinationTypes recombType;
      if (recombinationType == "CrossingEachExitInTurnMany")
        recombType = RecombinationTypes::CrossingEachExitInTurnMany;
      else if (recombinationType == "CrossingUniform")
        recombType = RecombinationTypes::CrossingUniform;
      else if (recombinationType == "CrossingTriadic")
        recombType = RecombinationTypes::CrossingTriadic;
      else if (recombinationType == "CrossingReducedReplacement")
        recombType = RecombinationTypes::CrossingReducedReplacement;
      else if (recombinationType == "CrossingShuffling")
        recombType = RecombinationTypes::CrossingShuffling;
      else {
        cerr << "Unsupported recombinationType." << endl;
        return;
      }
      
      double maskProb = 1.0;
      if (data.contains("mask_prob"))
        maskProb = data["mask_prob"];
      else
        cout << "Parameter mask_prob is not set." << endl;
      
      int populationSize = 1;
      if (data.contains("population_size"))
        populationSize = data["population_size"];
      else
        cout << "Parameter population_size is not set." << endl;

      int numOfCycles = 1;
      if (data.contains("cycles"))
        numOfCycles = data["cycles"];
      else
        cout << "Parameter cycles is not set." << endl;

      std::string selectionType = data["selection_type"];
      SelectionTypes selType;
      if (selectionType == "Base")
        selType = SelectionTypes::Base;

      int survNum = data["surv_num"];

      gp.setPopulationSize(populationSize);
      gp.setNumOfCycles(numOfCycles);
      gp.setRecombinationParameters(selecTypeParent, tourSize, recombType, refPoints, maskProb, recNum);
      gp.setMutationParameters(mType, mutChance, exchangeType, probabilityTruthTable);
      gp.setSelectionParameters(selType, survNum);
      gp.setKeyEndProcessIndex(outRatio);
      //gp.setGeneticParameters(numOfSurv, mutType, mutChance, swapType, ratioInTable, recNum, refPoints, tourSize, selectionTypeParent);
    }
    
    
    DataBaseGeneratorParameters dbgp(minInputs, maxInputs, minOutputs, maxOutputs, repeats, gt, gp);

    DataBaseGenerator generator(dbgp);

    auto start = high_resolution_clock::now();

    // Запускаем генерацию с учетом многопоточности и создания поддерикторий
    generator.generateType(
        dbgp,
        data.contains("multithread") ? (bool)data["multithread"] : false,
        data.contains("create_id_directories") ? (bool)data["create_id_directories"] : true);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::clog << "Time taken: " << duration.count() << " microseconds" << std::endl;
  }
}
