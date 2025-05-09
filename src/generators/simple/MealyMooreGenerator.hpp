#pragma once
#include <generators/simple/SimpleGenerator.hpp>

namespace CG_Gen {

class MealyMooreGenerator : public SimpleGenerator {
public:
  MealyMooreGenerator();
  MealyMooreGenerator(uint_fast32_t i_seed);
  explicit MealyMooreGenerator(const GenerationParameters &i_param);

  /// @brief generatorMealy represents the generation of a sequential circuit
  /// of a Mealy machine. Generator creates a Mealy machine with random
  /// transitions and outputs based on the given parameters. The result is in a
  /// form of a dot file and can be later used to transform it into
  /// OrientedGraph.
  /// @param i_input The number of input variables in the graph
  /// @param i_output The number of outputs in the graph
  /// @param i_numStates The number of states in the graph
  /// @param i_seed The seed used for randomizing transisions and outputs
  /// @param i_saveDOT_mmg Flag for either creating (1) or not (0) of a dot file
  /// @return the created dot form of a graph
  DotReturn generatorMealy(uint32_t i_Inputs, uint32_t i_Outputs,
                           uint32_t i_numStates, uint32_t i_seed,
                           bool i_saveDOT_mmg);

  /// @brief generatorMoore represents the generation of a sequential circuit
  /// of a Moore machine. Generator creates a Moore machine with random
  /// transitions and outputs based on the given parameters. The result is in a
  /// form of a dot file and can be later used to transform it into
  /// OrientedGraph.
  /// @param i_input The number of input variables in the graph
  /// @param i_output The number of outputs in the graph
  /// @param i_numStates The number of states in the graph
  /// @param i_seed The seed used for randomizing transisions and outputs
  /// @param i_saveDOT_mmg Flag for either creating (1) or not (0) of a dot file
  /// @return the created dot form of a graph
  DotReturn generatorMoore(uint32_t i_Inputs, uint32_t i_Outputs,
                           uint32_t i_numStates, uint32_t i_seed,
                           bool i_saveDOT_mmg);

  DotReturn generatorMealyMoore(const GenerationParameters &i_param);

  DotReturn generatorMealyMoore();

  /// @brief generatorDotReturnToGraphMealy represents the generation of a
  /// sequential circuit of a Mealy machine. Generator creates a Mealy machine
  /// with random transitions and outputs based on the given parameters. The
  /// result in a form of a Dotreturn is then transitioned into std::string
  /// content and used to create OrientedGraph, similar to DotToGraphGenerator
  /// @param i_input The number of input variables in the graph
  /// @param i_output The number of outputs in the graph
  /// @param i_numStates The number of states in the graph
  /// @param i_seed The seed used for randomizing transisions and outputs
  /// @param i_saveDOT_mmg Flag for either creating (1) or not (0) of a dot file
  /// @return OrientedGraph
  GraphPtr generatorDotReturnToGraphMealy(uint32_t i_Inputs, uint32_t i_Outputs,
                                          uint32_t i_numStates, uint32_t i_seed,
                                          bool i_saveDOT_mmg);

  /// @brief generatorDotReturnToGraphMoore represents the generation of a
  /// sequential circuit of a Moore machine. Generator creates a Mealy machine
  /// with random transitions and outputs based on the given parameters. The
  /// result in a form of a Dotreturn is then transitioned into std::string
  /// content and used to create OrientedGraph, similar to DotToGraphGenerator
  /// @param i_input The number of input variables in the graph
  /// @param i_output The number of outputs in the graph
  /// @param i_numStates The number of states in the graph
  /// @param i_seed The seed used for randomizing transisions and outputs
  /// @param i_saveDOT_mmg Flag for either creating (1) or not (0) of a dot file
  /// @return OrientedGraph
  GraphPtr generatorDotReturnToGraphMoore(uint32_t i_Inputs, uint32_t i_Outputs,
                                          uint32_t i_numStates, uint32_t i_seed,
                                          bool i_saveDOT_mmg);

  GraphPtr generatorDotReturnToGraph(const GenerationParameters &i_param);

  GraphPtr generatorDotReturnToGraph();
};

} // namespace CG_Gen
