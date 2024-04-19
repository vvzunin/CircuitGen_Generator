#pragma once

#include <string>

/// class CircuitParameters
///
/// This is the detailed one. More details
/// @param d_name This name of the Circuit
/// @param d_numInputs This the number of inputs in the Circuit
/// @param d_numOutputs This the number of outputs in the Circuit
/// @param d_maxLevel  This parameter shows length of the longest path from the
/// entrance to the exit*
/// @param d_numEdges This the number of transitions within the circuit, they
/// are called edges, as in graphs the transition between vertices*
/// @param d_numGates This parameter shows the number of logical elements in the
/// circuit. For example, the number of logic gates, transistors, or other basic
/// elements
/// @param d_hashCode ???
/// @param d_numElementsOfEachType This map contains the name of the element and
/// how many times it occurs in the Circuit?
/// @param d_numEdgesOfEachType ???

class CircuitParameters {
public:
  CircuitParameters()                                               = default;

  // TODO: rewrite getters and setters
  std::string                                        d_name         = "";
  int                                                d_numInputs    = 0;
  int                                                d_numConstants = 0;
  int                                                d_numOutputs   = 0;
  unsigned                                           d_maxLevel     = 0;
  int                                                d_numEdges     = 0;
  int                                                d_numGates     = 0;
  std::string                                        d_hashCode     = "";
  std::map<std::string, int>                         d_numElementsOfEachType;
  std::map<std::pair<std::string, std::string>, int> d_numEdgesOfEachType;
};