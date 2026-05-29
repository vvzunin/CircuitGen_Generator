#include "ArithmeticGenerator.hpp"

#include <CircuitGenGraph/GraphUtils.hpp>
#include <CircuitGenGraph/GraphVertexBase.hpp>

#include <cstddef>
#include <string>

namespace CG_Gen {

GraphPtr ArithmeticGenerator::generatorBusSummator(uint32_t i_bits,
                                                bool i_overflowIn,
                                                bool i_overflowOut,
                                                bool i_minus,
                                                std::string_view i_name) const {
  std::vector<VertexPtr> inputs;
  VertexPtr overflowOut = nullptr;
  std::string busX = "busX_";
  std::string busY = "busY_";
  GraphPtr busConnectGraph = std::make_shared<OrientedGraph>();
  busConnectGraph->setName(busConnectGraph->getName() + "_CRA");
  VertexPtr x = busConnectGraph->addInputBus("busX", i_bits);
  VertexPtr y = busConnectGraph->addInputBus("busY", i_bits);
  VertexPtr s = busConnectGraph->addOutputBus("sum", i_bits);
  inputs.push_back(busConnectGraph->addSliceBus(x, 0, 1, busX+'0'));
  inputs.push_back(busConnectGraph->addSliceBus(y, 0, 1, busY+'0'));
    if (i_overflowIn) {
  inputs.push_back(busConnectGraph->addInput("overflowIn"));
  }
  for(size_t i = 1; i < i_bits; ++i) {
    inputs.push_back(busConnectGraph->addSliceBus(x, i, 1, busX + std::to_string(i)));
    inputs.push_back(busConnectGraph->addSliceBus(y, i, 1, busY + std::to_string(i)));
  }

  GraphPtr summatorGraph = generatorSummator(i_bits, i_overflowIn, i_overflowOut, i_minus);
  std::vector<VertexPtr> outputs = busConnectGraph->addSubGraph(summatorGraph, inputs);
  auto lastSumBit = outputs.end();
  VertexPtr concatenationSum = busConnectGraph->addGateBus(GateConcatenation);
  if (i_overflowOut) {
         busConnectGraph->addEdge(outputs.back(), busConnectGraph->addOutput("overflowOut"));
         --lastSumBit;
  }
  busConnectGraph->addEdges({outputs.begin(),lastSumBit}, concatenationSum);
  busConnectGraph->addEdge(concatenationSum, s);
  return busConnectGraph;
}

GraphPtr ArithmeticGenerator::generatorSummator(uint32_t i_bits,
                                                bool i_overflowIn,
                                                bool i_overflowOut,
                                                bool i_minus) const{
  GraphPtr graph(new OrientedGraph);
  std::string str_x;
  std::string str_y;

  VertexPtr const_1;

  std::string cond = std::string(i_overflowIn ? "t" : "f") +
                     (i_overflowOut ? "t" : "f") + (i_minus ? "t" : "f");
  std::string z = std::string(i_minus ? "n" : "") + "s" +
                  (!i_overflowIn && !i_overflowOut
                       ? "0"
                       : (!i_overflowIn && i_overflowOut
                              ? "1"
                              : (i_overflowIn && !i_overflowOut ? "2" : "3"))) +
                  "_";
  VertexPtr curr_p;
  VertexPtr next_p;

  for (int32_t i = 0; i < i_bits; i++) {
    std::string S = std::to_string(i);
    std::string NextS = std::to_string(i + 1);

    str_x = "sum_a" + cond + S;
    str_y = "sum_b" + cond + S;

    VertexPtr input_x = graph->addInput(str_x);
    VertexPtr input_y = graph->addInput(str_y);
    VertexPtr nx;
    VertexPtr ny;

    if (i_minus) {
      nx = graph->addGate(Gates::GateNot, "na" + S);
      ny = graph->addGate(Gates::GateNot, "nb" + S);
      graph->addEdge(input_x, nx);
      graph->addEdge(input_y, ny);
    }
    VertexPtr output_sum;

    output_sum = graph->addOutput(z + S);

    VertexPtr xorab = graph->addGate(Gates::GateXor, "xorab" + S);
    graph->addEdges({i_minus ? nx : input_x, i_minus ? ny : input_y}, xorab);
    VertexPtr andab = graph->addGate(Gates::GateAnd, "andab" + S);
    graph->addEdges({i_minus ? nx : input_x, i_minus ? ny : input_y}, andab);

    if (i == 0) {
      if (i_overflowIn) {
        curr_p = graph->addInput("p" + S);
        VertexPtr xorabp = graph->addGate(Gates::GateXor, "xorabp" + S);
        graph->addEdges({xorab, curr_p}, xorabp);

        graph->addEdge(xorabp, output_sum);

        VertexPtr andpxor = graph->addGate(Gates::GateAnd, "andpxor" + S);
        graph->addEdges({xorab, curr_p}, andpxor);

        next_p = graph->addGate(Gates::GateOr, "p" + NextS);
        graph->addEdges({andab, andpxor}, next_p);
      } else {
        next_p = graph->addGate(Gates::GateBuf, "p" + NextS);
        graph->addEdge(andab, next_p);

        graph->addEdge(xorab, output_sum);
      }
    }
    if (i > 0) {
      VertexPtr xorabp = graph->addGate(Gates::GateXor, "xorabp" + S);
      graph->addEdges({xorab, curr_p}, xorabp);
      graph->addEdge(xorabp, output_sum);

      VertexPtr andpxor = graph->addGate(Gates::GateAnd, "andpxor" + S);
      graph->addEdges({xorab, curr_p}, andpxor);

      next_p = graph->addGate(Gates::GateOr, "p" + NextS);
      graph->addEdges({andab, andpxor}, next_p);
    }
    if (i_overflowOut && i + 1 == i_bits) {
      output_sum = graph->addOutput(z + NextS);
      graph->addEdge(next_p, output_sum);
    }
    curr_p = next_p;
  }
  return graph;
}

GraphPtr
ArithmeticGenerator::generatorSummator(const GenerationParameters &i_param) const{
  int32_t bits = i_param.getInputs();
  bool overflowIn = i_param.getSummator().getOverFlowIn();
  bool overflowOut = i_param.getSummator().getOverFlowOut();
  bool minus = i_param.getSummator().getMinus();
  return generatorSummator(bits, overflowIn, overflowOut, minus);
}

GraphPtr ArithmeticGenerator::generatorSummator() {
  return generatorSummator(getParameters());
}

} // namespace CG_Gen
