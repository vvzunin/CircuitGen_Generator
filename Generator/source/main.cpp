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

#include <nlohmann/json.hpp>

#include <AuxiliaryMethods.h>
#include <DataBase/DataBaseGenerator.h>
#include <generators/GenerationParameters.h>
#include <DataBase/DataBaseGeneratorParameters.h>

using namespace std::chrono;

void runGenerationFromJson(std::string json_path);

int main(int argc, char **argv)
{
    std::string json_path;
    // std::string json_path = "../Generator/docs/sample.json";
    // Use getopt to parse command line arguments

    const char *const short_opts = "j:n:";
    const option long_opts[] = {
        {"json_path", required_argument, nullptr, 'j'},
        {"num_nodes", required_argument, nullptr, 'n'}};
    int c;

    int opt;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1)
    {
        switch (opt)
        {
        case 'j':
            json_path = optarg;
            break;
        case '?':
            // Unknown option or missing argument
            break;
        default:
            std::cerr << "Unknown error while parsing command line arguments." << std::endl;
            return 1;
        }
    }

    runGenerationFromJson(json_path);
}
void runGenerationFromJson(std::string json_path)
{
    std::ifstream f(json_path);
    nlohmann::json DATA = nlohmann::json::parse(f);
    // Read all json objects in json file.
    for (auto it = DATA.begin(); it != DATA.end(); it++)
    {
        nlohmann::json data = *it;

        AuxMethods::setRandSeed(!data.contains("seed") || data["seed"] == -1 ? static_cast<unsigned>(std::time(0)) : static_cast<unsigned>(data["seed"]));

        GenerationTypes gt;
        if (data["type_of_generation"] == "From Random Truth Table")
            gt = GenerationTypes::FromRandomTruthTable;
        if (data["type_of_generation"] == "Rand Level")
            gt = GenerationTypes::RandLevel;
        if (data["type_of_generation"] == "Num Operation")
            gt = GenerationTypes::NumOperation;
        if (data["type_of_generation"] == "Genetic")
            gt = GenerationTypes::Genetic;

        int requestIdINT = data["id"];
        std::string requestId = std::to_string(requestIdINT);
        assert(requestId != "");

        // std::cout << data.dump(4);

        int minInputs = data["min_in"];
        int maxInputs = data["max_in"];
        int minOutputs = data["min_out"];
        int maxOutputs = data["max_out"];
        int repeats = data["repeat_n"];
        int maxLevel = data["max_level"];
        int maxElement = data["max_elem"];
        //    bool limit = data["limit_generation"];
        bool CNFF = data["CNFF"];
        bool CNFT = data["CNFT"];
        // this is for ABC
        bool calculateStatsAbc = data.contains("calculate_stats_abc") ? (bool)data["calculate_stats_abc"] : false;
        bool makeOptimizedFiles = data.contains("make_optimized_files") ? (bool)data["make_optimized_files"] : false;
        std::string libraryName = data.contains("library_name") ? (std::string)data["library_name"] : "";
        bool LeaveEmptyOut = data["leave_empty_out"];
        int numOfSurv = data["surv_num"];
        std::string datasetId = data["dataset_id"];

        std::string mutType = data["mut_type"];
        MutationTypes mType;
        if (mutType == "Binary")
            mType = MutationTypes::Binary;
        if (mutType == "Density")
            mType = MutationTypes::Density;
        if (mutType == "AccessionDel")
            mType = MutationTypes::AccessionDel;
        if (mutType == "InsertDel")
            mType = MutationTypes::InsertDel;
        if (mutType == "Exchange")
            mType = MutationTypes::Exchange;
        if (mutType == "Delete")
            mType = MutationTypes::Delete;

        double mutChance = data["mut_chance"];
        int exchangeType = data["swap_type"];
        double outRatio = data["out_ratio"];
        double probabilityTruthTable = data["ratio_in_table"];
        int recNum = data["rec_num"];
        int refPoints = data["ref_points"];
        int tourSize = data["tour_size"];

        std::string selectionTypeParent = data["selection_type_parent"];
        ParentsTypes selecTypeParent;
        if (selectionTypeParent == "Panmixia")
            selecTypeParent = ParentsTypes::Panmixia;
        if (selectionTypeParent == "Inbringing")
            selecTypeParent = ParentsTypes::Inbringing;
        if (selectionTypeParent == "Outbrinding")
            selecTypeParent = ParentsTypes::Outbrinding;
        if (selectionTypeParent == "Tournament")
            selecTypeParent = ParentsTypes::Tournament;
        if (selectionTypeParent == "Roulette")
            selecTypeParent = ParentsTypes::Roulette;

        std::string recombinationType = data["playback_type"];
        RecombinationTypes recombType;
        if (recombinationType == "CrossingEachExitInTurnMany")
            recombType = RecombinationTypes::CrossingEachExitInTurnMany;
        if (recombinationType == "CrossingUniform")
            recombType = RecombinationTypes::CrossingUniform;
        if (recombinationType == "CrossingTriadic")
            recombType = RecombinationTypes::CrossingTriadic;
        if (recombinationType == "CrossingReducedReplacement")
            recombType = RecombinationTypes::CrossingReducedReplacement;
        if (recombinationType == "CrossingShuffling")
            recombType = RecombinationTypes::CrossingShuffling;

        double maskProb = data["mask_prob"];
        int populationSize = data["population_size"];
        int numOfCycles = data["cycles"];
        int inputs = minInputs;
        int outputs = minOutputs;

        std::string selectionType = data["selection_type"];
        SelectionTypes selType;
        if (selectionType == "Base")
            selType = SelectionTypes::Base;

        int survNum = data["surv_num"];

        std::map<std::string, int> m;
        std::vector<std::string> v =
            {"num_and", "num_nand", "num_or", "num_not",
             "num_nor", "num_buf", "num_xor", "num_xnor"};

        for (auto &el : data.items())
        {
            if (std::find(v.begin(), v.end(), el.key()) != v.end())
                m.insert({el.key().substr(4, 10), el.value()});
        }

        std::map<std::string, std::vector<int>> gatesInfo;

        if (data.contains("gates_number"))
        {
            for (auto gate : data["gates_number"].items())
            {
                std::vector<int> gatesNumber = static_cast<std::vector<int>>(gate.value());

                // if vector is empty (suddenly), we add default gates number
                if (!(int)gatesNumber.size())
                    gatesNumber.push_back(2);

                gatesInfo[gate.key()] = gatesNumber;
            }
        }
        else
        {
            // default init data
            gatesInfo["and"] = {2};
            gatesInfo["nand"] = {2};
            gatesInfo["or"] = {2};
            gatesInfo["nor"] = {2};
            gatesInfo["xor"] = {2};
            gatesInfo["xnor"] = {2};
        }

        // JSON params = JSON::Read("params.json");

        // TODO:: make function that return DataBaseGeneratorParameters from json
        // Recording of json data to gp
        GenerationParameters gp(
            datasetId,
            requestId,
            inputs,
            outputs,
            repeats,
            maxLevel,
            maxElement,
            libraryName,
            calculateStatsAbc,
            makeOptimizedFiles
        );

        gp.setName(datasetId);
        gp.setCNFF(CNFF);
        gp.setCNFT(CNFT);
        //    gp.setLimit(limit);
        gp.setNumOperationParameters(m, LeaveEmptyOut);
        gp.setPopulationSize(populationSize);
        gp.setNumOfCycles(numOfCycles);
        gp.setRecombinationParameters(selecTypeParent, tourSize, recombType, refPoints, maskProb, recNum);
        gp.setMutationParameters(mType, mutChance, exchangeType, probabilityTruthTable);
        gp.setSelectionParameters(selType, survNum);
        gp.setKeyEndProcessIndex(outRatio);
        //    gp.setGeneticParameters(numOfSurv, mutType, mutChance, swapType, ratioInTable, recNum, refPoints, tourSize,    selectionTypeParent);
        //
        DataBaseGeneratorParameters dbgp(minInputs, maxInputs, minOutputs, maxOutputs, repeats, gt, gp);

        DataBaseGenerator generator(dbgp);

        auto start = high_resolution_clock::now();

        generator.generateType(
            dbgp, 
            data.contains("multithread") ? (bool)data["multithread"] : false,
            data.contains("create_id_directories") ? (bool)data["create_id_directories"] : true
        );

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::clog << "Time taken: " << duration.count() << " microseconds" << std::endl;
    }
}
