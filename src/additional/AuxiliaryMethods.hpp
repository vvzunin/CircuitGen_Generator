#pragma once
#include <cstdint>
#include <fstream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>

/// @file AuxiliaryMethods.hpp
/// TODO: ToEnum
/// TODO: if need LineReader
/// TODO: if need CopyDirectory

/// namespace AuxMethods It was created to organize a set of auxiliary
/// functions and methods that can be used in various parts of a
/// software project
/// Functions: Random number generation, Reading files,
/// Data sorting and processing (includes methods for sorting
/// dictionaries by their values and for working with spaces in strings)
/// TO DO: list the other functions
/// </summary>

#include <circuit/Circuit.hpp>

namespace AuxMethods {

/// @brief setRandSeed Sets the grain to generate pseudorandom numbers
/// @param seed A grain for generating random numbers. Must be a positive
/// integer
/// @code
/// Setting the grain to generate random numbers
/// AuxMethods::setRandSeed(42);
/// @endcode
void               setRandSeed(std::uint_fast32_t seed);

/// @brief getRandSeed Returns the current grain for generating
/// pseudo-random numbers
/// @return Grain for generating random numbers

std::uint_fast32_t getRandSeed();

/// @brief getRandInt Returns a random integer in the specified range
/// @param lower The lower limit of the range
/// @param upper The upper limit of the range
/// @param inclusively Indicates whether the upper limit of the range
/// is included in the possible values
/// @return A random integer in the specified range
/// @code
/// Generating a random number in the range [1, 100] inclusive
/// int randomNumber = AuxMethods::getRandInt(1, 100, true);
/// //randomNumber = 45;
/// @endcode

int                getRandInt(int lower, int upper, bool inclusively = false);

// @brief getRandDouble Returns a random floating point number in the
/// specified range
/// @param lower The lower limit of the range
/// @param upper The upper limit of the range
/// @return A random floating point number in the specified range
/// @code
/// Generating a random floating point number in the range [0.0, 1.0]
/// double randomNumber = AuxMethods::getRandDouble(0.0, 1.0);
/// // randomNumber = 0.35;
/// @endcode

double             getRandDouble(double lower, double upper);

/// @brief readAllFile Reads the contents of the file and returns it as a
/// string
/// @param filename The name of the file to read
/// @return The contents of the file as a string
/// @code
/// // Reading the contents "example.txt "
/// std::string content = Auxiliary methods::Reading the entire
/// file("example.txt ")
/// std::cout << "File content:" << std::endl;
/// std::cout << content << std::endl;
/// @endcode
/// @throws std::runtime_error if the file cannot be opened

std::string        readAllFile(const std::string& filename);

/// @brief getRandomIntList Generates a list of random integers in a given
/// range with certain restrictions on the number of elements and the
/// presence of repetitions
/// @param i_n An integer indicating the desired size of the list
/// @param i_minNumber The lower limit of the range for generating random
/// numbers
/// @param i_maxNumber The upper limit of the range for generating random
/// numbers
/// @param repite A flag indicating whether the repetition of numbers in
/// the list is allowed (true - allowed, false - not allowed). Default - false
/// @return a vector<int> of random numbers according to the specified
/// parameters
/// @code
/// std::vector<int>  randomList = getRandomIntList(10, 1, 100, false);
/// std::cout << "Random list without repetition: ";
/// for (int num : randomList)
/// {
///     std::cout << num << " ";
/// }
/// // Conclusion: the vector contains 10 integers in the range from 1 to 100
/// // and they are all different.
/// @endcode

std::vector<int>   getRandomIntList(
      int  i_n,
      int  i_minNumber,
      int  i_maxNumber,
      bool repite = false
  );

/// @brief sortDictByValue Sorting the associative container by values and
/// returning sorted key-value pairs as a vector. Sorting can be performed both
/// in ascending and descending order of values
/// @tparam Key The key type of the associative container
/// @tparam Value The value type of the associative container
/// @param i_dict A constant reference to an associative container that needs
/// to be sorted by values
/// @param up If `true`, the sorting takes place in ascending order, otherwise
/// in descending order
/// @return A vector of key-value pairs containing dictionary elements sorted
/// by values
/// @code
/// std::map<std::string, int> myDict;
/// myDict["apple"]  = 5;
/// myDict["banana"] = 3;
/// myDict["orange"] = 7;
/// // Sorting the dictionary by values in ascending order
/// std::vector<std::pair<std::string, int>> sortedPairs =
/// AuxMethods::sortDictByValue(myDict, true);

/// // Output sorted key-value pairs
/// std::cout << "Sorted dictionary by value in ascending order:" << std::endl;
/// for (const auto& pair : sortedPairs) {
/// std::cout << pair.first << ": " << pair.second << std::endl;
/// }
/// @endcode

template<typename Key, typename Value>
std::vector<std::pair<Key, Value>>
            sortDictByValue(const std::map<Key, Value>& i_dict, bool up = true);
// TODO: ToEnum
// TODO: if need LineReader

/// @brief removeSpaces Removes spaces, tabs, and newline characters from a
/// string
/// @param i_s The string to remove the whitespace characters from
/// @return A string without spaces
/// @code
/// // The original string with whitespace characters
/// std::string inputString  = "  Hello\tWorld\n!";
/// // Removing whitespace characters from a string
/// std::string resultString = AuxMethods::removeSpaces(inputString);
/// Output of the result
/// std::cout << "Original string: " << inputString << std::endl;
/// std::cout << "String without spaces: " << resultString << std::endl;
/// @endcode

std::string removeSpaces(const std::string& i_s);

/// @brief skipSpaces Skips whitespace characters in the string starting
/// from the specified position. By default - 0
/// @param i_s The line in which to skip the whitespace characters
/// @param i_start The starting position from which to start searching for
/// whitespace characters.
/// @return The index of the first character that is not whitespace, or the
/// index outside the line,
/// @code
/// std::string str = "    \t\nHello, world!";
/// int startIndex    = 0;
/// // Skip the whitespace characters in the string
/// int nonSpaceIndex = AuxMethods::skipSpaces(str, startIndex);
/// // Output the result
/// if (nonSpaceIndex < str.size())
/// {
///  std::cout << "The first non-whitespace character is found by the index: ";
///  std::cout << nonSpaceIndex << std::endl;
///  std::cout <<"Symbol: " << str[nonSpaceIndex] << std::endl;
/// }
/// else
/// {
///  std::cout << "The string consists entirely of whitespace characters.";
///  std::endl;
/// }
/// @endcode

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
