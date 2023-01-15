#include <filesystem>

#include "../Generators/TruthTable.h"
#include "../FilesTools.h"
#include "DataBaseGenerator.h"


void DataBaseGenerator::generateType(
  const DataBaseGeneratorParameters& i_dbgp,
  bool parallel
)
{

  std::string s = i_dbgp.getGenerationTypeString();
  std::function<void(const GenerationParameters&)> generator = getGenerateMethod(s);

  std::string dir = d_settings.getDatasetPath() + "/" + s;

  d_dirCount = 0;

  if (std::filesystem::is_directory(dir))
  {
    for (const auto item : FilesTools::getDirectories(dir))
    {
      std::string s0 = item;
      auto pos = s0.find(d_settings.getGenerationMethodPrefix(s));
      s.replace(pos, d_settings.getGenerationMethodPrefix(s).size(), "");
      
      auto jk = s0.find("_"); // TODO: maybe it need last find of "_"?
      if (jk == std::string::npos)
        jk = s0.size();
      
      s0 = s0.substr(0, jk);

      d_dirCount = std::max(d_dirCount, std::stoi(s0) + 1); // TODO: in general code n is int32, is it really need?
    }
  }

  for (int i = i_dbgp.getMinInputs(); i <= i_dbgp.getMaxInputs(); ++i)
  {
    for (int j = i_dbgp.getMinOutputs(); j <= i_dbgp.getMaxOutputs(); ++j)
    {
      d_parameters.setInputs(i);
      d_parameters.setOutputs(j);

      if (parallel)
      {
        exit(1); //TODO: write to multithreading
      }
      else
      {
        for (int tt = 0; tt < i_dbgp.getEachIteration(); ++tt)
        {
          d_parameters.setIteration(tt);
          d_parameters.setName(d_settings.getGenerationMethodPrefix(s) + std::to_string(d_dirCount + tt));
          generator(d_parameters.getGenerationParameters());
        }
      }
    }
    d_dirCount++;
  }
}


void DataBaseGenerator::generateDataBaseFromRandomTruthTable(const GenerationParameters& i_param)
{
  TruthTable<Chronosome<TruthTable>> tt(i_param.getInputs(), i_param.getOutputs(), {});
  tt.generateRandom({i_param.getInputs(), i_param.getOutputs()});

  SimpleGenerators tftt;

  std::string<std::pair<std::string, std::vector<std::string>>> circs;

  if (i_param.cnfFromTruthTableParameters.CNFT)
    circs.push_back("CNFT", tftt.cnfFromTruthTable(tt, true));

  if (i_param.cnfFromTruthTableParameters.CNFF)
    circs.push_back("CNFF", tftt.cnfFromTruthTable(tt, false));

  for (const auto& [name, expr] : circs)
  {
    Parser pCNFT(expr);
    pCNFT.parseAll();
    
    OrientedGraph graph = pCNFT.getGraph();
    Circuit c(graph, expr);
    c.settTable(tt);
    c.setPath(d_mainPath + "/FromRandomTruthTable/");
    c.setCircuitName(i_param.getName() + "_" + name);
    c.generate();
  }
}

void DataBaseGenerator::generateDataBaseRandLevel(GenerationParameters i_param)
{
  SimpleGenerator generator;
  std::vector<std::pair<std::string, std::vector<std::string>>> circs;
  circs.push_back("RandLevel",
                  generator.generatorRandLevel(i_param.generatorRandLevelParameters.maxLevel,
                                               i_param.generatorRandLevelParameters.maxElements,
                                               i_param.getInputs(),
                                               i_param.getOutputs()
                                               )
  );

  for (const auto& [name, graph] : circs)
  {
    Circuit c(graph);
    c.setPath(d_mainPath + "/RandLevel/");
    c.setCircuitName(i_param.getName());
    c.generate();
  }
}

void DataBaseGenerator::generateDataBaseNumOperation(GenerationParameters i_param)
{
  SimpleGenerator generator;
  std::vector<std::pair<std::string, OrientedGraph>> circs;
  circs.push_back("RandLevel", 
                  generator.generatorNumOperation(
                    i_param.inputs,
                    i_param.generatorNumOperationParameters.getLogicOper,
                    i_param.generatorNumOperationParameters.getLeaveEmptyOut
                  )
  );
  
  for (const auto &[name expr] : circs)
  {
    Circuit c(graph);
    c.setPath(d_mainPath + "/NumOperation/");
    c.setCircuitName(i_param.name);
    c.generate();
  }
}

void DataBaseGenerator::generateDataBaseGenetic(GenerationParameters i_param)
{
  i_param.geneticParameters.setInputs(param.getInputs());
  i_param.geneticParameters.setOutputs(param.getOutputs());

  GeneticGeneration<TruthTable, TruthTableParameters> gg({i_param.getGeneticParameters()},
                                                         {i_param.getInputs(), i_param.getOutputs()},
                                                         d_mainPath + "/");
  gg.generate();
}

std::function<void(const GenerationParameters&)> DataBaseGenerator::getGenerateMethod(const std::string& i_methodName)
{
  if (i_methodName == "FromRandomTruthTable")
    return generateDataBaseFromRandomTruthTable;
  if (i_methodName == "RandLevel")
    return generateDataBaseRandLevel;
  if (i_methodName == "NumOperation")
    return generateDataBaseNumOperations;
  if (i_methodName == "Genetic")
    return generateDataBaseGenetic;

  std::cout << "UNDEFINED FUNC << " << i_methodName << std::endl;
  return generateDataBaseFromRandomTruthTable;

}
