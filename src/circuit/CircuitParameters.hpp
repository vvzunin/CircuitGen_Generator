#pragma once

#include <string>
#include <sstream>

/// @todo: to add desc fields of the class
/// class CircuitParameters
///
/// This is the detailed one. More details
/// @param d_name This name of the Circuit
/// @param d_numImputs This the number of inputs in the Circuit
/// @param d_numOutputs This the number of outputs in the Circuit
/// @param d_maxLevel This possible maximum number of logical operations, also
/// is level of the Circuit*
/// @param d_numEdges This the number of transitions within the circuit, they
/// are called edges, as in graphs the transition between vertices*
/// @param d_reliability This parameter shows the probability that we will
/// receive a true signal at the output. Its range is between 0 and 1
/// @param d_size This parameter shows the number of logical elements in the
/// circuit. For example, the number of logic gates, transistors, or other basic
/// elements
/// @param d_area In the Circuit, it usually refers to the physical area
/// @param d_longestPath This parameter shows the longest path from the entrance
/// to the exit*
/// @param d_gates The number of different logical operations on the circuit,
/// for example and, or, XOR, and so on
/// @param d_sensitivityFactor This parameter gives information about possible
/// change in the output signal, when measuring the input signal*
/// @param d_reliabilityPercent The percentage of reliability in combination
/// circuits usually means the probability that the circuit will work correctly
/// under given input conditions for a certain period of time or number of
/// operations*
/// @param d_hashCode ???
/// @param d_numElementsOfEachType This map contains the name of the element and
/// how many times it occurs in the Circuit?
/// @param d_numEdgesOfEachType ???
/// @param d_abc_Stats ???

class CircuitParameters {
public:
  CircuitParameters()                                               = default;

  std::string getDataForLogging() const {
    std::vector<std::string> result = {};
    result.push_back(std::string("name: ") + d_name);
    result.push_back(std::string("numInputs: ") + std::to_string(d_numInputs));
    result.push_back(std::string("numConstants: ") + std::to_string(d_numConstants));
    result.push_back(std::string("numOutputs: ") + std::to_string(d_numOutputs));
    result.push_back(std::string("maxLevel: ") + std::to_string(d_maxLevel));
    result.push_back(std::string("numEdges: ") + std::to_string(d_numEdges));
    result.push_back(std::string("numGates: ") + std::to_string(d_numGates));
    result.push_back(std::string("size: ") + std::to_string(d_size));
    result.push_back(std::string("area: ") + std::to_string(d_area));
    result.push_back(std::string("hashCode: ") + d_hashCode);
    std::stringstream ss;
    ss << "{";
    for(auto it = d_numElementsOfEachType.begin(); it != d_numElementsOfEachType.end(); ++it) {
        if (it != d_numElementsOfEachType.begin()) {
            ss << ", "; 
        }
        ss << "\"" << it->first << "\": " << it->second;
    }
    ss << "}";
    result.push_back(ss.str());
    std::string tmp = "{";
    for (const auto& item : d_numEdgesOfEachType) {
        const auto& key = item.first;
        int value = item.second;
        tmp += "(" + key.first + ", " + key.second + "): " + std::to_string(value) + ", ";
    }
    if (!d_numEdgesOfEachType.empty())
        tmp.pop_back();
    tmp += "}";
    result.push_back(tmp);
    std::string concat = "";
    for(const auto& s: result)
      if (concat.empty())
        concat = s;
      else
        concat += ";" + s;
    return concat;
  }
  /// @todo: rewrite getters and setters
  std::string                                        d_name         = "";
  int                                                d_numInputs    = 0;
  int                                                d_numConstants = 0;
  int                                                d_numOutputs   = 0;
  unsigned                                           d_maxLevel     = 0;
  int                                                d_numEdges     = 0;
  int                                                d_numGates     = 0;
  double                                             d_size         = 0.;
  double                                             d_area         = 0.;
  std::string                                        d_hashCode     = "";
  std::map<std::string, int>                         d_numElementsOfEachType;
  std::map<std::pair<std::string, std::string>, int> d_numEdgesOfEachType;
};
