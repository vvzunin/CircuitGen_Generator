#include "FromTruthTableGenerator.hpp"
#include <baseStructures/Parser.hpp>

FromTruthTableGenerator::FromTruthTableGenerator() : SimpleGenerator() {
}

FromTruthTableGenerator::FromTruthTableGenerator(uint_fast32_t i_seed) :
    SimpleGenerator(i_seed) {
}

FromTruthTableGenerator::FromTruthTableGenerator(
    const GenerationParameters &i_param) :
    SimpleGenerator(i_param) {
}

GraphPtr FromTruthTableGenerator::cnfFromTruthTable(const TruthTable &i_table,
                                                    bool i_tp) {
  std::vector<std::string> fun;
  fun.reserve(i_table.getOutput());
  std::vector<std::vector<bool>> bin = i_table.convToBinary();

  GraphPtr graph = std::make_shared<OrientedGraph>(
      "", (2 + (i_table.getInput() + 1) * ((i_table.getInput() - 1)) *
                   (i_table.getOutput() + 1)) *
              sizeof(GraphVertexBase));
  std::vector<VertexPtr> inputs;
  inputs.reserve(i_table.getInput());
  for (size_t k = 0; k < i_table.getInput(); ++k) {
    inputs.push_back(graph->addInput("x" + std::to_string(k)));
  }

  // TODO make nand-or generation etc
  if (!d_gatesInputsInfo.count(Gates::GateAnd)) {
    d_gatesInputsInfo[Gates::GateAnd] = {(int32_t)inputs.size()};
  }
  if (!d_gatesInputsInfo.count(Gates::GateOr)) {
    d_gatesInputsInfo[Gates::GateOr] = {(int32_t)inputs.size()};
  }

  std::map<VertexPtr, VertexPtr> inputs_not;
  GraphVertexBase *constGate_0 = nullptr, *constGate_1 = nullptr;

  Parser parserMany;
  parserMany.setGatesInputsInfo(d_gatesInputsInfo);

  for (size_t j = 0; j < i_table.getOutput(); ++j) {
    VertexPtr out = graph->addOutput("f" + std::to_string(j));
    int32_t mem = 0;
    int32_t tmp = 0;

    for (int32_t i = 0; i < i_table.size(); ++i) {
      if (!(i_table.getOutTable(i, j) ^ i_tp))
        mem++;
    }

    if (mem == 0 || mem == i_table.size()) {
      if (i_tp && mem == 0 || !i_tp && mem == i_table.size()) {
        if (constGate_0 == nullptr) {
          constGate_0 = graph->addConst('0');
        }
        graph->addEdge(constGate_0, out);
      } else {
        if (constGate_1 == nullptr) {
          constGate_1 = graph->addConst('1');
        }
        graph->addEdge(constGate_1, out);
      }
      continue;
    }

    Gates exter = i_tp ? Gates::GateOr : Gates::GateAnd;
    Gates inter = i_tp ? Gates::GateAnd : Gates::GateOr;
    int32_t curSize = 0;

    std::vector<VertexPtr> nextLayoutExt;
    std::vector<VertexPtr> nextLayout;

    nextLayout.reserve(inputs.size());

    // Here we create operations in brackets
    for (int32_t i = 0; i < mem; ++i) {
      while ((i_table.getOutTable(tmp, j) ^ i_tp) && tmp < i_table.size())
        ++tmp;

      // create layout of "input"
      for (size_t k = 0; k < inputs.size(); ++k) {
        VertexPtr x_input = inputs[k];

        // add NOT
        if (bin[tmp][k] ^ i_tp) {
          if (!inputs_not.count(x_input)) {
            inputs_not[x_input] =
                graph->addGate(Gates::GateNot, x_input->getName("not_"));
          }

          // Get NOT operation
          x_input = inputs_not[x_input];
          graph->addEdge(inputs[k], x_input);
        }

        nextLayout.push_back(x_input);
      }

      nextLayoutExt.push_back(
          parserMany.multipleVerteciesToOne(nextLayout, inter, graph));

      nextLayout.clear();
      ++tmp;
    }

    // and here operations with brackets
    graph->addEdge(
        parserMany.multipleVerteciesToOne(nextLayoutExt, exter, graph), out);
  }

  return graph;
}
GraphPtr
FromTruthTableGenerator::zhegalkinFromTruthTable(const TruthTable &i_table) {
  int32_t num_inputs = i_table.getInput();
  int32_t num_outputs = i_table.getOutput();

  GraphPtr graph(new OrientedGraph());
  std::vector<VertexPtr> inputs;
  inputs.reserve(num_inputs);

  for (int32_t k = 0; k < num_inputs; ++k) {
    inputs.push_back(graph->addInput("x" + std::to_string(k)));
  }

  for (int32_t j = 0; j < num_outputs; ++j) {
    VertexPtr out = graph->addOutput("f" + std::to_string(j));

    int32_t mem = 0;
    for (int32_t i = 0; i < i_table.size(); ++i) {
      mem += i_table.getOutTable(i, j);
    }

    if (mem == 0) {
      VertexPtr constGate = graph->addConst('0');
      graph->addEdge(constGate, out);
    } else if (mem == i_table.size()) {
      VertexPtr constGate = graph->addConst('1');
      graph->addEdge(constGate, out);
    } else {
      bool first_term = true;

      for (int32_t term = 0; term < (1 << num_inputs); ++term) {
        if (i_table.getOutTable(term, j)) {
          if (!first_term) {
            VertexPtr xorOper = graph->addGate(Gates::GateXor);
            graph->addEdge(xorOper, out);
            out = xorOper;
          }

          if (term == 0) {
            VertexPtr constGate = graph->addConst('0');
            graph->addEdge(constGate, out);
          } else {
            VertexPtr andOper = graph->addGate(Gates::GateAnd);

            for (int32_t i = 0; i < num_inputs; ++i) {
              VertexPtr x_input = inputs[i];
              bool negated = ((term >> (num_inputs - i - 1)) & 1) == 0;

              if (negated) {
                VertexPtr notGate = graph->addGate(Gates::GateNot);
                graph->addEdge(inputs[i], notGate);
                x_input = notGate;
              }

              graph->addEdge(x_input, andOper);
            }

            graph->addEdge(andOper, out);
          }
          first_term = false;
        }
      }
    }
  }
  return graph;
}
