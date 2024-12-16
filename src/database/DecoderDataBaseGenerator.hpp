#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class DecoderDataBaseGenerator : public DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief DecoderDataBaseGenerator
  /// @param i_parameters

  DecoderDataBaseGenerator(const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  /// @brief generateDataBase
  /// Generates a database representing a decoder circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the decoder circuit database

  void generateDataBase(const GenerationParameters &i_param) override;
};