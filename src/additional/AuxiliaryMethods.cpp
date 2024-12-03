#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string_view>
#include <utility>
#include <vector>

#include "AuxiliaryMethods.hpp"

#include <additional/AuxiliaryMethods.hpp>

#include "RandomGeneratorWithSeed.hpp"

namespace {
std::vector<std::string> splitString(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream ss(s);
  std::string token;

  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }

  return tokens;
}

RandomGeneratorWithSeed gen;

// namespace end
} // namespace

void AuxMethods::setRandSeed(std::uint_fast32_t seed) {
  gen.setSeed(seed);
}

std::uint_fast32_t AuxMethods::getRandSeed() {
  return gen.getSeed();
}

int32_t AuxMethods::getRandInt(int32_t lower, int32_t upper, bool inclusively) {
  return gen.getRandInt(lower, upper, inclusively);
}

double AuxMethods::getRandDouble(double lower, double upper) {
  return gen.getRandDouble(lower, upper);
}

std::string AuxMethods::readAllFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("Failed to open file: " + filename);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string str = buffer.str();
  size_t pos;
  // Замена всех вхождений \r\n на \n
  while ((pos = str.find("\r\n")) != std::string::npos) {
    str.replace(pos, 2, "\n");
  }
  return str;

  return buffer.str();
}

std::vector<int32_t> AuxMethods::getRandomIntList(size_t i_n,
                                                  int32_t i_minNumber,
                                                  int32_t i_maxNumber,
                                                  bool repite) {
  return gen.getRandomIntList(i_n, i_minNumber, i_maxNumber, repite);
}

template<typename Key, typename Value>
std::vector<std::pair<Key, Value>>
AuxMethods::sortDictByValue(const std::map<Key, Value> &i_dict, bool up) {
  std::vector<std::pair<Key, Value>> pairs(i_dict.begin(), i_dict.end());

  // Define a lambda function to compare values
  auto cmp = [](const std::pair<Key, Value> &lhs,
                const std::pair<Key, Value> &rhs) {
    return lhs.second < rhs.second;
  };

  // Sort the vector of pairs based on the values
  std::sort(pairs.begin(), pairs.end(), cmp);
  if (!up)
    std::reverse(pairs.begin(), pairs.end());

  return pairs;
}

template<typename T>
std::vector<std::vector<T>>
AuxMethods::transpose(const std::vector<std::vector<T>> &matrix) {
  if (matrix.empty() || matrix[0].empty())
    return matrix;

  std::vector<std::vector<T>> transposed(matrix[0].size(),
                                         std::vector<T>(matrix.size()));

  for (size_t i = 0; i < matrix.size(); ++i) {
    for (size_t j = 0; j < matrix[i].size(); ++j) {
      transposed[j][i] = matrix[i][j];
    }
  }

  return transposed;
}

template std::vector<std::vector<VertexPtr>>
AuxMethods::transpose(const std::vector<std::vector<VertexPtr>> &matrix);
// explicit instantiation of sortDictByValue
// if you want to use this func with other types, just add corresponding
// instantiation below, compilation error otherwise.
template std::vector<std::pair<int32_t, int32_t>>
AuxMethods::sortDictByValue(const std::map<int32_t, int32_t> &i_dict, bool up);

template std::vector<std::pair<int32_t, double>>
AuxMethods::sortDictByValue(const std::map<int32_t, double> &i_dict, bool up);

template std::vector<std::pair<std::string, int32_t>>
AuxMethods::sortDictByValue(const std::map<std::string, int32_t> &i_dict,
                            bool up);

std::string AuxMethods::removeSpaces(const std::string &i_s) {
  std::string res = "";
  for (const auto c: i_s)
    if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
      res += c;

  return res;
}

size_t AuxMethods::skipSpaces(const std::string &i_s, size_t i_start) {
  size_t res = i_start;
  while (res < i_s.size() && (i_s[res] == ' ' || i_s[res] == '\t' ||
                              i_s[res] == '\n' || i_s[res] == '\r'))
    ++res;
  return res;
}

std::string AuxMethods::intToStringWithZeroes(uint32_t i_num,
                                              size_t i_totalDigits) {
  size_t numLength = std::to_string(i_num).length();
  i_totalDigits = std::max(numLength, i_totalDigits);
  std::stringstream ss;
  ss << std::setw((int)i_totalDigits) << std::setfill('0') << i_num;
  return ss.str();
}
