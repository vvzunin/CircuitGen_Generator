#include "GraphVertex.h"
#include <iostream>

GraphVertexGates::GraphVertexGates(
  Gates i_gate, 
  OrientedGraph* const i_baseGraph)
: GraphVertexBase (
    VertexTypes::gate,
    i_baseGraph) {
  d_gate = i_gate;
}

GraphVertexGates::GraphVertexGates(
  Gates i_gate, 
  const std::string i_name, 
  OrientedGraph* const i_baseGraph)
: GraphVertexBase(
    VertexTypes::gate,
    i_name,
    i_baseGraph) {
  d_gate = i_gate;
}

char GraphVertexGates::updateValue() {
  std::map<char, char> table;
  if (d_inConnections.size() > 0) {
    d_value = d_inConnections[0]->getValue();
    if (d_gate == Gates::GateBuf) 
      d_value = tableBuf.at(d_inConnections[0]->getValue());
    if (d_gate == Gates::GateNot) 
      d_value = tableNot.at(d_inConnections[0]->getValue());
    for (int i = 1; i < d_inConnections.size(); i++) {
      switch (d_gate) {
        case(Gates::GateAnd):
          table = tableAnd.at(d_value);
          break;
        case(Gates::GateNand):
          table = tableNand.at(d_value);
          break;
        case(Gates::GateOr):
          table = tableOr.at(d_value);
          break;
        case(Gates::GateNor):
          table = tableNor.at(d_value);
          break;
        case(Gates::GateXor):
          table = tableXor.at(d_value);
          break;
        case(Gates::GateXnor):
          table = tableXnor.at(d_value);
          break;
        default:
          std::cerr << "Error" << std::endl;
      }
      d_value = table.at(d_inConnections[i]->getValue());
    }
  }
  return d_value;
}