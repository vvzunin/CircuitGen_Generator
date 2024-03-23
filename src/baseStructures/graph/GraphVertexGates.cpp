#include <iostream>

#include "GraphVertex.h"

GraphVertexGates::GraphVertexGates(
    Gates i_gate, OrientedGraph *i_baseGraph)
    : GraphVertexBase(VertexTypes::gate, i_baseGraph) {
  d_gate = i_gate;
}

GraphVertexGates::GraphVertexGates(
    Gates i_gate, const std::string i_name,
    OrientedGraph *i_baseGraph)
    : GraphVertexBase(VertexTypes::gate, i_name, i_baseGraph) {
  d_gate = i_gate;
}

Gates GraphVertexGates::getGate() const {
  return d_gate;
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
        case (Gates::GateAnd):
          table = tableAnd.at(d_value);
          break;
        case (Gates::GateNand):
          table = tableNand.at(d_value);
          break;
        case (Gates::GateOr):
          table = tableOr.at(d_value);
          break;
        case (Gates::GateNor):
          table = tableNor.at(d_value);
          break;
        case (Gates::GateXor):
          table = tableXor.at(d_value);
          break;
        case (Gates::GateXnor):
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

std::string GraphVertexGates::calculateHash(bool recalculate) {
  if (hashed != "" && !recalculate) return hashed;

  if (d_type == VertexTypes::output && !d_baseGraph) return "";

  hashed = std::to_string(d_outConnections.size()) + std::to_string(d_gate);

  for (auto& child : d_outConnections) {
    hashed += child->calculateHash(recalculate);
  }

  hashed = std::to_string(std::hash<std::string>{}(hashed));

  return hashed;
}

std::string GraphVertexGates::getVerilogString() const {
  std::string s = "";

  if (d_inConnections.size() > 0) {
    if (this->d_baseGraph == d_inConnections[0]->getBaseGraph())
      s = d_inConnections[0]->getName();
    else
      s = d_inConnections[0]->getBaseGraph()->getName() + "_" +
          d_inConnections[0]->getName();

    if (d_gate == Gates::GateNot) s = "~" + s;
    if ((d_gate == Gates::GateNand) || (d_gate == Gates::GateNor)) s = "~(" + s;

    for (int i = 1; i < d_inConnections.size(); i++) {
      std::string name;
      if (this->d_baseGraph == d_inConnections[i]->getBaseGraph())
        name = d_inConnections[i]->getName();
      else
        name = d_inConnections[i]->getBaseGraph()->getName() + "_" +
               d_inConnections[i]->getName();
      switch (d_gate) {
        case (Gates::GateAnd):
          s += " & " + name;
          break;
        case (Gates::GateNand):
          s += " & " + name;
          break;
        case (Gates::GateOr):
          s += " | " + name;
          break;
        case (Gates::GateNor):
          s += " | " + name;
          break;
        case (Gates::GateXor):
          s += " ^ " + name;
          break;
        case (Gates::GateXnor):
          s += " ~^ " + name;
          break;
        default:
          std::cerr << "Error" << std::endl;
      }
    }

    if ((d_gate == Gates::GateNand) || (d_gate == Gates::GateNor)) s += ")";
  }

  return s;
}