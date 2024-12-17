#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class RandLevelExperimentalDataBaseGenerator : public DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief RandLevelExperimentalDataBaseGenerator
  /// @param i_parameters

  RandLevelExperimentalDataBaseGenerator(
      const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  /// @brief generateDataBase The method is intended for
  /// experimental database generation based on randomly generated levels using
  /// an optimized algorithm
  /// @param i_param An object of the Generation Parameters class containing
  /// parameters for generating a database
  /// */

  void generateDataBase(const GenerationParameters &i_param) override;
};