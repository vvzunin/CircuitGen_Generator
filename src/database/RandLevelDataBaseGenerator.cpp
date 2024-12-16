#include "RandLevelDataBaseGenerator.hpp"

#include <generators/simple/RandLevelGenerator.hpp>

void RandLevelDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  RandLevelGenerator generator(i_param);
  GraphPtr graph = generator.generatorRandLevel();

  processCircuit(graph, i_param);
}
