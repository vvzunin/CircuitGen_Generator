#pragma once

#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <utility>

#include <additional/filesTools/FilesTools.hpp>
#include <baseStructures/Parser.hpp>
#include <baseStructures/truthTable/TruthTable.hpp>
#include <circuit/Circuit.hpp>
#include <generators/simple/SimpleGenerators.hpp>

#include "ChronosomeType.h"
#include "Mutations/Mutation.h"
#include "Recombination/Recombinations.h"
#include "Selections/Selections.h"

bool isNumber(const std::string& s) {
  for (auto c : s) {
    if (!std::isdigit(c))
      return false;
  }
  return true;
}

uint32_t getNumFolderFromString(const std::string& path) {
  size_t lastSlash = 0;
  for (size_t i = 0; i < path.size(); ++i) {
    if (path[i] == '_')
      lastSlash = i;
  }

  std::string lastDir = path.substr(lastSlash);

  if (!isNumber(lastDir))
    return 0;
  return std::stoi(lastDir);
}

/// @brief GeneticGenerator
/// Template class for generating genetic populations
/// @tparam Type Type of chromosome in a genetic population
/// @tparam ParametersType Type of parameters used to generate genetics
/// @param d_inputs Number of inputs for genetic population
/// @param d_outputs Number of outputs for a genetic population
/// @param d_numCross Number of intersections for genetic operations
/// @param d_population Genetic population
/// @param d_settings Pointer to a settings instance
/// @param d_parameters Parameters for genetic generation
/// @param d_mainPath Main path for storing data
/// @param d_foldersCount Data folder counter

template<typename Type, typename ParametersType>
class GeneticGenerator {
public:
  GeneticGenerator(
      const ParametersType&       i_parameters,
      std::pair<int32_t, int32_t> i_inout,
      const std::string&          i_mainPath
  ) :
    d_parameters(i_parameters),
    d_inputs(i_inout.first),
    d_outputs(i_inout.second),
    d_mainPath(i_mainPath) {
    std::string dataPath = "../." + d_settings->getDatasetPath()
                         + "/Genetic";  // TODO:: Make general function
    if (FilesTools::isDirectoryExists(dataPath)) {
      for (const auto& entry : std::filesystem::directory_iterator(dataPath)) {
        d_foldersCount =
            std::max(d_foldersCount, getNumFolderFromString(entry.path()) + 1);
      }
    } else {
      std::filesystem::create_directories(dataPath);
    }
  }

  /// @brief generate
  /// Generates a genetic population and carries out evolutionary processes
  /// The method creates an initial population, calculates the value of the
  /// process end function, and in a cycle performs the operations of
  /// recombination, mutation and selection until reaching criterion for
  /// completing a process or reaching the maximum number of cycles. On each
  /// iteration preserves the population. Upon completion, returns the final
  /// population.
  /// @return Final genetic population

  std::vector<ChronosomeType<Type, ParametersType>> generate() {
    createPopulation();
    double d = endProcessFunction();
    for (int32_t i = 0;
         (i < d_parameters.getNumOfCycles())
         && (endProcessFunction() < d_parameters.getKeyEndProcessIndex());
         ++i) {
      std::vector<ChronosomeType<Type, ParametersType>> newPopulation =
          RecombinationType<Type, ParametersType>(
              d_parameters.getRecombinationParameters(), d_population
          );
      std::vector<ChronosomeType<Type, ParametersType>> mutants =
          MutationType<Type, ParametersType>(
              d_parameters.getMutationParameters(), newPopulation
          );
      std::vector<ChronosomeType<Type, ParametersType>> d_population =
          SelectionType<Type, ParametersType>(
              d_parameters.getSelectionParameters(), mutants
          );
      savePopulation(d_population);
    }

    return d_population;
  }

private:
  uint32_t                                          d_inputs;
  uint32_t                                          d_outputs;
  uint32_t                                          d_numCross;
  std::vector<ChronosomeType<Type, ParametersType>> d_population;
  std::shared_ptr<Settings> d_settings = Settings::getInstance("GraphVertex");
  ParametersType            d_parameters;
  std::string               d_mainPath;
  uint32_t                  d_foldersCount = 0;

