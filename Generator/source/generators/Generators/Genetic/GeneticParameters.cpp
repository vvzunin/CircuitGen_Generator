#include "GeneticParameters.h"

GeneticParameters::GeneticParameters(int i_inputs, int i_outputs) :
  d_inputs(i_inputs),
  d_outputs(i_outsputs)
  {};

GeneticParameters::getInputs() const
{
  return d_inputs();
}

void setInputs(int i_inputs)
{
  d_inputs = i_inputs;
}

int getOutputs() const
{
  return d_outputs;
}

void setOutputs(int i_outputs)
{
  d_outputs = i_outputs;
}

SelectionParameters getSelectionParameters() const
{
  return d_selectionParameters;
}

void setSelectionParameters(const SelectionParameters& i_sp)
{
  d_selectionParameters = i_sp;
}

RecombinationParameters getRecombinationParameters() const
{
  return d_recombinationParameters;
}

void setRecombinationParameters(const RecombinationParameters& i_rp)
{
  d_recombinationParameters = i_rp
}

MutationParameters getMutationParameters() const
{
  return d_mutationParameters;
}

void setMutationParameters(const MutationParameters& i_mp)
{
  d_mutationParameters = i_mp;
}

TruthTableParameters::TruthTableParameters(int i_inputs = 0, int i_outputs = 0) :
  d_inputs(i_inputs),
  d_outputs(i_outputs)
  {};

TruthTableParameters::TruthTableParameters(const GeneticParameteres& i_gp) :
  d_inputs(i_gp.d_inputs),
  d_outputs(i_gp.d_outputs),
  d_populationSize(i_gp.d_population),
  d_numOfCycles(i_gp.d_numOfCycles),
  d_selectionParameters(i_gp.d_selectionParameters),
  d_recombinationParameters(i_gp.d_recombinationParameters),
  d_mutationParameters(i_gp.d_mutationParameters),
  d_keyEndProcessIndex(i_gp.d_keyEndProcessIndex)
  {};

TruthTableParameters::size() const
{
  return 1u << d_inputs;
}
