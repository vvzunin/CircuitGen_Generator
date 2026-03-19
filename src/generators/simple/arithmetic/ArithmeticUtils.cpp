#include "ArithmeticUtils.hpp"
#include "../common/GeneratorUtils.hpp"

#include <CircuitGenGraph/GraphUtils.hpp>
#include <CircuitGenGraph/GraphVertexBase.hpp>
#include <utility>

namespace CG_Gen {

std::vector<VertexPtr>
synthLadnerFisherPrefixDecisionTree(
    GraphPtr graph,
    const std::vector<VertexPtr> &inputs,
    uint16_t outSize,
    CG_Graph::Gates operation
) {
  outSize = std::min(outSize, static_cast<uint16_t>(inputs.size()));
  std::vector<VertexPtr> current = inputs;
  current.resize(outSize);

  for (uint16_t basicStep = 1u; basicStep < outSize; basicStep <<= 1) {
    const uint16_t delta = basicStep << 1;
    // here we select batch, with size delta and put index in its center
    for (uint16_t batch = basicStep - 1u; batch <= outSize; batch += delta) {
      // skip first iteration
      // we need it only if we have carry input
      if (!batch) {
        continue;
      }
      auto *first = current[batch - 1];
      // set child index to value at max possible pos (if we choose
      // outSizeA - 1, we should be sure, that will set index to correct pos,
      // when outSizeA % 2 == 0, we need to sub 1)
      uint16_t pos =
          std::min(basicStep - 1u + batch, outSize - 1u - (!(outSize & 1)));

      // we start from the end and move to middle with step 2.
      // we are sure, that the "child" value would be smaller than 2 ^ 15 - 1,
      // as such a bits' number is not correct in fact. But if something will
      // change, it would be better to be prepared
      for (int32_t child = pos; child >= batch; child -= 2) {
        auto *tmp = graph->addGate(operation);
        graph->addEdges({current[child], first}, tmp);
        current[child] = tmp;
      }
    }
  }
  for (uint16_t pos = 1; pos < outSize; pos += 2) {
    auto *tmp = graph->addGate(operation);
    graph->addEdges({current[pos], current[pos - 1]}, tmp);
    current[pos] = tmp;
  }
  return current;
}

std::vector<VertexPtr>
commonPrefixOperations(GraphPtr graph,
                       const std::vector<VertexPtr> &word,
                       const uint32_t width,
                       const bool signExtend,
                       ArithemticOperations::Types oper) {
  const auto size = std::min(word.size(), static_cast<size_t>(width));
  assert(size != 0);

  const auto logicOper = oper == ArithemticOperations::ADD
      ? CG_Graph::GateAnd
      : CG_Graph::GateOr;

  const auto decisionTree = synthLadnerFisherPrefixDecisionTree(
      graph, word, size, logicOper
  );

  std::vector<VertexPtr> result(size);
  if (oper == ArithemticOperations::NEG) {
    result[0] = word[0];
  } else {
    auto *inv = graph->addGate(CG_Graph::GateNot);
    graph->addEdge(word[0], inv);
    result[0] = inv;
  }
  for (size_t i = 1; i < size; ++i) {
    CG_Graph::GraphVertexBase *whenFalse, *inv;
    inv = graph->addGate(CG_Graph::GateNot);
    graph->addEdge(word[i], inv);
    whenFalse = word[i];
    if (oper == ArithemticOperations::SUB) {
      std::swap(inv, whenFalse);
    }
    result[i] = MuxGenerator::addMux2(
        graph, decisionTree[i - 1], whenFalse, inv
    );
  }
  auto *sign = decisionTree.back();
  if (signExtend) {
    sign = result.back();
  } else if (oper == ArithemticOperations::SUB) {
    auto *inv = graph->addGate(CG_Graph::GateNot);
    graph->addEdge(sign, inv);
    sign = inv;
  } else if (oper == ArithemticOperations::ADD && size < width) {
    result.push_back(sign);
    sign = graph->addConst('0');
  }
  result.resize(width, sign);

  return result;
}

std::vector<VertexPtr>
twosComplement(
    GraphPtr graph,
    const std::vector<VertexPtr> &word,
    const uint32_t width,
    const bool signExtend
) {
  return commonPrefixOperations(
      graph, word, width, signExtend, ArithemticOperations::NEG
  );
}

} // namespace CG_Gen
