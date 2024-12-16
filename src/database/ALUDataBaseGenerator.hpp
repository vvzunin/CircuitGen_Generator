#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class ALUDataBaseGenerator : public DataBaseGenerator {
public:
  ALUDataBaseGenerator(const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  void generateDataBase(const GenerationParameters &i_param) override;
};