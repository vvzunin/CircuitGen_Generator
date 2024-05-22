#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

#include <additional/RandomGeneratorWithSeed.hpp>
#include <baseStructures/truthTable/TruthTable.hpp>
#include <CircuitGenGenerator/OrientedGraph.hpp>
#include <limits.h>
#include <settings/Settings.hpp>

/// @file SimpleGenerators.hpp
/// TO DO: Description generatorNumOperation
/// TO DO: check and change the body if necessary generatorSummator,
/// generatorComparison and generatorEncoder
///

using GatesInfo = std::map<Gates, std::vector<int32_t>>;

namespace {
/// @addtogroup UnnamedNamespaces
/// @{
/// @file SimpleGenerators.hpp
/// @brief maxValueInMap Find the maximum value in a map
///
/// @tparam T The type of the map keys
/// @param i_map The map whose maximum value is to be found
/// @return The maximum value in the map. If the map is empty, returns -1
/// @note The function assumes that the map values are of type int32_t
/// @}
template<typename T>
int32_t maxValueInMap(const std::map<T, int32_t>& i_map) {
  if (i_map.size() == 0) {
    return -1;
  }
  int32_t res = (*i_map.begin()).second;

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
/// (std::map<std::string, std::vector<int32_t>>), where the keys are strings
/// (names of logical operations), and the values are vectors of integers
/// representing information about the inputs (indexes) of gates associated with
/// each logical operation. This is a general description***
/// @param d_randGenerator An object of the Random Generator With Seed class,
/// which is used to generate random numbers based on a given grain (seed).
/// @param d_maxGateNumber An integer value representing the maximum gate number
/// in the system. This value is probably used to control the allocation of new
/// gate numbers when creating new elements.
/// */

class SimpleGenerators {
  using GatesInfo = std::map<Gates, std::vector<int32_t>>;

public:
  SimpleGenerators();
  SimpleGenerators(uint_fast32_t i_seed);

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
  /// // @todo: Examples
  /// @endcode

  GraphPtr cnfFromTruthTable(const TruthTable& i_table, bool i_tp = true);
  GraphPtr zhegalkinFromTruthTable(const TruthTable& i_table);

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

  GraphPtr generatorRandLevel(
      uint32_t i_minLevel,
      uint32_t i_maxLevel,
      uint32_t i_minElements,
      uint32_t i_maxElements,
      uint32_t i_inputs,
      uint32_t i_outputs
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
  /// // @todo: Examples
  /// @end_code
  /// @throw std::invalid_argument. The method starts by checking the input
  /// parameters for correctness: if the minimum level is greater than the
  /// maximum or the minimum number of elements is greater than the maximum,
  /// the method throws an exception std::invalid_argument.

  GraphPtr generatorRandLevelExperimental(
      uint32_t i_minLevel,
      uint32_t i_maxLevel,
      uint32_t i_minElements,
      uint32_t i_maxElements,
      uint32_t i_inputs,
      uint32_t i_outputs
  );

  /// @todo: Description algorithm
  /// @brief generatorNumOperation
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

  GraphPtr generatorNumOperation(
      uint32_t                 i_input,
      uint32_t                 i_output,
      std::map<Gates, int32_t> i_logicOper,
      bool                     i_leaveEmptyOut = true
  );

  /// @brief generatorSummator represents the generation of a combinational
  /// adder circuit. It is based on the arithmetic operation of addition in the
  /// decimal system and creates a graph of logical elements for its
  /// implementation. The number of bits fed into it is the length of the
  /// numbers that are converted from decimal to binary notation to implement
  /// the graph. Both the half-version and the full version are used as the
  /// basis of the generation.
  /// @param i_bits The number of bits, or in other words, input vertices
  /// (variables), which will be twice as many in the graph
  /// @param i_overflowIn A Boolean flag indicating whether to create an
  /// additional input vertex (variable) in the graph at the beginning of
  /// generation
  /// @param i_overflowOut A Boolean flag indicating whether to create an
  /// additional output vertex (variable) in the graph at the end of generation
  /// @param i_minus A Boolean flag indicating whether it is worth adding
  /// logical vertices of type NOT to the graph to select a negative sum
  /// @return the created OrientedGraph

  GraphPtr generatorSummator(
      uint32_t i_bits,
      bool     i_overflowIn,
      bool     i_overflowOut,
      bool     i_minus
  );

  /// @brief generatorComparison represents the generation of a combinational
  /// comparator circuit. It is able to compare the submitted data in three
  /// variants: "equal", "less", "more". Reads the bits of numbers from larger
  /// to smaller, taking into account the significance of the higher bits.
  /// numbers that are converted from decimal to binary notation to implement
  /// the graph
  /// @param i_bits The number of bits, or in other words, input vertices
  /// (variables), which will be twice as many in the graph
  /// @param compare0 A Boolean flag indicating whether to perform the
  /// "equality" ("=") comparison operation between two bits of different
  /// numbers.
  /// @param compare1 A Boolean flag indicating indicating whether to perform
  /// the "less" ("<") comparison operation between two bits of different
  /// numbers.
  /// @param compare2 A Boolean flag indicating indicating whether to perform
  /// the "more" (">") comparison operation between two bits of different
  /// numbers.
  /// @return the created OrientedGraph

  GraphPtr generatorComparison(
      uint32_t i_bits,
      bool     compare0,
      bool     compare1,
      bool     compare2
  );

  /// @brief generatorEncoder represents the generation of a combinational
  /// scheme of a standard binary encoder. The number of incoming bits (n) must
  /// be equal to two in degree (m), whose value is the number of outputs in the
  /// graph. If the number n is not equal to two in any degree, then the power
  /// of two is selected, at which the value will be the nearest and greater
  /// than the value of n itself. If one bit is applied to the input, the
  /// generation is canceled.
  /// @param i_bits The number of bits, or in other words, input vertices
  /// (variables) in the graph.
  /// @return the created OrientedGraph

  GraphPtr generatorEncoder(uint32_t i_bits);

  /// @brief generatorSubtractor represents the generation of a combinational
  /// subtractor scheme. It is based on the arithmetic difference operation,
  /// implementing its logic through logical operations. The generation logic is
  /// close to the logic of generatorSummator, with the difference that the user
  /// can choose which input vertices will be the bits of the reduced and which
  /// ones will be subtracted. Both the half-version and the full version are
  /// used as the basis of the generation.
  /// @param i_bits The number of bits, or in other words, input vertices
  /// (variables), which will be twice as many in the graph
  /// @param i_overflowIn A Boolean flag indicating whether to create an
  /// additional input vertex (variable) in the graph at the beginning of
  /// generation
  /// @param i_overflowOut A Boolean flag indicating whether to create an
  /// additional output vertex (variable) in the graph at the end of generation
  /// @param i_sub A Boolean flag indicating which input vertices will be the
  /// bits of the reduced and which bits of the subtracted (if false, then B-A
  /// is executed, if true, then A-B)
  /// @return the created OrientedGraph

  GraphPtr generatorSubtractor(
      uint32_t i_bits,
      bool     i_overflowIn,
      bool     i_overflowOut,
      bool     i_sub
  );

  /// @brief generatorMultiplexer represents the generation of a combinational
  /// multiplexer circuit. When generating to the standard input vertices,
  /// additional ones are created, which are control inputs in the multiplexer
  /// circuit. Their number is a power of two, which is equal to or greater than
  /// the number of input vertices, and is the closest to the number of input
  /// vertices. There is always one output vertex. If the number of input
  /// vertices is less than two, the generation will be rejected.
  /// @param i_bits The number of bits, or in other words, input vertices
  /// (variables) in the graph.
  /// @return the created OrientedGraph

  GraphPtr generatorMultiplexer(uint32_t i_bits);

  /// @brief generatorDemultiplexer represents the generation of the
  /// combinational circuit of the demultiplexer. The generation logic almost
  /// completely repeats the logic of generatorMultiplexer. The difference lies
  /// in the use of logical operations and the fact that the user sets the
  /// number of output vertices, while the input vertex is always one.
  /// @param i_bits The number of bits, or in other words, input vertices
  /// (variables) in the graph.
  /// @return the created OrientedGraph

  GraphPtr generatorDemultiplexer(uint32_t i_bits);

  /// @brief generatorDecoder represents the generation of a combinational
  /// decoder circuit. The logic of generation is close to the logic of
  /// generating an encoder, except for logical operations and the fact that the
  /// number of input vertices is a power of two of the number of output
  /// vertices. The number of input vertices can range from 1 to the desired
  /// number by the user.
  /// @param i_bits The number of bits, or in other words, input vertices
  /// (variables) in the graph.
  /// @return the created OrientedGraph

  GraphPtr generatorDecoder(uint32_t i_bits);

  /// @brief generatorParity represents the generation of a combinational parity
  /// check scheme. The graph is based on the logical XOR operation, which is
  /// used to check the parity of the resulting number in binary form. The graph
  /// can be generated from any number of supplied bits, if their number is at
  /// least two. Otherwise, the generation will be canceled.
  /// @param i_bits The number of bits, or in other words, input vertices
  /// (variables) in the graph.
  /// @return the created OrientedGraph

  GraphPtr generatorParity(uint32_t i_bits);

  /// @brief generatorMultiplier represents the generation of a combinational
  /// multiplier circuit. It is based on the arithmetic multiplication operation
  /// implemented through logical operations and generatorSummator. Arithmetic
  /// multiplication consists of addition, so the logical implementation is
  /// based on a semi- and full implementation of the generatorSummator. The
  /// multiplier structure is a matrix of AND operations and adders, in which
  /// all adders are interconnected through value transfers. The user cannot
  /// influence the operation of the adders inside the multiplier.
  /// @param i_bits The number of bits, or in other words, input vertices
  /// (variables) in the graph.
  /// @return the created OrientedGraph

  GraphPtr generatorMultiplier(uint32_t i_bits);

  /// @brief generatorALU represents the generation of a combinational circuit
  /// of an ALU (Arithmetic Logic Unit). It is a multi-structured graph
  /// consisting of a set of subgraphs selected by the user. The framework of
  /// the ALU generator is a multiplexer, which is a subgraph. This subgraph is
  /// connected to other subgraphs, which are almost all the declared generators
  /// above. Their generation takes place at the user's choice and the output
  /// vertices are connected to the input vertices of the multiplexer subgraph.
  /// As a result, the ALU has one output vertex from each multiplexer, which
  /// transmit the result to the output based on the signals of the control
  /// input vertices.
  /// @param i_bits The number of bits, which specifies for what size of input
  /// values each generators should be.
  /// @param i_outbits The number of bits, which specifies for what size of
  /// output values each generators should be.
  /// @param ALL A Boolean flag indicating whether it is worth selecting all
  /// types of generation from the available ones
  /// @param SUM A Boolean flag indicating whether to choose summator generation
  /// with positive numbers
  /// @param SUB A Boolean flag indicating whether it is worth choosing to
  /// generate a subtractor with a choice of a reduced B and subtracted A
  /// @param NSUM A Boolean flag indicating whether to choose summator
  /// generation with negative numbers
  /// @param NSUB A Boolean flag indicating whether it is worth choosing to
  /// generate a subtractor with a choice of a reduced A and subtracted B
  /// @param MULT A Boolean flag indicating whether to choose multiplier
  /// generation
  /// @param COM A Boolean flag indicating whether to choose the generation of
  /// the comparator
  /// @param AND A Boolean flag indicating whether to choose to generate a
  /// logical operation AND
  /// @param NAND A Boolean flag indicating whether to choose to generate a
  /// logical operation NAND
  /// @param OR A Boolean flag indicating whether to choose to generate a
  /// logical operation OR
  /// @param NOR A Boolean flag indicating whether to choose to generate a
  /// logical operation NOR
  /// @param XOR A Boolean flag indicating whether to choose to generate a
  /// logical operation XOR
  /// @param XNOR A Boolean flag indicating whether to choose to generate a
  /// logical operation XNOR
  /// @param CNF A Boolean flag indicating whether it is worth choosing to
  /// generate a generator based on a Random Truth Table
  /// @param RNL A Boolean flag indicating whether it is worth choosing to
  /// type of generation Rand Level
  /// @param NUM_OP A Boolean flag indicating whether it is worth choosing to
  /// type of generation Num Operation
  /// @param minLevel The minimum level of complexity of the graph from
  /// generation based on Rand Level
  /// @param maxLevel The maximum level of complexity of the graph from
  /// generation based on Rand Level. If the value is set to 0, only the minimum
  /// level will be used.
  /// @param minElement The minimum number of elements (valves) at each
  /// level from generation based on Rand Level
  /// @param maxElement The maximum number of elements (valves) at each
  /// level from generation based on Rand Level
  /// @param m A dictionary containing a set of logical operations
  /// (gates) and their numbers that can be used to generate a graph from
  /// generation based on Num Operation
  /// @param LeaveEmptyOut A Boolean flag indicating whether to leave the
  /// output vertices empty if the number of output vertices is greater than
  /// the number of logical operations in the graph from generation based on Num
  /// Operation. If true, the remaining output vertices will remain empty, if
  /// false, they will be deleted
  /// @return the created OrientedGraph

  GraphPtr generatorALU(
      int32_t                  i_bits,
      int32_t                  i_outbits,
      bool                     ALL,
      bool                     SUM,
      bool                     SUB,
      bool                     NSUM,
      bool                     NSUB,
      bool                     MULT,
      bool                     COM,
      bool                     AND,
      bool                     NAND,
      bool                     OR,
      bool                     NOR,
      bool                     XOR,
      bool                     XNOR,
      bool                     CNF,
      bool                     RNL,
      bool                     NUM_OP,
      uint32_t                 minLevel,
      uint32_t                 maxLevel,
      uint32_t                 minElement,
      uint32_t                 maxElement,
      std::map<Gates, int32_t> m,
      bool                     LeaveEmptyOut
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
  /// std::map<std::string, std::vector<int32_t>> gateInputsInfo =
  /// {
  /// {"AND", {2, 3}},
  /// {"OR", {2, 3}},
  /// {"NOT", {1}},
  /// // Add more gate input information as needed
  /// };
  /// // Set the input information for logic gates
  /// generators.setGatesInputsInfo(gateInputsInfo);
  /// @endcode

  void setGatesInputsInfo(
      const std::map<std::string, std::vector<int32_t>>& i_info
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
  std::map<Gates, int32_t>  delNull(std::map<Gates, int32_t> i_copyLogicOper);

  // moved it here, because we need to use templates
  template<typename T>
  T randomGenerator(const std::map<T, int32_t>& i_map) {
    // rand element of map
    auto val = i_map.begin();
    std::advance(val, d_randGenerator.getRandInt(0, i_map.size()));

    return val->first;
  }

  std::pair<Gates, int32_t> getRandomElement(const GatesInfo& i_info);
  std::pair<Gates, int32_t> getRandomElement(u_int32_t i_gatesLimit);

  /// @brief getRangomAndNumber The getRangomAndNumber method returns a random
  /// value from the list of possible input ports for the "AND" operator.
  /// @return a random value representing the input port number for the "AND"
  /// operator.
  /// */

  int32_t                   getRangomAndNumber();

  /// @brief getRangomOrNumber method is a random value from the list of
  /// possible input ports for the "OR" operator
  /// @return a random value representing the input port number for the "OR"
  /// operator.
  /// */

  int32_t                   getRangomOrNumber();

  /// @brief getRangomNandNumber The method returns a random value from the list
  /// of possible input ports for the "NAND" operator.
  /// @return a random value representing the input port number for the "NAND"
  /// operator
  /// */

  int32_t                   getRangomNandNumber();

  /// @brief getRangomNorNumber The method returns a random value from the list
  /// of possible input ports for the "NOR" operator.
  /// @return a random value representing the input port number for the "NOR"
  /// operator
  /// */

  int32_t                   getRangomNorNumber();

  /// @brief getRangomXorNumber The method returns a random value from the list
  /// of possible input ports for the "XOR" operator.
  /// @return a random value representing the input port number for the "XOR"
  /// operator.
  /// */

  int32_t                   getRangomXorNumber();

  /// @brief The method returns a random value from the list of possible input
  /// ports for the "XNOR" operator.
  /// @return a random value representing the input port number for the "XNOR"
  /// operator
  /// */

  int32_t                   getRangomXnorNumber();

  GatesInfo                 d_gatesInputsInfo;
  RandomGeneratorWithSeed   d_randGenerator;
  int32_t                   d_maxGateNumber = 0;
  int32_t                   d_minGateNumber = 0;
};