
#pragma once

#include <functional>

#include <settings/Settings.hpp>

#include "DataBaseGeneratorParameters.hpp"

/// class DataBaseGenerator
/// @param d_mainPath A string containing the path to the main database
/// directory. The default value is ".", which means the current working
/// directory
/// @param d_settings A smart pointer to an object of the Settings class
/// representing the settings for the database generator
/// @param d_parameters An object of the DataBase Generator Parameters class
/// containing parameters for generating a database. This object is used to
/// configure database generation
/// @param d_dirCount An integer value representing the number of directories
/// created during database generation
///
/// */

class DataBaseGenerator {
public:
  DataBaseGenerator(const DataBaseGeneratorParameters& i_parameters) :
    d_parameters(i_parameters) {};

  /// @brief generateType The generate Type method of the DataBase Generator
  /// class is responsible for generating a database of a certain type based on
  /// the passed parameters.
  /// @param i_gp An object of the DataBase Generator Parameters class
  /// containing parameters for generating a database
  /// @param parallel A flag indicating whether the generation should be
  /// performed in parallel. If set to true, generation will occur in parallel;
  /// otherwise, generation will be sequential
  /// @param createIdDirectories A flag indicating whether to create directories
  /// with IDs. If set to true, directories with IDs will be created, otherwise
  /// not.
  /// */

  void generateType(
      const DataBaseGeneratorParameters& i_gp,
      bool                               parallel            = true,
      bool                               createIdDirectories = true
  );

private:
  std::string               d_mainPath = ".";
  std::shared_ptr<Settings> d_settings =
      Settings::getInstance("DataBaseGenerator");
  DataBaseGeneratorParameters d_parameters;  // why we need this var?
  int                         d_dirCount = 0;

  /// @brief generateDataBaseFromRandomTruthTable The generate DataBase From
  /// Random Truth Table method of the DataBase Generator class is responsible
  /// for generating a database from random truth tables based on the passed
  /// parameters
  ///
  /// @param i_param An object of the Generation Parameters class containing
  /// parameters for generating a database
  ///
  /// */

  void generateDataBaseFromRandomTruthTable(const GenerationParameters& i_params
  );

  /// @brief generateDataBaseRandLevel The method is responsible for generating
  /// a database based on randomly generated levels.
  ///
  /// @param i_param An object of the Generation Parameters class containing
  /// parameters for generating a database
  /// */

  void generateDataBaseRandLevel(const GenerationParameters& i_params);

  /// @brief generateDataBaseRandLevelExperimental The method is intended for
  /// experimental database generation based on randomly generated levels using
  /// an optimized algorithm
  /// @param i_param An object of the Generation Parameters class containing
  /// parameters for generating a database
  /// */

  void generateDataBaseRandLevelExperimental(const GenerationParameters& i_param
  );

  /// @brief generateDataBaseNumOperations The method is designed to generate a
  /// database based on a given number of logical operations. Here is its
  /// description and parameters:
  /// @param i_param An object of the Generation Parameters class containing
  /// parameters for generating a database.
  /// */

  void generateDataBaseNumOperations(const GenerationParameters& i_param);

  /// @brief generateDataBaseGenetic The method is designed to generate a
  /// database using genetic algorithms
  /// @param i_param An object of the Generation Parameters class containing
  /// parameters for generating a database using genetic algorithms
  /// */

  void generateDataBaseGenetic(const GenerationParameters& i_param);

  /// @brief GenerateDataBaseSummator The method is designed to generate a
  /// database using adders
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating a database using adders
  /// */

  void GenerateDataBaseSummator(GenerationParameters& i_param);

  /// @brief GenerateDataBaseComparison The method is designed to generate a
  /// database using comparators.
  /// @param i_param An object of the Generation Parameters class containing
  /// parameters for generating a database using comparators
  /// */

  void GenerateDataBaseComparison(const GenerationParameters& i_param);

   /// @brief getGenerateMethod The method returns a function that corresponds to the specified database generation method. This method is used to dynamically select the generation method depending on the passed method name.
   /// @param i_methodName a string containing the name of the database generation method
   /// @return A function that accepts a Generation Parameters object and returns no value
   /// */

  void GenerateDataBaseEncoder(const GenerationParameters& i_param);

  /// @brief getGenerateMethod The method returns a function that corresponds to
  /// the specified database generation method. This method is used to
  /// dynamically select the generation method depending on the passed method
  /// name.
  /// @param i_methodName a string containing the name of the database
  /// generation method
  /// @return A function that accepts a Generation Parameters object and returns
  /// no value
  /// */

  std::function<void(const GenerationParameters&)> getGenerateMethod(
      const std::string& i_methodName
  );
};
