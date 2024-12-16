#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class DemultiplexerDataBaseGenerator : public DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief DemultiplexerDataBaseGenerator
  /// @param i_parameters

  DemultiplexerDataBaseGenerator(
      const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  /// @brief generateDataBase
  /// Generates a database representing a demultiplexer circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the demultiplexer circuit database

  void generateDataBase(const GenerationParameters &i_param) override;
};