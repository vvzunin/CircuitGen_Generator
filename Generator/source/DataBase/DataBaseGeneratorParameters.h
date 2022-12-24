#pragma once

class DataBaseGeneratorParameters //TODO: maybe it need heritance from GenerationParameters?
{
public:

private:
  int d_minInputs = 0;
  int d_maxInputs = 0;
  int d_minOutputs = 0;
  int d_maxOutputs = 0;
  int d_eachIteration = 0;
  GeneretionTypes d_generationTypes = fromRandomTruthTable;
  GenerationParameters d_generationParameters;
}
