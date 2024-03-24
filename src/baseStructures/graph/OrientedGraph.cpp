#include "OrientedGraph.h"

#include <baseStructures/graph/GraphVertex.h>
#include <baseStructures/graph/GraphVertexBase.h>
#include <baseStructures/graph/GraphMLTemplates.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

uint_fast64_t OrientedGraph::d_countGraph = 0;

OrientedGraph::OrientedGraph(const std::string i_name) {
  this_ptr.reset(this);
  if (i_name == "")
    d_name = "graph_" + std::to_string(d_countGraph++);
  else
    d_name = i_name;

  // filling edges
  for (auto cur_gate : d_settings->getLogicOperationsKeys()) {
    d_edgesGatesCount[cur_gate] = d_gatesCount;
  }
}

OrientedGraph::~OrientedGraph() {}

std::shared_ptr<OrientedGraph> OrientedGraph::shared_from_this() {
  return this_ptr;
}

int OrientedGraph::baseSize() const {
  return d_vertexes.at(VertexTypes::gate).size();
}

int OrientedGraph::fullSize() const {
  int size = this->baseSize();
  for (std::shared_ptr<OrientedGraph> vert : d_subGraphs)
    size += vert->fullSize();
  return size;
}

bool OrientedGraph::isEmpty() const { return this->fullSize() == 0; }

bool OrientedGraph::isEmptyFull() const {
  bool f = true;
  for (const auto& [key, value] : d_vertexes) f &= value.size() == 0;
  if (!f) return f;

  for (std::shared_ptr<OrientedGraph> vert : d_subGraphs)
    f &= vert->isEmptyFull();
  return f;
}

void OrientedGraph::setName(const std::string& i_name) { d_name = i_name; }

std::string OrientedGraph::getName() const { return d_name; }

bool OrientedGraph::needToUpdateLevel() const { return d_needLevelUpdate; }

void OrientedGraph::updateLevels() {
  // for (std::shared_ptr<GraphVertexBase> vert :
  // d_vertexes.at(VertexTypes::output)) {
  //   vert->updateLevel();
  //   d_level = d_level > vert->getLevel() ? d_level : vert->getLevel();
  // }
}

unsigned OrientedGraph::getMaxLevel() {
  this->updateLevels();
  unsigned mx = 0;
  for (std::shared_ptr<GraphVertexBase> vert :
       d_vertexes.at(VertexTypes::output)) {
    mx = mx < vert->getLevel() ? mx : vert->getLevel();
  }
  return mx;
}

void OrientedGraph::setBaseGraph(
    std::shared_ptr<OrientedGraph> const i_baseGraph) {
  d_baseGraph = i_baseGraph;
}

std::shared_ptr<OrientedGraph> OrientedGraph::getBaseGraph() const {
  return d_baseGraph;
}

std::shared_ptr<GraphVertexBase> OrientedGraph::addInput(
    const std::string i_name) {
  std::shared_ptr<GraphVertexBase> newVertex(
      new GraphVertexInput(i_name, shared_from_this()));
  d_vertexes[VertexTypes::input].push_back(newVertex);

  return newVertex;
}

std::shared_ptr<GraphVertexBase> OrientedGraph::addOutput(
    const std::string i_name) {
  std::shared_ptr<GraphVertexBase> newVertex(
      new GraphVertexOutput(i_name, shared_from_this()));
  d_vertexes[VertexTypes::output].push_back(newVertex);

  return newVertex;
}

std::shared_ptr<GraphVertexBase> OrientedGraph::addConst(
    const char i_value, const std::string i_name) {
  std::shared_ptr<GraphVertexBase> newVertex(
      new GraphVertexConstant(i_value, i_name, shared_from_this()));
  d_vertexes[VertexTypes::constant].push_back(newVertex);

  return newVertex;
}

std::shared_ptr<GraphVertexBase> OrientedGraph::addGate(
    const Gates i_gate, const std::string i_name) {
  std::shared_ptr<GraphVertexBase> newVertex(
      new GraphVertexGates(i_gate, i_name, shared_from_this()));
  d_vertexes[VertexTypes::gate].push_back(newVertex);

  ++d_gatesCount[i_gate];

  return newVertex;
}

std::shared_ptr<OrientedGraph> OrientedGraph::addSubGraph(
    const std::string i_name) {
  std::shared_ptr<OrientedGraph> newGraph(new OrientedGraph(i_name));
  d_subGraphs.push_back(newGraph);
  newGraph->setBaseGraph(shared_from_this());

  return newGraph;
}

