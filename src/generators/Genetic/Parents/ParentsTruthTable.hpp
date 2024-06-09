#pragma once

#include <algorithm>
#include <ctime>
#include <map>
#include <vector>

#include <additional/AuxiliaryMethods.hpp>
#include <baseStructures/truthTable/TruthTable.hpp>

#include "../ChromosomeType.hpp"

inline std::vector<int32_t> GetHemming(
    int32_t                                                       i_t,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
) {
  int32_t                        count = 0;
  std::vector<std::vector<bool>> p1 =
      i_population[i_t].getChromosomeType().getOutTable();
  std::map<int32_t, int32_t> dict;
  std::vector<int32_t>       res;

  for (size_t i = 0; i < i_population.size(); ++i) {
    if (i != i_t) {
      count = 0;
      std::vector<std::vector<bool>> p2 =
          i_population[i].getChromosomeType().getOutTable();
      for (size_t j = 0; j < p1.size(); ++j) {
        for (size_t k = 0; k < p1[0].size(); ++k) {
          if (p2[j][k] == p1[j][k])  // what? is it Hemming dist?
            ++count;
        }
      }
      dict[i] = count;
    }
  }

  for (const auto& [key, value] : AuxMethods::sortDictByValue(dict))
    res.push_back(key);

  std::reverse(res.begin(), res.end());

  return res;
};

inline std::vector<int32_t> ParentsPanmixia(
    ParentsParameters i_parentsParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
) {
  std::srand(std::time(0));
  int32_t parent1 = 0, parent2 = 0;

  while (i_population.size() > 2 && parent1 == parent2) {
    parent1 = AuxMethods::getRandInt(0, i_population.size());
    parent2 = AuxMethods::getRandInt(0, i_population.size());
  }

  return {parent1, parent2};
}

inline std::vector<int32_t> ParentsInbrinding(
    ParentsParameters i_parentsParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
) {
  std::srand(std::time(0));

  int32_t parent1 = AuxMethods::getRandInt(0, i_population.size());
  int32_t parent2 = GetHemming(parent1, i_population).back();

  return {parent1, parent2};
}

inline std::vector<int32_t> ParentsOutbrinding(
    ParentsParameters i_parentsParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
) {
  std::srand(std::time(0));

  int32_t parent1 = AuxMethods::getRandInt(0, i_population.size());
  int32_t parent2 = GetHemming(parent1, i_population).front();

  return {parent1, parent2};
}

inline std::vector<int32_t> ParentsTournament(
    ParentsParameters i_parentsParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
) {
  std::vector<int32_t> beforeAdaptation = AuxMethods::getRandomIntList(
      i_parentsParameters.getTournamentNumber(), 0, i_population.size(), false
  );

  std::map<int32_t, double> adaptationIndex;

  for (const auto& k : beforeAdaptation)
    adaptationIndex[k] = i_population[k].getAdaptationIndex();

  std::vector<int32_t> res;

  for (const auto& [key, value] :
       AuxMethods::sortDictByValue(adaptationIndex, false))
    res.push_back(key);
  std::reverse(res.begin(), res.end());

  return {res[0], res[1]};
}

// TODO: is this ParentTournament???
inline std::vector<int32_t> ParentsRoulette(
    ParentsParameters i_parentsParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
) {
  return ParentsTournament(i_parentsParameters, i_population);
}
