#pragma once

#include <vector>

#include "ParentsParameters.h"
#include "../ChronosomeType.h"

/// @brief ParentsTypesWorker There is a comment in the method //TODO: info
/// about Parents Roulette, which involves adding processing of another type
/// of parental choice - "roulette", but this case is not being processed yet!
/// P.S. Possible recommendations:
/// 1. There is no processing of all possible types of parent selection.
/// If the type does not match any of the processed ones, an error message is
/// displayed, but no value is returned, which may lead to undesirable behavior.
/// 2. There is no return value in case of successful execution of the function
/// for all types of parent selection.
/// @param i_parentsParameters This is an object of the Parent's Parameters
/// class, which contains information about the type of parental choice***
/// @param i_population containing a population of chromosomes for which
/// parental selection will be made. Each element of the vector represents
/// a chromosome of a certain type Type with the corresponding
/// ParametersType parameters.
/// @return A vector representing the indices of the selected parents in
/// the population. Depending on the chosen parental choice strategy,
/// this vector contains chromosome indexes from i_population, which will
/// be used to create new individuals in the next generation
/// 

template<typename Type, typename ParametersType>
std::vector<int> ParentsTypesWorker(ParentsParameters i_parentsParameters,
                              std::vector<ChronosomeType<Type, ParametersType>> i_population
);
