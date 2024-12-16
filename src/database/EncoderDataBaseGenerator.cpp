#include "EncoderDataBaseGenerator.hpp"

#include <generators/simple/CoderGenerator.hpp>

void EncoderDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  CoderGenerator sg(i_param);
  GraphPtr graph = sg.generatorEncoder();

  processCircuit(graph, i_param);
}
