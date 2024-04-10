#ifndef RANDOM_GENERATION_WITH_SEED
#define RANDOM_GENERATION_WITH_SEED

#include <cstdint>
#include <random>
#include <stdexcept>
#include <unordered_set>

class RandomGeneratorWithSeed {
public:
  RandomGeneratorWithSeed() = default;
  RandomGeneratorWithSeed(std::uint_fast32_t i_seed) { setSeed(i_seed); }

  RandomGeneratorWithSeed(const RandomGeneratorWithSeed& other)       = default;

  RandomGeneratorWithSeed& operator=(const RandomGeneratorWithSeed& other
  )                                                                   = default;

  RandomGeneratorWithSeed(RandomGeneratorWithSeed&& other)            = default;

  RandomGeneratorWithSeed& operator=(RandomGeneratorWithSeed&& other) = default;

  std::uint_fast32_t       getSeed() const { return d_seed; }

  void setSeed(std::uint_fast32_t i_seed) { d_gen.seed(i_seed); }

  int  getRandInt(int lower, int upper, bool inclusively = false) {
    if (!inclusively)
      upper--;

    if (upper == lower)
      return upper;

    if (upper < lower)
      throw std::invalid_argument(
          "RandomGeneratorWithSeed random int: upper: " + std::to_string(upper)
          + " boder is bigger than lower: " + std::to_string(lower)
      );

    std::uniform_int_distribution<> dis(lower, upper);

    return dis(d_gen);
  }

  std::vector<int> getRandomIntList(int i_n, int i_minNumber,
                                    int i_maxNumber, bool repite = false)
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

  double getRandDouble(double lower, double upper) {
    std::uniform_real_distribution<> dis(lower, upper);
    return dis(d_gen);
  }

private:
  std::uint_fast32_t d_seed;
  std::minstd_rand   d_gen;
};

#endif