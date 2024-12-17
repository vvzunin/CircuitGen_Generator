#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class ALUDataBaseGenerator : public DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief ALUDataBaseGenerator
  /// @param i_parameters

  ALUDataBaseGenerator(const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  /// @brief generateDataBase
  /// Generates a database representing an Arithmetic Logic Unit (ALU) circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the ALU circuit database

  void generateDataBase(const GenerationParameters &i_param) override;
};