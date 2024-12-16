#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class ComparisonDataBaseGenerator : public DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief ComparisonDataBaseGenerator
  /// @param i_parameters

  ComparisonDataBaseGenerator(const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  /// @brief generateDataBase
  /// Generates a database representing a comparison circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the comparison circuit database

  void generateDataBase(const GenerationParameters &i_param) override;
};