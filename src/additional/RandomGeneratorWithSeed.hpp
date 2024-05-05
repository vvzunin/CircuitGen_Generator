#ifndef RANDOM_GENERATION_WITH_SEED
#define RANDOM_GENERATION_WITH_SEED

#include <cstdint>
#include <random>
#include <stdexcept>
#include <unordered_set>

/// class RandomGeneratorWithSeed
/// The Random Generator With Seed class is a C++ class designed to generate
/// random numbers using a specified seed value
/// @param d_seed Holds the current seed value.
/// @param d_gen std::minstd_rand object used for generating random numbers.
/// */

class RandomGeneratorWithSeed {
public:
  RandomGeneratorWithSeed() = default;
  RandomGeneratorWithSeed(std::uint_fast32_t i_seed) { setSeed(i_seed); }

  RandomGeneratorWithSeed(const RandomGeneratorWithSeed& other)       = default;

  RandomGeneratorWithSeed& operator=(const RandomGeneratorWithSeed& other
  )                                                                   = default;

  RandomGeneratorWithSeed(RandomGeneratorWithSeed&& other)            = default;

  RandomGeneratorWithSeed& operator=(RandomGeneratorWithSeed&& other) = default;

  /// @brief getSeed
  /// Get the current seed value
  /// This method returns the current seed value used to initialize the random
  /// number generator
  /// @return The seed value as a 32-bit unsigned integer.

  std::uint_fast32_t       getSeed() const { return d_seed; }

  void setSeed(std::uint_fast32_t i_seed) { d_gen.seed(i_seed); }

  /// @brief getRandInt Method to generate a random integer within a specified
  /// range.
  /// @param lower The lower limit of the range of random integers, inclusive,
  /// from which to generate a number
  /// @param upper The upper limit of the range of random integers, inclusive,
  /// from which to generate a number
  /// @param inclusively flag indicating whether the upper limit of the range is
  /// inclusive. If set to true, the upper bound is also included in the range
  /// of random numbers, otherwise it is excluded from the range
  /// @return dis The generated integer in the range between lower and upper
  /// */

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

  std::vector<int> getRandomIntList(
      int  i_n,
      int  i_minNumber,
      int  i_maxNumber,
      bool repite = false
  ) {
    std::vector<int> randomNumbers;

    if (repite) {
      // Если повторения разрешены, просто генерируем числа.
      for (int i = 0; i < i_n; ++i) {
        randomNumbers.push_back(getRandInt(i_minNumber, i_maxNumber, false));
      }
    } else {
      // Если повторения запрещены, используем set для проверки существующих
      // чисел.
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