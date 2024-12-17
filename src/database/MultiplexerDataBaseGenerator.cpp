#include "MultiplexerDataBaseGenerator.hpp"

#include <generators/simple/PlexerGenerator.hpp>

void MultiplexerDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  PlexerGenerator sg(i_param);
  GraphPtr graph = sg.generatorMultiplexer();

  processCircuit(graph, i_param);
}
