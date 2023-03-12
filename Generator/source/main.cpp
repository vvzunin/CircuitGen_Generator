#include <iostream>

#include "./DataBase/DataBaseGenerator.h"
#include "./DataBase/DataBaseGeneratorParameters.h"

int main()
{
  //JSON params = JSON::Read("params.json");

  //TODO:: make function that return DataBaseGeneratorParameters from json

  GenerationParameters gp("My_first_test", 2, 4, 0);
  DataBaseGeneratorParameters dbgp(2, 4, 3, 5, 3, GenerationTypes::FromRandomTruthTable, gp);

  DataBaseGenerator generator(dbgp);

  generator.generateType(dbgp, false);

  std::cout << "All ok";
}
