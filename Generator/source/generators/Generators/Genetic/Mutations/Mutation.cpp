#include "Mutation.h"

std::vector<ChronosomeType<Type, ParametersType>> Mutaions::MutationType(
    MutationParameters i_mutationParameters,
    std::vector<ChronosomeType<Type, ParametersType>> i_population)
{
  GenerateDelegate handler;
  std::string s = MutationParameters::mutationToString(mutationParameters);
  std::string methodName = "Mutation" + s;

}