  void                      savePopulation(
                           const std::vector<ChronosomeType<Type, ParametersType>>& i_population
                       ) {
    for (const auto& ttp : i_population) {
      Type tt;
      tt = ttp.getChronosomeType();

      SimpleGenerators                              tftt;
      std::vector<std::pair<std::string, GraphPtr>> circs;
      circs.push_back(
          {d_settings->getGenerationMethodPrefix(GenerationTypes::Genetic)
               + std::to_string(d_foldersCount++),
           tftt.cnfFromTruthTable(tt, true)}
      );
      circs.push_back(
          {d_settings->getGenerationMethodPrefix(GenerationTypes::Genetic)
               + std::to_string(d_foldersCount++),
           tftt.cnfFromTruthTable(tt, false)}
      );

      for (const auto& nameexpr : circs) {
        std::string name  = nameexpr.first;
        GraphPtr    graph = nameexpr.second;
        // Parser pCNFT(expr);
        // pCNFT.parseAll();
        // GraphPtr graph = pCNFT.getGraph();
        Circuit     c(graph);
        c.setTable(tt);
        c.setPath(d_mainPath + "Genetic/");
        c.setCircuitName(name);
        c.generate();
      }
    }
  }

  /// @brief createPopulation
  /// Creates the initial genetic population
  /// The method clears the current population and then generates a new
  /// population of a given size. For each individual in the population, a
  /// random chromosome of Type is generated using passed parameters.
  /// Individuals are added to a population and then the population is
  /// maintained

  void createPopulation() {
    d_population.clear();
    for (int32_t i = 0; i < d_parameters.getPopulationSize(); ++i) {
      Type gen;
      gen.generateRandom(d_parameters);
      ChronosomeType<Type, ParametersType> ind =
          ChronosomeType<Type, ParametersType>(
              std::string("ind" + std::to_string(i)), gen
          );
      d_population.push_back(ind);
    }
    savePopulation(d_population);
  }

  /// @brief endProcessFunction
  /// Calculates the value of the process termination function
  /// The method goes through the entire current population and calculates the
  /// maximum value adaptation index among all individuals. This value is used
  /// to determine completion of the process of evolution of the genetic
  /// population.
  /// @return The maximum value of the adaptation index in the population

  double endProcessFunction() const {
    double max = 0;
    for (const auto& i : d_population) {
      max = std::max(max, i.getAdaptationIndex());
    }

    return max;
  }
};

// template<typename Type, typename ParametersType>
// GeneticGenerator<Type, ParametersType>::GeneticGenerator(
//     const ParametersType& i_parameters,
//     std::pair<int, int> i_inout,
//     const std::string& i_mainPath) :
//     d_parameters(i_parameters),
//     d_inputs(i_inout.first),
//     d_outputs(i_inout.second),
//     d_mainPath(i_mainPath)
// {
//     std::string dataPath = d_settings->getDatasetPath() + "/Genetic";//TODO::
//     Make general function if (FilesTools::isDirectoryExists(dataPath))
//     {
//         for (const auto& entry :
//         std::filesystem::directory_iterator(dataPath))
//         {
//             d_foldersCount = std::max(d_foldersCount,
//             getNumFolderFromString(entry.path()) + 1);
//         }
//     }
//     else
//     {
//         std::cout << "Folder for data not exists, you need to create
//         Directory \""
//             << dataPath << "\"" << std::endl;
//         std::exit(0);
//     }
// }

// template<typename Type, typename ParametersType>
// void GeneticGenerator<Type, ParametersType>::savePopulation(
//     const std::vector<ChronosomeType<Type, ParametersType>>& i_population
// )

// template<typename Type, typename ParametersType>
// void GeneticGenerator<Type, ParametersType>::createPopulation()

// template<typename Type, typename ParametersType>
// std::vector<ChronosomeType<Type, ParametersType>> GeneticGenerator<Type,
// ParametersType>::generate()

// template<typename Type, typename ParametersType>
// double GeneticGenerator<Type, ParametersType>::endProcessFunction() const
// {
//     double max = 0;
//     for (const auto& i : d_population)
//     {
//         max = std::max(max, i.getAdaptationIndex());
//     }

//     return max;
// }
