#include <iostream>

#include "GraphVertex.hpp"

GraphVertexInput::GraphVertexInput(
    GraphPtr          i_baseGraph,
    const VertexTypes i_type
) :
  GraphVertexBase(i_type, i_baseGraph) {}

GraphVertexInput::GraphVertexInput(
    const std::string i_name,
    GraphPtr          i_baseGraph,
    const VertexTypes i_type
) :
  GraphVertexBase(i_type, i_name, i_baseGraph) {}

char GraphVertexInput::updateValue() {
  if (d_inConnections.size() > 0) {
    if (!d_baseGraph.lock()) {
      if (auto ptr = d_inConnections[0].lock()) {
        d_value = ptr->getValue();
      } else {
        throw std::invalid_argument("Dead pointer!");
        return 'x';
      }

      for (int i = 1; i < d_inConnections.size(); i++) {
        if (auto ptr = d_inConnections[i].lock()) {
          if (ptr->getValue() != d_value) {
            d_value = 'x';
          }
        } else {
          throw std::invalid_argument("Dead pointer!");
        }
      }

    } else {
      std::cerr << "Error" << std::endl;
    }
  }
  return d_value;
}

void GraphVertexInput::updateLevel() {
  for (VertexPtrWeak vert : d_inConnections) {
    if (auto ptr = vert.lock()) {
      d_level = (ptr->getLevel() > d_level) ? ptr->getLevel() : d_level;
    } else {
      throw std::invalid_argument("Dead pointer!");
    }
  }
}