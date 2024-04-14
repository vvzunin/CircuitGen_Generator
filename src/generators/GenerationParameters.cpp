// #include <vector>

// #include "GenerationParameters.hpp"
// void GenerationParameters::setRecombinationParameters(ParentsTypes
// i_parentsType, int i_tournamentSize, RecombinationTypes i_recombinationType,
// int i_refPoints, double i_maskProbability, int i_recombinationNumber)
// {
//     RecombinationParameters RP;
//     RP.setParentsParameters(i_parentsType, i_tournamentSize);
//     RP.setRefPoints(i_refPoints);
//     RP.setRecombinationParameters(i_recombinationNumber);
//     RP.setRecombinationType(i_recombinationType);
//     RP.setMaskProbability(i_maskProbability);
//     d_geneticParameters.setRecombinationParameters(RP);
// }

// void GenerationParameters::setMutationParameters(MutationTypes
// i_mutationType, double i_probabilityGen, int i_exchangeType, double
// i_probabilityTruthTable)
// {
//     MutationParameters MP;
//     MP.setMutationType(i_mutationType);
//     MP.setProbabilityGen(i_probabilityGen);
//     MP.setExchangeType(i_exchangeType);
//     MP.setProbabilityTruthTable(i_probabilityTruthTable);
//     d_geneticParameters.setMutationParameters(MP);
// }

// void GenerationParameters::setSelectionParameters(SelectionTypes
// i_selectionType, int i_numOfSurvivors)
// {
//     SelectionParameters SP;
//     SP.setSelectionType(i_selectionType);
//     SP.setNumOfSurvivors(i_numOfSurvivors);
//     d_geneticParameters.setSelectionParameters(SP);
// }