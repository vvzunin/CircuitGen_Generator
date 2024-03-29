#include <iostream>

#include "GraphVertex.h"

GraphVertexInput::GraphVertexInput(OrientedGraph *i_baseGraph,
                                   const VertexTypes i_type)
    : GraphVertexBase(i_type, i_baseGraph) {}

GraphVertexInput::GraphVertexInput(const std::string i_name,
                                   OrientedGraph *i_baseGraph,
                                   const VertexTypes i_type)
    : GraphVertexBase(i_type, i_name, i_baseGraph) {}

char GraphVertexInput::updateValue() {
  if (d_inConnections.size() > 0) {
    if (!d_baseGraph) {
      d_value = d_inConnections[0]->getValue();

      for (int i = 1; i < d_inConnections.size(); i++)
        if (d_inConnections[i]->getValue() != d_value) d_value = 'x';

    } else {
      std::cerr << "Error" << std::endl;
    }
  }
  return d_value;
}

void GraphVertexInput::updateLevel() {
  for (std::shared_ptr<GraphVertexBase> vert : d_inConnections)
    d_level = (vert->getLevel() > d_level) ? vert->getLevel() : d_level;
}