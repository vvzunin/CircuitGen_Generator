#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class ArithmeticGenerator : public SimpleGenerator {
public:
  ArithmeticGenerator();
  ArithmeticGenerator(uint_fast32_t i_seed);
  ArithmeticGenerator(const GenerationParameters &i_param);

  /// @brief generatorSummator represents the generation of a combinational
  /// adder circuit. It is based on the arithmetic operation of addition in the
  /// decimal system and creates a graph of logical elements for its
  /// implementation. The number of bits fed into it is the length of the
  /// numbers that are converted from decimal to binary notation to implement
  /// the graph. Both the half-version and the full version are used as the
  /// basis of the generation.
  /// @param i_bits The number of bits, or in other words, input vertices
  /// (variables), which will be twice as many in the graph
  /// @param i_overflowIn A Boolean flag indicating whether to create an
  /// additional input vertex (variable) in the graph at the beginning of
  /// generation
  /// @param i_overflowOut A Boolean flag indicating whether to create an
  /// additional output vertex (variable) in the graph at the end of generation
  /// @param i_minus A Boolean flag indicating whether it is worth adding
  /// logical vertices of type NOT to the graph to select a negative sum
  /// @return the created OrientedGraph

  GraphPtr generatorSummator(uint32_t i_bits, bool i_overflowIn,
                             bool i_overflowOut, bool i_minus);

  /// @brief generatorComparison represents the generation of a combinational
  /// comparator circuit. It is able to compare the submitted data in three
  /// variants: "equal", "less", "more". Reads the bits of numbers from larger
  /// to smaller, taking into account the significance of the higher bits.
  /// numbers that are converted from decimal to binary notation to implement
  /// the graph
  /// @param i_bits The number of bits, or in other words, input vertices
  /// (variables), which will be twice as many in the graph
  /// @param compare0 A Boolean flag indicating whether to perform the
  /// "equality" ("=") comparison operation between two bits of different
  /// numbers.
  /// @param compare1 A Boolean flag indicating indicating whether to perform
  /// the "less" ("<") comparison operation between two bits of different
  /// numbers.
  /// @param compare2 A Boolean flag indicating indicating whether to perform
  /// the "more" (">") comparison operation between two bits of different
  /// numbers.
  /// @return the created OrientedGraph

  GraphPtr generatorSubtractor(uint32_t i_bits, bool i_overflowIn,
                               bool i_overflowOut, bool i_sub);

  GraphPtr generatorMultiplier(uint32_t i_bits);

  GraphPtr generatorSummator(const GenerationParameters &i_param);

  GraphPtr generatorSubtractor(const GenerationParameters &i_param);

  GraphPtr generatorMultiplier(const GenerationParameters &i_param);

  GraphPtr generatorSummator();

  GraphPtr generatorSubtractor();

  GraphPtr generatorMultiplier();
};
