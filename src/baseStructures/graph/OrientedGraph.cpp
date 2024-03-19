#include "OrientedGraph.h"

#include <baseStructures/graph/GraphVertex.h>
#include <baseStructures/graph/GraphVertexBase.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

uint_fast64_t OrientedGraph::d_countGraph = 0;

OrientedGraph::OrientedGraph(const std::string i_name) {
  if (i_name == "")
    d_name = "graph_" + std::to_string(d_countGraph++);
  else
    d_name = i_name;
}

OrientedGraph::~OrientedGraph() {
  for (const auto& [key, value] : d_vertexes) {
    for (GraphVertexBase* vert : value) {
      if (vert != nullptr) delete vert;
    }
  }
  for (OrientedGraph* vert : d_subGraphs) delete vert;
}

int OrientedGraph::baseSize() const {
  return d_vertexes.at(VertexTypes::gate).size();
}

int OrientedGraph::fullSize() const {
  int size = this->baseSize();
  for (OrientedGraph* vert : d_subGraphs) size += vert->fullSize();
  return size;
}

bool OrientedGraph::isEmpty() const { return this->fullSize() == 0; }

bool OrientedGraph::isEmptyFull() const {
  bool f = true;
  for (const auto& [key, value] : d_vertexes) f &= value.size() == 0;
  if (!f) return f;

  for (OrientedGraph* vert : d_subGraphs) f &= vert->isEmptyFull();
  return f;
}

void OrientedGraph::setName(const std::string& i_name) { d_name = i_name; }

std::string OrientedGraph::getName() const { return d_name; }

bool OrientedGraph::needToUpdateLevel() const { return d_needLevelUpdate; }

void OrientedGraph::updateLevels() {
  // for (GraphVertexBase* vert : d_vertexes.at(VertexTypes::output)) {
  //   vert->updateLevel();
  //   d_level = d_level > vert->getLevel() ? d_level : vert->getLevel();
  // }
}

unsigned OrientedGraph::getMaxLevel() {
  this->updateLevels();
  unsigned mx = 0;
  for (GraphVertexBase* vert : d_vertexes.at(VertexTypes::output)) {
    mx = mx < vert->getLevel() ? mx : vert->getLevel();
  }
  return mx;
}

void OrientedGraph::setBaseGraph(OrientedGraph* const i_baseGraph) {
  d_baseGraph = i_baseGraph;
}

OrientedGraph* OrientedGraph::getBaseGraph() const { return d_baseGraph; }

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

GraphVertexBase* OrientedGraph::addConst(const char i_value,
                                         const std::string i_name) {
  GraphVertexBase* newVertex = new GraphVertexConstant(i_value, i_name, this);
  d_vertexes[VertexTypes::constant].push_back(newVertex);

  return newVertex;
}

GraphVertexBase* OrientedGraph::addGate(const Gates i_gate,
                                        const std::string i_name) {
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
  // TODO: Добавить проверку на разные baseGraph. Если from - output, то to -
  // любой. Либо to - input, а from - любой.
  bool f = from->addVertexToOutConnections(to);
  int n = to->addVertexToInConnections(from);
  return f && (n > 0);
}

bool OrientedGraph::addEdges(std::vector<GraphVertexBase*> from1,
                             GraphVertexBase* to) {
  bool f = true;
  for (GraphVertexBase* vert : from1) f &= this->addEdge(vert, to);
  return f;
}

std::vector<OrientedGraph*> OrientedGraph::getSubGraphs() const {
  return d_subGraphs;
}

std::map<VertexTypes, std::vector<GraphVertexBase*>>
OrientedGraph::getBaseVertexes() const {
  return d_vertexes;
}

