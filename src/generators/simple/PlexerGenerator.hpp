#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class PlexerGenerator : public SimpleGenerator {
public:
  PlexerGenerator();
  PlexerGenerator(uint_fast32_t i_seed);
  PlexerGenerator(const GenerationParameters& i_param);

  GraphPtr generatorMultiplexer(uint32_t i_bits);
  GraphPtr generatorDemultiplexer(uint32_t i_bits);

  GraphPtr generatorMultiplexer(const GenerationParameters &i_param);
  GraphPtr generatorDemultiplexer(const GenerationParameters &i_param);

  GraphPtr generatorMultiplexer();
  GraphPtr generatorDemultiplexer();
};
