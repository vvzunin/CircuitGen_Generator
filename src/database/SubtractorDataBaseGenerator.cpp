#include "SubtractorDataBaseGenerator.hpp"

#include <generators/simple/ArithmeticGenerator.hpp>

void SubtractorDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  ArithmeticGenerator sg(i_param);
  GraphPtr graph = sg.generatorSubtractor();

  processCircuit(graph, i_param);
}
