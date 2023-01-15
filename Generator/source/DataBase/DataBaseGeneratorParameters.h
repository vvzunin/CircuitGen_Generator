#pragma once
#include "../Generators/GenerationParameters.h"
#include "../Settings.h"

enum GenerationTypes
{
  FromRandomTruthTable,
  RandLevel,
  NumOperation,
  Genetic
};

class DataBaseGeneratorParameters //TODO: maybe it need heritance from GenerationParameters?
{
public:
  DataBaseGeneratorParameters(
    int i_minInputs,
    int i_maxInputs,
    int i_minOutputs,
    int i_maxOutputs,
    int i_eachIteration,
    GenerationTypes i_gt,
    GenerationParameters i_gp
  ) : d_minInputs(i_minInputs),
      d_maxInputs(i_maxInputs),
      d_minOutputs(i_minOutputs),
      d_maxOutputs(i_maxOutputs),
      d_eachIteration(i_eachIteration),
      d_generationTypes(i_gt),
      d_generationParameters(i_gp) {};

  void setInputs(int i_inputs)
  {
    d_generationParameters.setInputs(i_inputs);
  }

  void setOutputs(int i_outputs)
  {
    d_generationParameters.setOutputs(i_outputs);
  }

  void setIteration(int i_iteration)
  {
    d_generationParameters.setIteration(i_iteration);
  }

  void setName(const std::string& i_name)
  {
    d_generationParameters.setName(i_name);
  }

  int getMinInputs() const
  {
    return d_minInputs;
  }

  int getMaxInputs() const
  {
    return d_maxInputs;
  }

  int getMinOutputs() const
  {
    return d_minOutputs;
  }

  int getMaxOutputs() const
  {
    return d_maxOutputs;
  }

  int getEachIteration() const
  {
    return d_eachIteration;
  }
  
  GenerationParameters getGenerationParameters() const
  {
    return d_generationParameters;
  }

  std::string getGenerationTypeString() const
  {
    if (d_generationTypes == GenerationTypes::FromRandomTruthTable)
      return "FromRandomTruthTable";
    if (d_generationTypes == GenerationTypes::RandLevel)
      return "RandLevel";
    if (d_generationTypes == GenerationTypes::NumOperation)
      return "NumOperation";
    if (d_generationTypes == GenerationTypes::Genetic)
      return "Genetic";
    return "FromRandomTruthTable";
  }

private:
  int d_minInputs = 0;
  int d_maxInputs = 0;
  int d_minOutputs = 0;
  int d_maxOutputs = 0;
  int d_eachIteration = 0;
  GenerationTypes d_generationTypes = GenerationTypes::FromRandomTruthTable;
  GenerationParameters d_generationParameters;
};
