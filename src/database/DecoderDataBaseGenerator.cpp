#include "DecoderDataBaseGenerator.hpp"

#include <generators/simple/CoderGenerator.hpp>

void DecoderDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  CoderGenerator sg(i_param);
  GraphPtr graph = sg.generatorDecoder();

  processCircuit(graph, i_param);
}
