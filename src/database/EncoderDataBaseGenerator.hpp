#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class EncoderDataBaseGenerator : public DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief EncoderDataBaseGenerator
  /// @param i_parameters

  EncoderDataBaseGenerator(const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  /// @brief generateDataBase
  /// Generates a database representing a comparison circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the comparison circuit database

  void generateDataBase(const GenerationParameters &i_param) override;
};