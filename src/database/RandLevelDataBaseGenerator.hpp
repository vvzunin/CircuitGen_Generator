#pragma once

#include "DataBaseGeneratorParameters.hpp"

#include "database/DataBaseGenerator.hpp"

class RandLevelDataBaseGenerator : public DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief RandLevelDataBaseGenerator
  /// @param i_parameters

  RandLevelDataBaseGenerator(const DataBaseGeneratorParameters &i_parameters) :
      DataBaseGenerator(i_parameters){};

  /// @brief generateDataBase The method is responsible for generating
  /// a database based on randomly generated levels.
  ///
  /// @param i_param An object of the Generation Parameters class containing
  /// parameters for generating a database
  /// */

  void generateDataBase(const GenerationParameters &i_param) override;
};