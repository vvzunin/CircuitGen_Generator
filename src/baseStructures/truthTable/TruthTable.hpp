#pragma once

#include <memory>
#include <vector>

#include <additional/RandomGeneratorWithSeed.hpp>
#include <generators/Genetic/GeneticParameters.h>
#include <settings/Settings.hpp>

/// class TruthTable
/// Represents a truth table for a combinational logic circuit
/// This class encapsulates the functionality to generate, manipulate, and
/// analyze truth tables for combinational logic circuits.
/// @param d_input Number of input variables.
/// @param d_output Number of output variables.
/// @param size Size of the truth table (number of rows).
/// @param d_array Output table representing the truth values.
/// @param d_settings Shared pointer to Settings object.
/// @param d_randGenerator Random number generator.

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

  /// @brief setSeed
  /// Set the seed for random number generation.
  /// This method sets the seed for the random number generator used in
  /// generating the truth table. Setting the seed allows for reproducible
  /// random number sequences.
  /// @param i_seed The seed for random number generation.
  /// @code
  /// TruthTable table;
  /// table.setSeed(123);
  /// @endcode
  /// For the getSeed method there is getSeed in RandomGeneratorWithSeed.hpp
  /// @see RandomGeneratorWithSeed

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

  /// @brief generateTable
  /// Generate a truth table with specified probability.
  /// This method generates a truth table with the given probability 'i_p".
  /// If `i_p` is greater than 0 and less than or equal to 1.
  /// @param i_p The probability of generating a true value for each cell
  /// in the truth table.

  void                           generateTable(double i_p = 0);

  /// @brief getInput
  /// Get the number of input variables in the truth table.
  /// @return The number of input variables.
  /// @code
  /// TruthTable table;
  /// int numInputs = table.getInput();
  /// std::cout << "Number of input variables: " << numInputs << std::endl;
  /// @endcode

  int                            getInput() const;

  /// @brief getOutput
  /// Get the number of output variables in the truth table
  /// @return The number of output variables.
  /// @code
  /// TruthTable table;
  /// int numOutputs = table.getOutput();
  /// std::cout << "Number of output variables: " << numOutputs << std::endl;
  /// @endcode

  int                            getOutput() const;

  /// @brief size
  /// Get the size of the truth table.
  /// This method returns the total number of rows in the truth table.
  /// Each rows corresponds to a unique combination of input values
  /// @return The size of the truth table (number of rows).
  /// @code
  /// // Creating a truth table with 3 input variables and 2 output variables
  /// TruthTable table (3,2);
  /// int tableSize = table.size();
  /// std::cout << "Size of the truth table: " << tableSize << std::endl;
  /// @endcode

  int                            size() const;

  /// @brief getOutTable
  /// Get the output table.
  /// This method returns a copy of the entire output table of the truth table.
  /// The output table contains the truth values for each combination of input
  /// variables.
  /// @return The output table as a two-dimensional vector of boolean values.
  /// @code
  /// // Assuming a truth table with 2 input variables and 1 output variable
  /// TruthTable table(2, 1);
  /// Get the output table
  /// std::vector<std::vector<bool>> outputTable = table.getOutTable();
  /// // Print the output table
  /// std::cout << "Output Table: " << std::endl;
  /// for (const auto& row : outputTable)
  /// {
  ///   for (bool value : row)
  ///   {
  ///     std:: cout << value << " ";
  ///   }
  ///   std::cout << endl;
  /// }
  /// @endcode

  std::vector<std::vector<bool>> getOutTable() const;

  /// @brief getOutTable
  /// Get the truth value at a specific position in the output table.
  /// This method returns the truth value at the specified position (i, j) in
  /// the output table.
  /// The position (i, j) corresponds to the i-th row and j-th column of the
  /// output table, representing a specific combination of input variables.
  /// @param i The row index of the output table.
  /// @param j The column index of the ouput table.
  /// @return The truth value at the specified position.
  /// @code
  /// // Assuming a truth table with 3 input variables and 2 output variable
  /// TruthTable table(3, 2);
  /// // Get the truth value at position (1, 0) in the output table
  /// bool value = table.getOutTable(1,0);
  /// @endcode

  bool                           getOutTable(int i, int j) const;

  /// @brief convToBinary
  /// Convert truth table indices to binary representation
  /// This method converts the indices of the truth table into binary
  /// representation.
  /// Each row index of the truth table corresponds to a unique combination
  /// of input variables, which is represented in binary form. For example,
  /// if the number of input variables is 3, the binary representation of the
  /// row index 5 (101 in binary) corresponds to the input combination
  /// [true, false, true].
  /// @return A two-dimensional vector representing the binary representation
  /// of each row index in the truth table.
  /// @code
  /// // Assuming a truth table with 3 input variables and 2 output variable
  /// TruthTable table(3, 2);
  /// Convert truth table indices to binary representation
  /// std::vector<std::vector<bool>> binRepresentation = table.convToBinary();
  /// // Print the binary representation
  /// std::cout << "Binary Representation of Truth Table Indices" << std::endl;
  /// for (cosnt auto& row: binRepresentation)
  /// {
  ///   for (bool bit : row)
  ///   {
  ///     std::cout << bit << " ";
  ///   }
  ///   std::cout << std::endl;
  /// }
  /// @endcode

  std::vector<std::vector<bool>> convToBinary() const;

  /// @brief printTable
  /// Print the truth table.
  /// This method prints the entire truth table to the standard output stream.
  /// Each row of the truth table is printed as a space-separated sequence of
  /// boolean values.
  /// After printing the table, a newline character is inserted to separate
  /// rows.
  /// @code
  /// // Assuming a truth table with 3 input variables and 2 output variable
  /// TruthTable table(3, 2);
  /// // Print the truth table
  /// table.printTable();
  /// @endcode

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
