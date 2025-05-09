#include "BasisConverter.hpp"
#include <CircuitGenGraph/GraphUtils.hpp>
#include <CircuitGenGraph/OrientedGraph.hpp>
#include <functional>
#include <unordered_map>
#include <iostream>

namespace {
using namespace CG_Gen;

#define Ensure(CONDITION, MESSAGE) \
  if (!(CONDITION)) { \
    throw std::runtime_error(MESSAGE); \
  }

std::string gateTypeToString(Gates gate) {
  switch (gate) {
    case Gates::GateAnd:
      return "and";
    case Gates::GateOr:
      return "or";
    case Gates::GateXor:
      return "xor";
    case Gates::GateXnor:
      return "xnor";
    case Gates::GateNot:
      return "not";
    case Gates::GateNand:
      return "nand";
    case Gates::GateNor:
      return "nor";
    case Gates::GateDefault:
      return "default";
    default:
      return "unknown";
  }
}

BasisType
getBasisType(const GenerationParameters::GatesInputsInfo &gatesInputsInfo) {
  std::vector<BasisType> allowedTypes;
  if (gatesInputsInfo.find("nand") != gatesInputsInfo.end() &&
      !gatesInputsInfo.at("nand").empty()) {
    allowedTypes.push_back(BasisType::AIG);
  }

  if (gatesInputsInfo.find("nor") != gatesInputsInfo.end() &&
      !gatesInputsInfo.at("nor").empty()) {
    allowedTypes.push_back(BasisType::NOR);
  }

  if (allowedTypes.empty()) {
    throw std::invalid_argument("No allowed basis type found");
  }

  return allowedTypes.front();
}

VertexPtr addNand(GraphPtr graph, VertexPtr left, VertexPtr right,
                  const std::string &name) {
  VertexPtr nand = graph->addGate(Gates::GateNand, name);
  graph->addEdge(left, nand);
  graph->addEdge(right, nand);
  return nand;
}

VertexPtr addAIGNot(GraphPtr graph, VertexPtr parent, const std::string &name) {
  VertexPtr nand = addNand(graph, parent, parent, name);
  return nand;
}

VertexPtr addAIGAnd(GraphPtr graph, VertexPtr left, VertexPtr right,
                    const std::string &name) {
  VertexPtr nand1 = addNand(graph, left, right, name);
  VertexPtr nand2 = addNand(graph, nand1, nand1, name);
  return nand2;
}

VertexPtr addAIGOr(GraphPtr graph, VertexPtr left, VertexPtr right,
                   const std::string &name) {
  VertexPtr nand1 = addNand(graph, left, left, name);
  VertexPtr nand2 = addNand(graph, right, right, name);
  VertexPtr nand3 = addNand(graph, nand1, nand2, name);
  return nand3;
}

VertexPtr addAIGNor(GraphPtr graph, VertexPtr left, VertexPtr right,
                    const std::string &name) {
  VertexPtr nand1 = addNand(graph, left, left, name);
  VertexPtr nand2 = addNand(graph, right, right, name);
  VertexPtr nand3 = addNand(graph, nand1, nand2, name);
  VertexPtr nand4 = addNand(graph, nand3, nand3, name);
  return nand4;
}

VertexPtr addAIGXor(GraphPtr graph, VertexPtr left, VertexPtr right,
                    const std::string &name) {
  VertexPtr nand1 = addNand(graph, left, right, name);
  VertexPtr nand2 = addNand(graph, left, nand1, name);
  VertexPtr nand3 = addNand(graph, right, nand1, name);
  VertexPtr nand4 = addNand(graph, nand2, nand3, name);
  return nand4;
}

VertexPtr addAIGXnor(GraphPtr graph, VertexPtr left, VertexPtr right,
                     const std::string &name) {
  VertexPtr nand1 = addNand(graph, left, right, name);
  VertexPtr nand2 = addNand(graph, left, nand1, name);
  VertexPtr nand3 = addNand(graph, right, nand1, name);
  VertexPtr nand4 = addNand(graph, nand2, nand3, name);
  VertexPtr nand5 = addNand(graph, nand4, nand4, name);
  return nand5;
}

VertexPtr
addMultipleInputGate(GraphPtr graph, VertexPtr vertex,
                     const std::vector<VertexPtr> &parents,
                     std::function<VertexPtr(GraphPtr, VertexPtr, VertexPtr,
                                             const std::string &)>
                         addGate) {
  std::vector<VertexPtr> inputs = parents;
  const auto gateType = vertex->getGate();
  const std::string name =
      "gate_" + gateTypeToString(gateType) + "_" + vertex->getName();
  while (inputs.size() > 1) {
    VertexPtr left = inputs.back();
    inputs.pop_back();
    VertexPtr right = inputs.back();
    inputs.pop_back();
    inputs.push_back(addGate(graph, left, right, name));
  }
  return inputs.front();
}

VertexPtr addGateToAIG(GraphPtr graph, VertexPtr vertex,
                       std::vector<VertexPtr> &parents) {
  if (vertex->getGate() == Gates::GateAnd) {
    Ensure(parents.size() >= 2,
           "AND gate must have at least 2 inputs, current size: " +
               std::to_string(parents.size()));
    return addMultipleInputGate(graph, vertex, parents, addAIGAnd);
  }
  if (vertex->getGate() == Gates::GateNand) {
    Ensure(parents.size() >= 2,
           "NAND gate must have at least 2 inputs, current size: " +
               std::to_string(parents.size()));
    VertexPtr andGate = addMultipleInputGate(graph, vertex, parents, addAIGAnd);
    return addAIGNot(graph, andGate, "nand_not_" + vertex->getName());
  }
  if (vertex->getGate() == Gates::GateOr) {
    Ensure(parents.size() >= 2,
           "OR gate must have at least 2 inputs, current size: " +
               std::to_string(parents.size()));
    return addMultipleInputGate(graph, vertex, parents, addAIGOr);
  }
  if (vertex->getGate() == Gates::GateNor) {
    Ensure(parents.size() >= 2,
           "NOR gate must have at least 2 inputs, current size: " +
               std::to_string(parents.size()));
    VertexPtr orGate = addMultipleInputGate(graph, vertex, parents, addAIGOr);
    return addAIGNot(graph, orGate, "nor_not_" + vertex->getName());
  }
  if (vertex->getGate() == Gates::GateXor) {
    Ensure(parents.size() == 2, "XOR gate must have 2 inputs, current size: " +
                                    std::to_string(parents.size()));
    return addMultipleInputGate(graph, vertex, parents, addAIGXor);
  }
  if (vertex->getGate() == Gates::GateXnor) {
    Ensure(parents.size() == 2, "XNOR gate must have 2 inputs, current size: " +
                                    std::to_string(parents.size()));
    return addMultipleInputGate(graph, vertex, parents, addAIGXnor);
  }
  if (vertex->getGate() == Gates::GateNot) {
    Ensure(parents.size() == 1, "NOT gate must have 1 input, current size: " +
                                    std::to_string(parents.size()));
    return addAIGNot(graph, parents[0], "nand_not_" + vertex->getName());
  }
  throw std::invalid_argument("Unsupported gate type for converting to AIG");
}

VertexPtr addNOR(GraphPtr graph, VertexPtr left, VertexPtr right,
                 const std::string &name) {
  VertexPtr nor = graph->addGate(Gates::GateNor, name);
  graph->addEdge(left, nor);
  graph->addEdge(right, nor);
  return nor;
}

VertexPtr addNORNot(GraphPtr graph, VertexPtr parent, const std::string &name) {
  VertexPtr nor = addNOR(graph, parent, parent, name);
  return nor;
}

VertexPtr addNORAnd(GraphPtr graph, VertexPtr left, VertexPtr right,
                    const std::string &name) {
  VertexPtr nor1 = addNOR(graph, left, left, name);
  VertexPtr nor2 = addNOR(graph, right, right, name);
  VertexPtr nor3 = addNOR(graph, nor1, nor2, name);
  return nor3;
}

VertexPtr addNORNand(GraphPtr graph, VertexPtr left, VertexPtr right,
                     const std::string &name) {
  VertexPtr nor1 = addNOR(graph, left, left, name);
  VertexPtr nor2 = addNOR(graph, right, right, name);
  VertexPtr nor3 = addNOR(graph, nor1, nor2, name);
  VertexPtr nor4 = addNOR(graph, nor3, nor3, name);
  return nor4;
}

VertexPtr addNOROr(GraphPtr graph, VertexPtr left, VertexPtr right,
                   const std::string &name) {
  VertexPtr nor = addNOR(graph, left, right, name);
  VertexPtr nor1 = addNOR(graph, nor, nor, name);
  return nor1;
}

VertexPtr addNORXor(GraphPtr graph, VertexPtr left, VertexPtr right,
                    const std::string &name) {
  VertexPtr nor1 = addNOR(graph, left, right, name);
  VertexPtr nor2 = addNOR(graph, left, nor1, name);
  VertexPtr nor3 = addNOR(graph, right, nor1, name);
  VertexPtr nor4 = addNOR(graph, nor2, nor3, name);
  VertexPtr nor5 = addNOR(graph, nor4, nor4, name);
  return nor5;
}

VertexPtr addNORXnor(GraphPtr graph, VertexPtr left, VertexPtr right,
                     const std::string &name) {
  VertexPtr nor1 = addNOR(graph, left, right, name);
  VertexPtr nor2 = addNOR(graph, left, nor1, name);
  VertexPtr nor3 = addNOR(graph, right, nor1, name);
  VertexPtr nor4 = addNOR(graph, nor2, nor3, name);
  return nor4;
}

VertexPtr addGateToNOR(GraphPtr graph, VertexPtr vertex,
                       std::vector<VertexPtr> &parents) {
  if (vertex->getGate() == Gates::GateAnd) {
    Ensure(parents.size() >= 2,
           "AND gate must have at least 2 inputs, current size: " +
               std::to_string(parents.size()));
    return addMultipleInputGate(graph, vertex, parents, addNORAnd);
  }
  if (vertex->getGate() == Gates::GateNand) {
    Ensure(parents.size() >= 2,
           "NAND gate must have at least 2 inputs, current size: " +
               std::to_string(parents.size()));
    VertexPtr andGate = addMultipleInputGate(graph, vertex, parents, addNORAnd);
    return addNORNot(graph, andGate, vertex->getName());
  }
  if (vertex->getGate() == Gates::GateOr) {
    Ensure(parents.size() >= 2,
           "OR gate must have at least 2 inputs, current size: " +
               std::to_string(parents.size()));
    return addMultipleInputGate(graph, vertex, parents, addNOROr);
  }
  if (vertex->getGate() == Gates::GateNor) {
    Ensure(parents.size() >= 2,
           "NOR gate must have at least 2 inputs, current size: " +
               std::to_string(parents.size()));
    VertexPtr orGate = addMultipleInputGate(graph, vertex, parents, addNOROr);
    return addNORNot(graph, orGate, vertex->getName());
  }
  if (vertex->getGate() == Gates::GateXor) {
    Ensure(parents.size() == 2, "XOR gate must have 2 inputs, current size: " +
                                    std::to_string(parents.size()));
    return addMultipleInputGate(graph, vertex, parents, addNORXor);
  }
  if (vertex->getGate() == Gates::GateXnor) {
    Ensure(parents.size() == 2, "XNOR gate must have 2 inputs, current size: " +
                                    std::to_string(parents.size()));
    return addMultipleInputGate(graph, vertex, parents, addNORXnor);
  }
  if (vertex->getGate() == Gates::GateNot) {
    Ensure(parents.size() == 1, "NOT gate must have 1 input, current size: " +
                                    std::to_string(parents.size()));
    return addNORNot(graph, parents[0], vertex->getName());
  }
  throw std::invalid_argument("Unsupported gate type for converting to NOR");
}

VertexPtr addVertexToBasis(
    GraphPtr graph, VertexPtr vertex, std::vector<VertexPtr> &parents,
    const GenerationParameters::GatesInputsInfo &gatesInputsInfo,
    std::function<VertexPtr(GraphPtr, VertexPtr, std::vector<VertexPtr> &)>
        vertexConverter,
    const std::string &name) {
  if (vertex->getType() == CG_Graph::VertexTypes::input) {
    return graph->addInput("input_" + vertex->getName());
  }
  if (vertex->getType() == CG_Graph::VertexTypes::output) {
    return graph->addOutput("output_" + vertex->getName());
  }
  if (vertex->getType() == CG_Graph::VertexTypes::constant) {
    return graph->addConst(vertex->getValue(), "const_" + vertex->getName());
  }
  if (vertex->getType() == CG_Graph::VertexTypes::gate) {
    if (gatesInputsInfo.find(gateTypeToString(vertex->getGate())) ==
            gatesInputsInfo.end() ||
        gatesInputsInfo.at(gateTypeToString(vertex->getGate())).empty()) {
      return vertexConverter(graph, vertex, parents);
    }
    VertexPtr vert =
        graph->addGate(vertex->getGate(), "gate_" + vertex->getName());
    for (const auto &parent: parents) {
      graph->addEdge(parent, vert);
    }
    return vert;
  }

  std::stringstream ss;
  ss << "Unsupported vertex type for converting to " << name;
  throw std::invalid_argument(ss.str());
}

void printVertex(VertexPtr vertex) {
  std::cout << "vertex: '" << vertex->getName() << "'" << std::endl;
  std::cout << "type name: '" << vertex->getTypeName() << "'" << std::endl;
  std::cout << "gate: '" << gateTypeToString(vertex->getGate()) << "' "
            << std::endl;
  std::cout << "level: " << vertex->getLevel() << std::endl;
  std::cout << "parent count: " << vertex->getInConnections().size()
            << std::endl;
  std::cout << "parents: " << std::endl;
  for (const auto &parent: vertex->getInConnections()) {
    std::cout << "\t'" << parent->getName() << "' '" << parent->getTypeName()
              << "'" << std::endl;
  }
  std::cout << std::endl;
}

} // namespace

