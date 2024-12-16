#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class ParityDataBaseGenerator : public DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief ParityDataBaseGenerator
  /// @param i_parameters

  ParityDataBaseGenerator(const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  /// @brief generateDataBase
  /// Generates a database representing a parity circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the parity circuit database

  void generateDataBase(const GenerationParameters &i_param) override;
};