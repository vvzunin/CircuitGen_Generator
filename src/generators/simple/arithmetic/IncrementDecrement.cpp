#include "../ArithmeticGenerator.hpp"
#include "generators/simple/arithmetic/ArithmeticUtils.hpp"
#include <vector>

namespace CG_Gen {

GraphPtr ArithmeticGenerator::generateIncrement(
    const GenerationParameters &i_param) const {
  uint32_t sizeA = i_param.getArithmetic().getSizeA();
  uint32_t sizeY = i_param.getArithmetic().getSizeY();
  bool useSign = i_param.getArithmetic().getSign();

  GraphPtr graph = std::make_shared<OrientedGraph>();

  std::vector<VertexPtr> inputsForA = graph->addInputs(sizeA);

  if (useSign && sizeA > inputsForA.size()) {
    inputsForA.push_back(inputsForA.back());
  }
  graph->addOutputs(commonPrefixOperations(graph, inputsForA, sizeY, useSign,
                                           ArithemticOperations::ADD));
  return graph;
}

GraphPtr ArithmeticGenerator::generateDecrement(
    const GenerationParameters &i_param) const {
  uint32_t sizeA = i_param.getArithmetic().getSizeA();
  uint32_t sizeY = i_param.getArithmetic().getSizeY();
  bool useSign = i_param.getArithmetic().getSign();

  GraphPtr graph = std::make_shared<OrientedGraph>();

  std::vector<VertexPtr> inputsForA = graph->addInputs(sizeA);

  if (useSign && sizeA > inputsForA.size()) {
    inputsForA.push_back(inputsForA.back());
  }
  graph->addOutputs(commonPrefixOperations(graph, inputsForA, sizeY, useSign,
                                           ArithemticOperations::SUB));
  return graph;
}

} // namespace CG_Gen
