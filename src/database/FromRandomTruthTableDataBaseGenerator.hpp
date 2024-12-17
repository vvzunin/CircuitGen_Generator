#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class FromRandomTruthTableDataBaseGenerator : public DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief FromRandomTruthTableDataBaseGenerator
  /// @param i_parameters

  FromRandomTruthTableDataBaseGenerator(
      const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  /// @brief generateDataBase The generate DataBase From
  /// Random Truth Table method of the DataBase Generator class is responsible
  /// for generating a database from random truth tables based on the passed
  /// parameters
  /// @param i_param An object of the Generation Parameters class containing
  /// parameters for generating a database
  ///
  /// */

  void generateDataBase(const GenerationParameters &i_param) override;
};