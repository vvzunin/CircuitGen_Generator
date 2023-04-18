#include <iostream>
#include <filesystem>

#include "../generators/TruthTable.h"
#include "../generators/Genetic/GeneticParameters.h"
#include "../generators/SimpleGenerators.h"
#include "../generators/Parser.h"
#include "../generators/Genetic/GenGenerator.h"
#include "../circuits/CircuitsParameters.h"
#include "../circuits/Circuit.h"
#include "../FilesTools.h"
#include "DataBaseGenerator.h"


void DataBaseGenerator::generateType(
  const DataBaseGeneratorParameters& i_dbgp,
  bool parallel
)
{

  std::string s = i_dbgp.getGenerationTypeString();
  std::function<void(const GenerationParameters&)> generator = getGenerateMethod(s);
  //TODO: make normal code

  std::string dir = d_settings->getDatasetPath() + "/" + s;

  d_mainPath = d_settings->getDatasetPath();
  d_dirCount = 0;

  if (std::filesystem::is_directory(dir))
  {
    for (const auto item : FilesTools::getDirectories(dir))
    {
      std::string s0 = item;
      auto pos = s0.find(d_settings->getGenerationMethodPrefix(s));
      s0.replace(pos, d_settings->getGenerationMethodPrefix(s).size(), "");
      
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
          //TODO: it is that Rustam told about iteration?
          d_parameters.setIteration(tt);
          d_parameters.setName(d_settings->getGenerationMethodPrefix(s) + std::to_string(d_dirCount + tt));
          generator(d_parameters.getGenerationParameters());
        }
      }
    }
    d_dirCount++;
  }
}


void DataBaseGenerator::generateDataBaseFromRandomTruthTable(const GenerationParameters& i_param)
{
  TruthTable tt(i_param.getInputs(), i_param.getOutputs(), {});
  tt.generateRandom({i_param.getInputs(), i_param.getOutputs()});

  SimpleGenerators tftt;

  std::vector<std::pair<std::string, std::vector<std::string>>> circs;

  //if (i_param.getCNF().getCNFT()) TODO: remove costul. Need to make it by parameter
    circs.push_back({"CNFT", tftt.cnfFromTruthTable(tt, true)});

  if (i_param.getCNF().getCNFF())
    circs.push_back({"CNFF", tftt.cnfFromTruthTable(tt, false)});

  for (const auto& [name, expr] : circs)
  {
    Parser pCNFT(expr);
    pCNFT.parseAll();
    
    OrientedGraph graph = pCNFT.getGraph();
    Circuit c(graph, expr);
    c.setTable(tt);
    c.setPath(d_mainPath + "/FromRandomTruthTable/");
    c.setCircuitName(i_param.getName() + "_" + name);
    c.generate();
  }
}

void DataBaseGenerator::generateDataBaseRandLevel(const GenerationParameters& i_param)
{
  SimpleGenerators generator;
  std::vector<std::pair<std::string, OrientedGraph>> circs;
  circs.push_back({"RandLevel",
                  generator.generatorRandLevel(i_param.getRandLevel().getMaxLevel(),
                                               i_param.getRandLevel().getMaxElements(),
                                               i_param.getInputs(),
                                               i_param.getOutputs()
                                               )
  });

  for (const auto& [name, graph] : circs)
  {
    Circuit c(graph);
    c.setPath(d_mainPath + "/RandLevel/");
    c.setCircuitName(i_param.getName());
    c.generate();
  }
}

void DataBaseGenerator::generateDataBaseNumOperations(const GenerationParameters& i_param)
{
  SimpleGenerators generator;
  std::vector<std::pair<std::string, OrientedGraph>> circs;
  circs.push_back({"RandLevel", 
                  generator.generatorNumOperation(
                    i_param.getInputs(),
                    i_param.getOutputs(),
                    i_param.getNumOperations().getLogicOpers(),
                    i_param.getNumOperations().getLeaveEmptyOut()
                  )
  });
  
  for (const auto &[name, graph] : circs)
  {
    Circuit c(graph);
    c.setPath(d_mainPath + "/NumOperation/");
    c.setCircuitName(i_param.getName());
    c.generate();
  }
}

//void DataBaseGenerator::generateDataBaseGenetic(const GenerationParameters& i_param)
//{
//  i_param.getGenetic().setInputs(i_param.getInputs());
//  i_param.getGenetic().setOutputs(i_param.getOutputs());
//
//  GeneticGenerator<TruthTable, TruthTableParameters> gg(GeneticParameters(i_param.getGenetic()),
//                                                         {i_param.getInputs(), i_param.getOutputs()},
//                                                         d_mainPath + "/");
//  //TODO: uncomment gg.generate();
//}

std::function<void(const GenerationParameters&)> DataBaseGenerator::getGenerateMethod(const std::string& i_methodName)
{
  if (i_methodName == "FromRandomTruthTable")
    return std::bind(&DataBaseGenerator::generateDataBaseFromRandomTruthTable, this, std::placeholders::_1);
  if (i_methodName == "RandLevel")
    return std::bind(&DataBaseGenerator::generateDataBaseRandLevel, this, std::placeholders::_1);
  if (i_methodName == "NumOperation")
    return std::bind(&DataBaseGenerator::generateDataBaseNumOperations, this, std::placeholders::_1);
  //if (i_methodName == "Genetic")
  //  return std::bind(&DataBaseGenerator::generateDataBaseGenetic, this, std::placeholders::_1);
  // TODO: uncomment
  std::cout << "UNDEFINED FUNC << " << i_methodName << std::endl;
  return std::bind(&DataBaseGenerator::generateDataBaseFromRandomTruthTable, this, std::placeholders::_1);

}
