#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class RandLevelGenerator : public SimpleGenerator {
public:
  RandLevelGenerator();
  RandLevelGenerator(uint_fast32_t i_seed);
  RandLevelGenerator(const GenerationParameters& i_param);

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

  GraphPtr generatorRandLevel(const GenerationParameters &i_param);

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



  GraphPtr generatorRandLevelExperimental(const GenerationParameters &i_param);

  GraphPtr generatorRandLevel();

  GraphPtr generatorRandLevelExperimental();
};
