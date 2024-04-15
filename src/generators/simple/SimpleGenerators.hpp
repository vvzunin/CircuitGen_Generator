#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

#include <additional/RandomGeneratorWithSeed.hpp>
#include <baseStructures/graph/OrientedGraph.hpp>
#include <baseStructures/truthTable/TruthTable.hpp>
#include <limits.h>
#include <settings/Settings.hpp>

/// @file SimpleGenerators.hpp
/// TO DO: Description generatorNumOperation
/// TO DO: check and change the body if necessary generatorSummator,
/// generatorComparison and generatorEncoder
/// 


using GatesInfo = std::map<Gates, std::vector<int>>;



namespace {
/// @addtogroup UnnamedNamespaces
/// @{
/// @file SimpleGenerators.hpp
/// @brief maxValueInMap Find the maximum value in a map
/// 
/// @tparam T The type of the map keys
/// @param i_map The map whose maximum value is to be found
/// @return The maximum value in the map. If the map is empty, returns -1
/// @note The function assumes that the map values are of type int
/// @}
template<typename T>
int maxValueInMap(const std::map<T, int>& i_map) {
  if (i_map.size() == 0) {
    return -1;
  }
  int res = (*i_map.begin()).second;

  for (const auto& [key, value] : i_map) {
    res = std::max(res, value);
  }
  return res;
}

// namespace end
}  // namespace


/// class SimpleGenerators
/// @param d_settings A pointer to an object of the Settings class, which is a
/// singleton and is used to store settings associated with the vertices of the
/// graph.
/// @param d_gatesInputsInfo The data structure represented as a display
/// (std::map<std::string, std::vector<int>>), where the keys are strings (names
/// of logical operations), and the values are vectors of integers representing
/// information about the inputs (indexes) of gates associated with each logical
/// operation. This is a general description***
/// @param d_randGenerator An object of the Random Generator With Seed class,
/// which is used to generate random numbers based on a given grain (seed).
/// @param d_maxGateNumber An integer value representing the maximum gate number
/// in the system. This value is probably used to control the allocation of new
/// gate numbers when creating new elements.
/// */

class SimpleGenerators {
  using GatesInfo = std::map<Gates, std::vector<int>>;

public:
  SimpleGenerators();
  SimpleGenerators(int i_seed);

  SimpleGenerators(const SimpleGenerators& other)            = delete;
  SimpleGenerators& operator=(const SimpleGenerators& other) = delete;
  SimpleGenerators(SimpleGenerators&& other)                 = delete;
  SimpleGenerators& operator=(SimpleGenerators&& other)      = delete;

  GraphPtr cnfFromTruthTable(const TruthTable& i_table, bool i_tp = true);
  GraphPtr zhegalkinFromTruthTable(const TruthTable& i_table);

  GraphPtr generatorRandLevel(
      int i_minLevel,
      int i_maxLevel,
      int i_minElements,
      int i_maxElements,
      int i_inputs,
      int i_outputs
  );
  GraphPtr generatorRandLevelExperimental(
      u_int32_t i_minLevel,
      u_int32_t i_maxLevel,
      u_int32_t i_minElements,
      u_int32_t i_maxElements,
      u_int32_t i_inputs,
      u_int32_t i_outputs
  );

  GraphPtr generatorNumOperation(
      int                  i_input,
      int                  i_output,
      std::map<Gates, int> i_logicOper,
      bool                 i_leaveEmptyOut = true
  );
  GraphPtr generatorSummator(
      int  i_bits,
      bool i_overflowIn,
      bool i_overflowOut,
      bool i_minus,
      bool act = false
  );
  GraphPtr generatorComparison(
      int  bits,
      bool compare0,
      bool compare1,
      bool compare2,
      bool act = false
  );
  GraphPtr generatorEncoder(int bits);
  GraphPtr generatorParity(int i_bits);
  GraphPtr generatorSubtractor(
      int  i_bits,
      bool i_overflowIn,
      bool i_overflowOut,
      bool i_sub,
      bool act = false
  );
  GraphPtr generatorMultiplexer(int i_bits);
  GraphPtr generatorDemultiplexer(int i_bits);
  GraphPtr generatorMultiplier(int i_bits, bool act = false);
  GraphPtr generatorDecoder(int i_bits);
  GraphPtr generatorALU(
      int  i_bits,
      int  i_outbits,
      bool ALL,
      bool SUM,
      bool SUB,
      bool NSUM,
      bool NSUB,
      bool MULT,
      bool COM,
      bool AND,
      bool NAND,
      bool OR,
      bool NOR,
      bool XOR,
      bool XNOR,
      bool CNF
  );