bool OrientedGraph::addEdge(std::shared_ptr<GraphVertexBase> from,
                            std::shared_ptr<GraphVertexBase> to) {
  // TODO: Добавить проверку на разные baseGraph. Если from - output, то to -
  // любой. Либо to - input, а from - любой.
  bool f = from->addVertexToOutConnections(to);
  int n = to->addVertexToInConnections(from);

  ++d_edgesCount;

  if (from->getType() == VertexTypes::gate && to->getType() == VertexTypes::gate)
    ++d_edgesGatesCount[from->getGate()][to->getGate()];

  return f && (n > 0);
}

bool OrientedGraph::addEdges(
    std::vector<std::shared_ptr<GraphVertexBase>> from1,
    std::shared_ptr<GraphVertexBase> to) {
  bool f = true;
  for (std::shared_ptr<GraphVertexBase> vert : from1)
    f &= this->addEdge(vert, to);
  return f;
}

std::vector<std::shared_ptr<OrientedGraph>> OrientedGraph::getSubGraphs()
    const {
  return d_subGraphs;
}

std::map<VertexTypes, std::vector<std::shared_ptr<GraphVertexBase>>>
OrientedGraph::getBaseVertexes() const {
  return d_vertexes;
}

std::shared_ptr<GraphVertexBase> OrientedGraph::getVerticeByIndex(
    int idx) const {
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

std::vector<std::shared_ptr<GraphVertexBase>> OrientedGraph::getVerticesByLevel(
    const int i_level) {
  this->updateLevels();
  // TODO: Реализовать
}

std::vector<std::shared_ptr<GraphVertexBase>> OrientedGraph::getVerticesByType(
    const VertexTypes i_type, const std::string i_name,
    const bool i_addSubGraphs) const {
  if (i_name.size() != 0) return d_vertexes.at(i_type);

  std::vector<std::shared_ptr<GraphVertexBase>> resVert;
  for (std::shared_ptr<GraphVertexBase> vert : d_vertexes.at(i_type))
    if ((i_name == "") || (vert->getName() == i_name)) resVert.push_back(vert);

  if (i_addSubGraphs)
    for (std::shared_ptr<OrientedGraph> vert : d_subGraphs) {
      std::vector<std::shared_ptr<GraphVertexBase>> subResVert =
          vert->getVerticesByType(i_type, i_name, i_addSubGraphs);
      resVert.insert(resVert.end(), subResVert.begin(), subResVert.end());
    }
  return resVert;
}

std::vector<std::shared_ptr<GraphVertexBase>> OrientedGraph::getVerticesByName(
    const std::string i_name, const bool i_addSubGraphs) const {
  std::vector<std::shared_ptr<GraphVertexBase>> resVert;
  for (const auto& [key, value] : d_vertexes) {
    for (std::shared_ptr<GraphVertexBase> vert : value)
      if (vert->getName() == i_name) resVert.push_back(vert);
  }
  if (i_addSubGraphs)
    for (std::shared_ptr<OrientedGraph> vert : d_subGraphs) {
      std::vector<std::shared_ptr<GraphVertexBase>> subResVert =
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

std::map<Gates, int> OrientedGraph::getGatesCount() const {
  return d_gatesCount;
}

std::map<Gates, std::map<Gates, int>> 
    OrientedGraph::getEdgesGatesCount() const {
  return d_edgesGatesCount;
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
    const std::vector<std::shared_ptr<GraphVertexBase>>& verts =
        d_vertexes.at(VertexTypes::input);
    for (int i = 0; i < verts.size() - 1; i++) {
      const std::shared_ptr<GraphVertexBase> vert = verts[i];
      i_fileStream << vert->getName() + ", ";
    }
    i_fileStream << verts[verts.size() - 1]->getName() + ";\n";
  }

  if (d_vertexes.at(VertexTypes::output).size() > 0) {
    i_fileStream << verilogTab + "// Declare outputs\n";
    i_fileStream << verilogTab + "output ";
    const std::vector<std::shared_ptr<GraphVertexBase>>& verts =
        d_vertexes.at(VertexTypes::output);
    for (int i = 0; i < verts.size() - 1; i++) {
      const std::shared_ptr<GraphVertexBase> vert = verts[i];
      i_fileStream << vert->getName() + ", ";
    }
    i_fileStream << verts[verts.size() - 1]->getName() + ";\n\n";
  }

  i_fileStream << verilogTab + "// Declare constants\n";
  for (std::shared_ptr<GraphVertexBase> vert :
       d_vertexes.at(VertexTypes::constant)) {
    i_fileStream << verilogTab + "wire " + vert->getName() + " = 1'b" +
                        vert->getValue() + ";\n";
  }
  i_fileStream << "\n";

  for (std::shared_ptr<OrientedGraph> graph : d_subGraphs) {
    i_fileStream << verilogTab + graph->getName() + " " + graph->getName() +
                        "_inst(\n";

    {
      const std::vector<std::shared_ptr<GraphVertexBase>>& verts =
          graph->getVerticesByType(VertexTypes::input);
      if (verts.size() > 0) {
        std::string tab = verilogTab + verilogTab;
        i_fileStream << tab + "// inputs\n";

        for (int i = 0; i < verts.size() - 1; i++) {
          const std::shared_ptr<GraphVertexBase> vert = verts[i];
          i_fileStream << tab + "." + vert->getName() + "(";
          if (vert->getInConnections().size() > 0)
            i_fileStream << vert->getInConnections()[0]->getName();
          i_fileStream << "),\n";
        }
        const std::shared_ptr<GraphVertexBase> vert = verts[verts.size() - 1];
        i_fileStream << tab + "." + vert->getName() + "(";
        if (vert->getInConnections().size() > 0)
          i_fileStream << vert->getInConnections()[0]->getName();
        i_fileStream << ")";
      }
    }
    {
      const std::vector<std::shared_ptr<GraphVertexBase>>& verts =
          graph->getVerticesByType(VertexTypes::output);
      if (verts.size() > 0) {
        i_fileStream << ",\n\n";
        std::string tab = verilogTab + verilogTab;
        i_fileStream << tab + "// outputs\n";

        for (int i = 0; i < verts.size() - 1; i++) {
          const std::shared_ptr<GraphVertexBase> vert = verts[i];
          i_fileStream << tab + "." + vert->getName() + "(" + vert->getName() +
                              "),\n";
        }
        const std::shared_ptr<GraphVertexBase> vert = verts[verts.size() - 1];
        i_fileStream << tab + "." + vert->getName() + "(" + graph->getName() +
                            "_" + vert->getName() + ")";
      }
    }
    i_fileStream << "\n" + verilogTab + ");\n";

    for (std::shared_ptr<GraphVertexBase> vert :
         graph->getVerticesByType(VertexTypes::output))
      i_fileStream << verilogTab + "wire " + graph->getName() + "_" +
                          vert->getName() + ";\n";
    i_fileStream << "\n";
  }

  for (std::shared_ptr<GraphVertexBase> vert :
       d_vertexes.at(VertexTypes::gate)) {
    std::string s =
        std::static_pointer_cast<GraphVertexGates>(vert)->getVerilogString();
    if (s != "")
      i_fileStream << verilogTab + "wire " + vert->getName() + " = " + s +
                          ";\n";
  }

  for (std::shared_ptr<GraphVertexBase> vert :
       d_vertexes.at(VertexTypes::output)) {
    for (std::shared_ptr<GraphVertexBase> inVert : vert->getInConnections()) {
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

std::string OrientedGraph::toGraphML(int i_nesting) const {
  const std::string spaces(i_nesting * 4, ' ');

  std::string graphTemplate = format(rawGraphTemplate, spaces, d_name, spaces);
  std::string nodeTemplate = format(rawNodeTemplate, spaces, "%", spaces, "%", "%", spaces);
  std::string edgeTemplate = format(rawEdgeTemplate, spaces);

  std::string nodes, edges, graphs;

  for (const auto& [vertexType, vertexVector] : d_vertexes) {
    std::string vertexTypeName = d_settings->parseVertexToString(vertexType);
    for (const auto& vertex : vertexVector) {
      std::string vertexKindName = vertexTypeName == "g" ? d_settings->parseGateToString(vertex->getGate()) :
                                   vertexTypeName == "const" ? std::string(1, vertex->getValue()) :
                                   vertexTypeName;
      nodes += format(nodeTemplate, vertex->getName(), vertexKindName, "");
      for (const auto& source : vertex->getInConnections()) {
        edges += format(edgeTemplate, source->getName(), vertex->getName());
      }
    }
  }
  for (const auto& subGraph: d_subGraphs) {
    graphs += subGraph->toGraphML(i_nesting + 1);
  }

  std::string finalGraph = format(graphTemplate, nodes + graphs + edges);
  if (i_nesting != 0) {
    return finalGraph;
  }
  return format(mainTemplate, finalGraph);
}

bool OrientedGraph::toGraphML(std::ofstream& i_fileStream) const {
  i_fileStream << this->toGraphML();
  return true;
}