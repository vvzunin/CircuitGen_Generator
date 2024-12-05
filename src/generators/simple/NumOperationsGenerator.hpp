#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class NumOperationsGenerator : public SimpleGenerator {
public:
  NumOperationsGenerator();
  NumOperationsGenerator(uint_fast32_t i_seed);


  NumOperationsGenerator(const GenerationParameters& i_param);

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

  GraphPtr generatorNumOperation(const GenerationParameters &i_param);
  GraphPtr generatorNumOperation();
};