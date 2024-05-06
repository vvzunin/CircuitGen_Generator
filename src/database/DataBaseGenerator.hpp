
#pragma once

#include <functional>
#include <mutex>
#include <string>
#include <vector>

#include <additional/RandomGeneratorWithSeed.hpp>
#include <CircuitGenGenerator/OrientedGraph.hpp>
#include <settings/Settings.hpp>

#include "DataBaseGeneratorParameters.hpp"

using ResultGraph = std::pair<std::string, std::vector<GraphPtr>>;
using ResultPath  = std::pair<std::string, std::vector<std::string>>;

enum ReturnType {
  DEFAULT,
  GRAPH,
  PATH,
  FUNCTION
};

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
/// @param d_randGenerator Random number generator with seed

class DataBaseGenerator {
public:
  /// @todo: description default constructor
  /// @brief DataBaseGenerator
  /// @param i_parameters

  DataBaseGenerator(const DataBaseGeneratorParameters& i_parameters) :
    d_parameters(i_parameters) {};

  /// @brief generateTypeForGraph The generate Type method of the DataBase
  /// Generator class is responsible for generating a database of a certain type
  /// based on the passed parameters.
  /// @param i_gp An object of the DataBase Generator Parameters class
  /// containing parameters for generating a database
  /// @param parallel A flag indicating whether the generation should be
  /// performed in parallel. If set to true, generation will occur in parallel;
  /// otherwise, generation will be sequential
  /// @param createIdDirectories A flag indicating whether to create directories
  /// with IDs. If set to true, directories with IDs will be created, otherwise
  /// not.
  ///

  ResultGraph generateTypeForGraph(
      const DataBaseGeneratorParameters& i_gp,
      bool                               parallel            = true,
      bool                               createIdDirectories = true
  );

  ResultPath generateTypeForPath(
      const DataBaseGeneratorParameters& i_gp,
      bool                               parallel            = true,
      bool                               createIdDirectories = true
  );

  void generateTypeDefault(
      const DataBaseGeneratorParameters& i_gp,
      bool                               parallel            = true,
      bool                               createIdDirectories = true
  );

private:
  std::vector<GraphPtr>     d_generatedGraphs;
  std::vector<std::string>  d_generatedGraphsNames;
  std::mutex                d_resWrite;

  std::string               d_mainPath = ".";
  std::shared_ptr<Settings> d_settings =
      Settings::getInstance("DataBaseGenerator");
  DataBaseGeneratorParameters d_parameters;  // why we need this var?
  int                         d_dirCount = 0;

  /// @brief generateDataBaseFromRandomTruthTable The generate DataBase From
  /// Random Truth Table method of the DataBase Generator class is responsible
  /// for generating a database from random truth tables based on the passed
  /// parameters
  /// @param i_param An object of the Generation Parameters class containing
  /// parameters for generating a database
  ///
  /// */

  void                        runGeneratorByDefault(
                             const DataBaseGeneratorParameters& i_gp,
                             bool                               parallel = true,
                             bool                               createIdDirectories = true
                         );

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

  /// @brief generateDataBaseGenetic
  /// Generates a database using genetic algorithms
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating a database using genetic algorithms

  void generateDataBaseGenetic(const GenerationParameters& i_param);

  /// @brief generateDataBaseSummator
  /// Generates a database representing a summator circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the summator circuit database

  void generateDataBaseSummator(const GenerationParameters& i_param);

  /// @brief generateDataBaseComparison
  /// Generates a database representing a comparison circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the comparison circuit database

  void generateDataBaseComparison(const GenerationParameters& i_param);

  /// @brief generateDataBaseEncoder
  /// Generates a database representing a comparison circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the comparison circuit database

  void generateDataBaseEncoder(const GenerationParameters& i_param);

  /// @brief generateDataBaseParity
  /// Generates a database representing a parity circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the parity circuit database

  void generateDataBaseParity(const GenerationParameters& i_param);

  /// @brief generateDataBaseSubtractor
  /// Generates a database representing a subtractor circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the subtractor circuit database

  void generateDataBaseSubtractor(const GenerationParameters& i_param);

  /// @brief generateDataBaseMultiplexer
  /// Generates a database representing a multiplexer circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the multiplexer circuit database

  void generateDataBaseMultiplexer(const GenerationParameters& i_param);

  /// @brief generateDataBaseDemultiplexer
  /// Generates a database representing a demultiplexer circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the demultiplexer circuit database

  void generateDataBaseDemultiplexer(const GenerationParameters& i_param);

  /// @brief generateDataBaseMultiplier
  /// Generates a database representing a multiplier circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the multiplier circuit database

  void generateDataBaseMultiplier(const GenerationParameters& i_param);

  /// @brief generateDataBaseDecoder
  /// Generates a database representing a decoder circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the decoder circuit database

  void generateDataBaseDecoder(const GenerationParameters& i_param);

  /// @brief generateDataBaseALU
  /// Generates a database representing an Arithmetic Logic Unit (ALU) circuit
  /// @param i_param An object of the GenerationParameters class containing
  /// parameters for generating the ALU circuit database

  void generateDataBaseALU(const GenerationParameters& i_param);

  /// @brief getGenerateMethod
  /// Retrieves a method for generating a database based on the provided
  /// generation type
  /// @param i_methodType The type of generation method to retrieve
  /// @return Function pointer to the corresponding database generation method

  std::function<void(const GenerationParameters&)> getGenerateMethod(
      const GenerationTypes i_methodType
  );

  void                    addDataToReturn(GraphPtr graph);

  RandomGeneratorWithSeed d_randGenerator;

  ReturnType              d_type = ReturnType::DEFAULT;
};
