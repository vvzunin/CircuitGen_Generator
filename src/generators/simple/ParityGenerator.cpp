#include "ParityGenerator.hpp"

ParityGenerator::ParityGenerator() : SimpleGenerator() {}

ParityGenerator::ParityGenerator(uint_fast32_t i_seed) :
  SimpleGenerator(i_seed) {}

ParityGenerator::ParityGenerator(const GenerationParameters& i_param) :
  SimpleGenerator(i_param) {}

GraphPtr ParityGenerator::generatorParity(uint32_t i_bits) {
  // i_bits - количество входов
  // elem - массив для сохранения вершин
  // xors - промежуточный массив для сохранения вершин
  // F - функция на выходе

  GraphPtr graph(new OrientedGraph);
  if (i_bits <= 1) {
    std::cout << "Недостаточно входных сигналов" << std::endl;
    return graph;
  }
  VertexPtr output_f = graph->addOutput("F");
  std::vector<VertexPtr> elem(i_bits);
  std::vector<VertexPtr> xors;

  for (uint32_t i = 0; i < i_bits; i++) {
    elem[i] = graph->addInput("x" + std::to_string(i));
  }

  int32_t k = 0;
  bool shift;
  int32_t count = i_bits;
  while (count != 1) {
    count % 2 == 1 ? shift = true : shift = false;
    xors.clear();
    std::string str_k = std::to_string(k);
    int32_t n = 0;
    for (int32_t i = 1; i < count; i += 2) {
      std::string str_n = std::to_string(n);
      VertexPtr Xor =
          graph->addGate(Gates::GateXor, "xor_" + str_k + "_" + str_n);
      n++;
      graph->addEdges({elem[i - 1], elem[i]}, Xor);
      xors.push_back(Xor);
    }
    if (shift)
      xors.push_back(elem[count - 1]);
    count = xors.size();
    k++;
    elem = xors;
  }
  graph->addEdge(elem[0], output_f);
  return graph;
}

GraphPtr ParityGenerator::generatorParity(const GenerationParameters &i_param) {
  int32_t bits = i_param.getInputs();
  return generatorParity(bits);
}

GraphPtr ParityGenerator::generatorParity() {
  return generatorParity(getParameters());
}

