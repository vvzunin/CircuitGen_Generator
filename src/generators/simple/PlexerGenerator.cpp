#include <bitset>
#include "PlexerGenerator.hpp"

PlexerGenerator::PlexerGenerator() : SimpleGenerator() {}

PlexerGenerator::PlexerGenerator(uint_fast32_t i_seed) :
  SimpleGenerator(i_seed) {}

PlexerGenerator::PlexerGenerator(
    const GenerationParameters& i_param
) :
  SimpleGenerator(i_param) {}

GraphPtr PlexerGenerator::generatorMultiplexer(uint32_t i_bits) {
  GraphPtr graph(new OrientedGraph);
  VertexPtr output_f = graph->addOutput("f");
  std::vector<VertexPtr> inputs_x;
  int32_t k = 0;
  for (uint32_t t = 0; t <= i_bits; t++) {
    if (i_bits - 1 >= std::pow(2, t))
      k++;
  }

  std::vector<std::string> F(i_bits);
  std::vector<VertexPtr> ands(i_bits);
  std::vector<std::string> S(k);
  std::vector<VertexPtr> Sp(k);
  std::vector<VertexPtr> NSp(k);
  std::vector<std::string> Z(i_bits);
  std::vector<VertexPtr> Zp(i_bits);

  if (i_bits > 1) {
    // механизм создания управляющих входов и их инверсий
    for (int32_t p = 0; p < k; p++) {
      S[p] = std::to_string(p);
      Sp[p] = graph->addInput("a" + S[p]);
      // graph->addVertex("not a" + S[p], "not", "not a" + S[p]);
      NSp[p] = graph->addGate(Gates::GateNot, "not_a" + S[p]);
      graph->addEdge(Sp[p], NSp[p]);
    }
    // механизм создания входов
    for (int32_t i = 0; i < i_bits; i++) {
      Z[i] = std::to_string(i);
      Zp[i] = graph->addInput("x" + Z[i]);
      F[i] = std::bitset<8>(i).to_string();
    }
    // механизм создания связей между входами и and
    for (int32_t i = 0; i < i_bits; i++) {
      ands[i] = graph->addGate(Gates::GateAnd, "and_for_or_" + Z[i]);
      graph->addEdge(Zp[i], ands[i]);
    }

    for (int32_t i = 0; i < i_bits; i++) {
      int32_t len = F[i].size();
      for (int32_t w = 0; w < k; w++) {
        if (len < w + 1) {
          graph->addEdge(NSp[w], ands[i]);
        } else {
          char u = F[i][len - w - 1];
          if (u == '1') {
            graph->addEdge(Sp[w], ands[i]);
          } else {
            graph->addEdge(NSp[w], ands[i]);
          }
        }
      }
    }
    VertexPtr common_or = graph->addGate(Gates::GateOr, "or_for_output");
    graph->addEdges(ands, common_or);
    graph->addEdge(common_or, output_f);
  } else if (i_bits == 1) {
    Zp[0] = graph->addInput("x" + Z[0]);
    VertexPtr inBuf = graph->addGate(Gates::GateBuf, "buf");
    graph->addEdge(Zp[0], inBuf);
    graph->addEdge(inBuf, output_f);
  } else
    std::cout << "Недостаточно входных сигналов" << std::endl;
  return graph;
}

GraphPtr PlexerGenerator::generatorDemultiplexer(uint32_t i_bits) {
  // i_bits - количество выходных сигналов, то есть количество х
  // f - значение функции на входе
  // i_outbits - количество адресных входов, то есть количество а
  // F[] - массив для хранения индексов х в двоичном формате в строковом виде
  // S[] - массив для стринговых индексов а
  // Sp - вектор для указателей на входные сигналы
  // NSp - вектор для указателей на инвертированные входные сигналы
  // Z[] - массив для стринговых индексов х
  // Zp - вектор для указателей на выходные сигналы
  // len - количество символов в конкретной строке F[i], то есть двоичая
  // разрядность числа хi u - переменная для чтения одного символа из строки
  // F[i]

  GraphPtr graph(new OrientedGraph);
  VertexPtr input_f = graph->addInput("f");

  int32_t k = 0;
  for (uint32_t t = 0; t <= i_bits; t++) {
    if (i_bits - 1 >= std::pow(2, t))
      k++;
  }

  std::vector<std::string> F(i_bits);
  std::vector<VertexPtr> ands(i_bits);
  std::vector<std::string> S(k);
  std::vector<VertexPtr> Sp(k);
  std::vector<VertexPtr> NSp(k);
  std::vector<std::string> Z(i_bits);
  std::vector<VertexPtr> Zp(i_bits);

  if (i_bits > 1) {
    for (int32_t p = 0; p <= k - 1; p++) {
      S[p] = std::to_string(p);
      Sp[p] = graph->addInput("a" + S[p]);
      // graph->addVertex("not a" + S[p], "not", "not a" + S[p]);
      NSp[p] = graph->addGate(Gates::GateNot, "not_a" + S[p]);
      graph->addEdge(Sp[p], NSp[p]);
    }

    for (int32_t i = 0; i <= i_bits - 1; i++) {
      Z[i] = std::to_string(i);
      Zp[i] = graph->addOutput("x" + Z[i]);
      F[i] = std::bitset<8>(i).to_string();
    }

    for (int32_t i = 0; i <= i_bits - 1; i++) {
      ands[i] = graph->addGate(Gates::GateAnd, "and_for_output_" + Z[i]);
      graph->addEdge(input_f, ands[i]);
      graph->addEdge(ands[i], Zp[i]);
    }

    for (int32_t i = 0; i <= i_bits - 1; i++) {
      int32_t len = F[i].size();
      for (int32_t w = 0; w <= k - 1; w++) {
        if (len < w + 1) {
          graph->addEdge(NSp[w], ands[i]);
        } else {
          char u = F[i][len - w - 1];
          if (u == '1') {
            graph->addEdge(Sp[w], ands[i]);
          } else {
            graph->addEdge(NSp[w], ands[i]);
          }
        }
      }
    }
  } else
    std::cout << "Недостаточно выходных сигналов" << std::endl;
  return graph;
}

GraphPtr PlexerGenerator::generatorMultiplexer(const GenerationParameters &i_param) {
  int32_t i_bits = i_param.getInputs();
  return generatorMultiplexer(i_bits);
}

GraphPtr PlexerGenerator::generatorDemultiplexer(const GenerationParameters &i_param) {
  int32_t i_bits = i_param.getOutputs();
  return generatorDemultiplexer(i_bits);
}

GraphPtr PlexerGenerator::generatorMultiplexer() {
  return generatorMultiplexer(getParameters());
}

GraphPtr PlexerGenerator::generatorDemultiplexer() {
  return generatorDemultiplexer(getParameters());
}


