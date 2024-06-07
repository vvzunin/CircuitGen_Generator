#include <iostream>
#include <memory>
#include <stack>
#include <unordered_set>

#include "GraphVertex.hpp"

GraphVertexSubGraph::GraphVertexSubGraph(
    GraphPtr i_subGraph,
    GraphPtr i_baseGraph
) :
  GraphVertexBase(VertexTypes::subGraph, i_baseGraph) {
  d_subGraph = i_subGraph;
}
GraphVertexSubGraph::GraphVertexSubGraph(
    GraphPtr           i_subGraph,
    const std::string& i_name,
    GraphPtr           i_baseGraph
) :
  GraphVertexBase(VertexTypes::subGraph, i_name, i_baseGraph) {
  d_subGraph = i_subGraph;
}

// TODO add normal calculation
char GraphVertexSubGraph::updateValue() {
  return 'x';
}

// In fact is not needed
std::string GraphVertexSubGraph::getInstance() {
  return d_subGraph->getGraphInstance();
}

std::pair<bool, std::string>
    GraphVertexSubGraph::toVerilog(std::string i_path, std::string i_filename) {
  if (auto parentPtr = d_baseGraph.lock()) {
    d_subGraph->setCurrentParent(parentPtr);
  } else {
    throw std::invalid_argument("Dead pointer!");
  }

  return d_subGraph->toVerilog(i_path, i_filename);
}

bool GraphVertexSubGraph::toGraphML(std::ofstream& i_fileStream) const {
  return d_subGraph->toGraphMLClassic(i_fileStream);
}

std::string GraphVertexSubGraph::toGraphML(
    uint16_t    i_indent,
    std::string i_prefix
) const {
  return d_subGraph->toGraphMLClassic(i_indent, i_prefix);
}

std::string GraphVertexSubGraph::toVerilog() {
  return "DO NOT CALL IT";
}

void GraphVertexSubGraph::setSubGraph(GraphPtr i_subGraph) {
  d_subGraph = i_subGraph;
}

GraphPtr GraphVertexSubGraph::getSubGraph() const {
  return d_subGraph;
}

std::string GraphVertexSubGraph::calculateHash(bool recalculate) {
  if (hashed != "" && !recalculate)
    return hashed;

  // calc hash from subgraph
  hashed = d_subGraph->calculateHash();

  // futuire sorted struct
  std::vector<std::string> hashed_data;

  for (auto& child : d_outConnections) {
    hashed_data.push_back(child->calculateHash(recalculate));
  }
  std::sort(hashed_data.begin(), hashed_data.end());

  for (const auto& sub : hashed_data) {
    hashed += sub;
  }

  hashed = std::to_string(std::hash<std::string> {}(hashed));

  return hashed;
}

std::vector<VertexPtr> GraphVertexSubGraph::getOutputBuffersByOuterInput(
    VertexPtr i_outerInput
) const {
  size_t inputIndex = SIZE_MAX;
  for (size_t i = 0; i < d_inConnections.size(); ++i) {
    if (d_inConnections[i].lock() == i_outerInput) {
      inputIndex = i;
      break;
    }
  }
  if (inputIndex == SIZE_MAX) {
    throw std::invalid_argument(
        "Provided outer input does not correspond to this subgraph."
    );
  }
  VertexPtr sgInput =
      d_subGraph->getBaseVertexes().at(VertexTypes::input).at(inputIndex);
  std::vector<VertexPtr> sgAllOutputs =
      d_subGraph->getBaseVertexes().at(VertexTypes::output);
  std::vector<VertexPtr>        outputs;

  std::unordered_set<VertexPtr> visited;
  std::stack<VertexPtr>         stck;
  stck.push(sgInput);

  while (!stck.empty()) {
    VertexPtr current = stck.top();
    stck.pop();

    if (visited.find(current) == visited.end()) {
      visited.insert(current);

      for (auto v : current->getOutConnections()) {
        if (v->getType() == VertexTypes::output) {
          for (size_t i = 0; i < sgAllOutputs.size(); ++i) {
            if (sgAllOutputs[i] == v) {
              outputs.push_back(d_outConnections[i]);
            }
          }
        } else if (v->getType() != VertexTypes::subGraph) {
          stck.push(v);
        } else {
          auto subGraphPtr = std::dynamic_pointer_cast<GraphVertexSubGraph>(v);
          for (auto buf : subGraphPtr->getOutputBuffersByOuterInput(current)) {
            stck.push(buf);
          }
        }
      }
    }
  }
  return outputs;
}

std::vector<VertexPtr> GraphVertexSubGraph::getOuterInputsByOutputBuffer(
    VertexPtr i_outputBuffer
) const {
  size_t bufferIndex = SIZE_MAX;
  for (size_t i = 0; i < d_outConnections.size(); ++i) {
    if (d_outConnections[i] == i_outputBuffer) {
      bufferIndex = i;
      break;
    }
  }
  if (bufferIndex == SIZE_MAX) {
    throw std::invalid_argument(
        "Provided output buffer does not correspond to this subgraph."
    );
  }
  VertexPtr sgOutput =
      d_subGraph->getBaseVertexes().at(VertexTypes::output).at(bufferIndex);
  std::vector<VertexPtr> sgAllInputs =
      d_subGraph->getBaseVertexes().at(VertexTypes::input);
  std::vector<VertexPtr>        inputs;

  std::unordered_set<VertexPtr> visited;
  std::stack<VertexPtr>         stck;
  stck.push(sgOutput);

  while (!stck.empty()) {
    VertexPtr current = stck.top();
    stck.pop();

    if (visited.find(current) == visited.end()) {
      visited.insert(current);

      for (auto v : current->getInConnections()) {
        auto ptr = v.lock();
        if (!ptr) {
          throw std::invalid_argument("Dead pointer!");
        }
        if (ptr->getType() == VertexTypes::input) {
          for (size_t i = 0; i < sgAllInputs.size(); ++i) {
            if (sgAllInputs[i] == ptr) {
              inputs.push_back(d_inConnections[i].lock());
            }
          }
        } else if (ptr->getType() != VertexTypes::subGraph) {
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
  return inputs;
}