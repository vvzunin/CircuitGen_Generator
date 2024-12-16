#include "ParityDataBaseGenerator.hpp"

#include <generators/simple/ParityGenerator.hpp>

void ParityDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  ParityGenerator sg(i_param);
  GraphPtr graph = sg.generatorParity();

  processCircuit(graph, i_param);
}
