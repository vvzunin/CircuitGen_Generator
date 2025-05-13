#pragma once
#include <generators/simple/SimpleGenerator.hpp>
#include <random>

namespace CG_Gen {

class CascadeGenerator : public SimpleGenerator {
public:
  CascadeGenerator();
  CascadeGenerator(uint_fast32_t i_seed);
  explicit CascadeGenerator(const GenerationParameters &i_param);

  /// @brief generatorCascade represents the generation of a sequential circuit
  /// of a Cascade machine. Generator creates a Cascade machine with random
  /// transitions and outputs based on the given parameters. The result is in a
  /// form of OrientedGraph.
  /// @param i_input The number of input variables in the graph
  /// @param i_output The number of outputs in the graph
  /// @param i_MaxNumStates The maximum number of states in each machine
  /// @param i_MinNumStates The minimum number of states in each machine
  /// @param i_seed The seed used for randomizing transitions and outputs
  /// @param i_NumAutomatons The number of machines in graph
  /// @return the created graph
  GraphPtr generatorCascade();

private:
  uint32_t m_minStates;
  uint32_t m_maxStates;
  uint32_t m_numautomatons;
};

} // namespace CG_Gen
