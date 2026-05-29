#include "ArithmeticGenerator.hpp"
#include "ArithmeticUtils.hpp"
#include "generators/simple/common/GeneratorUtils.hpp"
#include <CircuitGenGraph/GraphUtils.hpp>
#include <CircuitGenGraph/GraphVertexBase.hpp>
#include <CircuitGenGraph/OrientedGraph.hpp>
#include <cstdint>
#include <memory>

namespace CG_Gen {

struct Sd2 {
  CG_Graph::GraphVertexBase *sign = nullptr, *digit = nullptr;
};

struct HcData {
  CG_Graph::GraphVertexBase *horizontal = nullptr, *carry = nullptr;
};

struct AbscData {
  Sd2 value;
  CG_Graph::GraphVertexBase *sign = nullptr, *notNull = nullptr;

  void copySN(const AbscData &data) {
    sign = data.sign;
    notNull = data.notNull;
  }

  void clearSN(VertexPtr zero) {
    sign = zero;
    notNull = zero;
  }
};

AbscData synthAbsc(GraphPtr graph, const AbscData &data,
                   CG_Graph::GraphVertexBase *zero) {
  // input [1:0] a, input n, input s
  if (data.value.digit == zero && data.value.sign == zero) {
    return data;
  }
  AbscData resp;
  if (data.notNull == zero) {
    resp.notNull = data.value.digit;
  } else {
    // assign n_o = n | a[0];
    resp.notNull = graph->addGate(GateOr);
    graph->addEdges({data.notNull, data.value.digit}, resp.notNull);
  }

  VertexPtr foundOne;
  if (data.value.sign == zero) {
    foundOne = zero;
  } else if (data.notNull == zero) {
    foundOne = data.value.sign;
  } else {
    auto *inv = graph->addGate(GateNot);
    graph->addEdge(data.notNull, inv);
    foundOne = graph->addGate(GateAnd);
    graph->addEdges({inv, data.value.sign}, foundOne);
  }

  if (data.sign == zero) {
    resp.sign = foundOne;
  } else if (foundOne == zero) {
    // assign s_o = s | (!n & a[1]);
    resp.sign = data.sign;
  } else {
    resp.sign = graph->addGate(GateOr);
    graph->addEdges({data.sign, foundOne}, resp.sign);
  }

  // assign abss[0] = a[0];
  resp.value.digit = data.value.digit;
  // assign abss[1] = (a[1] ^ s_o) & a[0];
  auto *signPart = graph->addGate(GateXor);
  graph->addEdges({data.value.sign, resp.sign}, signPart);

  resp.value.sign = graph->addGate(GateAnd);
  graph->addEdges({signPart, data.value.digit}, resp.value.sign);

  return resp;
}

HcData synthHc(GraphPtr graph, CG_Graph::GraphVertexBase *digit,
               const Sd2 &abss, CG_Graph::GraphVertexBase *zero) {
  HcData resp;
  if (digit == zero) {
    resp.carry = abss.sign;
    resp.horizontal = abss.digit;
    return resp;
  }
  if (abss.digit == zero) {
    resp.carry = digit;
    resp.horizontal = digit;
    return resp;
  }
  // assign h = abss[0] ^ d;
  resp.horizontal = graph->addGate(GateXor);
  graph->addEdges({digit, abss.digit}, resp.horizontal);

  // assign c = abss[1] | (d & ~abss[0]);
  auto *inv = graph->addGate(GateNot);
  graph->addEdge(abss.digit, inv);

  auto *isNegative = graph->addGate(GateAnd);
  graph->addEdges({digit, inv}, isNegative);

  if (abss.sign == zero) {
    resp.carry = isNegative;
  } else {
    resp.carry = graph->addGate(GateOr);
    graph->addEdges({abss.sign, isNegative}, resp.carry);
  }
  return resp;
}

Sd2 synthSum(GraphPtr graph, CG_Graph::GraphVertexBase *horizontal,
             CG_Graph::GraphVertexBase *carry,
             CG_Graph::GraphVertexBase *zero) {
  Sd2 resp;
  if (horizontal == zero) {
    resp.digit = carry;
    resp.sign = carry;
    return resp;
  }
  if (carry == zero) {
    resp.digit = horizontal;
    resp.sign = zero;
    return resp;
  }
  resp.digit = graph->addGate(GateXor);
  graph->addEdges({carry, horizontal}, resp.digit);

  auto *inv = graph->addGate(GateNot);
  graph->addEdge(horizontal, inv);
  resp.sign = graph->addGate(GateAnd);
  graph->addEdges({carry, inv}, resp.sign);
  return resp;
}

GraphPtr ArithmeticGenerator::generateNonRestoringDiv(
    const GenerationParameters &i_param) const {
  uint32_t sizeA = i_param.getArithmetic().getSizeA();
  uint32_t sizeB = i_param.getArithmetic().getSizeB();
  uint32_t sizeY = i_param.getArithmetic().getSizeY();
  bool useSign = i_param.getArithmetic().getSign();

  GraphPtr graph = std::make_shared<OrientedGraph>();

  auto inputsForA = graph->addInputs(sizeA);
  auto inputsForB = graph->addInputs(sizeB);

  VertexPtr inverseSign;
  if (useSign) {
    inverseSign = graph->addGate(GateXor);
    graph->addEdges({inputsForA.back(), inputsForB.back()}, inverseSign);
    auto negA = twosComplement(graph, inputsForA, inputsForA.size(), true);
    inputsForA =
        MuxGenerator::addMux2(graph, inputsForA.back(), inputsForA, negA);
  }
  auto *zero = graph->addConst('0');
  if (inputsForB.size() == 1) {
    inputsForA.resize(sizeY, zero);
    graph->addOutputs(inputsForA);
    return graph;
  }

  std::vector<VertexPtr> outputs;
  outputs.reserve(sizeY);

  if (useSign) {
    std::vector<VertexPtr> negB =
        twosComplement(graph, inputsForB, inputsForB.size(), true);
    inputsForB =
        MuxGenerator::addMux2(graph, inputsForB.back(), inputsForB, negB);
  }
  if (inputsForA.size() > inputsForB.size()) {
    inputsForB.resize(inputsForA.size(), useSign ? inputsForB.back() : zero);
  } else {
    inputsForA.resize(inputsForB.size(), useSign ? inputsForA.back() : zero);
  }

  int width = static_cast<int>(inputsForA.size());
  int size = width;
  std::vector<VertexPtr> dividendTree;
  if (size > 1) {
    dividendTree =
        synthLadnerFisherPrefixDecisionTree(graph, inputsForA, size - 1);
  }

  // prepare data structures
  std::vector<AbscData> abscVec;
  abscVec.reserve((width << 1) + 1);

  CG_Graph::GraphVertexBase *signPrev = zero, *q_neg;
  Sd2 value = {zero, inputsForA.back()};
  AbscData absc = {value, zero, zero};
  abscVec.push_back(absc);

  // fill with zeros; they would be skipped,
  // but are used for correct vector indexing
  value.digit = zero;
  absc.value = value;
  abscVec.resize(width + 1, absc);
  outputs.resize(std::min<int>(width, sizeY));

  for (int i = width - 1; i >= 0; --i) {
    HcData hcData, prevHcData;
    abscVec[width].clearSN(zero);
    for (int j = width; j >= 0; --j) {
      Sd2 sumData;
      prevHcData = hcData;

      if (j > 0) {
        auto *next = j <= size ? inputsForB[j - 1] : zero;
        hcData = synthHc(graph, next, abscVec[j - 1].value, zero);
      }

      if (j == 0) {
        sumData.digit = prevHcData.horizontal;
        sumData.sign = zero;
      } else if (j == width) {
        sumData = synthSum(graph, abscVec[j].value.digit, hcData.carry, zero);
      } else {
        sumData = synthSum(graph, prevHcData.horizontal, hcData.carry, zero);
      }
      abscVec[j].value = sumData;
      abscVec[j] = synthAbsc(graph, abscVec[j], zero);

      if (j > 0) {
        abscVec[j - 1].copySN(abscVec[j]);
      }
    }

    CG_Graph::GraphVertexBase *n, *s;
    if (i > 0) {
      n = graph->addGate(GateOr);
      graph->addEdges({dividendTree[i - 1], abscVec[0].notNull}, n);
      if (i == size - 1) {
        s = abscVec[0].sign;
      } else {
        auto *inv = graph->addGate(GateNot);
        graph->addEdge(abscVec[0].notNull, inv);

        s = graph->addGate(GateAnd);
        graph->addEdges({dividendTree[i - 1], inv, signPrev}, s);

        auto *tmp = graph->addGate(GateOr);
        graph->addEdges({s, abscVec[0].sign}, tmp);
        s = tmp;
      }
      if (signPrev != zero) {
        auto *tmp = graph->addGate(GateXor);
        graph->addEdges({signPrev, s}, tmp);
        signPrev = tmp;
      } else {
        signPrev = s;
      }

      absc.clearSN(zero);
      auto *nextN = inputsForA[i - 1];

      absc.value = {graph->addGate(GateAnd), nextN};
      graph->addEdges({nextN, signPrev}, absc.value.sign);

      abscVec.insert(abscVec.begin(), absc);
    } else {
      n = abscVec[0].notNull;
      s = abscVec[0].sign;
    }

    if (i == size - 1) {
      q_neg = s;
    } else {
      auto *tmp = graph->addGate(GateXor);
      graph->addEdges({s, q_neg}, tmp);
      q_neg = tmp;
    }
    auto *tmp = graph->addGate(GateAnd);
    graph->addEdges({n, q_neg}, tmp);
    q_neg = tmp;
    if (i < sizeY) {
      outputs[i] = graph->addGate(GateNot);
      graph->addEdge(q_neg, outputs[i]);
    }

    ++width;
  }

  if (useSign) {
    std::vector<VertexPtr> negOut =
        twosComplement(graph, outputs, outputs.size(), true);
    outputs = MuxGenerator::addMux2(graph, inverseSign, outputs, negOut);
  }
  outputs.resize(sizeY, useSign ? outputs.back() : zero);

  graph->addOutputs(outputs);
  return graph;
}

} // namespace CG_Gen