GraphVertexBase* OrientedGraph::getVerticeByIndex(int idx) const {
  if (sumFullSize() <= idx || idx < 0)
    throw std::invalid_argument(
        "OrientedGraph getVerticeByIndex: invalid index");

  // firstly - inputs, than - consts, than - gates, last - outputs
  if (d_vertexes.at(VertexTypes::input).size() > idx)
    return d_vertexes.at(VertexTypes::input).at(idx);
  idx -= d_vertexes.at(VertexTypes::input).size();

  // here const
  if (d_vertexes.at(VertexTypes::constant).size() > idx)
    return d_vertexes.at(VertexTypes::constant).at(idx);
  idx -= d_vertexes.at(VertexTypes::constant).size();

  // here gate
  if (d_vertexes.at(VertexTypes::gate).size() > idx)
    return d_vertexes.at(VertexTypes::gate).at(idx);
  idx -= d_vertexes.at(VertexTypes::gate).size();

  // here output
  return d_vertexes.at(VertexTypes::output).at(idx);
}

std::vector<GraphVertexBase*> OrientedGraph::getVerticesByLevel(
    const int i_level) {
  this->updateLevels();
  // TODO: Реализовать
}

std::vector<GraphVertexBase*> OrientedGraph::getVerticesByType(
    const VertexTypes i_type, const std::string i_name,
    const bool i_addSubGraphs) const {
  if (i_name.size() != 0) return d_vertexes.at(i_type);

  std::vector<GraphVertexBase*> resVert;
  for (GraphVertexBase* vert : d_vertexes.at(i_type))
    if ((i_name == "") || (vert->getName() == i_name)) resVert.push_back(vert);

  if (i_addSubGraphs)
    for (OrientedGraph* vert : d_subGraphs) {
      std::vector<GraphVertexBase*> subResVert =
          vert->getVerticesByType(i_type, i_name, i_addSubGraphs);
      resVert.insert(resVert.end(), subResVert.begin(), subResVert.end());
    }
  return resVert;
}

std::vector<GraphVertexBase*> OrientedGraph::getVerticesByName(
    const std::string i_name, const bool i_addSubGraphs) const {
  std::vector<GraphVertexBase*> resVert;
  for (const auto& [key, value] : d_vertexes) {
    for (GraphVertexBase* vert : value)
      if (vert->getName() == i_name) resVert.push_back(vert);
  }
  if (i_addSubGraphs)
    for (OrientedGraph* vert : d_subGraphs) {
      std::vector<GraphVertexBase*> subResVert =
          vert->getVerticesByName(i_name, i_addSubGraphs);
      resVert.insert(resVert.end(), subResVert.begin(), subResVert.end());
    }
  return resVert;
}

size_t OrientedGraph::sumFullSize() const {
  return d_vertexes.at(VertexTypes::input).size() +
         d_vertexes.at(VertexTypes::constant).size() +
         d_vertexes.at(VertexTypes::gate).size() +
         d_vertexes.at(VertexTypes::output).size();
}

std::string OrientedGraph::calculateHash(bool recalculate) {
  if (hashed != "" && !recalculate) return hashed;

  hashed = "";
  for (auto& input : d_vertexes[VertexTypes::input]) {
    hashed += input->calculateHash(recalculate);
  }

  hashed = std::to_string(std::hash<std::string>{}(hashed));

  return hashed;
}

bool OrientedGraph::operator==(const OrientedGraph& rhs) {
  bool correct = rhs.d_vertexes.at(VertexTypes::input).size() !=
                 d_vertexes.at(VertexTypes::input).size();
  correct &= rhs.d_vertexes.at(VertexTypes::output).size() !=
             d_vertexes.at(VertexTypes::output).size();
  correct &= rhs.d_vertexes.at(VertexTypes::constant).size() !=
             d_vertexes.at(VertexTypes::constant).size();
  correct &= rhs.d_vertexes.at(VertexTypes::gate).size() !=
             d_vertexes.at(VertexTypes::gate).size();

  if (!correct) return false;

  return hashed == rhs.hashed && hashed.size();
}

