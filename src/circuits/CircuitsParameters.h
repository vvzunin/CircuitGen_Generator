#pragma once

#include <string>

class CircuitParameters {
 public:
  CircuitParameters() = default;

  // TODO: rewrite getters and setters
  std::string d_name = "";
  int d_numInputs = 0;
  int d_numConstants = 0;
  int d_numOutputs = 0;
  unsigned d_maxLevel = 0;
  int d_numEdges = 0;
  int d_numGates = 0;
  double d_size = 0.;
  double d_area = 0.;
  std::string d_hashCode = "";
  std::map<std::string, int> d_numElementsOfEachType;
  std::map<std::pair<std::string, std::string>, int> d_numEdgesOfEachType;
};