#include <ctime>

#include "RecombinationsTruthTable.hpp"

#include <additional/AuxiliaryMethods.hpp>

#include "../Mutations/MutationTruthTable.hpp"
#include "../Parents/Parents.hpp"

namespace RecombinationsTruthTable {
std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
RecombinationCrossingEachExitInTurnMany(
    RecombinationParameters i_recombinationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
        i_population) {
  // TODO: is it need? Parents<TruthTable, TruthTableParameters> p;
  int32_t input = i_population[0].getChromosomeType().getInput();
  int32_t output = i_population[0].getChromosomeType().getOutput();
  int32_t size = i_population[0].getChromosomeType().size();
  int32_t refPoints = i_recombinationParameters.getRefPoints();

  std::vector<int32_t> referencePoints;
  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> survivors;

  for (int32_t cr = 0;
       cr < i_recombinationParameters.getRecombinationParameters(); ++cr) {
    std::vector<int32_t> parentsInt = ParentsTypesWorker(
        i_recombinationParameters.getParentsParameters(), i_population);
    int32_t child1 = parentsInt[0];
    int32_t child2 = parentsInt[1];

    referencePoints = AuxMethods::getRandomIntList(refPoints, 0, size, false);

    std::vector<std::vector<std::vector<bool>>> parents;
    parents.push_back(i_population[child1].getChromosomeType().getOutTable());
    parents.push_back(i_population[child2].getChromosomeType().getOutTable());
    std::vector<std::vector<bool>> child(size, std::vector<bool>());
    int32_t stage = 0;

    for (int32_t j = 0; j < size; ++j) {
      if (stage < referencePoints.size() && j == referencePoints[stage])
        stage++;
      child[j] = parents[stage % parents.size()][j];
    }

    TruthTable tt(input, output, child);
    ChromosomeType<TruthTable, TruthTableParameters> tmp(
        "ind" + std::to_string(cr + 1), tt);
    survivors.push_back(tmp);
  }
  return survivors;
}

std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
RecombinationCrossingUniform(
    RecombinationParameters i_recombinationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
        i_population) {
  // Parents<TruthTable, TruthTableParameters> p;
  int32_t input = i_population[0].getChromosomeType().getInput();
  int32_t output = i_population[0].getChromosomeType().getOutput();
  int32_t size = i_population[0].getChromosomeType().size();

  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> survivors;

  for (int32_t cr = 0;
       cr < i_recombinationParameters.getRecombinationParameters(); ++cr) {
    std::vector<int32_t> parentsInt = ParentsTypesWorker(
        i_recombinationParameters.getParentsParameters(), i_population);
    int32_t child1 = parentsInt[0];
    int32_t child2 = parentsInt[1];

    TruthTable mask(input, output,
                    i_recombinationParameters.getMaskProbability());

    std::vector<std::vector<std::vector<bool>>> parents;
    parents.push_back(i_population[child1].getChromosomeType().getOutTable());
    parents.push_back(i_population[child2].getChromosomeType().getOutTable());
    std::vector<std::vector<bool>> child(size, std::vector<bool>(output));

    for (int32_t i = 0; i < size; ++i) {
      for (int32_t j = 0; j < output; ++j) {
        child[i][j] = parents[mask.getOutTable(i, j) ? 1 : 0][i][j];
      }
    }

    TruthTable tt(input, output, child);
    ChromosomeType<TruthTable, TruthTableParameters> tmp(
        "ind" + std::to_string(cr + 1), tt);
    survivors.push_back(tmp);
  }
  return survivors;
}

std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
RecombinationCrossingTriadic(
    RecombinationParameters i_recombinationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
        i_population) {
  int32_t input = i_population[0].getChromosomeType().getInput();
  int32_t output = i_population[0].getChromosomeType().getOutput();
  int32_t size = i_population[0].getChromosomeType().size();

  int32_t child3;
  std::srand(std::time(0));

  for (int32_t cr = 0;
       cr < i_recombinationParameters.getRecombinationParameters(); ++cr) {
    child3 = 0;
    std::vector<int32_t> parentsInt = ParentsTypesWorker(
        i_recombinationParameters.getParentsParameters(), i_population);
    int32_t child1 = parentsInt[0];
    int32_t child2 = parentsInt[1];

    while (child1 == child3 || child2 == child3)
      child3 = AuxMethods::getRandInt(0, i_population.size());

    TruthTable mask(input, output,
                    MutationTruthTable::MutationTable(
                        i_population[child3].getChromosomeType().getOutTable(),
                        i_recombinationParameters.getMaskProbability()));

    std::vector<std::vector<std::vector<bool>>> parents;
    parents.push_back(i_population[child1].getChromosomeType().getOutTable());
    parents.push_back(i_population[child2].getChromosomeType().getOutTable());
    std::vector<std::vector<bool>> child(size, std::vector<bool>(output));

    for (int32_t i = 0; i < size; ++i) {
      for (int32_t j = 0; j < output; ++j) {
        child[i][j] = parents[mask.getOutTable(i, j) ? 0 : 1][i][j];
      }
    }

    TruthTable tt(input, output, child);

    ChromosomeType<TruthTable, TruthTableParameters> tmp(
        "ind" + std::to_string(cr + 1), tt);
    i_population.push_back(tmp); // what????
  }

  i_population.clear(); // what??
  return i_population;  // what????
}

std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
RecombinationCrossingReducedReplacement(
    RecombinationParameters i_recombinationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
        i_population) {
  std::srand(std::time(0));

  int32_t input = i_population[0].getChromosomeType().getInput();
  int32_t output = i_population[0].getChromosomeType().getOutput();
  int32_t size = i_population[0].getChromosomeType().size();
  int32_t referencePoint = AuxMethods::getRandInt(0, size);

  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> survivors;

  for (int32_t cr = 0;
       cr < i_recombinationParameters.getRecombinationParameters(); ++cr) {
    std::vector<int32_t> parentsInt = ParentsTypesWorker(
        i_recombinationParameters.getParentsParameters(), i_population);
    int32_t child1 = parentsInt[0];
    int32_t child2 = parentsInt[1];

    std::vector<std::vector<std::vector<bool>>> parents;
    parents.push_back(i_population[child1].getChromosomeType().getOutTable());
    parents.push_back(i_population[child2].getChromosomeType().getOutTable());
    std::vector<std::vector<bool>> child(size, std::vector<bool>(output));

    for (int32_t j = 0; j < output; ++j) {
      while (parents[0][referencePoint][j] == parents[1][referencePoint][j])
        referencePoint = AuxMethods::getRandInt(0, size);

      for (int32_t i = 0; i < size; ++i)
        child[i][j] = parents[i < referencePoint ? 0 : 1][i][j];
    }
    TruthTable tt(input, output, child);
    ChromosomeType<TruthTable, TruthTableParameters> tmp(
        "ind" + std::to_string(cr + 1), tt);
    survivors.push_back(tmp);
  }
  return survivors;
}

std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
RecombinationCrossingShuffling(
    RecombinationParameters i_recombinationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
        i_population) {
  std::srand(std::time(0));

  int32_t input = i_population[0].getChromosomeType().getInput();
  int32_t output = i_population[0].getChromosomeType().getOutput();
  int32_t size = i_population[0].getChromosomeType().size();
  int32_t referencePoint = AuxMethods::getRandInt(0, size);

  std::vector<ChromosomeType<TruthTable, TruthTableParameters>> survivors;

  for (int32_t cr = 0;
       cr < i_recombinationParameters.getRecombinationParameters(); ++cr) {
    std::vector<int32_t> parentsInt = ParentsTypesWorker(
        i_recombinationParameters.getParentsParameters(), i_population);
    int32_t child1 = parentsInt[0];
    int32_t child2 = parentsInt[1];

    referencePoint = AuxMethods::getRandInt(0, size);
    std::vector<std::vector<std::vector<bool>>> parents;
    parents.push_back(i_population[child1].getChromosomeType().getOutTable());
    parents.push_back(i_population[child2].getChromosomeType().getOutTable());
    std::vector<std::vector<bool>> child(size, std::vector<bool>(output));

    for (int32_t i = 0; i < size; ++i) {
      for (int32_t j = 0; j < output; ++j) {
        if (AuxMethods::getRandInt(0, 2))
          swap(parents[0][i][j], parents[1][i][j]);
      }
    }

    for (int32_t i = 0; i < size; ++i) {
      for (int32_t j = 0; j < output; ++j) {
        child[i][j] = parents[i < referencePoint ? 0 : 1][i][j];
      }
    }
    TruthTable tt(input, output, child);
    ChromosomeType<TruthTable, TruthTableParameters> tmp(
        "ind" + std::to_string(cr + 1), tt);
    survivors.push_back(tmp);
  }
  return survivors;
}
// namespace end
} // namespace RecombinationsTruthTable