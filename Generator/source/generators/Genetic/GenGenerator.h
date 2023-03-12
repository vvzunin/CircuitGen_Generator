#pragma once

#include <string>
#include <utility>

#include "ChronosomeTypes.h"

template<typename Type, typename ParametersType>
class GeneticGenerator
{
public:
  GeneticGenerator(const ParametersType& i_parameters,
                   std::pair<int, int> i_inout,
                   const std::string& i_mainPath = "");
  std::vector<ChronosomeType<Type, ParametersType>> generate();

private:
  int d_inputs;
  int d_outputs;
  int d_numCross;
  std::vector<ChronosomeType<Type, ParametersType>> d_population;
  Settings d_settings;
  ParametersType d_parameters;
  std::string d_mainPath;
  int d_foldersCount = 0;

  void savePopulation(
    const std::vector<ChronosomeType<Type, ParametersType>>& i_population
  );
  void createPopulation();
  double endProcessFunction() const;
};
