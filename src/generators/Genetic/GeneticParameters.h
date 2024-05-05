#pragma once

#include "./Selections/SelectionParameters.h"
#include "./Recombination/RecombinationParameters.h"
#include "./Mutations/MutationParameters.h"

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

  GeneticParameters(int i_inputs = 0, int outs = 0);


  /// @brief getInputs
  /// Get the number of inputs
  /// @return The number of inputs

  int getInputs() const;


  /// @brief setInputs
  /// Set the number of inputs
  /// @param i_inputs The number of inputs

  void setInputs(int i_inputs);


  /// @brief getOutputs
  /// Get the number of outputs
  /// @return The number of outputs

  int getOutputs() const;


  /// @brief setOutputs
  /// Set the number of outputs
  /// @param i_outputs The number of outputs

  void setOutputs(int i_outputs);


  SelectionParameters getSelectionParameters() const;
  void setSelectionParameters(const SelectionParameters& i_sp);
  RecombinationParameters getRecombinationParameters() const;
  void setRecombinationParameters(const RecombinationParameters& i_rp);
  MutationParameters getMutationParameters() const;
  void setMutationParameters(const MutationParameters& i_mp);
  void setPopulationSize(int i_populationSize);
  void setNumOfCycles(int i_numOfCycles);
  void setKeyEndProcessIndex(double i_keyEndProcessIndex);
  double getKeyEndProcessIndex() { return d_keyEndProcessIndex; }
  int getNumOfCycles() { return d_numOfCycles; }

 
protected:
  int d_inputs;
  int d_outputs;
  int d_populationSize = 0;
  int d_numOfCycles = 0;
  SelectionParameters d_selectionParameters;
  RecombinationParameters d_recombinationParameters;
  MutationParameters d_mutationParameters;
  double d_keyEndProcessIndex = 0;
};

/// @todo : is it really need to place it there and not in ../../graph/OrientedGraph.h?
class OrientedGraphParameters : public GeneticParameters
{
public:
  int getMaxLevel() const;
  int getMaxElements() const;
  bool empty() const;

private:
  int d_maxLevel = 0;
  int d_maxElements = 0;
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
  TruthTableParameters(int i_inputs = 0, int i_outputs = 0);

  /// @brief TruthTableParameters
  /// @param i_gp Genetic parameters used to generate the truth table
  TruthTableParameters(const GeneticParameters& i_gp);


  /// @brief getPopulationSize
  /// @todo: Why is this method needed if there is a size
  /// @return truth table population size
  int getPopulationSize() { return size(); }

  /// @brief size
  /// Returns the size of the truth table population
  /// @return truth table population size

  int size() const;


  /// @brief Overloaded comparison operator for Truth Table Parameters
  /// @param r Truth table parameters for comparison
  /// @return true if the parameters are equal, otherwise false
  bool operator== (const TruthTableParameters& r);
};
