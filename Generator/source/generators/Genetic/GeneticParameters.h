#pragma once

#include "./Selections/SelectionParameters.h"
#include "./Recombination/RecombinationParameters.h"
#include "./Mutations/MutationParameters.h"

class GeneticParameters
{
public:
  GeneticParameters(int i_inputs = 0, int outs = 0);
  int getInputs() const;
  void setInputs(int i_inputs);
  int getOutputs() const;
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

//TODO: is it really need to place it there and not in ../../graph/OrientedGraph.h?
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

class TruthTableParameters : public GeneticParameters
{
public:
  TruthTableParameters(int i_inputs = 0, int i_outputs = 0);
  TruthTableParameters(const GeneticParameters& i_gp);
  int size() const;
  bool operator== (const TruthTableParameters& r);
};
