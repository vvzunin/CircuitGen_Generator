#pragma once

class DataBaseGenerator
{
public:
  DataBaseGenerator(const DataBaseGeneratorParameters& i_parameters):
    d_parameters(i_parameters) {};
  void GenerateType(const DataBaseGeneratorParameters& i_gp,
                    bool parallel = true);


private:
  std::string d_mainPath;
  Settings d_settings readSettings();
  DataBaseGeneratorParameters d_parameters; // why we need this var?
  int d_dirCount = 0;

  void getGenerateMethod(const std::string& i_methodName);
  void GenerateDataBaseFromRandomTruthTable(const GenerationParameters& i_params);
  void GenerateDataBaseRandLevel(const GeneratiorParameters& i_params);
  void GenerateDataBaseNumOperations(const GenerationParameters& i_param);
  void GenerateDataBaseGenetic(const GenerationParameters& i_param);
}
