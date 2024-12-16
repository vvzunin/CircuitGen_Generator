#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class FromRandomTruthTableDataBaseGenerator : public DataBaseGenerator {
public:
  FromRandomTruthTableDataBaseGenerator(
      const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  void generateDataBase(const GenerationParameters &i_param) override;
};