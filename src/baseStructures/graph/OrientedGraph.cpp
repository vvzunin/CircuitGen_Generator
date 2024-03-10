#include <algorithm>
#include <stdexcept>
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

void OrientedGraph::setName(const std::string &i_name) {
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
  // TODO: Добавить проверку на разные baseGraph. Если from - output, то to - любой. Либо to - input, а from - любой.
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

GraphVertexBase* OrientedGraph::getVerticeByIndex(int idx) const {
  if (sumFullSize() >= idx || idx < 0)
    throw std::invalid_argument("OrientedGraph getVerticeByIndex: invalid index");

  // firstly - inputs, than - consts, than - gates, last - outputs
  if (d_vertexes.at(VertexTypes::input).size() - 1 < idx)
    return d_vertexes.at(VertexTypes::input).at(idx);
  idx -= d_vertexes.at(VertexTypes::input).size();

  // here const
  if (d_vertexes.at(VertexTypes::constant).size() - 1 < idx)
    return d_vertexes.at(VertexTypes::constant).at(idx);
  idx -= d_vertexes.at(VertexTypes::constant).size();

  // here gate
  if (d_vertexes.at(VertexTypes::gate).size() - 1 < idx)
    return d_vertexes.at(VertexTypes::gate).at(idx);
  idx -= d_vertexes.at(VertexTypes::gate).size();

  // here output
  return d_vertexes.at(VertexTypes::output).at(idx);
}

std::vector<GraphVertexBase*> OrientedGraph::getVerticesByLevel(const int i_level) {
  this->updateLevels();
  // TODO: Реализовать
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

size_t OrientedGraph::sumFullSize() const {
  return 
      d_vertexes.at(VertexTypes::input).size() + 
      d_vertexes.at(VertexTypes::constant).size() + 
      d_vertexes.at(VertexTypes::gate).size() + 
      d_vertexes.at(VertexTypes::output).size();
}

std::string OrientedGraph::calculateHash(bool recalculate) {
  if (hashed != "" && !recalculate)
    return hashed;
  
  hashed = "";
  for (auto &input : d_vertexes[VertexTypes::input]) {
    hashed += input->calculateHash(recalculate);
  }

  hashed = std::to_string(std::hash<std::string>{}(hashed));

  return hashed;
}

bool OrientedGraph::operator== (const OrientedGraph& rhs) {
  bool correct = rhs.d_vertexes.at(VertexTypes::input).size() != d_vertexes.at(VertexTypes::input).size();
  correct &= rhs.d_vertexes.at(VertexTypes::output).size() != d_vertexes.at(VertexTypes::output).size();
  correct &= rhs.d_vertexes.at(VertexTypes::constant).size() != d_vertexes.at(VertexTypes::constant).size();
  correct &= rhs.d_vertexes.at(VertexTypes::gate).size() != d_vertexes.at(VertexTypes::gate).size();

  if (!correct)
    return false;
  
  return hashed == rhs.hashed && hashed.size();
}

std::string OrientedGraph::toVerilog(const std::string &i_path) {
  //int previousSizeOfFileName = filename.size();
  // filename = i_path;

  // std::vector<std::string> inputs = d_graph->getVerticesByType("input");
  // std::vector<std::string> outputs = d_graph->getVerticesByType("output");
  // std::vector<std::string> consts = d_graph->getVerticesByType("const");

  // int pos = (s.find_last_of('/')) + 1;
  // int pos2 = (filename.find_last_of('/')) + 1;

  // if (previousSizeOfFileName == 0)
  //     s = std::filesystem::current_path().string() + "/" + filename; // static variable will be created one time and then will be used throught running of the program
  // else
  //     s.replace(pos, previousSizeOfFileName, filename, pos2, previousSizeOfFileName);

  // bool f = std::filesystem::exists(s);

  // std::ofstream w(filename);
  // for (const auto &expr : d_logExpressions)
  //     w << "//" << expr << '\n';

  // w << "module " << d_circuitName << "(";

  // std::string in = "";
  // std::string out = "";

  // const std::string inputModule = "\tinput";
  // const std::string outputModule = "\toutput";

  // for (const auto &in_i : inputs)
  //     if (in_i.find("x") != std::string::npos)
  //         in += " " + in_i + ",";

  // if (in.length())
  // {
  //     w << in;
  //     in[in.length() - 1] = ';';
  // }

  // bool first = true;
  // for (const auto &output : outputs)
  // {
  //     if (first)
  //     {
  //         out += " ";
  //         first = false;
  //     }
  //     else
  //     {
  //         out += ", ";
  //     }
  //     out += output;
  // }
  // w << out << " );\n\n";

  // if (in.length())
  //     w << inputModule << in << '\n';
  // w << outputModule << out << ";\n";

  // if (d_graph->size() - inputs.size() - outputs.size() - consts.size() > 0)
  // {
  //     w << "\n\twire";
  //     bool first = true;
  //     for (const auto &vert : d_graph->getVertices())
  //     {
  //         if (vert.getOperation() != "input" && vert.getOperation() != "output" && vert.getOperation() != "const")
  //         {
  //             if (first)
  //             {
  //                 w << " " << vert.getWireName();
  //                 first = false;
  //             }
  //             else
  //             {
  //                 w << ", " << vert.getWireName();
  //             }
  //         }
  //     }
  //     w << ";\n"
  //       << std::endl;
  // }

  // for (int j = 0; j < d_graph->size(); ++j)
  // {
  //     if (d_graph->getVertice(j).getOperation() != "input")
  //     {
  //         std::vector<int> inps;
  //         for (int i = 0; i < d_graph->size(); ++i)
  //             if (d_graph->getAdjacencyMatrix(i, j))
  //                 inps.push_back(i);

  //         if (d_graph->getVertice(j).getOperation() != "output" && d_graph->getVertice(j).getOperation() != "const")
  //         {
  //             w << "\t" << d_graph->getVertice(j).getOperation() << " ( " << d_graph->getVertice(j).getWireName();
  //             // TODO: on prev line add instance name
  //             for (auto k : inps)
  //                 w << ", " << d_graph->getVertice(k).getWireName();
  //             w << ");" << std::endl;
  //         }
  //         else if (d_graph->getVertice(j).getOperation() == "output" && inps.size() > 0)
  //         {
  //             w << "\tassign " << d_graph->getVertice(j).getWireName() << " = " << d_graph->getVertice(inps[0]).getWireName() << ";" << std::endl;
  //         }
  //     }
  // }

  // w << "endmodule" << std::endl;
  // w.close();
}