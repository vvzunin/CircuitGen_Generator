#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class EncoderDataBaseGenerator : public DataBaseGenerator {
public:
  EncoderDataBaseGenerator(const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  void generateDataBase(const GenerationParameters &i_param) override;
};