#include "DemultiplexerDataBaseGenerator.hpp"

#include <generators/simple/PlexerGenerator.hpp>

void DemultiplexerDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  PlexerGenerator sg(i_param);
  GraphPtr graph = sg.generatorDemultiplexer();

  processCircuit(graph, i_param);
}
