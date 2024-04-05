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

  RandomGeneratorWithSeed(const RandomGeneratorWithSeed &other) = default;

  RandomGeneratorWithSeed &operator=(const RandomGeneratorWithSeed &other) =
      default;

  RandomGeneratorWithSeed(RandomGeneratorWithSeed &&other) = default;

  RandomGeneratorWithSeed &operator=(RandomGeneratorWithSeed &&other) = default;

  std::uint_fast32_t getSeed() const { return d_seed; }

  void setSeed(std::uint_fast32_t i_seed) { d_gen.seed(i_seed); }

  int getRandInt(int lower, int upper, bool inclusively = false);
  std::vector<int> getRandomIntList(int i_n, int i_minNumber,
                                    int i_maxNumber, bool repite = false);
  
  double getRandDouble(double lower, double upper);
  
 private:
  std::uint_fast32_t d_seed;
  std::minstd_rand d_gen;
};

#endif
