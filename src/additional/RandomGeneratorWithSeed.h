#ifndef RANDOM_GENERATION_WITH_SEED
#define RANDOM_GENERATION_WITH_SEED

#include <random>
#include <cstdint>
#include <stdexcept>


class RandomGeneratorWithSeed {
    public:

    RandomGeneratorWithSeed() = default;
    RandomGeneratorWithSeed(std::uint_fast32_t i_seed) {
        setSeed(i_seed);
    }

    RandomGeneratorWithSeed(const RandomGeneratorWithSeed &other) = default;

    RandomGeneratorWithSeed &operator=(const RandomGeneratorWithSeed &other) = default;

    RandomGeneratorWithSeed(RandomGeneratorWithSeed &&other) = default;

    RandomGeneratorWithSeed &operator=(RandomGeneratorWithSeed &&other) = default;

    std::uint_fast32_t getSeed() const {
        return d_seed;
    }

    void setSeed(std::uint_fast32_t i_seed) {
        d_gen.seed(i_seed);
    }

    int getRandInt(int lower, int upper, bool inclusively = false)
    {
        if (!inclusively)
            upper--;
        
        if (upper == lower)
            return upper;
        
        if (upper < lower)
            throw std::invalid_argument("RandomGeneratorWithSeed random int: upper boder is bigger than lower");

        std::uniform_int_distribution<> dis(lower, upper);

        return dis(d_gen);
    }

    double getRandDouble(double lower, double upper)
    {
        std::uniform_real_distribution<> dis(lower, upper);
        return dis(d_gen);
    }

    private:
    std::uint_fast32_t d_seed;
    std::minstd_rand d_gen;
};

<<<<<<< HEAD:src/additional/RandomGeneratorWithSeed.h
#endif
=======
#endif
>>>>>>> main:Generator/source/AuxiliaryMethods/RandomGeneratorWithSeed.h
