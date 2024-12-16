#include "GeneticDataBaseGenerator.hpp"

#include <generators/Genetic/GenGenerator.hpp>

void GeneticDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  GeneticGenerator<TruthTable, TruthTableParameters> gg(
      GeneticParameters(i_param.getGenetic()),
      {i_param.getInputs(), i_param.getOutputs()}, d_mainPath,
      i_param.getName());

  const auto &population = gg.generate();
  auto graphs = gg.getGraphsFromPopulation(population);

  for (auto graph: graphs) {
    processCircuit(graph, i_param, graph->getName());
  }
}
