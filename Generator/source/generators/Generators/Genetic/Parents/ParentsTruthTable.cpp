#include <vector>
#include <map>
#include <algorithm>

#include "ParentsTruthTable.h"

std::vector<int> GetHemming(int i_t,
                            std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population)
{
  int count = 0;
  std::vector<std::vector<bool>> p1 = i_population[t].chronosome.OutTable;
  std::map<int, int> dict;
  std::vector<int> res;

  for (int i = 0; i < i_population.size(); ++i)
  {
    if (i != i_t)
    {
      count = 0;
      std::vector<std::vector<bool>> p2 = i_population[i].chronosome.OutTable;
      for (int j = 0; j < p1.size(); ++j)
      {
        for (int k = 0; k < p1[0].size(); ++k)
        {
          if (p2[j][k] == p1[j][k]) // what? is it Hemming dist?
            ++count;
        }
      }
      dict[i] = count;
    }
  }

  for (const auto &[key, value] : dict)
    res.push_back(key);

  std::reverse(res.begin(), res.end());

  return res;
}

std::vector<int> ParentsPanmixia(
  ParentsParameters i_parentsParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  std::srand(std::time(0));
  int parent1 = 0, parent2 = 0;
  
  while (i_population.size() > 2 && parent1 == parent2)
  {
    parent1 = rand() % i_population.size();
    parent2 = rand() % i_population.size();
  }

  return {parent1, parent2}
}

std::vector<int> ParentsInbrinding(
  ParentsParameters i_parentsParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  std::srand(std::time(0));

  int parent1 = rand() % i_population.size();
  int parent2 = GetGemming(parent1, i_population).back();

  return {parent1, parent2};
}

std::vector<int> ParentsOutbrinding(
  ParentsParameters i_parentsParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  std::srand(std::time(0));

  int parent1 = rand() % i_population.size();
  int parent2 = GetGemming(parent1, i_population).front();

  return {parent1, parent2};
}

std::vector<int> ParentTournament(
  ParentsParameters i_parentsParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  std::vector<int> beforeAdaptation = AuxilaryMethods.GetRandomIntList(
    i_parentsParameters.TournamentNumber,
    0,
    population.size();
    false
  );

  std::map<int, double> adaptationIndex;

  for (const auto& k : beforeAdaptation)
    adaptationIndex[k] = i_population[k].AdaptationIndex;

  std::vector<int> res;

  for (const auto &[key, value] : adaptationIndex)
    res.push_back(key);
  std::reverse(res.begin(), res.end());

  return {res[0], res[1]};
}

// is this ParentTournament???
std::vector<int> ParentsRoulette(
  ParentsParameters i_parentsParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  return ParentTournament(i_parentsParameters, i_population);
}
