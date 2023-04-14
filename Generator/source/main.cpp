#include <iostream>

#include "./DataBase/DataBaseGenerator.h"
#include "./DataBase/DataBaseGeneratorParameters.h"

int main()
{
  //JSON params = JSON::Read("params.json");

  //TODO:: make function that return DataBaseGeneratorParameters from json

  std::cout << "WTF IS IT WORK?\n";
  GenerationParameters gp("My_first_test", 2, 4, 0, 20, 10);
  std::cout << "WTF IS IT WORK?\n";
  DataBaseGeneratorParameters dbgp(2, 4, 3, 5, 3, GenerationTypes::RandLevel, gp);

  std::cout << "WTF IS IT WORK?\n";
  DataBaseGenerator generator(dbgp);

  std::cout << "WTF IS IT WORK?\n";

  generator.generateType(dbgp, false);

  std::cout << "All ok";
}
