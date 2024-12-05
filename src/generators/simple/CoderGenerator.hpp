#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class CoderGenerator : public SimpleGenerator {
public:
  CoderGenerator();
  CoderGenerator(uint_fast32_t i_seed);
  CoderGenerator(const GenerationParameters& i_param);


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

  GraphPtr generatorEncoder(const GenerationParameters &i_param);
  GraphPtr generatorDecoder(const GenerationParameters &i_param);

  GraphPtr generatorEncoder();
  GraphPtr generatorDecoder();
};
