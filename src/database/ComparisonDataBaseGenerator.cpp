#include "ComparisonDataBaseGenerator.hpp"

#include <generators/simple/ComparisonGenerator.hpp>

void ComparisonDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  ComparisonGenerator sg(i_param);
  GraphPtr graph = sg.generatorComparison();

  processCircuit(graph, i_param);
}
