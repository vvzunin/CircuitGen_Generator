#include <random>
#include <algorithm>
#include <vector>


std::vector<vector<bool>> MutationTable(const vector<vector<bool>>& i_table,
                                            double i_probability)
{
  std::srand(std::time(0));
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0,1.0);
  for (int i = 0; i < i_table.size(); ++i)
  {
    for (int j = 0; j < table[i].size(); ++j)
    {
      if (distribution(generator) < i_probability)
      {
        table[i][j] = !table[i][j];
      }
    }
  }
  return table;
}

std::vector<ChronosomeType<TruthTable, TruthParameters>> MutationBinary(
  MutationParameters i_mutationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> mutants;
  int num_mut, k, n;
  int size = i_population[i].chronosome.OutTable;
  std::srand(time(0));
  for (int i = 0; i < i_population.size(); ++i)
  {
    num_mut = (rand() % (size * output)) + 1;
    std::vector<std::vector<bool>> mutant = i_population[i].chronosome.OutTable;
    std::vector<int> m;
    for (int j = 0; j < num_mut; ++j)
    {
      do
      {
        n = rand() % output;
        k = rand() % size;
      }
      while (m.find(k*output + n) != m.end())
      m.push_back(k*output + n);
      mutant[k][n] = !mutant[k][n];
    }
    TruthTable tt = {i_population[i].chronosome, mutant};
    ChronosomeType<TruthTable, TruthTableParameters> tmp = {population[i].Name, tt};
    mutants.push_back(tmp);
  }
  return mutants;
}

vector<CrhonosomeType<TruthTable, TruthTableParameters>> MutationDensity(
  MutationParameters i_mutationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  std::srand(std::time(0));
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0,1.0);
  
  TruthTable tt = {population[0].chronosome.Input, population[0].chronosome.Output, NULL};
  std::vector<bool> bin = tt.OutTable;

  for (int i = 0; i < i_population.size(); ++i)
  {
    if (distribution(generator) < mutationParameters.probabilityGen)
    {
      std::vector<std::vector<bool>> mutant = MutationTalbe(i_mutationParameters.probabilityTruthTable, i_popultaion[i].chronosome.OutTbale);
      population[i].chronosome = TruthTable(i_population[i].chronosome, mutant);
    }
  }
  return population;
}

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationAccessionDel(
  MutationParameters i_mutationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  std::srand(std::time(0));
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0,1.0);
  int size = i_population[0].chronosome.size();

  TrturhTable tt = {i_population[0].chronosome.Input, i_population[0].chronosome.Output, NULL};
  std::vector<std::vector<bool>> bin = tt.OutTable;

  for (int i = 0; i < i_population.size(); ++i)
  {
    if(distribution(generator) < i_mutationParameters.probabilityGen)
    {
      std::vector<std::vector<bool>> bin2 = i_population[i].chronosome;
      bin2[size - 1] = bin[rand % size];
      population[i].chronosome = {i_population[0].chronosome, bin2};
    }
  }
  return i_population;
}

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationInsertDel(
  MutationParameters i_mutationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  std::srand(std::time(0));
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0,1.0);

  int size = i_population[0].chronosome.size();
  
  TruthTable tt = {i_population[0].chronosome};
  std::vector<std::vector<bool>> bin = tt.OutTable;

  for (int i = 0; i < population.size(); ++i)
  {
    if (distribution(generator) < i_mutationParameters.probabilityGen)
    {
      std::vector<std::vector<bool>> bin2 = i_population[i].chronosome;
      bin2[rand % size] = bin[rand % size];
      population[i].chronosome = {population[0].chronosome, bin2};
    }
  }
  return i_population;
}

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationExchange(
  MutationParameters i_mutationParameters,
  std::vector<ChronosomeTpye<TruthTable, TruthTableParameters>> i_population
)
{
  std::srand(std::time(0));
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0,1.0);
  
  int type = i_mutationParameters.exchangeType;
  int size = i_population[0].chronosome.size();
  int output = i_population[0].chronosome.Output;

  int k = rand() % size;
  int n = rand() % output;

  for (int z = 0; z < population.size(); ++z)
  {
    if (distribution(generator) < i_mutationParameters.probabilityGen)
    {
      if (type == 0 || type == 1 || type == 2)
      {
        if (type == 0 || type == 1)
        {
          std::vector<std::vector<bool>> bin = i_population[z].chronosome;
          std::swap(bin[k - 1][n], bin[k + 1][n]);
          i_population[z].chronosome = {i_population[z].chronosome, bin};
        }

        if (type == 0 || type == 2) 
        {
          std::vector<std::vector<bin>> = i_population[z].chronosome;
          std::swap(bin[k - 1], bin[k + 1]);
          i_population[z].chronosome = {i_population[z].chronosome.Input,
                                      i_population[z].chronosome.Output,
                                      bin};
        }
      }
    }
  }
  return i_population;
}

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationDelete(
  MutationParameters i_mutationParameters,
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  std::srand(std::time(0));
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0,1.0);
  
  int size = i_population[0].chronosome.size();
  int output = i_population[0].chronosome.Output;

  for (int i = 0; i < i_population.size(); ++i)
  {
    if (distribution(generator) < i_mutationParameters.probabilityGen)
    {
      for (int j = 0; j < size(); ++j)
      {
        for (int k = 0; k < output; ++k)
        {
          if (distribution(generator) < i_mutationParameters.probabilityTruthTable)
          {
            std::vector<std::vector<bool>> bin = i_population[i].chronosome;
            bin[j][k] = false;
            population[i].chronosome = {i_population[i].chronosome, bin};
          }
        }
      }
    }
  }
  return i_population
}
