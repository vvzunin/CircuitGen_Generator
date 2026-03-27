/**
 * @file Mutation.cpp
 * @author Vladimir Zunin <vzunin@hse.ru>
 * @author Чернявских Илья Игоревич <fuuulkrum7@gmail.com>
 * @author Fuuulkrum7 <ilka747428@gmail.com>
 * @author Zunin Vladimir <vzunin@hse.ru>
 * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
 * @author Asdfds1 <ziazetdinov@list.ru>
 */

#include <iostream>

#include "Mutation.hpp"

#include "MutationTruthTable.hpp"

namespace CG_Gen {

template<>
std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
MutationType(MutationParameters i_mutationParameters,
             std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
                 i_population) {
  if (i_mutationParameters.getMutationType() == MutationTypes::Binary)
    return MutationTruthTable::MutationBinary(i_mutationParameters,
                                              i_population);

  if (i_mutationParameters.getMutationType() == MutationTypes::Density)
    return MutationTruthTable::MutationDensity(i_mutationParameters,
                                               i_population);

  if (i_mutationParameters.getMutationType() == MutationTypes::AccessionDel)
    return MutationTruthTable::MutationAccessionDel(i_mutationParameters,
                                                    i_population);

  if (i_mutationParameters.getMutationType() == MutationTypes::InsertDel)
    return MutationTruthTable::MutationInsertDel(i_mutationParameters,
                                                 i_population);

  if (i_mutationParameters.getMutationType() == MutationTypes::Exchange)
    return MutationTruthTable::MutationExchange(i_mutationParameters,
                                                i_population);

  if (i_mutationParameters.getMutationType() == MutationTypes::Delete)
    return MutationTruthTable::MutationDelete(i_mutationParameters,
                                              i_population);

  std::cout << "UNRECOGNIZED MtationType AT Mutation.cpp" << std::endl;

  // default to remove warning
  return {};
}

} // namespace CG_Gen
