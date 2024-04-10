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
///
/// 


using GatesInfo = std::map<Gates, std::vector<int>>;



namespace {
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

  /// @brief cnfFromTruthTable accepts a truth table as an input in the form of
  /// a Truth Table object and returns a vector of rows representing an
  /// expression in the form of a conjunctive normal form (KNF) that
  /// corresponds to this truth table. The conjunctive normal form form
  /// represents a logical expression in the form of a conjunction of
  /// disjunctions
  /// @param i_table This is an object of the Truth Table type, which is a
  /// truth table. The truth table consists of a set of rows, where each row
  /// represents a possible combination of variable values in a logical
  /// expression, and each column represents the value of a variable in that
  /// combination.
  /// @param i_tp This is a Boolean flag (true/false) that indicates whether
  /// to add negation before variables that have the value "False" in the
  /// truth table. If i_tp is set to true, negation will be added to the
  /// variables with the value "False". If i_tp is set to false, the
  /// negation will not be added. This allows you to choose between the
  /// representation of the truth table in KNF or in disjunctive normal
  /// form (DNF)
  /// @return a vector of strings representing an expression in the form of
  /// conjunctive normal form (KNF) corresponding to the input truth table
  /// @code
  /// // TO DO: Examples
  /// @endcode

  std::vector<std::string>
                cnfFromTruthTable(const TruthTable& i_table, bool i_tp = true);
  
  /// @brief generatorRandLevel creates an oriented graph (represented by
  /// an OrientedGraph object) with a given level of complexity and number
  /// of elements. The graph is a circuit consisting of logic gates, inputs
  /// and outputs
  /// The method starts by creating graph inputs (variables). Then he gradually
  /// adds levels with valves to the graph, while the number of valves at each
  /// level is randomly selected within the specified limits. For each valve,
  /// the type of operation is randomly selected from a predefined set, then
  /// the corresponding valve object is created and added to the graph. At the
  /// end, the method adds outputs from the graph, connecting them to the last
  /// level of the gates
  /// @param i_minLevel The minimum level of complexity of the graph???
  /// @param i_maxLevel The maximum level of complexity of the graph. If the
  /// value is set to 0, only the minimum level will be used
  /// @param i_minElements The minimum number of elements (valves) at each
  /// level
  /// @param i_maxElements The maximum number of elements (valves) at each
  /// level
  /// @param i_inputs The number of inputs to the graph
  /// @param i_outputs The number of exits from the graph
  
  OrientedGraph generatorRandLevel(
      int i_minLevel,
      int i_maxLevel,
      int i_minElements,
      int i_maxElements,
      int i_inputs,
      int i_outputs
  );

  /// @brief generatorRandLevelExperimental The method generates a random level
  /// of complexity of the graph within the specified boundaries. After that,
  /// the method adds input vertices (variables) to the graph. Next, there is a
  /// step-by-step addition of levels with gates (logical operations) to the
  /// graph. Each level can contain a different number of gates, randomly
  /// selected within the specified boundaries. Also, at each level, the type
  /// of operation for each valve is randomly selected. The method uses some
  /// additional algorithms to select parent vertices for each gate to provide
  /// more diverse graphs. In particular, at each level, the algorithm randomly
  /// selects parent vertices from existing vertices, and the vertices are
  /// selected based on their location in the graph, which increases the
  /// flexibility of generation. At the end, the method adds output vertices
  /// (outputs) from the graph, connecting them to the last level of the gates
  /// @param i_minLevel The minimum level of complexity of the graph.
  /// The difficulty level determines the number of levels in the graph.
  /// The more levels there are, the more complex the scheme becomes
  /// @param i_maxLevel The maximum level of complexity of the graph.
  /// If the value is set to 0, only the minimum level will be used
  /// @param i_minElements The minimum number of elements (valves) at each
  /// level
  /// @param i_maxElements The maximum number of elements (valves) at each
  /// level
  /// @param i_inputs The number of inputs to the graph
  /// @param i_outputs The number of exits from the graph
  /// @return the created OrientedGraph, which is a circuit with logic gates,
  /// inputs and outputs
  /// @code
  /// // TO DO: Examples
  /// @endcode
  /// @throw std::invalid_argument. The method starts by checking the input
  /// parameters for correctness: if the minimum level is greater than the
  /// maximum or the minimum number of elements is greater than the maximum,
  /// the method throws an exception std::invalid_argument.

  OrientedGraph generatorRandLevelExperimental(
      u_int32_t i_minLevel,
      u_int32_t i_maxLevel,
      u_int32_t i_minElements,
      u_int32_t i_maxElements,
      u_int32_t i_inputs,
      u_int32_t i_outputs
  );

  /// @brief generatorNumOperation TO DO: Description algorithm
  /// 
  /// @param i_input The number of input vertices (variables) in the graph
  /// @param i_output The number of output vertices (functions) in the graph
  /// @param i_logicOper A dictionary containing a set of logical operations
  /// (gates) and their numbers that can be used to generate a graph
  /// @param i_leaveEmptyOut A Boolean flag indicating whether to leave the
  /// output vertices empty if the number of output vertices is greater than
  /// the number of logical operations in the graph. If true, the remaining
  /// output vertices will remain empty, if false, they will be deleted
  /// @return the created OrientedGraph

  OrientedGraph generatorNumOperation(
      int                  i_input,
      int                  i_output,
      std::map<Gates, int> i_logicOper,
      bool                 i_leaveEmptyOut = true
  );
  OrientedGraph generatorSummator(
      int  bits,
      bool overflowIn,
      bool overflowOut,
      bool minus,
      bool act = false
  );
  OrientedGraph generatorComparison(
      int  bits,
      bool compare0,
      bool compare1,
      bool compare2,
      bool act = false
  );
  OrientedGraph generatorEncoder(int bits);

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