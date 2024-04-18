#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "OrientedGraph.hpp"

#include <additional/AuxiliaryMethods.hpp>
#include <baseStructures/graph/GraphMLTemplates.hpp>
#include <baseStructures/graph/GraphVertex.hpp>
#include <baseStructures/graph/GraphVertexBase.hpp>

uint_fast64_t OrientedGraph::d_countGraph            = 0;
size_t        OrientedGraph::d_countNewGraphInstance = 0;

OrientedGraph::OrientedGraph(const std::string& i_name) {
  d_currentInstance = d_countNewGraphInstance++;
  // this_ptr.reset(this);
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

int OrientedGraph::baseSize() const {
  return d_vertexes.at(VertexTypes::gate).size();
}

int OrientedGraph::fullSize() const {
  int size = this->baseSize();
  for (GraphPtr vert : d_subGraphs)
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

  for (GraphPtr vert : d_subGraphs)
    f &= vert->isEmptyFull();
  return f;
}

void OrientedGraph::setName(const std::string& i_name) {
  d_name = i_name;
}

std::string OrientedGraph::getName() const {
  return d_name;
}

bool OrientedGraph::needToUpdateLevel() const {
  return d_needLevelUpdate;
}

void OrientedGraph::updateLevels() {
  // for (VertexPtr vert :
  // d_vertexes.at(VertexTypes::output)) {
  //   vert->updateLevel();
  //   d_level = d_level > vert->getLevel() ? d_level : vert->getLevel();
  // }
}

unsigned OrientedGraph::getMaxLevel() {
  this->updateLevels();
  unsigned mx = 0;
  for (VertexPtr vert : d_vertexes.at(VertexTypes::output)) {
    mx = mx < vert->getLevel() ? mx : vert->getLevel();
  }
  return mx;
}

void OrientedGraph::addParentGraph(GraphPtr i_baseGraph) {
  d_parentGraphs.push_back(i_baseGraph);
}

std::vector<GraphPtrWeak> OrientedGraph::getParentGraphs() const {
  return d_parentGraphs;
}

VertexPtr OrientedGraph::addInput(const std::string& i_name) {
  VertexPtr newVertex(new GraphVertexInput(i_name, shared_from_this()));
  d_vertexes[VertexTypes::input].push_back(newVertex);

  return newVertex;
}

VertexPtr OrientedGraph::addOutput(const std::string& i_name) {
  VertexPtr newVertex(new GraphVertexOutput(i_name, shared_from_this()));
  d_vertexes[VertexTypes::output].push_back(newVertex);

  return newVertex;
}

VertexPtr
    OrientedGraph::addConst(const char& i_value, const std::string& i_name) {
  VertexPtr newVertex(
      new GraphVertexConstant(i_value, i_name, shared_from_this())
  );
  d_vertexes[VertexTypes::constant].push_back(newVertex);

  return newVertex;
}

VertexPtr
    OrientedGraph::addGate(const Gates& i_gate, const std::string& i_name) {
  VertexPtr newVertex(new GraphVertexGates(i_gate, i_name, shared_from_this()));
  d_vertexes[VertexTypes::gate].push_back(newVertex);

  ++d_gatesCount[i_gate];

  return newVertex;
}

std::vector<VertexPtr> OrientedGraph::addSubGraph(
    GraphPtr               i_subGraph,
    std::vector<VertexPtr> i_inputs
) {
  std::clog << d_name << std::endl;
  std::vector<VertexPtr> iGraph =
      i_subGraph->getVerticesByType(VertexTypes::input);

  i_subGraph->addParentGraph(shared_from_this());
  i_subGraph->setCurrentParent(shared_from_this());

  if (i_inputs.size() != iGraph.size()) {
    throw std::invalid_argument(
        "Number of inputs should be same, as subgrap inputs number"
    );
  }

  std::vector<VertexPtr> outputs;

  for (auto outVert : i_subGraph->getVerticesByType(VertexTypes::output)) {
    VertexPtr newVertex(new GraphVertexGates(Gates::GateBuf, shared_from_this())
    );

    outputs.push_back(newVertex);
    d_allSubGraphsOutputs.push_back(newVertex);
  }

  // here we save our inputs and outputs to instance number
  i_subGraph->d_subGraphsInputsPtr[d_currentInstance].push_back(i_inputs);
  i_subGraph->d_subGraphsOutputsPtr[d_currentInstance].push_back(outputs);

  // here we use i_subGraph like an instance of BasicType,
  // and we call it's toVerilog, having in multiple instance
  // of one i_subGraph, so we can have many times "moduleName name (inp, out);"
  // having different names of module, inputs and outputs
  d_subGraphs.push_back(i_subGraph);

  return outputs;
}

bool OrientedGraph::addEdge(VertexPtr from, VertexPtr to) {
  bool f;
  int  n;
  if (from->getBaseGraph().lock() == to->getBaseGraph().lock()) {
    f = from->addVertexToOutConnections(to);
    n = to->addVertexToInConnections(from);
  } else {
    if (from->getType() == VertexTypes::output) {
      n = to->addVertexToInConnections(from);
    } else {
      throw std::invalid_argument(
          "Not allowed to add edge from one subgraph to another, if from "
          "vertex is not output"
      );
    }
    if (to->getType() == VertexTypes::input) {
      f = from->addVertexToOutConnections(to);
    } else {
      throw std::invalid_argument(
          "Not allowed to add edge from one subgraph to another, if to vertex "
          "is not input"
      );
    }
  }
  d_edgesCount += f && (n > 0);

  if (from->getType() == VertexTypes::gate
      && to->getType() == VertexTypes::gate)
    ++d_edgesGatesCount[from->getGate()][to->getGate()];

  return f && (n > 0);
}

bool OrientedGraph::addEdges(std::vector<VertexPtr> from1, VertexPtr to) {
  bool f = true;
  for (VertexPtr vert : from1)
    f &= this->addEdge(vert, to);
  return f;
}

std::vector<GraphPtr> OrientedGraph::getSubGraphs() const {
  return d_subGraphs;
}

std::map<VertexTypes, std::vector<VertexPtr>> OrientedGraph::getBaseVertexes(
) const {
  return d_vertexes;
}

VertexPtr OrientedGraph::getVerticeByIndex(int idx) const {
  if (sumFullSize() <= idx || idx < 0)
    throw std::invalid_argument("OrientedGraph getVerticeByIndex: invalid index"
    );

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

std::vector<VertexPtr> OrientedGraph::getVerticesByLevel(const int& i_level) {
  this->updateLevels();
  std::vector<VertexPtr> a;
  // TODO: Реализовать
  return a;
}

std::vector<VertexPtr> OrientedGraph::getVerticesByType(
    const VertexTypes& i_type,
    const std::string& i_name,
    const bool&        i_addSubGraphs
) const {
  if (i_name.size() != 0)
    return d_vertexes.at(i_type);

  std::vector<VertexPtr> resVert;
  for (VertexPtr vert : d_vertexes.at(i_type))
    if ((i_name == "") || (vert->getName() == i_name))
      resVert.push_back(vert);

  if (i_addSubGraphs)
    for (GraphPtr vert : d_subGraphs) {
      std::vector<VertexPtr> subResVert =
          vert->getVerticesByType(i_type, i_name, i_addSubGraphs);
      resVert.insert(resVert.end(), subResVert.begin(), subResVert.end());
    }
  return resVert;
}

std::vector<VertexPtr> OrientedGraph::getVerticesByName(
    const std::string& i_name,
    const bool&        i_addSubGraphs
) const {
  std::vector<VertexPtr> resVert;
  for (const auto& [key, value] : d_vertexes) {
    for (VertexPtr vert : value)
      if (vert->getName() == i_name)
        resVert.push_back(vert);
  }
  if (i_addSubGraphs)
    for (GraphPtr vert : d_subGraphs) {
      std::vector<VertexPtr> subResVert =
          vert->getVerticesByName(i_name, i_addSubGraphs);
      resVert.insert(resVert.end(), subResVert.begin(), subResVert.end());
    }
  return resVert;
}

size_t OrientedGraph::sumFullSize() const {
  return d_vertexes.at(VertexTypes::input).size()
       + d_vertexes.at(VertexTypes::constant).size()
       + d_vertexes.at(VertexTypes::gate).size()
       + d_vertexes.at(VertexTypes::output).size();
}

std::map<Gates, int> OrientedGraph::getGatesCount() const {
  return d_gatesCount;
}

std::map<Gates, std::map<Gates, int>> OrientedGraph::getEdgesGatesCount(
) const {
  return d_edgesGatesCount;
}

std::string OrientedGraph::calculateHash(bool recalculate) {
  if (d_hashed != "" && !recalculate)
    return d_hashed;

  std::vector<std::string> hashed_data;
  d_hashed = "";

  for (auto& input : d_vertexes[VertexTypes::input]) {
    hashed_data.push_back(input->calculateHash(recalculate));
  }
  std::sort(hashed_data.begin(), hashed_data.end());

  for (const auto& sub : hashed_data) {
    d_hashed += sub;
  }

  d_hashed = std::to_string(std::hash<std::string> {}(d_hashed));

  return d_hashed;
}

std::set<GraphPtr> OrientedGraph::getSetSubGraphs() const {
  std::set<GraphPtr> toParse(d_subGraphs.begin(), d_subGraphs.end());

  return toParse;
}

bool OrientedGraph::operator==(const OrientedGraph& rhs) {
  bool correct = rhs.d_vertexes.at(VertexTypes::input).size()
              != d_vertexes.at(VertexTypes::input).size();
  correct &= rhs.d_vertexes.at(VertexTypes::output).size()
          != d_vertexes.at(VertexTypes::output).size();
  correct &= rhs.d_vertexes.at(VertexTypes::constant).size()
          != d_vertexes.at(VertexTypes::constant).size();
  correct &= rhs.d_vertexes.at(VertexTypes::gate).size()
          != d_vertexes.at(VertexTypes::gate).size();

  if (!correct)
    return false;

  return d_hashed == rhs.d_hashed && d_hashed.size();
}

void OrientedGraph::setCurrentParent(GraphPtr i_parent) {
  d_currentParentGraph = i_parent;
}

void OrientedGraph::resetCounters(GraphPtr i_where) {
  d_graphInstanceToVerilogCount[i_where->d_currentInstance] = 0;
}

std::string OrientedGraph::getGraphInstance() {
  uint64_t* verilogCount =
      &d_graphInstanceToVerilogCount[d_currentParentGraph.lock()
                                         ->d_currentInstance];
  uint64_t allCount =
      d_subGraphsInputsPtr[d_currentParentGraph.lock()->d_currentInstance].size(
      );

  if (*verilogCount == allCount) {
    throw std::out_of_range(
        "Incorrect getInstance call. All modules of "
        + d_currentParentGraph.lock()->getName() + " ("
        + std::to_string(allCount) + ") were already parsed"
    );
  }

  std::string verilogTab = "  ";
  // module_name module_name_inst_1 (
  std::string module_ver = verilogTab + d_name + " " + d_name + "_inst_"
                         + std::to_string(*verilogCount) + " (\n";

  for (size_t i = 0; i < d_vertexes[VertexTypes::input].size(); ++i) {
    auto inp =
        d_subGraphsInputsPtr[d_currentParentGraph.lock()->d_currentInstance]
                            [*verilogCount][i];
    std::string inp_name  = d_vertexes[VertexTypes::input][i]->getName();

    module_ver           += verilogTab + verilogTab + "." + inp_name + "( ";
    module_ver           += inp->getName() + " ),\n";
  }

  for (size_t i = 0; i < d_vertexes[VertexTypes::output].size() - 1; ++i) {
    VertexPtr out =
        d_subGraphsOutputsPtr[d_currentParentGraph.lock()->d_currentInstance]
                             [*verilogCount][i];
    std::string out_name  = d_vertexes[VertexTypes::output][i]->getName();

    module_ver           += verilogTab + verilogTab + "." + out_name + "( ";
    module_ver           += out->getName() + " ),\n";
  }

  std::string out_name  = d_vertexes[VertexTypes::output].back()->getName();

  module_ver           += verilogTab + verilogTab + "." + out_name + "( ";
  module_ver +=
      d_subGraphsOutputsPtr[d_currentParentGraph.lock()->d_currentInstance]
                           [*verilogCount]
                               .back()
                               ->getName()
      + " )\n";
  module_ver += verilogTab + "); \n";

  ++(*verilogCount);

  return module_ver;
}

std::pair<bool, std::string>
    OrientedGraph::toVerilog(std::string i_path, std::string i_filename) {
  if (d_alreadyParsed && d_parentGraphs.size()) {
    return std::make_pair(true, getGraphInstance());
  }
  // В данном методе происходит только генерация одного графа. Без подграфов.
  std::string verilogTab = "  ";

  if (!i_filename.size()) {
    i_filename = d_name + ".v";
  }
  std::string   path = i_path + (d_parentGraphs.size() ? "/submodules" : "");

  std::ofstream fileStream(path + "/" + i_filename);

  if (!fileStream) {
    std::cerr << "cannot write file to " << path << std::endl;
    return std::make_pair(false, "");
  }

  fileStream << "module " << d_name << "(\n" << verilogTab;

  // here we are parsing inputs by their wire size
  for (auto inp : d_vertexes[VertexTypes::input]) {
    fileStream << inp->getName() << ", ";
  }
  fileStream << '\n' << verilogTab;

  // and outputs
  for (auto outVert : d_vertexes[VertexTypes::output]) {
    fileStream << outVert->getName(
    ) << ((outVert == d_vertexes[VertexTypes::output].back()) ? "\n" : ", ");
  }
  fileStream << ");\n" << verilogTab;

  // parsing inputs, outputs and wires for subgraphs
  for (auto eachVertex :
       {d_vertexes[VertexTypes::input],
        d_vertexes[VertexTypes::output],
        d_allSubGraphsOutputs}) {
    if (eachVertex.size()) {
      fileStream << VertexUtils::vertexTypeToVerilog(eachVertex.back()->getType(
      )) << " ";
    }

    for (auto value : eachVertex) {
      fileStream << value->getName()
                 << (value != eachVertex.back() ? ", " : ";\n");
    }
    fileStream << verilogTab;
  }

  if (d_vertexes[VertexTypes::constant].size()) {
    fileStream << "\n";
  }
  // writing consts
  for (auto oper : d_vertexes[VertexTypes::constant]) {
    fileStream << verilogTab << oper->getInstance() << "\n";
  }

  if (d_subGraphs.size()) {
    fileStream << "\n";
  }
  // and all modules
  for (auto sub : d_subGraphs) {
    sub->setCurrentParent(shared_from_this());
    std::pair<bool, std::string> val = sub->toVerilog(i_path);
    if (!val.first)
      return std::make_pair(false, "");
    fileStream << val.second;
  }

  if (d_vertexes[VertexTypes::gate].size()) {
    fileStream << "\n";
  }
  // and all operations
  for (auto oper : d_vertexes[VertexTypes::gate]) {
    fileStream << verilogTab << oper->getInstance() << "\n";
    fileStream << verilogTab << oper->toVerilog() << "\n";
  }

  fileStream << "\n";
  // and all outputs
  for (auto oper : d_vertexes[VertexTypes::output]) {
    fileStream << verilogTab << oper->toVerilog() << "\n";
  }

  fileStream << "endmodule\n";

  d_alreadyParsed = true;

  if (d_parentGraphs.size()) {
    return std::make_pair(true, getGraphInstance());
  }

  fileStream.close();
  return std::make_pair(true, "");
}

std::string OrientedGraph::toGraphML(int i_nesting) const {
  const std::string spaces(i_nesting * 4, ' ');

  const std::string graphTemplate =
      AuxMethods::format(rawGraphTemplate, spaces, d_name, "%", spaces);
  const std::string nodeTemplate = AuxMethods::format(
      rawNodeTemplate, spaces, "%", spaces, "%", "%", spaces
  );
  const std::string edgeTemplate =
      AuxMethods::format(rawEdgeTemplate, spaces, "%", "%");

  std::string nodes, edges, graphs;

  for (const auto& [VertexTypes, vertexVector] : d_vertexes) {
    const std::string vertexTypeName =
        d_settings->parseVertexToString(VertexTypes);
    for (const auto& vertex : vertexVector) {
      const std::string vertexKindName =
          vertexTypeName == "g"
              ? d_settings->parseGateToString(vertex->getGate())
          : vertexTypeName == "const" ? std::string(1, vertex->getValue())
                                      : vertexTypeName;

      nodes += AuxMethods::format(
          nodeTemplate, vertex->getName(), vertexKindName, ""
      );
      for (const auto& source : vertex->getInConnections()) {
        if (auto ptr = source.lock()) {
          edges += AuxMethods::format(
              edgeTemplate, ptr->getName(), vertex->getName()
          );
        } else {
          throw std::invalid_argument("Dead pointer!");
        }
      }
    }
  }
  for (const auto& i_subGraph : d_subGraphs) {
    graphs += AuxMethods::format(
        nodeTemplate,
        i_subGraph->getName() + "_subgraph",
        "graph",
        '\n' + i_subGraph->toGraphML(i_nesting + 1)
    );
  }
  std::string finalGraph =
      AuxMethods::format(graphTemplate, nodes + graphs + edges);
  if (i_nesting != 0) {
    return finalGraph;
  }
  return AuxMethods::format(mainTemplate, finalGraph);
}

bool OrientedGraph::toGraphML(std::ofstream& fileStream) const {
  fileStream << this->toGraphML();
  return true;
}