namespace CG_Gen {

GraphPtr
convertGraphToBasis(GraphPtr graph,
                    GenerationParameters::GatesInputsInfo gatesInputsInfo) {
  const auto converterType = getBasisType(gatesInputsInfo);

  std::function<VertexPtr(GraphPtr, VertexPtr, std::vector<VertexPtr> &)>
      converter;
  std::string basisName;

  switch (converterType) {
    case BasisType::AIG:
      converter = addGateToAIG;
      basisName = "AIG";
      break;
    case BasisType::NOR:
      converter = addGateToNOR;
      basisName = "NOR";
      break;
    default:
      throw std::invalid_argument("Unsupported basis type");
  }

  GraphPtr newGraph = std::make_shared<CG_Graph::OrientedGraph>();
  std::vector<VertexPtr> vertices =
      graph->getBaseVertexes()[CG_Graph::VertexTypes::input];

  size_t maxLevel = graph->getMaxLevel();
  size_t idx = 0;
  std::unordered_map<VertexPtr, VertexPtr> vertexOld2New;

  for (size_t level = 0; level <= maxLevel; ++level) {
    const auto &verticesByLevel = graph->getVerticesByLevel(level);
    for (const auto &vertex: verticesByLevel) {
      const auto parentsOld = vertex->getInConnections();
      std::vector<VertexPtr> parentsNew;
      for (const auto &parent: parentsOld) {
        parentsNew.push_back(vertexOld2New[parent]);
      }

      VertexPtr basisVertex = addVertexToBasis(
          newGraph, vertex, parentsNew, gatesInputsInfo, converter, basisName);
      vertexOld2New[vertex] = basisVertex;
    }
  }

  return newGraph;
}

} // namespace CG_Gen
