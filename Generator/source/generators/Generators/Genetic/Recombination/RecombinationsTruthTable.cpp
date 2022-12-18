#include "RecombinationsTruthTable.h"

namespace {
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingEachExitInTurnMany
  (
    RecombinationParameters i_recombinationParameters,
    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
  )
  {
    Parents<TruthTable, TruthTableParameters> p;
    int input = i_population[0].chronosome.Input;
    int output = i_population[0].chronosome.Output;
    int size = i_population[0].chronosome.size();
    int refPoints = i_recombinationParameters.refPoints;

    std::vector<int> referencePoints;
    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> survivors;

    for (int cr = 0; cr < recombinationParameters.getRecombinationParameters(); ++cr)
    {
      std::vector<int> parentsInt = p.ParentTypes(
        i_recombinationParameters.getParentsParameters(),
        i_population
      );
      int child1 = parentsInt[0];
      int child2 = parentsInt[1];

      referencePoints = AuxilaryMethods.GetRandomIntList(ref_point, 0, size, false);

      std::vector<std::vector<std::vector<bool>>> parents;
      parents.push_back(i_population[ch1].OutTable);
      parents.push_back(i_population[ch2].OutTable);
      std::vector<std::vector<bool>> child(size, std::vector<bool>());
      int stage = 0;

      for (int j = 0; j < size; ++j)
      {
        if (stage < referencePoints.size() && j == referencePoints[stage])
          stage++;
        child[j] = parents[stage % parents.size()][j];
      }

      TruthTable tt(input, output, child);
      ChronosomeType<TruthTable, TruthTableParameters> tmp("ind" + std::to_string(cr + 1), tt);
      survivors.push_back(tmp);
    }
    return survivors;
  }

  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingUniform
  (
    RecombinationParameters i_recombinationParameters,
    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
  )
  {
    Parents<TruthTable, TruthTableParameters> p;
    int input = i_population[0].chronosome.Input;
    int output = i_population[0].chronosome.Output;
    int size = i_population[0].chronosome.size();

    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> survivors;
  
    for (int cr = 0; cr < recombinationParameters.getRecombinationParameters(); ++cr)
    {
      std::vector<int> parentsInt = p.ParentTypes(
        i_recombinationParameters.getParentsParameters(),
        i_population
      );
      int child1 = parentsInt[0];
      int child2 = parentsInt[1];
    
      TruthTable mask(
        input, 
        output, 
        i_recombinationParameters.getMaskProbability()
      );

      std::vector<std::vector<std::vector<bool>>> parents;
      parents.push_back(i_population[ch1].OutTable);
      parents.push_back(i_population[ch2].OutTable);
      std::vector<std::vector<bool>> child(size, std::vector<bool>(output));

      for (int i = 0; i < size; ++i)
      {
        for (int j = 0; j < output; ++j)
        {
          child[i][j] = parents[mask.array[i][j] ? 1 : 0][i][j];
        }
      }

      TruthTable tt(input, output, child);
      ChronosomeType<TruthTable, TruthTableParameters> tmp("ind" + std::to_string(cr + 1), tt);
      survivors.push_back(tmp);
    }
    return survivors;
  }

  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingTriadic
  (
    RecombinationParameters i_recombinationParameters,
    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
  )
  {
    Parents<TruthTable, TruthTableParameters> p;
    int input = i_population[0].chronosome.Input;
    int output = i_population[0].chronosome.Output;
    int size = i_population[0].chronosome.size();

    int child3;
    std::srand(std::time(0));

    for (int cr = 0; cr < recombinationParameters.getRecombinationParameters(); ++cr)
    {
      child3 = 0;
      std::vector<int> parentsInt = p.ParentTypes(
        i_recombinationParameters.getParentsParameters(),
        i_population
      );
      int child1 = parentsInt[0];
      int child2 = parentsInt[1];

      while (child1 == child3 || child2 == child3)
        c3 = rand() % i_population.size();

      TruthTable mask(
        input,
        output,
        Mutations<TruthTable, TruthTableParameters>.MutationTable(
          i_recombinationParameters.getMaskProbability,
          i_poppulation[ch3].chronosome.OutTable
        )
      );

      std::vector<std::vector<std::vector<bool>>> parents;
      parents.push_back(i_population[child1].chronosome.OutTable);
      parents.push_back(i_population[child2].chronosome.OutTable);
      std::vector<std::vector<bool>> child(size, std::vector<bool>(output));

      for (int i = 0; i < size; ++i)
      {
        for (int j = 0; j < output; ++j)
        {
          child[i][j] = parents[mask.array[i][j] ? 0 : 1][i][j];
        }
      }

      TruthTable tt(
        input,
        output,
        child
      );
    
      ChronosomeType<TruthTable, TruthTableParameters> tmp("ind" + std::to_string(cr + 1), tt);
      population.push_back(tmp); // what????
    }

    population.clear(); // what??
    return population; // what????
  }

  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingReducedReplacement
  (
    RecombinationParameters i_recombinationParameters,
    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
  )
  {
    std::srand(std::time(0));

    Parents<TruthTable, TruthTableParameters> p;
    int input = i_population[0].chronosome.Input;
    int output = i_population[0].chronosome.Output;
    int size = i_population[0].chronosome.size();
    int referencePoint = rand() % size;

    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> survivors;

    for (int cr = 0; cr < recombinationParameters.getRecombinationParameters(); ++cr)
    {
      std::vector<int> parentsInt = p.ParentTypes(
        i_recombinationParameters.getParentsParameters(),
        i_population
      );
      int child1 = parentsInt[0];
      int child2 = parentsInt[1];
    
      std::vector<std::vector<std::vector<bool>>> parents;
      parents.push_back(i_population[child1].chronosome.OutTable);
      parents.push_back(i_population[child2].chronosome.OutTable);
      std::vector<std::vector<bool>> child(size, std::vector<bool>(output));

      for (int j = 0; j < output; ++j)
      {
        while (parents[0][referencePoint][j] == parents[1][referencePoint][j])
          referencePoint = rand() % size;

        for (int i = 0; i < size; ++i)
          child[i][j] = parents[i < referencePoint ? 0 : 1][i][j];
      }
      TruthTable tt(input, output, child);
      ChronosomeType<TruthTable, TruthTableParameters> tmp("ind" + std::to_string(cr + 1), tt);
      survivors.push_back(tmp);
    }
    return survivors;
  }

  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> RecombinationCrossingShuffling
  (
    RecombinationParameters i_recombinationParameters,
    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
  )
  {
    std::srand(std::time(0));

    Parents<TruthTable, TruthTableParameters> p;
    int input = i_population[0].chronosome.Input;
    int output = i_population[0].chronosome.Output;
    int size = i_population[0].chronosome.size();
    int referencePoint = rand() % size;

    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> survivors;
  
    for (int cr = 0; cr < recombinationParameters.getRecombinationParameters(); ++cr)
    {
      std::vector<int> parentsInt = p.ParentTypes(
        i_recombinationParameters.getParentsParameters(),
        i_population
      );
      int child1 = parentsInt[0];
      int child2 = parentsInt[1];
    
      std::vector<std::vector<std::vector<bool>>> parents;
      parents.push_back(i_population[child1].chronosome.OutTable);
      parents.push_back(i_population[child2].chronosome.OutTable);
      std::vector<std::vector<bool>> child(size, std::vector<bool>(output));
    
      for (int i = 0; i < size; ++i)
      {
        for (int j = 0; j < output; ++j)
        {
          if (rand() % 2)
            swap(parents[0][i][j], parents[1][i][j]);
        }
      }

      for (int i = 0; i < size; ++i)
      {
        for (int j = 0; j < output; ++j)
        {
          child[i][j] = parents[i < referencePoint ? 0 : 1][i][j];
        }
      }
      TruthTable tt(input, output, child);
      ChronosomeType<TruthTable, TruthTableParameters> tmp("ind" + std::to_string(cr + 1), tt);
      survivors.push_back(tmp);
    }
    return survivors;
  }

std::vector<ChronosomeType<Type, ParametersType>> RecombinationType
(
  RecombinationParameters i_recombinationParameters,
  std::vector<ChronosomeType<Type, ParametersType>> i_population
)
{
  std::vector<ChronosomeType<Type, ParametersType>> res;
  switch (i_recombinaionParameters.RecombinationType)
  {
    RecombinationTypes.CrossingEachExitInTurnMany:
      res = RecombinationCrossingEachExitInTurnMany(
        i_recombinationParameters,
        i_population
      );
      break;

    RecombinationTypes.CrossingUniform:
      res = RecombinationCrossingUniform(
        i_recombinationParameters,
        i_population
      );
      break;

    RecombinationTypes.CrossingTriadic:
      res = RecombinationCrossingTriadic(
        i_recombinationParameters,
        i_population
      );
      break;

    RecombinationTypes.CrossingReducedReplacement:
      res = RecombinationCrossingReducedReplacement(
        i_recombinationParameters,
        i_population
      );
      break;

    RecombinationTypes.CorssingShuffling:
      res = RecombinationCorssingShuffling(
        i_recombinationParameters,
        i_population
      );
      break;
  }
  return res;
}
