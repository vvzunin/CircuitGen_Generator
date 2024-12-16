#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class NumOperationsDataBaseGenerator : public DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief NumOperationsDataBaseGenerator
  /// @param i_parameters

  NumOperationsDataBaseGenerator(
      const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  /// @brief generateDataBase The method is designed to generate a
  /// database based on a given number of logical operations. Here is its
  /// description and parameters:
  /// @param i_param An object of the Generation Parameters class containing
  /// parameters for generating a database.
  /// */

  void generateDataBase(const GenerationParameters &i_param) override;
};