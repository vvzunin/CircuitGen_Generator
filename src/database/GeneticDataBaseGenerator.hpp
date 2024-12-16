#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class GeneticDataBaseGenerator : public DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief GeneticDataBaseGenerator
  /// @param i_parameters

  GeneticDataBaseGenerator(const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  /// @brief generateDataBase The method is designed to generate a
  /// database using genetic algorithms
  /// @param i_param An object of the Generation Parameters class containing
  /// parameters for generating a database using genetic algorithms
  /// */

  void generateDataBase(const GenerationParameters &i_param) override;
};