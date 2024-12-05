#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class PlexerGenerator : public SimpleGenerator {
public:
  PlexerGenerator();
  PlexerGenerator(uint_fast32_t i_seed);
  PlexerGenerator(const GenerationParameters& i_param);

  
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

  GraphPtr generatorMultiplexer(const GenerationParameters &i_param);
  GraphPtr generatorDemultiplexer(const GenerationParameters &i_param);

  GraphPtr generatorMultiplexer();
  GraphPtr generatorDemultiplexer();
};
