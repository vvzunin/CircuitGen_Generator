#pragma once

#include <map>
#include <memory>
#include <vector>
#include <algorithm>

#include <graph/OrientedGraph.h>
#include <AuxiliaryMethods/RandomGeneratorWithSeed.h>

#include "./TruthTable.h"

using GatesInfo = std::map<std::string, std::vector<int>>;

class SimpleGenerators
{
public:
    SimpleGenerators();
    SimpleGenerators(int i_seed);

    SimpleGenerators(const SimpleGenerators &other) = delete;
    SimpleGenerators &operator=(const SimpleGenerators &other) = delete;
    SimpleGenerators(SimpleGenerators &&other) = delete;
    SimpleGenerators &operator=(SimpleGenerators &&other) = delete;

    std::vector<std::string> cnfFromTruthTable(const TruthTable &i_table, bool i_tp = true);

    OrientedGraph generatorRandLevel(
        int minLevel,
        int i_maxLevel, 
        int i_maxElements, 
        int i_inputs, 
        int i_outputs);
    OrientedGraph generatorRandLevelExperimental(
        u_int32_t minLevel,
        u_int32_t i_maxLevel,
        u_int32_t i_maxElements,
        u_int32_t i_inputs,
        u_int32_t i_outputs);

    OrientedGraph generatorNumOperation(
        int i_input,
        int i_output,
        std::map<std::string, int> i_logicOper,
        bool i_leaveEmptyOut = true);
    OrientedGraph generatorSummator(int bits, bool overflowIn, bool overflowOut, bool minus, bool act = false);
    OrientedGraph generatorComparison(int bits, bool compare0, bool compare1, bool compare2, bool act = false);
    OrientedGraph generatorEncoder(int bits);

    void setGatesInputsInfo(const std::map<std::string, std::vector<int>> &i_info)
    {
        d_gatesInputsInfo = i_info;

        for (auto &[key, value] : d_gatesInputsInfo)
        {
            d_maxGateNumber = std::max(
                *std::max_element(value.begin(), value.end()),
                d_maxGateNumber);
        }

        // TODO is it a good idea to add here hew gates
        d_gatesInputsInfo["not"] = {1};
        d_gatesInputsInfo["buf"] = {1};
    }

    GatesInfo getGatesInputsInfo() const
    {
        return d_gatesInputsInfo;
    }

private:
    std::shared_ptr<Settings> d_settings = Settings::getInstance("GraphVertex");
    std::map<std::string, int> delNull(std::map<std::string, int> i_copyLogicOper);
    std::string randomGenerator(const std::map<std::string, int> &i_map);

    std::pair<std::string, int> getRandomElement(const GatesInfo &i_info);
    std::pair<std::string, int> getRandomElement(u_int32_t i_gatesLimit);

    int getRangomAndNumber();
    int getRangomOrNumber();
    int getRangomNandNumber();
    int getRangomNorNumber();
    int getRangomXorNumber();
    int getRangomXnorNumber();

    GatesInfo d_gatesInputsInfo;
    RandomGeneratorWithSeed d_randGenerator;
    int d_maxGateNumber = 0;
};
