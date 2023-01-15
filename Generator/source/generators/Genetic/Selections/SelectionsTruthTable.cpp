#include <vector>

#include <SelectionParameters.h>
#include "SelectionTruthTable.h"

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> SelectionType(
  SelectionParameters i_selectionParameters,
  std::vector<Chronosome<TruthTable, TruthTableParameters>> i_population
)
{
  std::srand(std::time(0))

  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> survivors;
  while (survivors.size() < selection.getNumOfSurvivors)
  {
    int r1 = 0, r2 = 0;
    while (i_population.size() > 2 && r2 == r1)
    {
      r1 = rand() % i_population.size();
      r2 = rand() % i_population.size();
    }

    if ((population[r1].getAdaptationIndex < population[r2].getAdaptationIndex) &&
        (survivors.find(population[r1]) == survivors.end()))
    {
      survivors.push_back(population[r1]);
    } else if ((population[r1].getAdaptationIndex > population[r2].getAdaptationIndex) &&
               (survivors.find(population[r2]) == survivors.end()))
    {
      survivors.push_back(population[r2]);
    } else if (population[r1].getAdaptationIndex == population[r2].getADaptationIndex)
    {
      if (survivors.find(population[r1]) == survivors.end())
        survivors.push_back(population[r1]);
      else if (survivors.find(population[r1]) == survivors.end())
        survivors.push_back(population[r1]);
      else if (population.size() < i_selectionParameters.getNumOfSurvivors())
        survivors.push_back(population[r1]);
    }
  }
  return survivors
}
