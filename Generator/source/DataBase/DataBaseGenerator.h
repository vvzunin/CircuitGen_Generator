#pragma once

#include <functional>

#include "DataBaseGeneratorParameters.h"
#include "../Settings.h"

class DataBaseGenerator
{
public:
  DataBaseGenerator(const DataBaseGeneratorParameters& i_parameters):
    d_parameters(i_parameters) 
  {
    d_settings.loadSettings();
  };
  void generateType(const DataBaseGeneratorParameters& i_gp,
                    bool parallel = true);


private:
  std::string d_mainPath;
  Settings d_settings;
  DataBaseGeneratorParameters d_parameters; // why we need this var?
  int d_dirCount = 0;

  void generateDataBaseFromRandomTruthTable(const GenerationParameters& i_params);
  void generateDataBaseRandLevel(const GenerationParameters& i_params);
  void generateDataBaseNumOperations(const GenerationParameters& i_param);
  void generateDataBaseGenetic(GenerationParameters i_param);
  std::function<void(const GenerationParameters&)> getGenerateMethod(const std::string& i_methodName);
};
