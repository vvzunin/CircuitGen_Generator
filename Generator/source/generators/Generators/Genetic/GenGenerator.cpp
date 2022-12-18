
#include "cstdlib"
#include <filesystem>
#include <string>
#include <utility>

#include "GenGenerator.h"

namespace
{
  isDirectorExist(const string& path)
  {
    try
    {
      filesystem::path pathObj(filePath);
      if (filesystem::exists(pathObj) && filesystem::is_directory(pathObj))
        return true;
    }
    catch(filesystem::filesystem_error & e)
    {
      std::cerr << e.what() << std::endl;
    }
    return false;
  }

  bool isNumber(const std::string& s)
  {
    for (auto c : s)
    {
      if (!std::isdigit(c))
        return false;
    }
    return true;
  }

  int getNumFolderFromString(const std::string path)
  {
    int lastSlash = 0;
    for (int i = 0; i < path.size(); ++i)
    {
      if (path[i] == '_')
        lastSlash = i;
    }
    path = path.subsrt(lastSlash);
    int res = 0;
    if (!isNumber(path))
      return 0;
    return std::stoi(path);
  }
}

GeneticGenerator::GeneticGenerator(
  const ParametersType& i_parameters,
  std::pair<int, int> i_inout,
  const std::string& i_mainPath = "") :
  d_parameters(i_parameters),
  d_inputs(i_inout.first),
  d_outputs(i_inout.second),
  d_mainPath(i_mainPath),

{
  std::string dataPath = d_settings.getDatasetPath + "/Genetic";
  if (isDirectoryExists(dataPath))
  {
    for (const auto & entry : filesystem::directory_iterator(dataPath))
    {
      d_foldersCount = max(d_foldersCount, getNumFolderFromString(entry.path()) + 1);
    }
  }
  else
  {
    std::cout << "Folder for data not exists, you need to create Directory \""
      << dataPath << "\"" << std::endl;
    std::exit(0);
  }
}

void GeneticGenerator::savePopulation(
  const std::vector<ChronosomeType<Type, ParametersType>>& i_population
)
{
  for (const auto& ttp : i_population)
  {
    TruthTable tt;
    tt = ttp.chronosome;

    SimpleGenerators tftt;
    std::vector<str::pair<std::string, std::vector<std::string>>> circs;
    circs.push_back({d_settings.fromGenMethodToPrefix("Genetic") + std::tostring(d_foldersCount++), tftt.cnfFromTruthTable(tt, true)});
    circs.push_back({d_settings.fromGenMethodToPrefix("Genetic") + std::tostring(d_foldersCount++), tftt.cnfFromtruthTable(tt, false)});

    for (const auto& nameexpr : circs)
    {
      std::string name = nameexpr.Item1;
      std::vector<std::string> expr = nameexpr.Item2;
      Parser pCNFT(expr);
      pcnft.ParseAll();
      OrientedGraph graph = pCNFT.getGraph();
      Circuit c(graph, expr);
      c.settTable(tt);
      c.setPath(d_mainPath + "/Genetic/");
      c.setCircuitName(d_name);
      c.generate();
    }
  }
}

void GeneticGenerator::createPopulation()
{
  d_population.clear();
  for (int i = 0; i < d_parameters.getPopulationSize(); ++i)
  {
    Type gen;
    gen.generateRandom(d_parameters);
    ChronosomeType<Type, ParametersType> ind("ind" + std::stoi(i), gen);
    d_population.push_back(ind);
  }
  savePopulation(population);
}

std::vector<ChronosomeType<Type, ParametersType>> GeneticGenerator::generate()
{
  createPopulation();
  double d = endProceessFunction();
  for (int i = 0; i < d_parameterss.getNumOfCycles && endProcessFunction() < d_parameters.getKeyEndProcessIndex; ++i)
  {
    std::vector<ChromosomeType<Type, ParametersType>> newPopulation = getRecombinationType(d_parameters.getRecombinationParameter, d_population);
    std::vector<ChromosomeType<Type, ParametersType>> mutants = getMutationType(d_parameters.getMutationParameter, newPopulation);
    d_population = getSelectionType(d_parameters.getSelectionParameter, mutants);
    savePopulation(d_population);
  }
}
