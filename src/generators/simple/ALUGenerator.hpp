#pragma once
#include <generators/simple/SimpleGenerator.hpp>
#include <baseStructures/truthTable/TruthTable.hpp>

class ALUGenerator : public SimpleGenerator {
public:
  ALUGenerator();
  ALUGenerator(uint_fast32_t i_seed);
  ALUGenerator(const GenerationParameters& i_param);

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

  GraphPtr generatorALU(const GenerationParameters &i_param);
  GraphPtr generatorALU();

private:
  GraphPtr generatorSummator(
      uint32_t i_bits,
      bool     i_overflowIn,
      bool     i_overflowOut,
      bool     i_minus
  );
  GraphPtr generatorSubtractor(
      uint32_t i_bits,
      bool     i_overflowIn,
      bool     i_overflowOut,
      bool     i_sub
  );
  GraphPtr generatorMultiplier(uint32_t i_bits);
  GraphPtr generatorComparison(
      uint32_t i_bits,
      bool     compare0,
      bool     compare1,
      bool     compare2
  );
  GraphPtr generatorMultiplexer(uint32_t i_bits);
  GraphPtr cnfFromTruthTable(const TruthTable& i_table, bool i_tp = true);
  GraphPtr zhegalkinFromTruthTable(const TruthTable& i_table);
  GraphPtr generatorRandLevel(
      uint32_t i_minLevel,
      uint32_t i_maxLevel,
      uint32_t i_minElements,
      uint32_t i_maxElements,
      uint32_t i_inputs,
      uint32_t i_outputs
  );
  GraphPtr generatorNumOperation(
      uint32_t                 i_input,
      uint32_t                 i_output,
      std::map<Gates, int32_t> i_logicOper,
      bool                     i_leaveEmptyOut = true
  );
};