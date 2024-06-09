#include <ctime>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

#include "TruthTable.hpp"

#include <additional/AuxiliaryMethods.hpp>

TruthTable::TruthTable() {
  d_randGenerator.setSeed(AuxMethods::getRandSeed());
  d_settings = Settings::getInstance("TruthTable");
}

TruthTable::TruthTable(uint_fast32_t i_seed) {
  d_randGenerator.setSeed(i_seed);
  d_settings = Settings::getInstance("TruthTable");
}

// TruthTable::TruthTable(const Chromosome<TruthTableParameters> &i_chr)
// {
//     d_randGenerator.setSeed(AuxMethods::getRandSeed());
//     d_settings = Settings::getInstance("TruthTable");
// }

void TruthTable::setSeed(uint_fast32_t i_seed) {
  d_randGenerator.setSeed(i_seed);
}

TruthTable::TruthTable(
    int32_t                               i_input,
    int32_t                               i_output,
    const std::vector<std::vector<bool>>& i_array
) :
  d_input(i_input), d_output(i_output) {
  d_size = 1u << d_input;
  if (i_array.size() == 0 || i_array.size() != d_size
      || i_array[0].size() != d_output)
    generateTable(0);
  else
    d_array = i_array;
}

TruthTable::TruthTable(
    const TruthTable&              i_tt,
    std::vector<std::vector<bool>> i_array
) {
  d_input  = i_tt.d_input;
  d_output = i_tt.d_output;
  d_size   = i_tt.d_size;
  if (i_array.empty() || i_array.size() != d_size
      || i_array[0].size() != d_output) {
    generateRandom(TruthTableParameters(d_input, d_output));
  } else {
    d_array = i_array;
  }
}

TruthTable::TruthTable(int32_t i_input, int32_t i_output, double i_p) :
  d_input(i_input), d_output(i_output) {
  d_size = (1u << i_input);
  generateTable(i_p);
}

std::vector<std::vector<bool>> TruthTable::convToBinary() const {
  std::vector<std::vector<bool>> bin(d_size, std::vector<bool>(d_input));
  for (int32_t i = 0; i < d_size; ++i) {
    for (int32_t j = d_input - 1, tmp = i; j >= 0; --j) {
      bin[i][j] = (tmp % 2) == 1;
      tmp       /= 2;
    }
  }
  return bin;
}

int32_t TruthTable::getInput() const {
  return d_input;
}

int32_t TruthTable::getOutput() const {
  return d_output;
}

int32_t TruthTable::size() const {
  return d_size;
}

std::vector<std::vector<bool>> TruthTable::getOutTable() const {
  return d_array;
}

bool TruthTable::getOutTable(int32_t i, int32_t j) const {
  return d_array.at(i).at(j);
}

void TruthTable::generateRandom(TruthTableParameters i_gp) {
  std::srand(std::time(0));
  if (i_gp.getInputs() == 0) {
    i_gp = TruthTableParameters();
    i_gp.setInputs(d_randGenerator.getRandInt(0, d_settings->getMaxInputs()));
    i_gp.setOutputs(d_randGenerator.getRandInt(0, d_settings->getMaxOutputs()));
  }

  d_input  = i_gp.getInputs();
  d_output = i_gp.getOutputs();
  d_size   = 1u << d_input;

  d_array.clear();
  d_array.resize(d_size);

  for (int32_t i = 0; i < d_size; ++i) {
    d_array[i].resize(i_gp.getOutputs());
    for (int32_t j = 0; j < i_gp.getOutputs(); ++j)
      d_array[i][j] = d_randGenerator.getRandInt(0, 1, true) == 1;
  }
}

void TruthTable::generateTable(double i_p) {
  if (i_p <= 0) {
    d_array.clear();
    d_array.resize(d_size);
    for (int32_t i = 0; i < d_size; ++i) {
      d_array[i].resize(d_output);
      for (int32_t j = 0; j < d_output; ++j)
        d_array[i][j] = d_randGenerator.getRandInt(0, 1, true) == 1;
    }
    return;
  }
  if (i_p > 0 && i_p <= 1) {
    d_array.clear();
    d_array.resize(d_size);
    for (int32_t i = 0; i < d_size; ++i) {
      d_array[i].resize(d_output);
      for (int32_t j = 0; j < d_output; ++j)
        d_array[i][j] = AuxMethods::getRandDouble(0, 1) < i_p;
    }
    return;
  }
}

bool TruthTable::operator==(const TruthTable& r) const {
  return std::tie(d_input, d_output, d_size, d_array)
      == std::tie(r.d_input, r.d_output, r.d_size, r.d_array);
}

void TruthTable::printTable() const {
  std::stringstream ss;
  for (const auto& row : d_array) {
    std::copy(row.begin(), row.end(), std::ostream_iterator<bool>(ss, " "));
    ss << '\n';
  }
  std::cout << ss.str();
}