
#include <algorithm>
#include <ctime>
#include <random>
#include <vector>

#include "MutationTruthTable.hpp"

#include <additional/AuxiliaryMethods.hpp>

namespace MutationTruthTable {
std::vector<std::vector<bool>> MutationTable(
    std::vector<std::vector<bool>> i_table,
    double                         i_probability
) {
  std::srand(std::time(0));
  std::default_random_engine             generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  for (size_t i = 0; i < i_table.size(); ++i) {
    for (size_t j = 0; j < i_table[i].size(); ++j) {
      if (distribution(generator) < i_probability) {
        i_table[i][j] = !i_table[i][j];
      }
    }
  }
  return i_table;
}

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationBinary(
    MutationParameters i_mutationParameters,
    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
) {
  std::vector<ChronosomeType<TruthTable, TruthTableParameters>> mutants;
  int32_t                                                       num_mut, k, n;
  size_t  size   = i_population[0].getChronosomeType().size();
  int32_t output = i_population[0].getChronosomeType().getOutput();
  std::srand(time(0));
  for (size_t i = 0; i < i_population.size(); ++i) {
    num_mut = AuxMethods::getRandInt(1, (size * output), true);
    std::vector<std::vector<bool>> mutant =
        i_population[i].getChronosomeType().getOutTable();
    std::vector<int32_t> m;
    for (int32_t j = 0; j < num_mut; ++j) {
      do {
        n = AuxMethods::getRandInt(0, output);
        k = AuxMethods::getRandInt(0, size);
      } while (std::find(m.begin(), m.end(), k * output + n) != m.end());
      m.push_back(k * output + n);
      mutant[k][n] = !mutant[k][n];
    }
    TruthTable tt = {i_population[i].getChronosomeType(), mutant};
    ChronosomeType<TruthTable, TruthTableParameters> tmp = {
        i_population[i].getName(), tt};
    mutants.push_back(tmp);
  }
  return mutants;
}

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationDensity(
    MutationParameters i_mutationParameters,
    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
) {
  std::srand(std::time(0));
  std::default_random_engine             generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  TruthTable                             tt = {
      i_population[0].getChronosomeType().getInput(),
      i_population[0].getChronosomeType().getOutput(),
      {}};
  // std::vector<bool> bin = tt.getOutTable();

  for (size_t i = 0; i < i_population.size(); ++i) {
    if (distribution(generator) < i_mutationParameters.getProbabilityGen()) {
      std::vector<std::vector<bool>> mutant = MutationTable(
          i_population[i].getChronosomeType().getOutTable(),
          i_mutationParameters.getProbabilityTruthTable()
      );
      i_population[i].setChronosomeType(
          TruthTable(i_population[i].getChronosomeType(), mutant)
      );
    }
  }
  return i_population;
}

std::vector<ChronosomeType<TruthTable, TruthTableParameters>>
    MutationAccessionDel(
        MutationParameters i_mutationParameters,
        std::vector<ChronosomeType<TruthTable, TruthTableParameters>>
            i_population
    ) {
  std::srand(std::time(0));
  std::default_random_engine             generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  int64_t    size = i_population[0].getChronosomeType().size();

  TruthTable tt   = {
      i_population[0].getChronosomeType().getInput(),
      i_population[0].getChronosomeType().getOutput(),
      {}};
  std::vector<std::vector<bool>> bin = tt.getOutTable();

  for (size_t i = 0; i < i_population.size(); ++i) {
    if (distribution(generator) < i_mutationParameters.getProbabilityGen()) {
      std::vector<std::vector<bool>> bin2 =
          i_population[i].getChronosomeType().getOutTable();
      bin2[size - 1] = bin[AuxMethods::getRandInt(0, size)];
      i_population[i].setChronosomeType(
          TruthTable(i_population[0].getChronosomeType(), bin2)
      );
    }
  }
  return i_population;
}

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationInsertDel(
    MutationParameters i_mutationParameters,
    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
) {
  std::srand(std::time(0));
  std::default_random_engine             generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  int64_t    size = i_population[0].getChronosomeType().size();

  TruthTable tt   = {i_population[0].getChronosomeType()};
  std::vector<std::vector<bool>> bin = tt.getOutTable();

  for (size_t i = 0; i < i_population.size(); ++i) {
    if (distribution(generator) < i_mutationParameters.getProbabilityGen()) {
      std::vector<std::vector<bool>> bin2 =
          i_population[i].getChronosomeType().getOutTable();
      bin2[AuxMethods::getRandInt(0, size)] =
          bin[AuxMethods::getRandInt(0, size)];
      i_population[i].setChronosomeType(
          TruthTable(i_population[0].getChronosomeType(), bin2)
      );
    }
  }
  return i_population;
}

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationExchange(
    MutationParameters i_mutationParameters,
    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
) {
  std::srand(std::time(0));
  std::default_random_engine             generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  int32_t type   = i_mutationParameters.getExchangeType();
  int32_t size   = i_population[0].getChronosomeType().size();
  int32_t output = i_population[0].getChronosomeType().getOutput();

  int32_t k      = AuxMethods::getRandInt(0, size);
  int32_t n      = AuxMethods::getRandInt(0, output);

  for (size_t z = 0; z < i_population.size(); ++z) {
    if (distribution(generator) < i_mutationParameters.getProbabilityGen()) {
      if (type == 0 || type == 1 || type == 2) {
        if (type == 0 || type == 1) {
          std::vector<std::vector<bool>> bin =
              i_population[z].getChronosomeType().getOutTable();
          bin[n].swap(bin[k - 1][n], bin[k + 1][n]);
          i_population[z].setChronosomeType(
              TruthTable(i_population[z].getChronosomeType(), bin)
          );
        }

        if (type == 0 || type == 2) {
          std::vector<std::vector<bool>> bin =
              i_population[z].getChronosomeType().getOutTable();
          std::vector tmp = bin[k - 1];
          bin[k - 1]      = bin[k + 1];
          bin[k + 1]      = tmp;
          i_population[z].setChronosomeType(TruthTable(
              i_population[z].getChronosomeType().getInput(),
              i_population[z].getChronosomeType().getOutput(),
              bin
          ));
        }
      }
    }
  }
  return i_population;
}

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> MutationDelete(
    MutationParameters i_mutationParameters,
    std::vector<ChronosomeType<TruthTable, TruthTableParameters>> i_population
) {
  std::srand(std::time(0));
  std::default_random_engine             generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  int32_t size   = i_population[0].getChronosomeType().size();
  int32_t output = i_population[0].getChronosomeType().getOutput();

  for (size_t i = 0; i < i_population.size(); ++i) {
    if (distribution(generator) < i_mutationParameters.getProbabilityGen()) {
      for (int32_t j = 0; j < size; ++j) {
        for (int32_t k = 0; k < output; ++k) {
          if (distribution(generator)
              < i_mutationParameters.getProbabilityTruthTable()) {
            std::vector<std::vector<bool>> bin =
                i_population[i].getChronosomeType().getOutTable();
            bin[j][k] = false;
            i_population[i].setChronosomeType(
                TruthTable(i_population[i].getChronosomeType(), bin)
            );
          }
        }
      }
    }
  }
  return i_population;
}
// namespace end
}  // namespace MutationTruthTable