bool OrientedGraph::toVerilog(std::ofstream& i_fileStream) {
  // В данном методе происходит только генерация одного графа. Без подграфов.
  std::string verilogTab = "  ";

  i_fileStream << "module " << d_name << "();\n";

  if (d_vertexes.at(VertexTypes::input).size() > 0) {
    i_fileStream << verilogTab + "// Declare inputs\n";
    i_fileStream << verilogTab + "input ";
    const std::vector<GraphVertexBase*>& verts =
        d_vertexes.at(VertexTypes::input);
    for (int i = 0; i < verts.size() - 1; i++) {
      const GraphVertexBase* vert = verts[i];
      i_fileStream << vert->getName() + ", ";
    }
    i_fileStream << verts[verts.size() - 1]->getName() + ";\n";
  }

  if (d_vertexes.at(VertexTypes::output).size() > 0) {
    i_fileStream << verilogTab + "// Declare outputs\n";
    i_fileStream << verilogTab + "output ";
    const std::vector<GraphVertexBase*>& verts =
        d_vertexes.at(VertexTypes::output);
    for (int i = 0; i < verts.size() - 1; i++) {
      const GraphVertexBase* vert = verts[i];
      i_fileStream << vert->getName() + ", ";
    }
    i_fileStream << verts[verts.size() - 1]->getName() + ";\n\n";
  }

  i_fileStream << verilogTab + "// Declare constants\n";
  for (GraphVertexBase* vert : d_vertexes.at(VertexTypes::constant)) {
    i_fileStream << verilogTab + "wire " + vert->getName() + " = 1'b" +
                        vert->getValue() + ";\n";
  }
  i_fileStream << "\n";

  for (OrientedGraph* graph : d_subGraphs) {
    i_fileStream << verilogTab + graph->getName() + " " + graph->getName() +
                        "_inst(\n";

    {
      const std::vector<GraphVertexBase*>& verts =
          graph->getVerticesByType(VertexTypes::input);
      if (verts.size() > 0) {
        std::string tab = verilogTab + verilogTab;
        i_fileStream << tab + "// inputs\n";

        for (int i = 0; i < verts.size() - 1; i++) {
          const GraphVertexBase* vert = verts[i];
          i_fileStream << tab + "." + vert->getName() + "(";
          if (vert->getInConnections().size() > 0)
            i_fileStream << vert->getInConnections()[0]->getName();
          i_fileStream << "),\n";
        }
        const GraphVertexBase* vert = verts[verts.size() - 1];
        i_fileStream << tab + "." + vert->getName() + "(";
        if (vert->getInConnections().size() > 0)
          i_fileStream << vert->getInConnections()[0]->getName();
        i_fileStream << ")";
      }
    }
    {
      const std::vector<GraphVertexBase*>& verts =
          graph->getVerticesByType(VertexTypes::output);
      if (verts.size() > 0) {
        i_fileStream << ",\n\n";
        std::string tab = verilogTab + verilogTab;
        i_fileStream << tab + "// outputs\n";

        for (int i = 0; i < verts.size() - 1; i++) {
          const GraphVertexBase* vert = verts[i];
          i_fileStream << tab + "." + vert->getName() + "(" + vert->getName() +
                              "),\n";
        }
        const GraphVertexBase* vert = verts[verts.size() - 1];
        i_fileStream << tab + "." + vert->getName() + "(" + graph->getName() +
                            "_" + vert->getName() + ")";
      }
    }
    i_fileStream << "\n" + verilogTab + ");\n";

    for (GraphVertexBase* vert : graph->getVerticesByType(VertexTypes::output))
      i_fileStream << verilogTab + "wire " + graph->getName() + "_" +
                          vert->getName() + ";\n";
    i_fileStream << "\n";
  }

  for (GraphVertexBase* vert : d_vertexes.at(VertexTypes::gate)) {
    std::string s = dynamic_cast<GraphVertexGates*>(vert)->getVerilogString();
    if (s != "")
      i_fileStream << verilogTab + "wire " + vert->getName() + " = " + s +
                          ";\n";
  }

  for (GraphVertexBase* vert : d_vertexes.at(VertexTypes::output)) {
    for (GraphVertexBase* inVert : vert->getInConnections()) {
      i_fileStream << verilogTab + "assign " + vert->getName() + " = ";
      if (vert->getBaseGraph() == inVert->getBaseGraph())
        i_fileStream << inVert->getName();
      else
        i_fileStream << inVert->getBaseGraph()->getName() + "_" +
                            inVert->getName();
    }
    i_fileStream << ";\n";
  }

  i_fileStream << "endmodule\n";
  return true;
}