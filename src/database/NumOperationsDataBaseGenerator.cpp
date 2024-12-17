#include "NumOperationsDataBaseGenerator.hpp"

#include <generators/simple/NumOperationsGenerator.hpp>

void NumOperationsDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  NumOperationsGenerator generator(i_param);

  std::vector<std::pair<std::string, GraphPtr>> circs;
  circs.push_back({"NumOperation", generator.generatorNumOperation()});

  for (auto [name, graph]: circs) {
    processCircuit(graph, i_param);
  }
}
