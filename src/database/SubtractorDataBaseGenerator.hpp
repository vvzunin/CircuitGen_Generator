#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class SubtractorDataBaseGenerator : public DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief SubtractorDataBaseGenerator
  /// @param i_parameters

  SubtractorDataBaseGenerator(const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  /// @brief generateDataBase
  /// Generates a database representing a subtractor circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the subtractor circuit database

  void generateDataBase(const GenerationParameters &i_param) override;
};