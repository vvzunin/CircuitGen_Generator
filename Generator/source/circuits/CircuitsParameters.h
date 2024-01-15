#pragma once

#include <string>
#include <map>

class CircuitParameters
{
public:
  CircuitParameters() = default;
  
  // TODO: rewrite getters and setters
  std::string d_name = "";
  int d_numInputs = 0;
  int d_numOutputs = 0;
  int d_maxLevel = 0;
  int d_numEdges = 0;
  double d_reliability = 0.;
  double d_size = 0.;
  double d_area = 0.;
  int d_longestPath = 0;
  int d_gates = 0;
  double d_sensitivityFactor = 0.;
  double d_reliabilityPercent = 0.;
  double d_sensitiveArea = 0.;
  double d_sensitiveAreaPercent = 0.;
  std::string d_hashCode = "";
  std::map<std::string, int> d_numElementsOfEachType;
  std::map<std::pair<std::string, std::string>, int> d_numEdgesOfEachType;
  std::map<std::string, std::string> d_abcStats;
};
