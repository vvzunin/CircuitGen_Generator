#include "RandLevelExperimentalDataBaseGenerator.hpp"

#include <generators/simple/RandLevelGenerator.hpp>

void RandLevelExperimentalDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  RandLevelGenerator generator(i_param);
  GraphPtr graph = generator.generatorRandLevelExperimental();

  processCircuit(graph, i_param);
}
