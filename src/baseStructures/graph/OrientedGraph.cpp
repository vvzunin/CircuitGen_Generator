#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include "OrientedGraph.h"
OrientedGraph::OrientedGraph() : 
GraphVertexBase{VertexTypes::graph}
{
}


// Переписать через addVertex
OrientedGraph::OrientedGraph(int i_inputs, int i_outputs) : 
GraphVertexBase{VertexTypes::graph}
{  
  d_vertexes[VertexTypes::input].resize(i_inputs);
  d_vertexes[VertexTypes::output].resize(i_outputs);
}

OrientedGraph::~OrientedGraph() {
  for (const auto& [key, value] : d_vertexes) {
    for (GraphVertexBase* vert : value)
      vert->~GraphVertexBase();
  }
}

int OrientedGraph::baseSize() const {
  return d_vertexes.at(VertexTypes::gate).size();
}

int OrientedGraph::fullSize() const {
  int size = this->baseSize();
  for (GraphVertexBase* vert : d_vertexes.at(VertexTypes::graph))
    size += (dynamic_cast<OrientedGraph*>(vert))->fullSize();
  return size;
}

bool OrientedGraph::isEmpty() const {
  return this->fullSize() == 0;
}

bool OrientedGraph::isEmptyFull() const {
  bool f = true;
  for (const auto& [key, value] : d_vertexes)
    f &= value.size() == 0;
  if (!f)
    return f;
  
  for (GraphVertexBase* vert : d_vertexes.at(VertexTypes::graph))
    f &= (dynamic_cast<OrientedGraph*>(vert))->isEmptyFull();
  return f;
}

void OrientedGraph::updateLevel() {
  for (GraphVertexBase* vert : d_vertexes.at(VertexTypes::output)) {
    vert->updateLevel();
    d_level = d_level > vert->getLevel() ? d_level : vert->getLevel();
  }
}

int OrientedGraph::getMaxLevel() {
  if (d_needLevelUpdate)
    this->updateLevel();
  int maxLevel = -1;
  for (GraphVertexBase* vert : d_vertexes.at(VertexTypes::output))
    maxLevel = vert->getLevel() > maxLevel ? vert->getLevel() : maxLevel;
  return maxLevel;
}

GraphVertexBase* OrientedGraph::addInput(const std::string i_name = "") {
  GraphVertexBase* newVertex = new GraphVertexInput(this, i_name);
  d_vertexes[VertexTypes::input].push_back(newVertex);
}