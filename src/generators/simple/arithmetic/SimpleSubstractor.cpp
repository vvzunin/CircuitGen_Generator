#include "../ArithmeticGenerator.hpp"

namespace CG_Gen {

GraphPtr ArithmeticGenerator::generatorSubtractor(uint32_t i_bits,
                                                  bool i_overflowIn,
                                                  bool i_overflowOut,
                                                  bool i_sub) {
  GraphPtr graph(new OrientedGraph);
  VertexPtr const_1;

  std::string cond = std::string(i_overflowIn ? "t" : "f") +
                     (i_overflowOut ? "t" : "f") + (i_sub ? "t" : "f");
  std::string s = std::string(i_sub ? "n" : "") + "d" +
                  (!i_overflowIn && !i_overflowOut
                       ? "0"
                       : (!i_overflowIn && i_overflowOut
                              ? "1"
                              : (i_overflowIn && !i_overflowOut ? "2" : "3"))) +
                  "_";

  VertexPtr next_z; // следующий заем
  VertexPtr curr_z; // нынешний заём

  for (uint32_t i = 0; i < i_bits; i++) {
    std::string Z = std::to_string(i);         // нынешний индекс
    std::string NextZ = std::to_string(i + 1); // следующий индекс
    std::string x = "suba" + cond + Z;
    std::string y = "subb" + cond + Z;
    VertexPtr input_x = graph->addInput(x);
    VertexPtr input_y = graph->addInput(y);
    VertexPtr output_sub;

    output_sub = graph->addOutput(s + Z);

    VertexPtr abxor = graph->addGate(Gates::GateXor, "abxor" + Z);
    graph->addEdges({input_x, input_y}, abxor);

    VertexPtr abandn;
    // i_sub отвечает за определение уменьшаемого и вычитываемого: B-A или A-B
    if (!i_sub) {
      VertexPtr nx = graph->addGate(Gates::GateNot, "na" + Z);
      graph->addEdge(input_x, nx);

      abandn = graph->addGate(Gates::GateAnd, "bna" + Z);
      graph->addEdges({input_y, nx}, abandn);
    }
    if (i_sub) {
      VertexPtr ny = graph->addGate(Gates::GateNot, "nb" + Z);
      graph->addEdge(input_y, ny);

      abandn = graph->addGate(Gates::GateAnd, "anb" + Z);
      graph->addEdges({input_x, ny}, abandn);
    }

    VertexPtr d; // результат

    if (i_overflowIn) {
      d = graph->addGate(Gates::GateXor, "d" + Z);
      next_z = graph->addGate(Gates::GateOr, "z" + NextZ);
      if (i == 0)
        curr_z = graph->addInput("z" + Z);

      VertexPtr nabxor = graph->addGate(Gates::GateNot, "nabxor" + Z);
      graph->addEdge(abxor, nabxor);

      VertexPtr nabxorz = graph->addGate(Gates::GateAnd, "abxornz" + Z);
      graph->addEdges({curr_z, nabxor}, nabxorz);

      graph->addEdges({nabxorz, abandn}, next_z); // перенос заема
      graph->addEdges({abxor, curr_z}, d);

      graph->addEdge(d, output_sub);
    }
    if (!i_overflowIn) {
      if (i == 0) {
        graph->addEdge(abxor, output_sub);
        next_z = graph->addGate(Gates::GateBuf, "z" + NextZ);
        graph->addEdge(abandn, next_z);
      }
      if (i > 0) {
        d = graph->addGate(Gates::GateXor, "d" + Z);
        next_z = graph->addGate(Gates::GateOr, "z" + NextZ);

        VertexPtr nabxor = graph->addGate(Gates::GateNot, "nabxor" + Z);
        graph->addEdge(abxor, nabxor);

        VertexPtr nabxorz = graph->addGate(Gates::GateAnd, "abxornz" + Z);
        graph->addEdges({curr_z, nabxor}, nabxorz);

        graph->addEdges({nabxorz, abandn}, next_z); // перенос заема
        graph->addEdges({abxor, curr_z}, d);
        graph->addEdge(d, output_sub);
      }
    }
    if (i_overflowOut && i + 1 == i_bits) {
      output_sub = graph->addOutput(s + NextZ);
      graph->addEdge(next_z, output_sub);
    }
    curr_z = next_z;
  }
  return graph;
}

GraphPtr
ArithmeticGenerator::generatorSubtractor(const GenerationParameters &i_param) {
  return generatorSubtractor(i_param.getInputs(),
                             i_param.getSubtractor().getOverFlowIn(),
                             i_param.getSubtractor().getOverFlowOut(),
                             i_param.getSubtractor().getSub());
}

GraphPtr ArithmeticGenerator::generatorSubtractor() {
  return generatorSubtractor(getParameters());
}

} // namespace CG_Gen
