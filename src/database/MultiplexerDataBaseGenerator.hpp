#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class MultiplexerDataBaseGenerator : public DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief MultiplexerDataBaseGenerator
  /// @param i_parameters

  MultiplexerDataBaseGenerator(
      const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  /// @brief generateDataBase
  /// Generates a database representing a multiplexer circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the multiplexer circuit database

  void generateDataBase(const GenerationParameters &i_param) override;
};