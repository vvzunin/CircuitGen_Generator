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
std::vector<std::string> splitString(const std::string& s, char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream        ss(s);
  std::string              token;

  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }

  return tokens;
}

RandomGeneratorWithSeed gen;

// namespace end
}  // namespace

void AuxMethods::setRandSeed(std::uint_fast32_t seed) {
  gen.setSeed(seed);
}

std::uint_fast32_t AuxMethods::getRandSeed() {
  return gen.getSeed();
}

int AuxMethods::getRandInt(int lower, int upper, bool inclusively) {
  return gen.getRandInt(lower, upper, inclusively);
}

double AuxMethods::getRandDouble(double lower, double upper) {
  return gen.getRandDouble(lower, upper);
}

std::string AuxMethods::readAllFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("Failed to open file: " + filename);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string str = buffer.str();
  size_t      pos;
  // Замена всех вхождений \r\n на \n
  while ((pos = str.find("\r\n")) != std::string::npos) {
    str.replace(pos, 2, "\n");
  }
  return str;

  return buffer.str();
}

std::vector<int> AuxMethods::getRandomIntList(
    int  i_n,
    int  i_minNumber,
    int  i_maxNumber,
    bool repite
) {
  return gen.getRandomIntList(i_n, i_minNumber, i_maxNumber, repite);
}

template<typename Key, typename Value>
std::vector<std::pair<Key, Value>>
    AuxMethods::sortDictByValue(const std::map<Key, Value>& i_dict, bool up) {
  std::vector<std::pair<Key, Value>> pairs(i_dict.begin(), i_dict.end());

  // Define a lambda function to compare values
  auto                               cmp = [](const std::pair<Key, Value>& lhs,
                const std::pair<Key, Value>& rhs) {
    return lhs.second < rhs.second;
  };

  // Sort the vector of pairs based on the values
  std::sort(pairs.begin(), pairs.end(), cmp);
  if (!up)
    std::reverse(pairs.begin(), pairs.end());

  return pairs;
}

template<typename T>
std::vector<std::vector<T>> AuxMethods::transpose(
    const std::vector<std::vector<T>>& matrix
) {
  if (matrix.empty() || matrix[0].empty())
    return matrix;

  std::vector<std::vector<T>> transposed(
      matrix[0].size(), std::vector<T>(matrix.size())
  );

  for (size_t i = 0; i < matrix.size(); ++i) {
    for (size_t j = 0; j < matrix[i].size(); ++j) {
      transposed[j][i] = matrix[i][j];
    }
  }

  return transposed;
}

template std::vector<std::vector<VertexPtr>> AuxMethods::transpose(
    const std::vector<std::vector<VertexPtr>>& matrix
);
// explicit instantiation of sortDictByValue
// if you want to use this func with other types, just add corresponding
// instantiation below, compilation error otherwise.
template std::vector<std::pair<int, int>>
    AuxMethods::sortDictByValue(const std::map<int, int>& i_dict, bool up);

template std::vector<std::pair<int, double>>
    AuxMethods::sortDictByValue(const std::map<int, double>& i_dict, bool up);

template std::vector<std::pair<std::string, int>> AuxMethods::sortDictByValue(
    const std::map<std::string, int>& i_dict,
    bool                              up
);

std::string AuxMethods::removeSpaces(const std::string& i_s) {
  std::string res = "";
  for (const auto c : i_s)
    if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
      res += c;

  return res;
}

int AuxMethods::skipSpaces(const std::string& i_s, int i_start) {
  int res = i_start;
  while (res < i_s.size()
         && (i_s[res] == ' ' || i_s[res] == '\t' || i_s[res] == '\n'
             || i_s[res] == '\r'))
    ++res;
  return res;
}

std::string AuxMethods::intToStringWithZeroes(int i_num, int i_totalDigits) {
  int numLength = std::to_string(i_num).length();
  i_totalDigits = std::max(numLength, i_totalDigits);
  std::stringstream ss;
  ss << std::setw(i_totalDigits) << std::setfill('0') << i_num;
  return ss.str();
}

std::string
    AuxMethods::replacer(const std::string& i_s, const std::string& i_r) {
  std::string res;
  res.reserve(i_s.length() * 2);

  std::string::size_type pos = 0, prev_pos = 0;

  while ((pos = i_s.find('%', pos)) != std::string::npos) {
    res.append(i_s, prev_pos, pos - prev_pos);
    res.append(i_r);
    prev_pos = ++pos;
  }

  res.append(i_s, prev_pos, i_s.length() - prev_pos);
  return res;
}