
#pragma once

#include <functional>
#include <mutex>
#include <string>
#include <vector>

#include <additional/RandomGeneratorWithSeed.hpp>
#include <baseStructures/truthTable/TruthTable.hpp>
#include <CircuitGenGraph/OrientedGraph.hpp>
#include <settings/Settings.hpp>

#include "DataBaseGeneratorParameters.hpp"

using ResultGraph = std::pair<std::string, std::vector<GraphPtr>>;
using ResultPath = std::pair<std::string, std::vector<std::string>>;

enum ReturnType { DEFAULT, GRAPH, PATH, FUNCTION };

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

  DataBaseGenerator(const DataBaseGeneratorParameters &i_parameters) :
      d_parameters(i_parameters){};

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

  ResultGraph generateTypeForGraph(const DataBaseGeneratorParameters &i_gp,
                                   uint8_t parallel = 1,
                                   bool createIdDirectories = true);

  ResultPath generateTypeForPath(const DataBaseGeneratorParameters &i_gp,
                                 uint8_t parallel = 1,
                                 bool createIdDirectories = true);

  void generateTypeDefault(const DataBaseGeneratorParameters &i_gp,
                           uint8_t parallel = 1,
                           bool createIdDirectories = true);

protected:
  virtual void generateDataBase(const GenerationParameters &i_param){};

  void processCircuit(std::shared_ptr<OrientedGraph> graph,
                      const TruthTable &tt, const GenerationParameters &i_param,
                      const std::string name = "");

  void processCircuit(std::shared_ptr<OrientedGraph> graph,
                      const GenerationParameters &i_param,
                      const std::string name = "");

  std::string d_mainPath = ".";

private:
  std::vector<GraphPtr> d_generatedGraphs;
  std::vector<std::string> d_generatedGraphsNames;
  std::mutex d_resWrite;

  std::shared_ptr<Settings> d_settings =
      Settings::getInstance("DataBaseGenerator");
  DataBaseGeneratorParameters d_parameters; // why we need this var?
  int32_t d_dirCount = 0;

  void runGeneratorByDefault(const DataBaseGeneratorParameters &i_gp,
                             uint8_t parallel = 1,
                             bool createIdDirectories = true);

  /// @brief getGenerateMethod
  /// Retrieves a method for generating a database based on the provided
  /// generation type
  /// @param i_methodType The type of generation method to retrieve
  /// @return Function pointer to the corresponding database generation method

  std::function<void(const GenerationParameters &)>
  getGenerateMethod(const GenerationTypes i_methodType);

  void addDataToReturn(GraphPtr graph);

  RandomGeneratorWithSeed d_randGenerator;

  ReturnType d_type = ReturnType::DEFAULT;
};
