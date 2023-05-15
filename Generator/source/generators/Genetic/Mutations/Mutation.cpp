#include <iostream>

#include "Mutation.h"
#include "MutationTruthTable.h"

template<typename Type, typename ParametersType>
std::vector<ChronosomeType<Type, ParametersType>> Mutations<Type, ParametersType>::MutationType(
    MutationParameters i_mutationParameters,
    std::vector<ChronosomeType<Type, ParametersType>> i_population)
{
  if (i_mutationParameters.getMutationType() == MutationTypes::Binary)
    return MutationBinary(i_mutationParameters, i_population);
  else if (i_mutationParameters.getMutationType() == MutationTypes::Density)
    return MutationDensity(i_mutationParameters, i_population);
  else if (i_mutationParameters.getMutationType() == MutationTypes::AccessionDel)
    return MutationAccessionDel(i_mutationParameters, i_population);
  else if (i_mutationParameters.getMutationType() == MutationTypes::InsertDel)
    return MutationInsertDel(i_mutationParameters, i_population);
  else if (i_mutationParameters.getMutationType() == MutationTypes::Exchange)
    return MutationExchange(i_mutationParameters, i_population);
  else if (i_mutationParameters.getMutationType() == MutationTypes::Delete)
    return MutationDelete(i_mutationParameters, i_population);

  std::cout << "UNRECOGNIZED MtationType AT Mutation.cpp" << std::endl;
}
