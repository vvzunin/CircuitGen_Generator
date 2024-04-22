#include <iostream>
#include <memory>

#include "GraphVertex.hpp"

GraphVertexSubGraph::GraphVertexSubGraph(
    GraphPtr i_subGraph,
    GraphPtr i_baseGraph
) :
  GraphVertexBase(VertexTypes::subGraph, i_baseGraph) {
  d_subGraph = i_subGraph;
}
GraphVertexSubGraph::GraphVertexSubGraph(
    GraphPtr           i_subGraph,
    const std::string& i_name,
    GraphPtr           i_baseGraph
) :
  GraphVertexBase(VertexTypes::subGraph, i_name, i_baseGraph) {
  d_subGraph = i_subGraph;
}

// TODO add normal calculation
char GraphVertexSubGraph::updateValue() {
  return 'x';
}

// In fact is not needed
std::string GraphVertexSubGraph::getInstance() {
  return "DO NOT CALL IT";
}

std::string GraphVertexSubGraph::toVerilog() {
  return "DO NOT CALL IT";
}

void GraphVertexSubGraph::setSubGraph(GraphPtr i_subGraph) {
  d_subGraph = i_subGraph;
}

GraphPtr GraphVertexSubGraph::getSubGraph() const {
  return d_subGraph;
}

std::string GraphVertexSubGraph::calculateHash(bool recalculate) {
  if (hashed != "" && !recalculate)
    return hashed;

  // calc hash from subgraph
  hashed = d_subGraph->calculateHash();

  // futuire sorted struct
  std::vector<std::string> hashed_data;

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
