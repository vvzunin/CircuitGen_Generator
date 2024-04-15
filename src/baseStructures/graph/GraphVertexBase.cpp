#include <algorithm>
#include <iostream>
#include <string>

#include "GraphVertexBase.hpp"

uint_fast64_t GraphVertexBase::d_count = 0;

std::string   VertexUtils::gateToString(Gates i_type) {
  switch (i_type) {
    case Gates::GateNot:
      return "~";
    case Gates::GateAnd:
    case Gates::GateNand:
      return "&";
    case Gates::GateOr:
    case Gates::GateNor:
      return "|";
    case Gates::GateXor:
    case Gates::GateXnor:
      return "^";
    case Gates::GateBuf:
      return "";
      // Default
    default:
      return "Error";
  }
}

std::string VertexUtils::vertexTypeToVerilog(VertexTypes i_type) {
  switch (i_type) {
    case VertexTypes::input:
      return "input";
    case VertexTypes::output:
      return "output";
    case VertexTypes::constant:
      return "localparam";
    case VertexTypes::gate:
      return "wire";
  }
  return "";
}

GraphVertexBase::GraphVertexBase(const VertexTypes i_type, GraphPtr i_graph) {
  d_baseGraph = i_graph;
  d_type      = i_type;
  d_name      = this->getTypeName() + "_" + std::to_string(d_count++);
  d_value     = 'x';
  d_level     = 0;
}

GraphVertexBase::GraphVertexBase(
    const VertexTypes i_type,
    const std::string i_name,
    GraphPtr          i_graph
) {
  d_baseGraph = i_graph;
  d_type      = i_type;
  if (i_name.size())
    d_name = i_name;
  else
    d_name = this->getTypeName() + "_" + std::to_string(d_count++);
  d_value = 'x';
  d_level = 0;
}

GraphVertexBase::~GraphVertexBase() {}

VertexTypes GraphVertexBase::getType() const {
  return d_type;
}

std::string GraphVertexBase::getTypeName() const {
  return d_settings->parseVertexToString(d_type);
}

void GraphVertexBase::setName(const std::string i_name) {
  d_name = i_name;
}

std::string GraphVertexBase::getName() const {
  return d_name;
}

void GraphVertexBase::setLevel(const unsigned i_level) {
  d_level = i_level;
}

unsigned GraphVertexBase::getLevel() const {
  return d_level;
}

void GraphVertexBase::updateLevel() {
  for (VertexPtr vert : d_inConnections)
    d_level = (vert->getLevel() >= d_level) ? vert->getLevel() + 1 : d_level;
}

char GraphVertexBase::getValue() const {
  return d_value;
}

GraphPtr GraphVertexBase::getBaseGraph() const {
  return d_baseGraph;
}

std::vector<VertexPtr> GraphVertexBase::getInConnections() const {
  return d_inConnections;
}

int GraphVertexBase::addVertexToInConnections(VertexPtr const i_vert) {
  d_inConnections.push_back(i_vert);
  int n = 0;
  // TODO use map<VertexPtr, int> instead of for
  for (VertexPtr vert : d_inConnections)
    n += (vert == i_vert);
  return n;
}

std::string GraphVertexBase::calculateHash(bool recalculate) {
  if (hashed != "" && !recalculate)
    return hashed;

  if (d_type == VertexTypes::output && !d_baseGraph)
    return "";

  // autosorted struct
  std::vector<std::string> hashed_data;
  hashed = "";

  for (auto& child : d_outConnections) {
    hashed_data.push_back(child->calculateHash(recalculate));
  }
  std::sort(hashed_data.begin(), hashed_data.end());

  for (const auto& sub : hashed_data) {
    hashed += sub;
  }

  hashed = std::to_string(std::hash<std::string> {}(hashed));

  return hashed;
}

bool GraphVertexBase::removeVertexToInConnections(
    VertexPtr const i_vert,
    bool            i_full
) {
  if (i_full) {
    bool f = false;
    for (int i = d_inConnections.size() - 1; i >= 0; i--) {
      d_inConnections.erase(d_inConnections.begin() + i);
      f = true;
    }
    return f;
  } else {
    for (int i = 0; i < d_inConnections.size(); i++) {
      d_inConnections.erase(d_inConnections.begin() + i);
      return true;
    }
    return false;
  }
}

std::vector<VertexPtr> GraphVertexBase::getOutConnections() const {
  return d_outConnections;
}

bool GraphVertexBase::addVertexToOutConnections(VertexPtr const i_vert) {
  int n = 0;
  for (VertexPtr vert : d_outConnections)
    n += (vert == i_vert);
  if (n == 0) {
    d_outConnections.push_back(i_vert);
    return true;
  }
  return false;
}

bool GraphVertexBase::removeVertexToOutConnections(VertexPtr const i_vert) {
  for (int i = 0; i < d_outConnections.size(); i++) {
    d_outConnections.erase(d_outConnections.begin() + i);
    return true;
  }
  return false;
}

std::string GraphVertexBase::getInstance() {
  if (!d_inConnections.size()) {
    std::cerr << "TODO: delete empty vertices instances" << std::endl;
    return "";
  }

  return VertexUtils::vertexTypeToVerilog(d_type) + " " + d_name + ";";
}

std::string GraphVertexBase::toVerilog() {
  if (d_type == VertexTypes::output) {
    return "assign " + d_name + " = " + d_inConnections.back()->getName() + ";";
  }
  return "";
}