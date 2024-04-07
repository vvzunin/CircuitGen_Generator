#include "GraphVertex.hpp"

GraphVertexOutput::GraphVertexOutput(GraphPtr i_baseGraph) :
  GraphVertexBase(VertexTypes::output, i_baseGraph) {}

GraphVertexOutput::GraphVertexOutput(
    const std::string i_name,
    GraphPtr          i_baseGraph
) :
  GraphVertexBase(VertexTypes::output, i_name, i_baseGraph) {}

char GraphVertexOutput::updateValue() {
  if (d_inConnections.size() > 0)
    d_value = d_inConnections[0]->getValue();
  for (int i = 1; i < d_inConnections.size(); i++)
    if (d_inConnections[i]->getValue() != d_value)
      d_value = 'x';
  return d_value;
}

void GraphVertexOutput::updateLevel() {
  for (VertexPtr vert : d_inConnections)
    d_level = (vert->getLevel() > d_level) ? vert->getLevel() : d_level;
}