  /// @brief setGatesInputsInfo It is designed to set information about the
  /// inputs for various logic gates. It takes as an argument a dictionary,
  /// where the keys are the names of logical gates (Gates), and the values
  /// are vectors of integers representing the entry ports for each gate.
  /// @param i_info A map containing information about the entrances to
  /// various gates. The map keys are the names of the gates, and the values
  /// are vectors of integers representing the entry ports for each gate
  /// @code
  /// SimpleGenerators generators;
  /// // Define input information for logic gates
  /// std::map<std::string, std::vector<int>> gateInputsInfo =
  /// {
  /// {"AND", {2, 3}},
  /// {"OR", {2, 3}},
  /// {"NOT", {1}},
  /// // Add more gate input information as needed
  /// };
  /// // Set the input information for logic gates
  /// generators.setGatesInputsInfo(gateInputsInfo);
  /// @endcode

  void setGatesInputsInfo(const std::map<std::string, std::vector<int>>& i_info
  ) {
    d_minGateNumber = INT_MAX;

    for (auto& [key, value] : i_info) {
      d_maxGateNumber = std::max(
          *std::max_element(value.begin(), value.end()), d_maxGateNumber
      );
      d_minGateNumber = std::min(
          *std::max_element(value.begin(), value.end()), d_minGateNumber
      );
      d_gatesInputsInfo[d_settings->parseStringToGate(key)] = value;
    }

    // TODO is it a good idea to add here hew gates
    d_gatesInputsInfo[Gates::GateNot] = {1};
    d_gatesInputsInfo[Gates::GateBuf] = {1};
  }

  GatesInfo getGatesInputsInfo() const { return d_gatesInputsInfo; }

private:
  std::shared_ptr<Settings> d_settings = Settings::getInstance("GraphVertex");
  std::map<Gates, int>      delNull(std::map<Gates, int> i_copyLogicOper);

  // moved it here, because we need to use templates
  template<typename T>
  T randomGenerator(const std::map<T, int>& i_map) {
    // rand element of map
    auto val = i_map.begin();
    std::advance(val, d_randGenerator.getRandInt(0, i_map.size()));

    return val->first;
  }

  GraphPtr ALU(
      int  i_bits,
      int  i_outbits,
      bool ALL,
      bool SUM,
      bool SUB,
      bool NSUM,
      bool NSUB,
      bool MULT,
      bool COM,
      bool AND,
      bool NAND,
      bool OR,
      bool NOR,
      bool XOR,
      bool XNOR,
      bool CNF
  );

  std::pair<Gates, int>   getRandomElement(const GatesInfo& i_info);
  std::pair<Gates, int>   getRandomElement(u_int32_t i_gatesLimit);

  /// @brief getRangomAndNumber The getRangomAndNumber method returns a random
  /// value from the list of possible input ports for the "AND" operator.
  /// @return a random value representing the input port number for the "AND"
  /// operator.
  /// */

  int                     getRangomAndNumber();

  /// @brief getRangomOrNumber method is a random value from the list of
  /// possible input ports for the "OR" operator
  /// @return a random value representing the input port number for the "OR"
  /// operator.
  /// */

  int                     getRangomOrNumber();

  /// @brief getRangomNandNumber The method returns a random value from the list
  /// of possible input ports for the "NAND" operator.
  /// @return a random value representing the input port number for the "NAND"
  /// operator
  /// */

  int                     getRangomNandNumber();

  /// @brief getRangomNorNumber The method returns a random value from the list
  /// of possible input ports for the "NOR" operator.
  /// @return a random value representing the input port number for the "NOR"
  /// operator
  /// */

  int                     getRangomNorNumber();

  /// @brief getRangomXorNumber The method returns a random value from the list
  /// of possible input ports for the "XOR" operator.
  /// @return a random value representing the input port number for the "XOR"
  /// operator.
  /// */

  int                     getRangomXorNumber();

  /// @brief The method returns a random value from the list of possible input
  /// ports for the "XNOR" operator.
  /// @return a random value representing the input port number for the "XNOR"
  /// operator
  /// */

  int                     getRangomXnorNumber();

  GatesInfo               d_gatesInputsInfo;
  RandomGeneratorWithSeed d_randGenerator;
  int                     d_maxGateNumber = 0;
  int                     d_minGateNumber = 0;
};