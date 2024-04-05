#include "RandomGeneratorWithSeed.h"

int RandomGeneratorWithSeed::getRandInt(int lower, int upper, bool inclusively)
{
  if (!inclusively) upper--;

  if (upper == lower) return upper;

  if (upper < lower)
      throw std::invalid_argument(
          "RandomGeneratorWithSeed random int: upper boder is bigger than "
          "lower");

  std::uniform_int_distribution<> dis(lower, upper);

  return dis(d_gen);
}

std::vector<int> RandomGeneratorWithSeed::getRandomIntList(int i_n, int i_minNumber, int i_maxNumber, bool repite)
{
  std::vector<int> randomNumbers;

  if (repite) {
    // Если повторения разрешены, просто генерируем числа.
    for (int i = 0; i < i_n; ++i) {
            randomNumbers.push_back(getRandInt(i_minNumber, i_maxNumber, false));
    }
  } 
  else {
    // Если повторения запрещены, используем set для проверки существующих чисел.
    std::unordered_set<int> used;
    while (randomNumbers.size() < static_cast<size_t>(i_n)) {
      int number = getRandInt(i_minNumber, i_maxNumber, false);
      // Добавляем только уникальные числа.
      if (used.insert(number).second) {
        randomNumbers.push_back(number);
      }
    }
  }
  return randomNumbers;
}

double RandomGeneratorWithSeed::getRandDouble(double lower, double upper)
{
  std::uniform_real_distribution<> dis(lower, upper);
  return dis(d_gen);
}
