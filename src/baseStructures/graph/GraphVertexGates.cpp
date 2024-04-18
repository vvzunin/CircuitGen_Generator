#include <iostream>

#include "GraphVertex.hpp"

GraphVertexGates::GraphVertexGates(Gates i_gate, GraphPtr i_baseGraph) :
  GraphVertexBase(VertexTypes::gate, i_baseGraph) {
  d_gate = i_gate;
}

GraphVertexGates::GraphVertexGates(
    Gates             i_gate,
    const std::string i_name,
    GraphPtr          i_baseGraph
) :
  GraphVertexBase(VertexTypes::gate, i_name, i_baseGraph) {
  d_gate = i_gate;
}

Gates GraphVertexGates::getGate() const {
  return d_gate;
}

char GraphVertexGates::updateValue() {
  std::map<char, char> table;
  if (d_inConnections.size() > 0) {
    VertexPtr ptr;
    // check if ptr is alive
    if (!(ptr = d_inConnections[0].lock())) {
      return 'x';
    }

    d_value = ptr->getValue();
    if (d_gate == Gates::GateBuf)
      d_value = tableBuf.at(ptr->getValue());
    if (d_gate == Gates::GateNot)
      d_value = tableNot.at(ptr->getValue());
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

      if (!(ptr = d_inConnections[i].lock())) {
        return 'x';
      }

      d_value = table.at(ptr->getValue());
    }
  }
  return d_value;
}

std::string GraphVertexGates::calculateHash(bool recalculate) {
  if (hashed != "" && !recalculate)
    return hashed;

  if (d_type == VertexTypes::output && !d_baseGraph.lock())
    return "";

  hashed = std::to_string(d_outConnections.size()) + std::to_string(d_gate);

  for (auto& child : d_outConnections) {
    hashed += child->calculateHash(recalculate);
  }

  hashed = std::to_string(std::hash<std::string> {}(hashed));

  return hashed;
}

std::string GraphVertexGates::getVerilogString() const {
  std::string s = "";

  if (d_inConnections.size() > 0) {
    VertexPtr ptr;

    // check if ptr is alive
    if (!(ptr = d_inConnections[0].lock())) {
      throw std::invalid_argument("Dead pointer!");
      return "";
    }

    if (this->d_baseGraph.lock() == ptr->getBaseGraph().lock())
      s = ptr->getName();
    else
      s = ptr->getBaseGraph().lock()->getName() + "_" + ptr->getName();

    if (d_gate == Gates::GateNot)
      s = "~" + s;
    if ((d_gate == Gates::GateNand) || (d_gate == Gates::GateNor)
        || (d_gate == Gates::GateXnor))
      s = "~(" + s;

    for (int i = 1; i < d_inConnections.size(); i++) {
      // check if ptr is alive
      if (!(ptr = d_inConnections[i].lock())) {
        throw std::invalid_argument("Dead pointer!");
        return "";
      }

      std::string name;
      if (this->d_baseGraph.lock() == ptr->getBaseGraph().lock())
        name = ptr->getName();
      else
        name = ptr->getBaseGraph().lock()->getName() + "_" + ptr->getName();

      s += " " + VertexUtils::gateToString(d_gate) + " " + name;
      if (d_gate == GateDefault)
        std::cerr << "Error" << std::endl;
    }

    if ((d_gate == Gates::GateNand) || (d_gate == Gates::GateNor)
        || (d_gate == Gates::GateXnor))
      s += ")";
  }

  return s;
}

std::string GraphVertexGates::toVerilog() {
  if (!d_inConnections.size()) {
    std::cerr << "TODO: delete empty vertices" << std::endl;
    return "";
  }
  std::string basic = "assign " + d_name + " = ";

  std::string oper  = VertexUtils::gateToString(d_gate);
  if (d_inConnections.empty()) {
    std::clog << d_name << std::endl;
  }
  if (VertexPtr ptr = d_inConnections.back().lock()) {
    if (d_gate == Gates::GateNot || d_gate == Gates::GateBuf) {
      basic += oper + ptr->getName() + ";";

      return basic;
    }
  } else {
    throw std::invalid_argument("Dead pointer!");
  }

  std::string end = "";

  if (d_gate == Gates::GateNand || d_gate == Gates::GateNor
      || d_gate == Gates::GateXnor) {
    basic += "~ ( ";

    end   = " )";
  }
  VertexPtr ptr;
  for (size_t i = 0; i < d_inConnections.size() - 1; ++i) {
    if (ptr = d_inConnections[i].lock()) {
      basic += ptr->getName() + " " + oper + " ";
    } else {
    }
  }

  if (ptr = d_inConnections.back().lock()) {
    basic += ptr->getName() + end + ";";
  } else {
    throw std::invalid_argument("Dead pointer!");
  }

  return basic;
}
