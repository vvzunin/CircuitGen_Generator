#pragma once


class GeneticParameters
{
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

protected:
  int d_inputs;
  int d_outputs;
  int d_populationSize = 0;
  int d_numOfCycles = 0;
  SelectionParameters d_selectionParameters;
  RecombinationParameters d_recombinationParameters;
  MutationParameters d_mutationParameters;
  double d_keyEndProcessIndex = 0;
}

//class OrientedGraphParameters : GeneticParameters
//{
//
//private:
//  int d_maxLevel;
//  int maxElements;
//}

class TruthTableParameters : GeneticParameters
{
  TruthTableParameters(int i_inputs = 0, int i_outputs = 0);
  TruthTableParameters(const GeneticParameteres& i_gp);
  int size() const;
}
