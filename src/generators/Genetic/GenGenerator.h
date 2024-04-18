#pragma once

#include <string>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <filesystem>
#include <string>
#include <utility>
#include <iostream>

#include <baseStructures/truthTable/TruthTable.hpp>
#include <generators/simple/SimpleGenerators.hpp>
#include <baseStructures/Parser.hpp>
#include <circuit/Circuit.hpp>
#include <additional/filesTools/FilesTools.hpp>
#include "ChronosomeType.h"
#include "Recombination/Recombinations.h"
#include "Selections/Selections.h"
#include "Mutations/Mutation.h"

bool isNumber(const std::string& s)
{
  for (auto c : s)
  {
    if (!std::isdigit(c))
      return false;
  }
  return true;
}

int getNumFolderFromString(const std::string& path)
{
  int lastSlash = 0;
  for (int i = 0; i < path.size(); ++i)
  {
    if (path[i] == '_')
      lastSlash = i;
  }
  std::string lastDir = path.substr(lastSlash);
  int res = 0;
  if (!isNumber(lastDir))
    return 0;
  return std::stoi(lastDir);
}

template<typename Type, typename ParametersType>
class GeneticGenerator
{
public:
  GeneticGenerator(
    const ParametersType& i_parameters,
    std::pair<int, int> i_inout,
    const std::string& i_mainPath) :
    d_parameters(i_parameters),
    d_inputs(i_inout.first),
    d_outputs(i_inout.second),
    d_mainPath(i_mainPath)
    {
        std::string dataPath = "../." + d_settings->getDatasetPath() + "/Genetic";//TODO:: Make general function
        if (FilesTools::isDirectoryExists(dataPath))
        {
            for (const auto& entry : std::filesystem::directory_iterator(dataPath))
            {
                d_foldersCount = std::max(d_foldersCount, getNumFolderFromString(entry.path()) + 1);
            }
        }
        else
        {
            std::cout << "Folder for data not exists, you need to create Directory \""
                << dataPath << "\"" << std::endl;
            std::exit(0);
        }
    }
  std::vector<ChronosomeType<Type, ParametersType>> generate()
  {
    createPopulation();
    double d = endProcessFunction();
    for (int i = 0; (i < d_parameters.getNumOfCycles()) && (endProcessFunction() < d_parameters.getKeyEndProcessIndex()); ++i)
    {
        std::vector<ChronosomeType<Type, ParametersType>> newPopulation = RecombinationType<Type, ParametersType>(d_parameters.getRecombinationParameters(), d_population);
        std::vector<ChronosomeType<Type, ParametersType>> mutants = MutationType<Type, ParametersType>(d_parameters.getMutationParameters(), newPopulation);
        std::vector<ChronosomeType<Type, ParametersType>> d_population = SelectionType<Type, ParametersType>(d_parameters.getSelectionParameters(), mutants);
        savePopulation(d_population);
    }

    return d_population;
  }

private:
  int d_inputs;
  int d_outputs;
  int d_numCross;
  std::vector<ChronosomeType<Type, ParametersType>> d_population;
  std::shared_ptr<Settings> d_settings = Settings::getInstance("GraphVertex");
  ParametersType d_parameters;
  std::string d_mainPath;
  int d_foldersCount = 0;

  void savePopulation(
    const std::vector<ChronosomeType<Type, ParametersType>>& i_population
  )
    {
        for (const auto& ttp : i_population)
        {
            Type tt;
            tt = ttp.getChronosomeType();

            SimpleGenerators tftt;
            std::vector<std::pair<std::string, GraphPtr>> circs;
            circs.push_back({ d_settings->getGenerationMethodPrefix(GenerationTypes::Genetic) + std::to_string(d_foldersCount++), tftt.cnfFromTruthTable(tt, true) });
            circs.push_back({ d_settings->getGenerationMethodPrefix(GenerationTypes::Genetic) + std::to_string(d_foldersCount++), tftt.cnfFromTruthTable(tt, false) });

            for (const auto& nameexpr : circs)
            {
                std::string name = nameexpr.first;
                GraphPtr graph = nameexpr.second;
                // Parser pCNFT(expr);
                // pCNFT.parseAll();
                // GraphPtr graph = pCNFT.getGraph();
                Circuit c(graph);
                c.setTable(tt);
                c.setPath(d_mainPath + "Genetic/");
                c.setCircuitName(name);
                c.generate();
            }
        }
    }
  void createPopulation()
  {
    d_population.clear();
    for (int i = 0; i < d_parameters.getPopulationSize(); ++i)
    {
        Type gen;
        gen.generateRandom(d_parameters);
        ChronosomeType<Type, ParametersType> ind = ChronosomeType<Type, ParametersType>(std::string("ind" + std::to_string(i)), gen);
        d_population.push_back(ind);
        
    }
    savePopulation(d_population);
  }
  double endProcessFunction() const
  {
    double max = 0;
    for (const auto& i : d_population)
    {
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
//     std::string dataPath = d_settings->getDatasetPath() + "/Genetic";//TODO:: Make general function
//     if (FilesTools::isDirectoryExists(dataPath))
//     {
//         for (const auto& entry : std::filesystem::directory_iterator(dataPath))
//         {
//             d_foldersCount = std::max(d_foldersCount, getNumFolderFromString(entry.path()) + 1);
//         }
//     }
//     else
//     {
//         std::cout << "Folder for data not exists, you need to create Directory \""
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
// std::vector<ChronosomeType<Type, ParametersType>> GeneticGenerator<Type, ParametersType>::generate()


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
