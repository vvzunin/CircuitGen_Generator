#include "GraphVertex.h"

GraphVertexConstant::GraphVertexConstant(char i_const) : GraphVertexInput(VertexTypes::constant)
{
  d_value = i_const;
}

void GraphVertexConstant::updateLevel() {
  d_level = 0;
}