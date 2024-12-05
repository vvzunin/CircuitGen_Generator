#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class ParityGenerator : public SimpleGenerator {
public:
  ParityGenerator();
  ParityGenerator(uint_fast32_t i_seed);
  ParityGenerator(const GenerationParameters& i_param);

  /// @brief generatorParity represents the generation of a combinational parity
  /// check scheme. The graph is based on the logical XOR operation, which is
  /// used to check the parity of the resulting number in binary form. The graph
  /// can be generated from any number of supplied bits, if their number is at
  /// least two. Otherwise, the generation will be canceled.
  /// @param i_bits The number of bits, or in other words, input vertices
  /// (variables) in the graph.
  /// @return the created OrientedGraph

  GraphPtr generatorParity(uint32_t i_bits);

  GraphPtr generatorParity(const GenerationParameters &i_param);
  GraphPtr generatorParity();
};