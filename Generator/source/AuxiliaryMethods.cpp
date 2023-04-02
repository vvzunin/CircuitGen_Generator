#include <algorithm>
#include <iostream>
#include <cassert>
#include <string_view>


#include "AuxiliaryMethods.h"

namespace
{
  int getRandInt(int i_lower, int i_upper)
  {
    assert(i_lower <= i_upper);
    int d = i_upper - i_lower + 1;
    return (rand() % d) + i_lower;
  }

  std::vector<std::string> splitString(const std::string& s, char delimiter)
  {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
  }
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

std::vector<int> AuxMethods::getRandomIntList(int i_n, int i_minNumber,
    int i_maxNumber, bool repite)
{
  std::srand(time(0));
  std::vector<int> lst;
  bool flag = true;
  //TODO: can we just rewrite it to simple while? and withour UB make flag = true before while?

  while (flag)
  {
    int i;
    flag = false;
    int k = i_n - lst.size();
    for (i = 0; i < k; ++i)
      lst.push_back(getRandInt(i_minNumber, i_maxNumber));

    sort(lst.begin(), lst.end());

    if (!repite)
    {
      i = 1;
      int insert = 0;
      while (i < lst.size() - 1)
      {
        if (lst[i] != lst[i - 1])
          lst[insert++] = lst[i];
        ++i;
      }
      if (insert != lst.size())
      {
        flag = true;
        lst.resize(insert);
      }
    }
  }

  return lst;
}

template<typename Key, typename Value>
std::vector<std::pair<Key, Value>> AuxMethods::sortDictByValue(const std::map<Key, Value>& i_dict, bool up)
{
  std::vector<std::pair<Key, Value>> pairs(i_dict.begin(), i_dict.end());

  // Define a lambda function to compare values
  auto cmp = [](const std::pair<Key, Value>& lhs, const std::pair<Key, Value>& rhs) {
      return lhs.second < rhs.second;
  };

  // Sort the vector of pairs based on the values
  std::sort(pairs.begin(), pairs.end(), cmp);
  if (!up)
    std::reverse(pairs.begin(), pairs.end());

  return pairs;
}

std::string AuxMethods::removeSpaces(const std::string& i_s)
{
  std::string res = "";
  for (const auto c : i_s)
    if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
      res += c;

  return res;
}

int AuxMethods::skipSpaces(const std::string& i_s, int i_start)
{
  int res = i_start;
  while (res < i_s.size() && (i_s[res] == ' ' || i_s[res] == '\t' || i_s[res] == '\n' || i_s[res] == '\r'))
    ++res;
  return res;
}

Circuit AuxMethods::parseVerilog(const std::string& i_filepath)
{
  Circuit circuit({}, {});
  circuit.setPath(i_filepath);

  std::string s = readAllFile(i_filepath);

  int start = s.find("module ");
  std::string ch = " (";
  size_t n2 = s.find_first_of(" (", start + 7);
  assert(n2 != std::string::npos);

  circuit.setCircuitName(removeSpaces(s.substr(start + 7, n2 - start - 7)));
  start = skipSpaces(s, n2 + 1);
  
  std::vector<std::string> inputs;
  std::string inps = "";
  std::string outs = "";

  if (s.find("input", start) == start) {
    int k = s.find("input ", start) + 6;
    int t = s.find("output ", k + 1) + 7;
    inps = removeSpaces(s.substr(k, t - k - 7));
    inps = inps.substr(0, inps.size() - 1);
    outs = removeSpaces(s.substr(t, s.find(");", t + 1) - t));
    start = s.find(");", t + 1);
  }
  else
  {
    start = s.find(");", start);
    int k = s.find("input ", start) + 6;
    int k_end = s.find(";", k);
    int t = s.find("output ", start) + 7;
    int t_end = s.find(";", t);
    inps = removeSpaces(s.substr(k, k_end - k));
    outs = removeSpaces(s.substr(t, t_end - t));
    start = std::max(k_end, t_end);
  }

  for (const auto& input : splitString(inps, ','))
    circuit.addVertex(input, "input");

  for (const auto& output : splitString(outs, ','))
    circuit.addVertex(output, "output");

  {
    int k = s.find("wire ", start) + 5;
    int k_end = s.find(";", k);
    //TODO: we really need this? std::string wires = removeSpaces(s.substr(k, k_end - k));
    start = k_end + 1;
  }

  {
    s = s.substr(start);
    s = s.substr(0, s.find("endmodule"));
    s = s.substr(skipSpaces(s));
    int n = 0;
    while(s.size() != 0)
    {
      if (!s.starts_with("assign")) {
        int end = s.find(";");
        std::string type = s.substr(0, s.find_first_of(ch));
        std::string wireList = removeSpaces(s.substr(s.find('(') + 1, end - 2 - s.find('(')));
        std::vector<std::string> wires = splitString(wireList, ',');
        int tt = circuit.getIndexOfWireName(wires[0]);
        if (tt != -1 && circuit.getVertice(tt).getOperation() == "output")
        {
          std::string w = "ewr_" + std::to_string(n++);
          circuit.addVertex(w, "none", w);
          circuit.addEdge(w, wires[0]);
          wires[0] = w;
        }

        for (const std::string& wire : wires)
          if (circuit.getIndexOfWireName(wire) == -1)
            circuit.addVertex(wire, "none", wire);


        circuit.setVerticeOperation(circuit.getIndexOfWireName(wires[0]), type);
        if (wires.size() > 3) //TODO: what the magic number?
        {
          std::string prev = wires[1];
          for (int i = 2; i + 1 < wires.size(); ++i)
          {
            std::string wire = "ewr_" + std::to_string(n++);
            circuit.addVertex(wire, type, wire);
            circuit.addDoubleEdge(wires[i], prev, wire);
            prev = wire;
          }
          circuit.addDoubleEdge(wires.back(), prev, wires[0]);
        }
        else
          for (int i = 1; i < wires.size(); ++i)
            circuit.addEdge(wires[i], wires[0]);

        s.erase(0, end + 1);
      }
      else
      {
        int end = s.find(";");
        std::string left = removeSpaces(s.substr(6, s.find('=') - 6));
        std::string right = removeSpaces(s.substr(s.find('=') + 1, end - s.find('=') - 1));
        bool f = circuit.addEdge(right, left, false);

        s.erase(0, end + 1);
      }
      s = s.erase(0, skipSpaces(s));
    }
  }
  return circuit;
}
