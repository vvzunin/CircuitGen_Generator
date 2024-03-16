#pragma once

#include <map>
#include <memory>
#include <vector>
#include <algorithm>

#include <graph/OrientedGraph.h>
#include <AuxiliaryMethods/RandomGeneratorWithSeed.h>

#include "./TruthTable.h"

using GatesInfo = std::map<std::string, std::vector<int>>;

/// class SimpleGenerators
/// @param d_settings A pointer to an object of the Settings class, which is a singleton and is used to store settings associated with the vertices of the graph.
/// @param d_gatesInputsInfo The data structure represented as a display (std::map<std::string, std::vector<int>>), where the keys are strings (names of logical operations), and the values are vectors of integers representing information about the inputs (indexes) of gates associated with each logical operation. This is a general description***
/// @param d_randGenerator An object of the Random Generator With Seed class, which is used to generate random numbers based on a given grain (seed).
/// @param d_maxGateNumber An integer value representing the maximum gate number in the system. This value is probably used to control the allocation of new gate numbers when creating new elements.
/// */

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
        int i_minLevel,
        int i_maxLevel, 
        int i_minElements, 
        int i_maxElements, 
        int i_inputs, 
        int i_outputs);
    OrientedGraph generatorRandLevelExperimental(
        u_int32_t i_minLevel,
        u_int32_t i_maxLevel,
        u_int32_t i_minElements,
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

    /// @brief getRangomAndNumber The getRangomAndNumber method returns a random value from the list of possible input ports for the "AND" operator.
    /// @return a random value representing the input port number for the "AND" operator.
    /// */

    int getRangomAndNumber();

    /// @brief getRangomOrNumber method is a random value from the list of possible input ports for the "OR" operator
    /// @return a random value representing the input port number for the "OR" operator.
    /// */

    int getRangomOrNumber();

    /// @brief getRangomNandNumber The method returns a random value from the list of possible input ports for the "NAND" operator.
    /// @return a random value representing the input port number for the "NAND" operator
    /// */

    int getRangomNandNumber();

    /// @brief getRangomNorNumber The method returns a random value from the list of possible input ports for the "NOR" operator.
    /// @return a random value representing the input port number for the "NOR" operator
    /// */

    int getRangomNorNumber();

    /// @brief getRangomXorNumber The method returns a random value from the list of possible input ports for the "XOR" operator.
    /// @return a random value representing the input port number for the "XOR" operator.
    /// */

    int getRangomXorNumber();

    /// @brief The method returns a random value from the list of possible input ports for the "XNOR" operator.
    /// @return a random value representing the input port number for the "XNOR" operator
    /// */

    int getRangomXnorNumber();

    GatesInfo d_gatesInputsInfo;
    RandomGeneratorWithSeed d_randGenerator;
    int d_maxGateNumber = 0;
};
