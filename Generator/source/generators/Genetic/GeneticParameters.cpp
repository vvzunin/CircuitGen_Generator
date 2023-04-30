#include <tuple>

#include "GeneticParameters.h"

void GeneticParameters::setPopulationSize(const int i_populationSize)
{
  d_populationSize = i_populationSize;
}

void GeneticParameters::setNumOfCycles(const int i_numOfCycles)
{
  d_numOfCycles = i_numOfCycles;
}

GeneticParameters::GeneticParameters(int i_inputs, int i_outputs) :
  d_inputs(i_inputs),
  d_outputs(i_outputs)
  {};

int GeneticParameters::getInputs() const
{
  return d_inputs;
}

void GeneticParameters::setInputs(int i_inputs)
{
  d_inputs = i_inputs;
}

int GeneticParameters::getOutputs() const
{
  return d_outputs;
}

void GeneticParameters::setOutputs(int i_outputs)
{
  d_outputs = i_outputs;
}

SelectionParameters GeneticParameters::getSelectionParameters() const
{
  return d_selectionParameters;
}

void GeneticParameters::setSelectionParameters(const SelectionParameters& i_sp)
{
  d_selectionParameters = i_sp;
}

RecombinationParameters GeneticParameters::getRecombinationParameters() const
{
  return d_recombinationParameters;
}

void GeneticParameters::setRecombinationParameters(const RecombinationParameters& i_rp)
{
  d_recombinationParameters = i_rp;
}

MutationParameters GeneticParameters::getMutationParameters() const
{
  return d_mutationParameters;
}

void GeneticParameters::setMutationParameters(const MutationParameters& i_mp)
{
  d_mutationParameters = i_mp;
}

int OrientedGraphParameters::getMaxLevel() const
{
  return d_maxLevel;
}

int OrientedGraphParameters::getMaxElements() const
{
  return d_maxElements;
}

bool OrientedGraphParameters::empty() const {
  return d_maxLevel == 0 && d_maxElements == 0;
}

TruthTableParameters::TruthTableParameters(int i_inputs, int i_outputs) :
  GeneticParameters(i_inputs, i_outputs)
  {}

TruthTableParameters::TruthTableParameters(const GeneticParameters& i_gp) :
  GeneticParameters(i_gp) {}

int TruthTableParameters::size() const
{
  return 1u << d_inputs;
}

bool TruthTableParameters::operator== (const TruthTableParameters& r)
{
  return std::tie(d_inputs, d_outputs, d_populationSize, d_numOfCycles, d_selectionParameters, d_recombinationParameters, d_mutationParameters, d_keyEndProcessIndex) == std::tie(r.d_inputs, r.d_outputs, r.d_populationSize, r.d_numOfCycles, r.d_selectionParameters, r.d_recombinationParameters, r.d_mutationParameters, r.d_keyEndProcessIndex);
}
