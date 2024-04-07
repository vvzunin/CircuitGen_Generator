#include <memory>

#include "GraphVertex.hpp"

GraphVertexConstant::GraphVertexConstant(char i_const, GraphPtr i_baseGraph) :
  GraphVertexInput(i_baseGraph, VertexTypes::constant) {
  d_value = i_const;
}
GraphVertexConstant::GraphVertexConstant(
    char              i_const,
    const std::string i_name,
    GraphPtr          i_baseGraph
) :
  GraphVertexInput(i_name, i_baseGraph, VertexTypes::constant) {
  d_value = i_const;
}

void GraphVertexConstant::updateLevel() {
  d_level = 0;
}

std::string GraphVertexConstant::getInstance() {
  return "wire " + d_name + " = 1'b" + d_value + ";";
}
