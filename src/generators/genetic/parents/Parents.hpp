#pragma once

#include "generators/genetic/chromosome/type/ChromosomeType.hpp"
#include "generators/genetic/parents/parameters/ParentsParameters.hpp"
#include <functional>
#include <generators/genetic/parents/ParentsTruthTable.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace CG_Gen {

template<typename Type, typename ParametersType>
std::vector<int32_t> ParentsTypesWorker(
    ParentsParameters i_parentsParameters,
    std::vector<ChromosomeType<Type, ParametersType>> i_population);
template<>
inline std::vector<int32_t>
ParentsTypesWorker(ParentsParameters i_parentsParameters,
                   std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
                       i_population) {
  if (i_parentsParameters.getParentsType() == ParentsTypes::Panmixia)
    return ParentsPanmixia(i_parentsParameters, i_population);
  if (i_parentsParameters.getParentsType() == ParentsTypes::Inbringing)
    return ParentsInbrinding(i_parentsParameters, i_population);
  if (i_parentsParameters.getParentsType() == ParentsTypes::Outbrinding)
    return ParentsOutbrinding(i_parentsParameters, i_population);
  if (i_parentsParameters.getParentsType() == ParentsTypes::Tournament)
    return ParentsTournament(i_parentsParameters, i_population);
  // TODO: info about ParentsRoulette
  std::cout << "UNUSUAL ParentTypes IN ParentsTypes" << std::endl;

  // default to remove warning
  return {};
}

} // namespace CG_Gen
