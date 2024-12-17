#include "MultiplierDataBaseGenerator.hpp"

#include <generators/simple/ArithmeticGenerator.hpp>

void MultiplierDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  ArithmeticGenerator sg(i_param);
  GraphPtr graph = sg.generatorMultiplier();

  processCircuit(graph, i_param);
}
