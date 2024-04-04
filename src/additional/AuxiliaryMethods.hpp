
#include <cstdint>
#include <fstream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>

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
// TODO: if need CopyDirectory

// namespace end
}  // namespace AuxMethods
