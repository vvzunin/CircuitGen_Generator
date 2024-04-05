#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <map>
#include <random>
#include <string_view>
#include <utility>
#include <vector>

#include "AuxiliaryMethods.hpp"

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
  return buffer.str();
}

std::vector<int> AuxMethods::getRandomIntList(
    int  i_n,
    int  i_minNumber,
    int  i_maxNumber,
    bool repite
) {
  std::vector<int> lst;
  bool             flag = true;
  // TODO: can we just rewrite it to simple while? and without UB make flag =
  // true before while?

  while (flag) {
    int i;
    flag  = false;
    int k = i_n - lst.size();
    for (i = 0; i < k; ++i)
      lst.push_back(getRandInt(i_minNumber, i_maxNumber, true));

    sort(lst.begin(), lst.end());

    if (!repite) {
      i          = 1;
      int insert = 0;
      while (i < lst.size() - 1) {
        if (lst[i] != lst[i - 1])
          lst[insert++] = lst[i];
        ++i;
      }
      if (insert != lst.size()) {
        flag = true;
        lst.resize(insert);
      }
    }
  }

  return lst;
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