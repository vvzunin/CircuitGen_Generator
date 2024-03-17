#pragma once

#include <functional>

#include "DataBaseGeneratorParameters.h"
#include <settings/Settings.h>

class DataBaseGenerator
{
public:
    DataBaseGenerator(const DataBaseGeneratorParameters &i_parameters) : d_parameters(i_parameters){};
    void generateType(const DataBaseGeneratorParameters &i_gp,
                      bool parallel = true, bool createIdDirectories = true);

private:
    std::string d_mainPath = ".";
    std::shared_ptr<Settings> d_settings = Settings::getInstance("DataBaseGenerator");
    DataBaseGeneratorParameters d_parameters; // why we need this var?
    int d_dirCount = 0;

    void generateDataBaseFromRandomTruthTable(const GenerationParameters &i_params);
    void generateDataBaseRandLevel(const GenerationParameters &i_params);
    void generateDataBaseRandLevelExperimental(const GenerationParameters &i_param);
    void generateDataBaseNumOperations(const GenerationParameters &i_param);
    void generateDataBaseGenetic(const GenerationParameters &i_param);
    void GenerateDataBaseSummator(GenerationParameters &i_param);
    void GenerateDataBaseComparison(const GenerationParameters &i_param);
    void GenerateDataBaseEncoder(const GenerationParameters &i_param);
    std::function<void(const GenerationParameters &)> getGenerateMethod(const std::string &i_methodName);
};
