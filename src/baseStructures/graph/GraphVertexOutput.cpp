#include "GraphVertex.h"

GraphVertexOutput::GraphVertexOutput() : GraphVertexBase{VertexTypes::output, 1, 0}
{
}

char GraphVertexOutput::updateValue() {
  if (d_inConnections.size() > 0)
    d_value = d_inConnections[0]->getValue();
    for (int i = 1; i < d_inConnections.size(); i++)
      if (d_inConnections[i]->getValue() != d_value)
        d_value = 'x';
  return d_value;
}

void GraphVertexOutput::updateLevel() {
  for (GraphVertexBase* vert : d_inConnections)
    d_level = (vert->getLevel() > d_level) ? vert->getLevel() : d_level;
}