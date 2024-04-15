#pragma once

#include <memory>
#include <vector>

#include <additional/RandomGeneratorWithSeed.hpp>
#include <generators/Genetic/GeneticParameters.h>
#include <settings/Settings.hpp>

/// class TruthTable
/// @param d_input The number of input variables of the combinational scheme,
/// which determines the number of bits of the input vector
/// @param d_output The number of output variables of the combinational circuit,
/// which determines the number of bits of the output vector
/// @param d_size The size of the truth table, which may differ from the total
/// number of combinations of input values (usually equal to 2^d_input)
/// @param d_array A two-dimensional vector representing the truth table of a
/// combinational scheme, where each element defines an output value for a
/// specific combination of input variables
/// @param d_setting A pointer to an object of the settings class, which is
/// probably used to control the behavior of the class or store some
/// configuration parameters
/// @param d_randGenerator A grain-set random number generator that is used to
/// create random truth tables
/// */

class TruthTable {
public:
  TruthTable();

  TruthTable(int seed);
  // TruthTable(const TruthTable& other)            = default;
  TruthTable& operator=(const TruthTable& other) = default;
  TruthTable(TruthTable&& other)                 = default;
  TruthTable& operator=(TruthTable&& other)      = default;
  TruthTable(
      int                                   i_input,
      int                                   i_output,
      const std::vector<std::vector<bool>>& i_array = {}
  );
  TruthTable(
      const TruthTable&              i_tt,
      std::vector<std::vector<bool>> i_array = {}
  );
  TruthTable(int i_input, int i_output, double i_p = 0.5);

  /// @brief setSeed The method sets the seed for the random number generator
  /// used in the class.
  /// @param i_seed The value of the grain to be set for the random number
  /// generator
  /// */

  void                           setSeed(int i_seed);
  // void generateRandom(TruthTableParameters i_gp) override;

  /// @brief generateTable The method generates a truth table for a
  /// combinational circuit with a given probability i_p for each output value.
  /// @param i_p The probability of generating a unit (true value) for each
  /// output bit. If i_p == 0, then all output values are randomly generated
  /// with equal probability. If i_p > 0 and i_p <= 1, then each output bit has
  /// a probability of i_p being equal to one.
  /// */

  void                           generateRandom(TruthTableParameters i_gp);
  void                           generateTable(double i_p = 0);

  /// @brief getInput The method returns the number of input variables of the
  /// combinational scheme
  /// @return The number of input variables of the combinational scheme
  /// */

  int                            getInput() const;

  /// @brief getOutput The method returns the number of output variables of the
  /// combinational scheme
  /// @return The number of output variables of the combinational circuit
  ///

  int                            getOutput() const;

  /// @brief size The method returns the size of the truth table, that is, the
  /// number of combinations of input variables
  /// @return The size of the truth table, that is, the number of combinations
  /// of input variables
  /// */

  int                            size() const;

  /// @brief getOutTable The method returns a truth table in the form of a
  /// two-dimensional vector std::vector<std::vector<bool>>.
  /// @return std::vector<std::vector<bool>>: The truth table of the
  /// combinational scheme, where each internal vector represents the values of
  /// the output variables for the corresponding combination of input variables
  /// */

  std::vector<std::vector<bool>> getOutTable() const;

  /// @brief getOutTable The method returns the value of the output variable for
  /// the specified combination of input variables
  /// @param i Index of the combination of input variables
  /// @param j Index of the output variable
  /// @return bool: The value of the output variable for the specified
  /// combination of input variables
  /// */

  bool                           getOutTable(int i, int j) const;

  /// @brief convToBinary The method converts indexes of combinations of input
  /// variables into their binary representation.
  /// @return std::vector<std::vector<bool>>: A two-dimensional vector where
  /// each internal vector represents a binary representation of the index of a
  /// combination of input variables
  /// */

  std::vector<std::vector<bool>> convToBinary() const;
  // TODO: Добавить
  void                           printTable() const;
  bool                           operator==(const TruthTable& r) const;

private:
  int                            d_input;
  int                            d_output;
  int                            d_size;
  std::vector<std::vector<bool>> d_array;
  std::shared_ptr<Settings> d_settings = Settings::getInstance("TruthTable");
  RandomGeneratorWithSeed   d_randGenerator;
};
