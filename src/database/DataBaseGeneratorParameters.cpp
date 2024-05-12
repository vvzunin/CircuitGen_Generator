#pragma once

#include <string>
#include "DataBaseGeneratorParameters.hpp"

DataBaseGeneratorParameters::DataBaseGeneratorParameters(
    int                  i_minInputs,
    int                  i_maxInputs,
    int                  i_minOutputs,
    int                  i_maxOutputs,
    int                  i_eachIteration,
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

std::string DataBaseGeneratorParameters::getDataForLogging() const {
	std::vector<std::string> result = {};
	result.push_back(std::string("minInputs: ") + std::to_string(d_minInputs));
	result.push_back(std::string("maxInputs: ") + std::to_string(d_maxInputs));
	result.push_back(std::string("minOutputs: ") + std::to_string(d_minOutputs));
	result.push_back(std::string("maxOutputs: ") + std::to_string(d_maxOutputs));
	result.push_back(std::string("eachIteration: ") + std::to_string(d_eachIteration));
	result.push_back(std::string("generationParameters: { ") + d_generationParameters.getDataForLogging() + " }");
	std::string concat = "";
	for(const auto& s: result)
		if (concat.empty())
			concat += s;
		else
			concat += "; " + s;
	return concat;
}


void DataBaseGeneratorParameters::setInputs(int i_inputs) {
  d_generationParameters.setInputs(i_inputs);
}

void DataBaseGeneratorParameters::setOutputs(int i_outputs) {
  d_generationParameters.setOutputs(i_outputs);
}

void DataBaseGeneratorParameters::setIteration(int i_iteration) {
  d_generationParameters.setIteration(i_iteration);
}

void DataBaseGeneratorParameters::setName(const std::string& i_name) {
  d_generationParameters.setName(i_name);
}

int DataBaseGeneratorParameters::getMinInputs() const {
  return d_minInputs;
}

int DataBaseGeneratorParameters::getMaxInputs() const {
  return d_maxInputs;
}

int DataBaseGeneratorParameters::getMinOutputs() const {
  return d_minOutputs;
}

int DataBaseGeneratorParameters::getMaxOutputs() const {
  return d_maxOutputs;
}

int DataBaseGeneratorParameters::getEachIteration() const {
  return d_eachIteration;
}

GenerationParameters DataBaseGeneratorParameters::getGenerationParameters(
) const {
  return d_generationParameters;
}

GenerationTypes DataBaseGeneratorParameters::getGenerationType() const {
  return d_generationTypes;
}
