#include <memory>

#include "GraphVertex.h"

GraphVertexConstant::GraphVertexConstant(
    char i_const, std::shared_ptr<OrientedGraph> const i_baseGraph)
    : GraphVertexInput(i_baseGraph, VertexTypes::constant) {
  d_value = i_const;
}
GraphVertexConstant::GraphVertexConstant(
    char i_const, const std::string i_name,
    std::shared_ptr<OrientedGraph> const i_baseGraph)
    : GraphVertexInput(i_name, i_baseGraph, VertexTypes::constant) {
  d_value = i_const;
}

void GraphVertexConstant::updateLevel() { d_level = 0; }