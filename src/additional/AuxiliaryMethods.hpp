#pragma once
#include <cstdint>
#include <fstream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>

#include <circuit/Circuit.hpp>

namespace AuxMethods {
void               setRandSeed(std::uint_fast32_t seed);
std::uint_fast32_t getRandSeed();

int                getRandInt(int lower, int upper, bool inclusively = false);
double             getRandDouble(double lower, double upper);

std::string        readAllFile(const std::string& filename);
std::vector<int>   getRandomIntList(
      int  i_n,
      int  i_minNumber,
      int  i_maxNumber,
      bool repite = false
  );

template<typename Key, typename Value>
std::vector<std::pair<Key, Value>>
            sortDictByValue(const std::map<Key, Value>& i_dict, bool up = true);
// TODO: ToEnum
// TODO: if need LineReader
std::string removeSpaces(const std::string& i_s);
int         skipSpaces(const std::string& i_s, int i_start = 0);
template<typename T>
std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>>& matrix
);

// TODO: if need CopyDirectory
std::string intToStringWithZeroes(int i_num, int i_totalDigits = 5);

template<class Tuple, std::size_t N>
struct TuplePrinter {
  static void print(const std::string& fmt, std::ostream& os, const Tuple& t) {
    const size_t idx = fmt.find_last_of('%');
    TuplePrinter<Tuple, N - 1>::print(std::string(fmt, 0, idx), os, t);
    os << std::get<N - 1>(t) << std::string(fmt, idx + 1);
  }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
  static void print(const std::string& fmt, std::ostream& os, const Tuple& t) {
    const size_t idx = fmt.find_first_of('%');
    os << std::string(fmt, 0, idx) << std::get<0>(t)
       << std::string(fmt, idx + 1);
  }
};

template<class... Args>
std::string format(const std::string& fmt, Args&&... args) {
  std::stringstream ss;

  const auto        t = std::make_tuple(std::forward<Args>(args)...);

  TuplePrinter<decltype(t), sizeof...(Args)>::print(fmt, ss, t);
  return ss.str();
}
}  // namespace AuxMethods
