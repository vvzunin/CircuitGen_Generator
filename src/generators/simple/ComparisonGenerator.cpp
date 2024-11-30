#include "ComparisonGenerator.hpp"

ComparisonGenerator::ComparisonGenerator() : SimpleGenerator() {}

ComparisonGenerator::ComparisonGenerator(uint_fast32_t i_seed) :
  SimpleGenerator(i_seed) {}

ComparisonGenerator::ComparisonGenerator(const GenerationParameters& i_param) :
  SimpleGenerator(i_param) {}

GraphPtr ComparisonGenerator::generatorComparison(
    uint32_t i_bits,
    bool     compare0,
    bool     compare1,
    bool     compare2
) {
  GraphPtr    graph(new OrientedGraph);
  VertexPtr   prev_p0_;
  VertexPtr   prev_p1_;
  VertexPtr   prev_p2_;

  VertexPtr   prev_np1_;
  VertexPtr   prev_np2_;
  std::string cond = std::string(compare0 ? "t" : "f") + (compare1 ? "t" : "f")
                   + (compare2 ? "t" : "f");
  for (int32_t i = i_bits - 1; i >= 0; i--) {
    std::string C     = std::to_string(i);
    std::string NextC = std::to_string(i - 1);
    std::string x     = "coma" + cond + C;
    std::string y     = "comb" + cond + C;
    if (i == 0) {
      NextC = "X";
    }
    VertexPtr input_x = graph->addInput(x);
    VertexPtr input_y = graph->addInput(y);
    VertexPtr nb      = graph->addGate(Gates::GateNot, "nb" + C);
    graph->addEdge(input_y, nb);
    VertexPtr na = graph->addGate(Gates::GateNot, "na" + C);
    graph->addEdge(input_x, na);

    VertexPtr const_1;
    VertexPtr En_;
    VertexPtr pn_;
    VertexPtr Enand1_;
    VertexPtr pEn_;
    if (compare0) {
      En_           = graph->addOutput("E0_" + C);
      VertexPtr nab = graph->addGate(Gates::GateAnd, "nab" + C);
      graph->addEdges({na, nb}, nab);
      VertexPtr ab = graph->addGate(Gates::GateAnd, "ab" + C);
      graph->addEdges({input_x, input_y}, ab);
      pn_ = graph->addGate(Gates::GateOr, "p0_" + NextC);
      graph->addEdges({nab, ab}, pn_);

      // in case of first iteration
      if (i == i_bits - 1) {
        graph->addEdge(pn_, En_);
      } else {
        pEn_ = graph->addGate(Gates::GateAnd, "pE0_" + C);
        graph->addEdges({prev_p0_, pn_}, pEn_);
        graph->addEdge(pEn_, En_);
      }
      prev_p0_ = pn_;
    }
    if (compare1) {
      En_ = graph->addOutput("E1_" + C);
      pn_ = graph->addGate(Gates::GateAnd, "p1_" + NextC);
      graph->addEdges({input_x, nb}, pn_);
      VertexPtr np1_;

      // in case of first iteration
      if (i == i_bits - 1) {
        graph->addEdge(pn_, En_);
        np1_ = graph->addGate(Gates::GateNot, "np1_" + NextC);
        graph->addEdge(pn_, np1_);
      } else {
        np1_ = graph->addGate(Gates::GateNot, "np1_" + NextC);
        // graph->addEdge(prev_p1_, prev_np1_);
        graph->addEdge(pn_, np1_);
        VertexPtr P11_ = graph->addGate(Gates::GateAnd, "P11_" + C);
        graph->addEdges({prev_np1_, pn_}, P11_);
        VertexPtr P12_ = graph->addGate(Gates::GateAnd, "P12_" + C);
        graph->addEdges({prev_p1_, np1_}, P12_);
        pEn_ = graph->addGate(Gates::GateOr, "pE1_" + C);
        graph->addEdges({P11_, P12_}, pEn_);
        graph->addEdge(pEn_, En_);
      }
      prev_p1_  = pn_;
      prev_np1_ = np1_;
    }
    if (compare2) {
      En_ = graph->addOutput("E2_" + C);
      pn_ = graph->addGate(Gates::GateAnd, "p2_" + NextC);
      graph->addEdges({input_y, na}, pn_);
      VertexPtr np2_;

      // first iteration
      if (i == i_bits - 1) {
        graph->addEdge(pn_, En_);
        np2_ = graph->addGate(Gates::GateNot, "np2_" + NextC);
        graph->addEdge(pn_, np2_);
      } else {
        np2_ = graph->addGate(Gates::GateNot, "np2_" + NextC);
        // graph->addEdge(prev_p2_, prev_np2_);
        graph->addEdge(pn_, np2_);
        VertexPtr P21_ = graph->addGate(Gates::GateAnd, "P21_" + C);
        graph->addEdges({prev_np2_, np2_}, P21_);
        VertexPtr P22_ = graph->addGate(Gates::GateAnd, "P22_" + C);
        graph->addEdges({prev_p2_, np2_}, P22_);
        pEn_ = graph->addGate(Gates::GateOr, "pE2_" + C);
        graph->addEdges({P21_, P22_}, pEn_);
        graph->addEdge(pEn_, En_);
      }
      prev_p2_  = pn_;
      prev_np2_ = np2_;
    }
  }
  return graph;
}

