#pragma once

#include <memory>
#include <vector>

#include <additional/RandomGeneratorWithSeed.hpp>
#include <generators/Genetic/GeneticParameters.h>
#include <settings/Settings.hpp>

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
  int                            getInput() const;
  int                            getOutput() const;
  int                            size() const;
  std::vector<std::vector<bool>> getOutTable() const;
  bool                           getOutTable(int i, int j) const;
  std::vector<std::vector<bool>> convToBinary() const;
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
