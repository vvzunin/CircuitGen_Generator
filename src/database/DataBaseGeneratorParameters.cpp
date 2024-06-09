#include "DataBaseGeneratorParameters.hpp"

DataBaseGeneratorParameters::DataBaseGeneratorParameters(
    uint32_t             i_minInputs,
    uint32_t             i_maxInputs,
    uint32_t             i_minOutputs,
    uint32_t             i_maxOutputs,
    uint32_t             i_eachIteration,
    GenerationTypes      i_gt,
    GenerationParameters i_gp
) :
  d_minInputs(i_minInputs),
  d_maxInputs(i_maxInputs),
  d_minOutputs(i_minOutputs),
  d_maxOutputs(i_maxOutputs),
  d_eachIteration(i_eachIteration),
  d_generationTypes(i_gt),
  d_generationParameters(i_gp) {};

void DataBaseGeneratorParameters::setInputs(uint32_t i_inputs) {
  d_generationParameters.setInputs(i_inputs);
}

void DataBaseGeneratorParameters::setOutputs(uint32_t i_outputs) {
  d_generationParameters.setOutputs(i_outputs);
}

void DataBaseGeneratorParameters::setIteration(uint32_t i_iteration) {
  d_generationParameters.setIteration(i_iteration);
}

void DataBaseGeneratorParameters::setName(const std::string& i_name) {
  d_generationParameters.setName(i_name);
}

uint32_t DataBaseGeneratorParameters::getMinInputs() const {
  return d_minInputs;
}

uint32_t DataBaseGeneratorParameters::getMaxInputs() const {
  return d_maxInputs;
}

uint32_t DataBaseGeneratorParameters::getMinOutputs() const {
  return d_minOutputs;
}

uint32_t DataBaseGeneratorParameters::getMaxOutputs() const {
  return d_maxOutputs;
}

uint32_t DataBaseGeneratorParameters::getEachIteration() const {
  return d_eachIteration;
}

GenerationParameters DataBaseGeneratorParameters::getGenerationParameters(
) const {
  return d_generationParameters;
}

GenerationTypes DataBaseGeneratorParameters::getGenerationType() const {
  return d_generationTypes;
}