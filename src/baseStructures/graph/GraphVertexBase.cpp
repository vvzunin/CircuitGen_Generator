#include "GraphVertexBase.h"

#include <set>
#include <string>

uint_fast64_t GraphVertexBase::d_count = 0;

GraphVertexBase::GraphVertexBase(const VertexTypes i_type,
                                 OrientedGraph *i_graph) {
  d_baseGraph = i_graph;
  d_type = i_type;
  d_name = this->getTypeName() + "_" + std::to_string(d_count++);
  d_value = 'x';
  d_level = 0;
}

GraphVertexBase::GraphVertexBase(const VertexTypes i_type,
                                 const std::string i_name,
                                 OrientedGraph *i_graph) {
  d_baseGraph = i_graph;
  d_type = i_type;
  if (i_name.size())
    d_name = i_name;
  else
    d_name = this->getTypeName() + "_" + std::to_string(d_count++);
  d_value = 'x';
  d_level = 0;
}

GraphVertexBase::~GraphVertexBase() {
  
}

VertexTypes GraphVertexBase::getType() const { return d_type; }

std::string GraphVertexBase::getTypeName() const {
  return d_settings->parseVertexToString(d_type);
}

void GraphVertexBase::setName(const std::string i_name) { d_name = i_name; }

std::string GraphVertexBase::getName() const { return d_name; }

void GraphVertexBase::setLevel(const unsigned i_level) { d_name = i_level; }

unsigned GraphVertexBase::getLevel() const { return d_level; }

void GraphVertexBase::updateLevel() {
  for (std::shared_ptr<GraphVertexBase> vert : d_inConnections)
    d_level = (vert->getLevel() >= d_level) ? vert->getLevel() + 1 : d_level;
}

char GraphVertexBase::getValue() const { return d_value; }

OrientedGraph *GraphVertexBase::getBaseGraph() const { return d_baseGraph; }

std::vector<std::shared_ptr<GraphVertexBase>> GraphVertexBase::getInConnections() const {
  return d_inConnections;
}

int GraphVertexBase::addVertexToInConnections(std::shared_ptr<GraphVertexBase> const i_vert) {
  d_inConnections.push_back(i_vert);
  int n = 0;
  // TODO use map<std::shared_ptr<GraphVertexBase>, int> instead of for
  for (std::shared_ptr<GraphVertexBase> vert : d_inConnections) n += (vert == i_vert);
  return n;
}

std::string GraphVertexBase::calculateHash(bool recalculate) {
  if (hashed != "" && !recalculate) return hashed;

  if (d_type == VertexTypes::output && !d_baseGraph) return "";

  // autosorted struct
  std::set<std::string> hashed_data;
  hashed = "";

  for (auto& child : d_outConnections) {
    hashed_data.insert(child->calculateHash(recalculate));
  }

  for (const auto& sub : hashed_data) {
    hashed += sub;
  }

  hashed = std::to_string(std::hash<std::string>{}(hashed));

  return hashed;
}

bool GraphVertexBase::removeVertexToInConnections(std::shared_ptr<GraphVertexBase> const i_vert,
                                                  bool i_full) {
  if (i_full) {
    bool f = false;
    for (int i = d_inConnections.size() - 1; i >= 0; i--) {
      d_inConnections.erase(d_inConnections.begin() + i);
      f = true;
    }
    return f;
  } else {
    for (int i = 0; i < d_inConnections.size(); i++) {
      d_inConnections.erase(d_inConnections.begin() + i);
      return true;
    }
    return false;
  }
}

std::vector<std::shared_ptr<GraphVertexBase>> GraphVertexBase::getOutConnections() const {
  return d_outConnections;
}

bool GraphVertexBase::addVertexToOutConnections(std::shared_ptr<GraphVertexBase> const i_vert) {
  int n = 0;
  for (std::shared_ptr<GraphVertexBase> vert : d_outConnections) n += (vert == i_vert);
  if (n == 0) {
    d_outConnections.push_back(i_vert);
    return true;
  }
  return false;
}

bool GraphVertexBase::removeVertexToOutConnections(
    std::shared_ptr<GraphVertexBase> const i_vert) {
  for (int i = 0; i < d_outConnections.size(); i++) {
    d_outConnections.erase(d_outConnections.begin() + i);
    return true;
  }
  return false;
}