
#pragma once

#include <functional>

#include <settings/Settings.hpp>

#include "DataBaseGeneratorParameters.hpp"

class DataBaseGenerator {
public:
  DataBaseGenerator(const DataBaseGeneratorParameters& i_parameters) :
    d_parameters(i_parameters) {};
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

  void generateDataBaseFromRandomTruthTable(const GenerationParameters& i_params
  );
  void generateDataBaseRandLevel(const GenerationParameters& i_params);
  void generateDataBaseRandLevelExperimental(const GenerationParameters& i_param
  );
  void generateDataBaseNumOperations(const GenerationParameters& i_param);
  void generateDataBaseGenetic(const GenerationParameters& i_param);
  void generateDataBaseSummator(const GenerationParameters& i_param);
  void generateDataBaseComparison(const GenerationParameters& i_param);
  void generateDataBaseEncoder(const GenerationParameters& i_param);
  void generateDataBaseParity(const GenerationParameters& i_param);
  void generateDataBaseSubtractor(const GenerationParameters& i_param);
  void generateDataBaseMultiplexer(const GenerationParameters& i_param);
  void generateDataBaseDemultiplexer(const GenerationParameters& i_param);
  void generateDataBaseMultiplier(const GenerationParameters& i_param);
  void generateDataBaseDecoder(const GenerationParameters& i_param);
  void generateDataBaseALU(const GenerationParameters& i_param);
  std::function<void(const GenerationParameters&)> getGenerateMethod(
      const GenerationTypes i_methodType
  );
};
