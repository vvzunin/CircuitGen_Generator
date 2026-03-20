#pragma once
#include <generators/simple/SimpleGenerator.hpp>

namespace CG_Gen {

class DotToGraphGenerator : public SimpleGenerator {
public:
  DotToGraphGenerator();
  DotToGraphGenerator(uint_fast32_t i_seed);
  explicit DotToGraphGenerator(const GenerationParameters &i_param);

  /// @brief generatorDotToGraphMealy represents the generation of a sequential
  /// circuit of a Mealy machine. Generator creates a Mealy machine from a first
  /// dot file located in a folder with a i_DotPath path.
  /// @param i_DotPath The path to a folder where dot file is located
  /// @return the created OrientedGraph

  GraphPtr generatorDotToGraphMealy(std::string i_DotPath);

  /// @brief generatorDotToGraphMoore represents the generation of a sequential
  /// circuit of a Moore machine. Generator creates a Moore machine from a first
  /// dot file located in a folder with a i_DotPath path.
  /// @param i_DotPath The path to a folder where dot file is located
  /// @return the created OrientedGraph

  GraphPtr generatorDotToGraphMoore(std::string i_DotPath);

  GraphPtr generatorDotToGraph(const GenerationParameters &i_param);

  GraphPtr generatorDotToGraph();
};

} // namespace CG_Gen
