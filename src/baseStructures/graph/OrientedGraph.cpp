#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#include <additional/AuxiliaryMethods.hpp>
#include <baseStructures/graph/GraphMLTemplates.hpp>
#include <baseStructures/graph/GraphVertex.hpp>
#include <baseStructures/graph/GraphVertexBase.hpp>
#include <CircuitGenGenerator/OrientedGraph.hpp>

std::atomic_size_t OrientedGraph::d_countGraph            = 0;
std::atomic_size_t OrientedGraph::d_countNewGraphInstance = 0;

OrientedGraph::OrientedGraph(const std::string& i_name) {
  d_graphID = d_countNewGraphInstance++;

  if (i_name == "")
    d_name = "graph_" + std::to_string(d_countGraph++);
  else
    d_name = i_name;

  // filling edges
  for (auto cur_gate : d_settings->getLogicOperationsKeys()) {
    d_edgesGatesCount[cur_gate] = d_gatesCount;
  }
}

OrientedGraph::~OrientedGraph() {
  for (auto sub : d_subGraphs) {
    sub->d_subGraphsInputsPtr.erase(d_graphID);
    sub->d_subGraphsOutputsPtr.erase(d_graphID);

    sub->d_currentParentGraph.lock() = nullptr;
  }
}

size_t OrientedGraph::baseSize() const {
  return d_vertexes.at(VertexTypes::gate).size();
}

