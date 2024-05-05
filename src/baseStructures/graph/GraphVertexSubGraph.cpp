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
  return d_subGraph->getGraphInstance();
}

std::pair<bool, std::string>
    GraphVertexSubGraph::toVerilog(std::string i_path, std::string i_filename) {
  if (auto parentPtr = d_baseGraph.lock()) {
    d_subGraph->setCurrentParent(parentPtr);
  } else {
    throw std::invalid_argument("Dead pointer!");
  }

  return d_subGraph->toVerilog(i_path, i_filename);
}

bool GraphVertexSubGraph::toGraphML(std::ofstream& i_fileStream) const {
  return d_subGraph->toGraphML(i_fileStream);
}

std::string GraphVertexSubGraph::toGraphML(int i_indent, std::string i_prefix)
    const {
  return d_subGraph->toGraphML(i_indent, i_prefix);
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
