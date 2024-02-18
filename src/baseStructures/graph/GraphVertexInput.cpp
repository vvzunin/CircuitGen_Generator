#include "GraphVertex.h"
#include <iostream>

GraphVertexInput::GraphVertexInput() : GraphVertexBase{nullptr, VertexTypes::input, 0, 1}
{
}

GraphVertexInput::GraphVertexInput(VertexTypes i_type) : GraphVertexBase{i_type, 0, 1}
{
}

char GraphVertexInput::updateValue() {
  if (d_inConnections.size() > 0) {
    if (!d_baseGraph) {
      d_value = d_inConnections[0]->getValue();
      for (int i = 1; i < d_inConnections.size(); i++)
        if (d_inConnections[i]->getValue() != d_value)
          d_value = 'x';
    } else {
      std::cerr << "Error" << std::endl;
    }
  }
  return d_value;
}

void GraphVertexInput::updateLevel() {
  for (GraphVertexBase* vert : d_inConnections)
    d_level = (vert->getLevel() > d_level) ? vert->getLevel() : d_level;
}