size_t OrientedGraph::fullSize() const {
  size_t size = this->baseSize();
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

uint32_t OrientedGraph::getMaxLevel() {
  this->updateLevels();
  uint32_t mx = 0;
  for (VertexPtr vert : d_vertexes.at(VertexTypes::output)) {
    mx = mx < vert->getLevel() ? mx : vert->getLevel();
  }
  return mx;
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
  std::vector<VertexPtr> iGraph =
      i_subGraph->getVerticesByType(VertexTypes::input);

  i_subGraph->setCurrentParent(shared_from_this());
  i_subGraph->d_isSubGraph = true;

  if (i_inputs.size() != iGraph.size()) {
    throw std::invalid_argument(
        "Number of inputs should be same, as subgraph inputs number"
    );
  }

  std::vector<VertexPtr> outputs;

  VertexPtr newGraph(new GraphVertexSubGraph(i_subGraph, shared_from_this()));
  d_vertexes[VertexTypes::subGraph].push_back(newGraph);

  // adding edges for subGraphs
  addEdges(i_inputs, newGraph);

  for (auto outVert : i_subGraph->getVerticesByType(VertexTypes::output)) {
    VertexPtr newVertex(new GraphVertexGates(Gates::GateBuf, shared_from_this())
    );

    outputs.push_back(newVertex);
    d_allSubGraphsOutputs.push_back(newVertex);

    addEdge(newGraph, newVertex);
  }

  // here we save our inputs and outputs to instance number
  i_subGraph->d_subGraphsInputsPtr[d_graphID].push_back(i_inputs);
  i_subGraph->d_subGraphsOutputsPtr[d_graphID].push_back(outputs);

  // here we use i_subGraph like an instance of BasicType,
  // and we call it's toVerilog, having in multiple instance
  // of one i_subGraph, so we can have many times "moduleName name (inp, out);"
  // having different names of module, inputs and outputs
  d_subGraphs.insert(i_subGraph);

  return outputs;
}

bool OrientedGraph::addEdge(VertexPtr from, VertexPtr to) {
  bool     f;
  uint32_t n;
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

std::set<GraphPtr> OrientedGraph::getSubGraphs() const {
  return d_subGraphs;
}

std::map<VertexTypes, std::vector<VertexPtr>> OrientedGraph::getBaseVertexes(
) const {
  return d_vertexes;
}

VertexPtr OrientedGraph::getVerticeByIndex(size_t idx) const {
  if (sumFullSize() <= idx)
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

std::vector<VertexPtr> OrientedGraph::getVerticesByLevel(const uint32_t& i_level
) {
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
       + d_vertexes.at(VertexTypes::output).size()
       + d_vertexes.at(VertexTypes::subGraph).size();
}

std::map<Gates, size_t> OrientedGraph::getGatesCount() const {
  return d_gatesCount;
}

std::map<Gates, std::map<Gates, size_t>> OrientedGraph::getEdgesGatesCount(
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
  correct &= rhs.d_vertexes.at(VertexTypes::subGraph).size()
          != d_vertexes.at(VertexTypes::subGraph).size();

  if (!correct)
    return false;

  return d_hashed == rhs.d_hashed && d_hashed.size();
}

void OrientedGraph::setCurrentParent(GraphPtr i_parent) {
  d_currentParentGraph = i_parent;
}

void OrientedGraph::resetCounters(GraphPtr i_where) {
  d_graphInstanceToVerilogCount[i_where->d_graphID] = 0;
}

std::string OrientedGraph::getGraphInstance() {
  uint64_t* verilogCount =
      &d_graphInstanceToVerilogCount[d_currentParentGraph.lock()->d_graphID];
  uint64_t allCount =
      d_subGraphsInputsPtr[d_currentParentGraph.lock()->d_graphID].size();

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
    auto inp = d_subGraphsInputsPtr[d_currentParentGraph.lock()->d_graphID]
                                   [*verilogCount][i];
    std::string inp_name = d_vertexes[VertexTypes::input][i]->getName();

    module_ver           += verilogTab + verilogTab + "." + inp_name + "( ";
    module_ver           += inp->getName() + " ),\n";
  }

  for (size_t i = 0; i < d_vertexes[VertexTypes::output].size() - 1; ++i) {
    VertexPtr out =
        d_subGraphsOutputsPtr[d_currentParentGraph.lock()->d_graphID]
                             [*verilogCount][i];
    std::string out_name = d_vertexes[VertexTypes::output][i]->getName();

    module_ver           += verilogTab + verilogTab + "." + out_name + "( ";
    module_ver           += out->getName() + " ),\n";
  }

  std::string out_name = d_vertexes[VertexTypes::output].back()->getName();

  module_ver           += verilogTab + verilogTab + "." + out_name + "( ";
  module_ver += d_subGraphsOutputsPtr[d_currentParentGraph.lock()->d_graphID]
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
  if (d_alreadyParsed && d_isSubGraph) {
    return std::make_pair(true, getGraphInstance());
  }
  // В данном методе происходит только генерация одного графа. Без подграфов.
  std::string verilogTab = "  ";

  if (!i_filename.size()) {
    i_filename = d_name + ".v";
  }
  std::string   path        = i_path + (d_isSubGraph ? "/submodules" : "");

  auto          correctPath = path + "/" + i_filename;
  std::ofstream fileStream(correctPath);

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

  // parsing inputs, outputs and wires for subgraphs. And wires for operations
  // too
  uint8_t count = 0;
  for (auto eachVertex :
       {d_vertexes[VertexTypes::input],
        d_vertexes[VertexTypes::output],
        d_allSubGraphsOutputs,
        d_vertexes[VertexTypes::gate]}) {
    if (eachVertex.size()) {
      auto usedType = eachVertex.back()->getType();

      fileStream << VertexUtils::vertexTypeToComment(usedType);

      switch (count) {
        case 2:
          fileStream << " for subGraphs outputs";
          break;
        case 3:
          fileStream << " for main graph";
          break;
      }
      fileStream << std::endl << verilogTab;

      fileStream << VertexUtils::vertexTypeToVerilog(usedType) << " ";
    }

    for (auto value : eachVertex) {
      fileStream << value->getName()
                 << (value != eachVertex.back() ? ", " : ";\n");
    }
    fileStream << verilogTab;

    ++count;
  }

  if (d_vertexes[VertexTypes::constant].size()) {
    fileStream << "\n";
  }
  // writing consts
  for (auto oper : d_vertexes[VertexTypes::constant]) {
    fileStream << verilogTab << oper->getInstance() << "\n";
    fileStream << verilogTab << oper->toVerilog() << "\n";
  }

  if (d_subGraphs.size()) {
    fileStream << "\n";
  }
  // and all modules
  for (auto subPtr : d_vertexes[VertexTypes::subGraph]) {
    auto sub = std::static_pointer_cast<GraphVertexSubGraph>(subPtr);

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
    fileStream << verilogTab << oper->toVerilog() << "\n";
  }

  fileStream << "\n";
  // and all outputs
  for (auto oper : d_vertexes[VertexTypes::output]) {
    fileStream << verilogTab << oper->toVerilog() << "\n";
  }

  fileStream << "endmodule\n";

  d_alreadyParsed = true;

  if (d_isSubGraph) {
    return std::make_pair(true, getGraphInstance());
  }

  fileStream.close();
  return std::make_pair(true, "");
}

std::string OrientedGraph::toGraphMLClassic(
    uint16_t           i_indent,
    const std::string& i_prefix
) const {
  using namespace AuxMethods;      // format() and replacer()
  using namespace ClassicGraphML;  // templates

  const std::string spaces(i_indent, ' ');

  const std::string graphTemplate =
      format(rawGraphTemplate, spaces, i_indent ? "%:" : "%", "%", spaces);
  const std::string nodeTemplate =
      format(rawNodeTemplate, spaces, "%", spaces, "%", "%%", spaces);
  const std::string edgeTemplate = format(rawEdgeTemplate, spaces, "%", "%");

  std::string       nodes, edges, graphs, vertexKindName;

  for (const auto& [vertexType, vertexVector] : d_vertexes) {
    switch (vertexType) {
      // skipping subgraphs, will be parsed later
      case VertexTypes::subGraph:
        continue;
      case VertexTypes::input:
      case VertexTypes::output:
        vertexKindName = d_settings->parseVertexToString(vertexType);
        break;
    }

    for (const auto& v : vertexVector) {
      // every "gate" and "const" vertex has subtypes
      switch (vertexType) {
        case VertexTypes::constant:
          vertexKindName = std::string(1, v->getValue());
          break;
        case VertexTypes::gate:
          vertexKindName = d_settings->parseGateToString(v->getGate());
          break;
      }

      nodes +=
          format(nodeTemplate, v->getName(i_prefix), vertexKindName, "", "");

      for (const auto& sink : v->getOutConnections()) {
        // parsing edges not related to subGraphs
        if (sink->getType() != VertexTypes::subGraph) {
          edges += format(
              edgeTemplate, v->getName(i_prefix), sink->getName(i_prefix)
          );
        }
      }
    }
  }

  std::string currentSubGraphTemplate, sgName;

  for (const auto& sg : d_subGraphs) {
    // preparing template for subGraphs as vertices
    currentSubGraphTemplate = format(
        nodeTemplate,
        "%",
        "subGraph",
        "\n",
        sg->toGraphMLClassic(i_indent + 4, i_prefix + "%::")
    );

    // graphInputs, graphOutputs, verticesInputs, verticesOutputs
    const auto& gInputs  = sg->d_vertexes.at(VertexTypes::input);
    const auto& gOutputs = sg->d_vertexes.at(VertexTypes::output);
    const auto& vInputs  = sg->d_subGraphsInputsPtr.at(d_graphID);
    const auto& vOutputs = sg->d_subGraphsOutputsPtr.at(d_graphID);

    for (size_t i = 0; i < vOutputs.size(); ++i) {
      // getting name of current subGraph vertex
      sgName = vOutputs[i][0]->getInConnections()[0].lock()->getName(i_prefix);

      // element->subGraph edges
      for (size_t j = 0; j < gInputs.size(); ++j) {
        edges += format(
            edgeTemplate,
            vInputs[i][j]->getName(i_prefix),
            gInputs[j]->getName(sgName + "::")
        );
      }
      // subGraph->element edges (skipping buffer)
      for (size_t j = 0; j < gOutputs.size(); ++j) {
        if (vOutputs[i][j]->getOutConnections().empty()) {
          continue;
        }
        edges += format(
            edgeTemplate,
            gOutputs[j]->getName(sgName + "::"),
            vOutputs[i][j]->getOutConnections()[0]->getName(i_prefix)
        );
      }

      // parsing subGraphs as vertices
      graphs += replacer(currentSubGraphTemplate, sgName);
    }
  }

  std::string finalGraph = format(graphTemplate, "%", nodes + graphs + edges);
  if (i_indent != 0) {
    return finalGraph;
  }
  return format(mainTemplate, format(finalGraph, d_name));
}

bool OrientedGraph::toGraphMLClassic(std::ofstream& fileStream) const {
  fileStream << this->toGraphMLClassic();
  return true;
}

bool OrientedGraph::toGraphMLPseudoABCD(std::ofstream& fileStream) const {
  fileStream << this->toGraphMLPseudoABCD();
  return true;
}

bool OrientedGraph::toGraphMLOpenABCD(std::ofstream& fileStream) const {
  fileStream << this->toGraphMLOpenABCD();
  return true;
}

std::string OrientedGraph::toGraphMLPseudoABCD() const {
  using namespace AuxMethods;  // format()
  using namespace PseudoABCD;  // templates

  std::shared_ptr<const OrientedGraph> graphPtr = shared_from_this();
  if (!d_vertexes.at(VertexTypes::subGraph).empty()) {
    graphPtr = this->unrollGraph();
  }

  std::string                     nodes, edges, nodeType, actualName, sinkName;
  std::map<std::string, uint32_t> nodeNames;
  uint32_t                        nodeCounter = 0;

  for (const auto& [vertexType, vertexVector] : graphPtr->d_vertexes) {
    switch (vertexType) {
      case VertexTypes::input:
        nodeType = "0";
        break;
      case VertexTypes::output:
        nodeType = "1";
        break;
    }

    for (const auto& v : vertexVector) {
      // every "gate" and "const" vertex has subtypes
      switch (vertexType) {
        case VertexTypes::constant:
          nodeType = "100" + std::string(1, v->getValue());
          break;
        case VertexTypes::gate:
          nodeType = gateToABCDType.at(v->getGate());
          break;
      }
      actualName = v->getName();
      if (nodeNames.find(actualName) == nodeNames.end()) {
        nodeNames[actualName] = nodeCounter++;
      }
      nodes +=
          format(nodeTemplate, nodeNames.at(actualName), actualName, nodeType);

      for (const auto& sink : v->getOutConnections()) {
        sinkName = sink->getName();
        if (nodeNames.find(sinkName) == nodeNames.end()) {
          nodeNames[sinkName] = nodeCounter++;
        }

        edges += format(
            edgeTemplate, nodeNames.at(actualName), nodeNames.at(sinkName)
        );
      }
    }
  }

  return format(mainTemplate, nodes + edges);
}

std::string OrientedGraph::toGraphMLOpenABCD() const {
  using namespace AuxMethods;  // format()
  using namespace OpenABCD;    // templates

  std::shared_ptr<const OrientedGraph> graphPtr = shared_from_this();
  if (!d_vertexes.at(VertexTypes::subGraph).empty()) {
    graphPtr = this->unrollGraph();
  }

  std::string nodes, edges, nodeType, actualName, currentName;
  Gates       currentGate, vGate, sGate;
  std::map<std::string, uint32_t> nodeNames;
  uint32_t                        nodeCounter = 0, inverted;

  for (const auto& [vertexType, vertexVector] : graphPtr->d_vertexes) {
    switch (vertexType) {
      case VertexTypes::input:
        nodeType = "0";
        break;
      case VertexTypes::output:
        nodeType = "1";
        break;
    }

    for (const auto& v : vertexVector) {
      // every "gate" and "const" vertex has subtypes
      switch (vertexType) {
        case VertexTypes::constant:
          nodeType = "100" + std::string(1, v->getValue());
          break;
        case VertexTypes::gate:
          vGate = v->getGate();
          if (vGate == Gates::GateBuf || vGate == Gates::GateNot) {
            continue;
          }
          nodeType = gateToABCDType.at(vGate);
          break;
      }

      actualName = v->getName();
      if (nodeNames.find(actualName) == nodeNames.end()) {
        nodeNames[actualName] = nodeCounter++;
      }

      inverted = 0;
      for (const auto& sink : v->getOutConnections()) {
        std::stack<std::pair<VertexPtr, bool>> stck;
        stck.push({sink, sink->getGate() == Gates::GateNot ? 1 : 0});

        while (!stck.empty()) {
          auto current = stck.top();
          stck.pop();
          currentGate = current.first->getGate();
          if (currentGate == Gates::GateBuf || currentGate == Gates::GateNot) {
            for (const auto& s : current.first->getOutConnections()) {
              sGate      = s->getGate();
              bool state = current.second;
              stck.push({s, sGate == Gates::GateNot ? !state : state});
            }
          } else {
            currentName = current.first->getName();
            if (nodeNames.find(currentName) == nodeNames.end()) {
              nodeNames[currentName] = nodeCounter++;
            }
            edges += format(
                edgeTemplate,
                nodeNames.at(actualName),
                nodeNames.at(currentName),
                current.second
            );
            inverted += current.second;
          }
        }
      }
      nodes += format(
          nodeTemplate, nodeNames.at(actualName), actualName, nodeType, inverted
      );
    }
  }
  return format(mainTemplate, nodes + edges);
}

GraphPtr OrientedGraph::unrollGraph() const {
  GraphPtr newGraph(new OrientedGraph(d_name + "_unrolled"));
  std::map<VertexPtr, VertexPtr> vPairs;

  for (const auto& v : d_vertexes.at(VertexTypes::input)) {
    vPairs.insert({v, newGraph->addInput(v->getName())});
  }
  for (const auto& v : d_vertexes.at(VertexTypes::output)) {
    vPairs.insert({v, newGraph->addOutput(v->getName())});
  }

  auto unroller = [&](std::shared_ptr<const OrientedGraph> graph,
                      std::string                          prefix,
                      auto&&                               unroller) -> void {
    for (const auto& [vertexType, vertices] : graph->getBaseVertexes()) {
      for (const auto& v : vertices) {
        VertexPtr newVertex;

        switch (vertexType) {
          case VertexTypes::constant:
            newVertex = newGraph->addConst(v->getValue(), v->getName(prefix));
            vPairs[v] = newVertex;
            break;
          case VertexTypes::gate:
            newVertex = newGraph->addGate(v->getGate(), v->getName(prefix));
            vPairs[v] = newVertex;
            break;

          case VertexTypes::subGraph: {
            const auto sgv = std::dynamic_pointer_cast<GraphVertexSubGraph>(v);
            const GraphPtr sg       = sgv->getSubGraph();
            const auto&    gInputs  = sg->d_vertexes.at(VertexTypes::input);
            const auto&    gOutputs = sg->d_vertexes.at(VertexTypes::output);
            const auto&    vInputs  = v->getInConnections();
            const auto&    vOutputs = v->getOutConnections();
            VertexPtr      ptr;

            unroller(sg, v->getName() + "::", unroller);

            for (size_t i = 0; i < vInputs.size(); ++i) {
              ptr = vInputs[i].lock();
              if (!ptr) {
                throw std::invalid_argument("Dead pointer!");
              }
              for (const auto& innerVertex : gInputs[i]->getOutConnections()) {
                if (vPairs.find(innerVertex) != vPairs.end()
                    && vPairs.find(ptr) != vPairs.end())
                  newGraph->addEdge(vPairs.at(ptr), vPairs.at(innerVertex));
              }
            }

            for (size_t i = 0; i < vOutputs.size(); ++i) {
              for (const auto& innerVertex : gOutputs[i]->getInConnections()) {
                ptr = innerVertex.lock();
                if (!ptr) {
                  throw std::invalid_argument("Dead pointer!");
                }
                for (const auto& nonBuffer : vOutputs[i]->getOutConnections()) {
                  if (vPairs.find(nonBuffer) != vPairs.end()
                      && vPairs.find(ptr) != vPairs.end())
                    newGraph->addEdge(vPairs.at(ptr), vPairs.at(nonBuffer));
                }
              }
            }

            break;
          }
          default:
            continue;
        }
      }
    }
  };

  unroller(shared_from_this(), "", unroller);

  for (const auto& pair : vPairs) {
    for (const auto& v : pair.first->getOutConnections()) {
      // if v is not subGraph and if v is not output from subGraph
      if (v->getType() != VertexTypes::subGraph
          && (v->getType() != VertexTypes::output
              || v->getBaseGraph().lock().get() == this)) {
        newGraph->addEdge(pair.second, vPairs.at(v));
      }
    }
  }

  return newGraph;
}

bool OrientedGraph::isConnected(bool i_recalculate) {
  if (d_connected && !i_recalculate) {
    return d_connected + 1;
  }

  size_t size = sumFullSize();
  if (size <= 1) {
    return (d_connected = 1);
  }

  size_t                        subGraphsBuffersCount = 0;
  std::unordered_set<VertexPtr> disconnectedSubGraphs;
  for (auto subGraph : d_vertexes[VertexTypes::subGraph]) {
    subGraphsBuffersCount += subGraph->getOutConnections().size();
    auto subGraphPtr = std::dynamic_pointer_cast<GraphVertexSubGraph>(subGraph);
    if (!subGraphPtr->getSubGraph()->isConnected()) {
      disconnectedSubGraphs.insert(subGraph);
    }
  }

  std::unordered_set<VertexPtr> visited;
  VertexPtr                     startVertex = nullptr;
  for (auto& [type, vertices] : d_vertexes) {
    if (type == VertexTypes::subGraph) {
      continue;
    }
    if (!vertices.empty()) {
      startVertex = vertices[0];
      break;
    }
  }

  dfs(startVertex, visited, disconnectedSubGraphs);

  if (visited.size()
      == size + subGraphsBuffersCount - disconnectedSubGraphs.size()) {
    return (d_connected = 1);
  } else {
    return (d_connected = -1) + 1;
  }
}

// void OrientedGraph::dfs(
//     VertexPtr                      i_v,
//     std::unordered_set<VertexPtr>& i_visited
// ) {
//   i_visited.insert(i_v);
//   for (auto v : i_v->getOutConnections()) {
//     if (i_visited.find(v) == i_visited.end()) {
//       dfs(v, i_visited);
//     }
//   }
//   for (auto v : i_v->getInConnections()) {
//     auto ptr = v.lock();
//     if (!ptr) {
//       throw std::invalid_argument("Dead pointer!");
//     }
//     if (i_visited.find(ptr) == i_visited.end()) {
//       dfs(ptr, i_visited);
//     }
//   }
// }

void OrientedGraph::dfs(
    VertexPtr                      i_startVertex,
    std::unordered_set<VertexPtr>& i_visited,
    std::unordered_set<VertexPtr>& i_dsg
) {
  std::stack<VertexPtr> stck;
  stck.push(i_startVertex);

  while (!stck.empty()) {
    VertexPtr current = stck.top();
    stck.pop();

    if (i_visited.find(current) == i_visited.end()) {
      i_visited.insert(current);

      for (auto v : current->getOutConnections()) {
        if (v->getType() != VertexTypes::subGraph
            || i_dsg.find(v) == i_dsg.end()) {
          stck.push(v);
        } else {
          auto subGraphPtr = std::dynamic_pointer_cast<GraphVertexSubGraph>(v);
          for (auto buf : subGraphPtr->getOutputBuffersByOuterInput(current)) {
            stck.push(buf);
          }
        }
      }
      for (auto v : current->getInConnections()) {
        auto ptr = v.lock();
        if (!ptr) {
          throw std::invalid_argument("Dead pointer!");
        }
        if (ptr->getType() != VertexTypes::subGraph
            || i_dsg.find(ptr) == i_dsg.end()) {
          stck.push(ptr);
        } else {
          auto subGraphPtr =
              std::dynamic_pointer_cast<GraphVertexSubGraph>(ptr);
          for (auto input :
               subGraphPtr->getOuterInputsByOutputBuffer(current)) {
            stck.push(input);
          }
        }
      }
    }
  }
}
