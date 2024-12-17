#include "SummatorDataBaseGenerator.hpp"

#include <generators/simple/ArithmeticGenerator.hpp>

void SummatorDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  ArithmeticGenerator sg(i_param);
  GraphPtr graph = sg.generatorSummator();

  processCircuit(graph, i_param);
}
