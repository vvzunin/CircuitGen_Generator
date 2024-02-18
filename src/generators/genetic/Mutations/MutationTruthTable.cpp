#include <algorithm>
#include <vector>
#include <ctime>

#include "MutationTruthTable.h"
#include "../../../AuxiliaryMethods.h"

std::vector<std::vector<bool>> MutationTable(std::vector<std::vector<bool>> i_table,
                                            double i_probability)
{
  for (int i = 0; i < i_table.size(); ++i)
  {
    for (int j = 0; j < i_table[i].size(); ++j)
    {
      if (AuxMethods::getRandDouble(0, 1) < i_probability)
      {
        i_table[i][j] = !i_table[i][j];
      }
    }
  }
  return i_table;
}

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> MutationBinary(
  MutationParameters i_mutationParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> mutants;
  int num_mut, k, n;
  int size = i_population[0].getChromosomeType().size();
  int output = i_population[0].getChromosomeType().getOutput();
  for (int i = 0; i < i_population.size(); ++i)
  {
    num_mut = (AuxMethods::getRandInt(1, size * output, true));
    std::vector<std::vector<bool>> mutant = i_population[i].getChromosomeType().getOutTable();
    std::vector<int> m;
    for (int j = 0; j < num_mut; ++j)
    {
      do
      {
        n = AuxMethods::getRandInt(0, output);
        k = AuxMethods::getRandInt(0, size);
      }
      while (std::find(m.begin(), m.end(), k*output + n) != m.end());
      m.push_back(k*output + n);
      mutant[k][n] = !mutant[k][n];
    }
    TruthTable tt = {i_population[i].getChromosomeType(), mutant};
    ChromosomeType<TruthTable, TruthTableParameters> tmp = {i_population[i].getName(), tt};
    mutants.push_back(tmp);
  }
  return mutants;
}

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> MutationDensity(
  MutationParameters i_mutationParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  
  TruthTable tt = {i_population[0].getChromosomeType().getInput(), i_population[0].getChromosomeType().getOutput(), {}};
  //std::vector<bool> bin = tt.getOutTable();

  for (int i = 0; i < i_population.size(); ++i)
  {
    if (AuxMethods::getRandDouble(0, 1) < i_mutationParameters.getProbabilityGen())
    {
      std::vector<std::vector<bool>> mutant = MutationTable(
        i_population[i].getChromosomeType().getOutTable(),
        i_mutationParameters.getProbabilityTruthTable()
      );
      i_population[i].setChromosomeType(TruthTable(i_population[i].getChromosomeType(), mutant));
    }
  }
  return i_population;
}

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> MutationAccessionDel(
  MutationParameters i_mutationParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  int size = i_population[0].getChromosomeType().size();

  TruthTable tt = {i_population[0].getChromosomeType().getInput(), i_population[0].getChromosomeType().getOutput(), {}};
  std::vector<std::vector<bool>> bin = tt.getOutTable();

  for (int i = 0; i < i_population.size(); ++i)
  {
    if (AuxMethods::getRandDouble(0, 1) < i_mutationParameters.getProbabilityGen())
    {
      std::vector<std::vector<bool>> bin2 = i_population[i].getChromosomeType().getOutTable();
      bin2[size - 1] = bin[AuxMethods::getRandInt(0, size)];
      i_population[i].setChromosomeType(TruthTable(i_population[0].getChromosomeType(), bin2));
    }
  }
  return i_population;
}

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> MutationInsertDel(
  MutationParameters i_mutationParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
)
{

  int size = i_population[0].getChromosomeType().size();
  
  TruthTable tt = {i_population[0].getChromosomeType()};
  std::vector<std::vector<bool>> bin = tt.getOutTable();

  for (int i = 0; i < i_population.size(); ++i)
  {
    if (AuxMethods::getRandDouble(0, 1) < i_mutationParameters.getProbabilityGen())
    {
      std::vector<std::vector<bool>> bin2 = i_population[i].getChromosomeType().getOutTable();
      bin2[AuxMethods::getRandInt(0, size)] = bin[AuxMethods::getRandInt(0, size)];
      i_population[i].setChromosomeType(TruthTable(i_population[0].getChromosomeType(), bin2));
    }
  }
  return i_population;
}

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> MutationExchange(
  MutationParameters i_mutationParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  
  int type = i_mutationParameters.getExchangeType();
  int size = i_population[0].getChromosomeType().size();
  int output = i_population[0].getChromosomeType().getOutput();

  int k = AuxMethods::getRandInt(0, size);
  int n = AuxMethods::getRandInt(0, output);

  for (int z = 0; z < i_population.size(); ++z)
  {
    if (AuxMethods::getRandDouble(0, 1) < i_mutationParameters.getProbabilityGen())
    {
      if (type == 0 || type == 1 || type == 2)
      {
        if (type == 0 || type == 1)
        {
          std::vector<std::vector<bool>> bin = i_population[z].getChromosomeType().getOutTable();
          std::swap(bin[k - 1][n], bin[k + 1][n]);
          i_population[z].setChromosomeType(TruthTable(i_population[z].getChromosomeType(), bin));
        }

        if (type == 0 || type == 2) 
        {
          std::vector<std::vector<bool>> bin = i_population[z].getChromosomeType().getOutTable();
          std::swap(bin[k - 1], bin[k + 1]);
          i_population[z].setChromosomeType(TruthTable(i_population[z].getChromosomeType().getInput(),
                                      i_population[z].getChromosomeType().getOutput(),
                                      bin));
        }
      }
    }
  }
  return i_population;
}

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> MutationDelete(
  MutationParameters i_mutationParameters,
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
)
{
  
  int size = i_population[0].getChromosomeType().size();
  int output = i_population[0].getChromosomeType().getOutput();

  for (int i = 0; i < i_population.size(); ++i)
  {
    if (AuxMethods::getRandDouble(0, 1) < i_mutationParameters.getProbabilityGen())
    {
      for (int j = 0; j < size; ++j)
      {
        for (int k = 0; k < output; ++k)
        {
          if (AuxMethods::getRandDouble(0, 1) < i_mutationParameters.getProbabilityTruthTable())
          {
            std::vector<std::vector<bool>> bin = i_population[i].getChromosomeType().getOutTable();
            bin[j][k] = false;
            i_population[i].setChromosomeType(TruthTable(i_population[i].getChromosomeType(), bin));
          }
        }
      }
    }
  }
  return i_population;
}
