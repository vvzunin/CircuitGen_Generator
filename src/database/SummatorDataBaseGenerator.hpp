#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class SummatorDataBaseGenerator : public DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief SummatorDataBaseGenerator
  /// @param i_parameters

  SummatorDataBaseGenerator(const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  /// @brief generateDataBase
  /// Generates a database representing a summator circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the summator circuit database

  void generateDataBase(const GenerationParameters &i_param) override;
};