#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>

#include "./circuits/Circuit.h"

namespace AuxMethods
{
  std::string readAllFile(const std::string& filename);
  std::vector<int> getRandomIntList(int i_n, int i_minNumber,
    int i_maxNumber, bool repite = false);
  template<typename Key, typename Value>
  std::vector<std::pair<Key, Value>> sortDictByValue(const std::map<Key, Value>& i_dict, bool up = true);
  //TODO: ToEnum
  //TODO: if need LineReader
  std::string removeSpaces(const std::string& i_s);
  int skipSpaces(const std::string& i_s, int i_start = 0);
  //TODO: if need CopyDirectory
  Circuit parseVerilog(const std::string& i_filepath);
}
