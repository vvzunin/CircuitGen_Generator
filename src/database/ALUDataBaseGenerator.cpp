#include "ALUDataBaseGenerator.hpp"

#include <generators/simple/ALUGenerator.hpp>

void ALUDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  ALUGenerator sg(i_param);
  GraphPtr graph = sg.generatorALU();

  processCircuit(graph, i_param);
}
