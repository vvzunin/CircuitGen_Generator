#include "DataBaseGenerator.h"

void DataBaseGenerator::GenerateType(
  const DataBaseGeneratorParameters& i_gp,
  bool parallel = true
{

  std::string s = i_gp.d_generationType.toString();
  auto generator = getGenerateMethod("GenerateDataBase" + s);

  std::string dir = d_settings.getDatasetPath + "/" + s;

  d_dirCount = 0;

  if (!isExistDir(dir))
  {
    for (const auto item : getDirectories(dir))
    {
      std::string s0 = item;
      auto pos = s0.find(d_settings.getGenerationMethodPrefix(s));
      s.replace(pos, d_settings.getGenerationMethodPrefix(s).size(), "");
      
      auto jk = s0.find("_"); // TODO: maybe it need last find of "_"?
      if (jk == s0.end())
        jk = s0.size();
      
      s0 = s0.substr(0, jk);

      d_dirCount = std::max(d_dirCount, std::to_string(s0) + 1); // TODO: in general code n is int32, is it really need?
    }
  }

  for (int i = i_gp.getMinInputs(); i <= i_gp.getMaxInputs(); ++i)
  {
    for (int j = i_gp.getMinOutputs(); j <= i_gp.getMaxOutputs(); ++j)
    {
      d_parameters.d_generationParameters.setInputs(i);
      d_parameters.d_generationParameters.setOutputs(j);

      if (parallel)
      {
        exit(1); //TODO: write to multithreading
      }
      else
      {
        for (int tt = 0; tt < i_gp.getEachIteration; ++tt)
        {
          d_parameters.d_generationParameters.setIteration(tt);
          d_parameters.d_generationParameters.setName(d_settings.generationMethodToPrefix(s) + std::to_string(n + tt));
          genFunc(d_parameters.d_generationParameters);
        }
      }
    }
    d_dirCount++;
  }
}

void generateDataBaseFromRandomTruthTable(GenerationParams i_param)
{
  TruthTable tt(i_param.inputs, i_param.outputs, {});
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

void generateDataBaseRandLevel(GenerationParameters i_param)
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
