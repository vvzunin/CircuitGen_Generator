#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include "OrientedGraph.h"
#include <baseStructures/graph/GraphVertex.h>
#include <baseStructures/graph/GraphVertexBase.h>

uint_fast64_t OrientedGraph::d_countGraph = 0;

OrientedGraph::OrientedGraph(const std::string i_name)
{
  if (i_name == "")
    d_name = "graph_" + std::to_string(d_countGraph++);
  else
    d_name = i_name;
}

OrientedGraph::~OrientedGraph() {
  for (const auto& [key, value] : d_vertexes) {
    for (GraphVertexBase* vert : value)
      vert->~GraphVertexBase();
  }
  for (OrientedGraph* vert : d_subGraphs) 
    vert->~OrientedGraph();
}

int OrientedGraph::baseSize() const {
  return d_vertexes.at(VertexTypes::gate).size();
}

int OrientedGraph::fullSize() const {
  int size = this->baseSize();
  for (OrientedGraph* vert : d_subGraphs)
    size += vert->fullSize();
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
  
  for (OrientedGraph* vert : d_subGraphs)
    f &= vert->isEmptyFull();
  return f;
}

void setName(const std::string &i_name) {
  d_name = i_name;
}

std::string OrientedGraph::getName() const {
  return d_name;
}

bool OrientedGraph::needToUpdateLevel() const {
  return d_needLevelUpdate;
}

void OrientedGraph::updateLevels() {
  // for (GraphVertexBase* vert : d_vertexes.at(VertexTypes::output)) {
  //   vert->updateLevel();
  //   d_level = d_level > vert->getLevel() ? d_level : vert->getLevel();
  // }
}

void OrientedGraph::setBaseGraph(OrientedGraph* const i_baseGraph) {
  d_baseGraph = i_baseGraph;
}

OrientedGraph* OrientedGraph::getBaseGraph() const {
  return d_baseGraph;
}

GraphVertexBase* OrientedGraph::addInput(const std::string i_name) {
  GraphVertexBase* newVertex = new GraphVertexInput(i_name, this);
  d_vertexes[VertexTypes::input].push_back(newVertex);

  return newVertex;
}

GraphVertexBase* OrientedGraph::addOutput(const std::string i_name) {
  GraphVertexBase* newVertex = new GraphVertexOutput(i_name, this);
  d_vertexes[VertexTypes::output].push_back(newVertex);

  return newVertex;
}

GraphVertexBase* OrientedGraph::addConst(const char i_value, const std::string i_name) {
  GraphVertexBase* newVertex = new GraphVertexConstant(i_value, i_name, this);
  d_vertexes[VertexTypes::constant].push_back(newVertex);

  return newVertex;
}

GraphVertexBase* OrientedGraph::addGate(const Gates i_gate, const std::string i_name) {
  GraphVertexBase* newVertex = new GraphVertexGates(i_gate, i_name, this);
  d_vertexes[VertexTypes::gate].push_back(newVertex);

  return newVertex;
}

OrientedGraph* OrientedGraph::addSubGraph(const std::string i_name) {
  OrientedGraph* newGraph = new OrientedGraph(i_name);
  d_subGraphs.push_back(newGraph);
  newGraph->setBaseGraph(this);

  return newGraph;
}

bool OrientedGraph::addEdge(GraphVertexBase* from, GraphVertexBase* to) {
  bool f = from->addVertexToOutConnections(to);
  int n = to->addVertexToInConnections(from);
  return f && (n > 0);
}

bool OrientedGraph::addEdges(std::vector<GraphVertexBase*> from1, GraphVertexBase* to) {
  bool f = true;
  for (GraphVertexBase* vert : from1)
    f &= this->addEdge(vert, to);
  return f;
}

std::vector<OrientedGraph*> OrientedGraph::getSubGraphs() const {
  return d_subGraphs;
}

std::map<VertexTypes, std::vector<GraphVertexBase*>> OrientedGraph::getBaseVertexes() const {
  return d_vertexes;
}

std::vector<GraphVertexBase*> OrientedGraph::getVerticesByLevel(const int i_level) {
  this->updateLevels();
}

std::vector<GraphVertexBase*> OrientedGraph::getVerticesByType(const VertexTypes i_type, const std::string i_name, const bool i_addSubGraphs) const {
  if (i_name.size() != 0)
    return d_vertexes.at(i_type);

  std::vector<GraphVertexBase*> resVert;
  for (GraphVertexBase* vert : d_vertexes.at(i_type))
    if (vert->getName() == i_name)
      resVert.push_back(vert);
  
  if (i_addSubGraphs)
    for (OrientedGraph* vert : d_subGraphs) {
      std::vector<GraphVertexBase*> subResVert = vert->getVerticesByType(i_type, i_name, i_addSubGraphs);
      resVert.insert(resVert.end(), subResVert.begin(), subResVert.end());
    }
  return resVert;
}

std::vector<GraphVertexBase*> OrientedGraph::getVerticesByName(const std::string i_name, const bool i_addSubGraphs) const {
  std::vector<GraphVertexBase*> resVert;
  for (const auto& [key, value] : d_vertexes) {
    for (GraphVertexBase* vert : value)
      if (vert->getName() == i_name)
        resVert.push_back(vert);
  }
  if (i_addSubGraphs)
    for (OrientedGraph* vert : d_subGraphs) {
      std::vector<GraphVertexBase*> subResVert = vert->getVerticesByName(i_name, i_addSubGraphs);
      resVert.insert(resVert.end(), subResVert.begin(), subResVert.end());
    }
  return resVert;
}
