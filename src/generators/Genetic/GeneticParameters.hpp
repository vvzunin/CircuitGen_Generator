#pragma once

#include "./Selections/SelectionParameters.hpp"
#include "./Recombination/RecombinationParameters.hpp"
#include "./Mutations/MutationParameters.hpp"

/// @todo: fill in the description of the class fields
/// @class GeneticParameters
/// Class representing genetic algorithm parameters
/// @param d_inputs Number of inputs
/// @param d_outputs Number of outputs
/// @param d_populationSize Population size
/// @param d_numOfCycles Number of cycles
/// @param d_selectionParameters
/// @param d_recombinationParameters
/// @param d_mutationParameters
/// @param d_keyEndProcessIndex

class GeneticParameters
{
public:

  /// @brief GeneticParameters
  /// 
  /// @param i_inputs Number of inputs
  /// @param outs Number of outputs

  GeneticParameters(uint32_t i_inputs = 0, uint32_t outs = 0);


  /// @brief getInputs
  /// Get the number of inputs
  /// @return The number of inputs

  uint32_t getInputs() const;


  /// @brief setInputs
  /// Set the number of inputs
  /// @param i_inputs The number of inputs

  void setInputs(uint32_t i_inputs);


  /// @brief getOutputs
  /// Get the number of outputs
  /// @return The number of outputs

  uint32_t getOutputs() const;


  /// @brief setOutputs
  /// Set the number of outputs
  /// @param i_outputs The number of outputs

  void setOutputs(uint32_t i_outputs);


  SelectionParameters getSelectionParameters() const;
  void setSelectionParameters(const SelectionParameters& i_sp);
  RecombinationParameters getRecombinationParameters() const;
  void setRecombinationParameters(const RecombinationParameters& i_rp);
  MutationParameters getMutationParameters() const;
  void setMutationParameters(const MutationParameters& i_mp);
  void setPopulationSize(uint32_t i_populationSize);
  void setNumOfCycles(uint32_t i_numOfCycles);
  void setKeyEndProcessIndex(double i_keyEndProcessIndex);
  double getKeyEndProcessIndex() { return d_keyEndProcessIndex; }
  uint32_t getNumOfCycles() { return d_numOfCycles; }

 
protected:
  uint32_t d_inputs;
  uint32_t d_outputs;
  uint32_t d_populationSize = 0;
  uint32_t d_numOfCycles = 0;
  SelectionParameters d_selectionParameters;
  RecombinationParameters d_recombinationParameters;
  MutationParameters d_mutationParameters;
  double d_keyEndProcessIndex = 0;
};

/// @todo : is it really need to place it there and not in ../../graph/OrientedGraph.h?
class OrientedGraphParameters : public GeneticParameters
{
public:
  uint32_t getMaxLevel() const;
  uint32_t getMaxElements() const;
  bool empty() const;

private:
  uint32_t d_maxLevel = 0;
  uint32_t d_maxElements = 0;
};


/// @class TruthTableParameters
/// Parameters for generating truth tables
/// The class provides the parameters needed to generate truth tables.
/// These parameters include the number of entries and exits, population size,
/// parameters for selection, recombination and mutation operations, as well as
/// termination criteria truth table generation process

class TruthTableParameters : public GeneticParameters
{
public:


  /// @brief TruthTableParameters
  /// @param i_inputs Number of truth table inputs
  /// @param i_outputs Number of truth table outputs
  TruthTableParameters(uint32_t i_inputs = 0, uint32_t i_outputs = 0);

  /// @brief TruthTableParameters
  /// @param i_gp Genetic parameters used to generate the truth table
  TruthTableParameters(const GeneticParameters& i_gp);


  /// @brief getPopulationSize
  /// @todo: Why is this method needed if there is a size
  /// @return truth table population size
  uint32_t getPopulationSize() { return size(); }

  /// @brief size
  /// Returns the size of the truth table population
  /// @return truth table population size

  uint32_t size() const;


  /// @brief Overloaded comparison operator for Truth Table Parameters
  /// @param r Truth table parameters for comparison
  /// @return true if the parameters are equal, otherwise false
  bool operator== (const TruthTableParameters& r);
};
