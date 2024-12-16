#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class ParityDataBaseGenerator : public DataBaseGenerator {
public:
  ParityDataBaseGenerator(const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  void generateDataBase(const GenerationParameters &i_param) override;
};