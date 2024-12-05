#include <bitset>

#include "CoderGenerator.hpp"

CoderGenerator::CoderGenerator() : SimpleGenerator() {}

CoderGenerator::CoderGenerator(uint_fast32_t i_seed) :
  SimpleGenerator(i_seed) {}

CoderGenerator::CoderGenerator(
    const GenerationParameters& i_param
) :
  SimpleGenerator(i_param) {}

GraphPtr CoderGenerator::generatorEncoder(uint32_t i_bits) {
  GraphPtr graph(new OrientedGraph);
  if (i_bits < 2) {
    std::cout << "Недостаточно входных сигналов" << std::endl;
  } else {
    int32_t i_outbits = 0;
    while (i_bits > pow(2, i_outbits))
      i_outbits++;

    std::vector<VertexPtr> inputs_x(i_bits);
    std::vector<VertexPtr> not_x(i_bits);
    std::vector<VertexPtr> ands(pow(2, i_outbits));

    // создание инверсий входов
    for (uint32_t i = 0; i < i_bits; i++) {
      VertexPtr x = graph->addInput("x" + std::to_string(i + 1));
      inputs_x[i] = x;
      VertexPtr nx =
          graph->addGate(Gates::GateNot, "nx" + std::to_string(i + 1));
      graph->addEdge(x, nx);
      not_x[i] = nx;
    }

    int32_t shift = 1;
    int32_t count = 0;
    bool check = false;
    for (int32_t i = 0; i < pow(2, i_outbits); i++) {
      VertexPtr and_xs =
          graph->addGate(Gates::GateAnd, "and_for_or" + std::to_string(i + 1));
      // создание массива значений для операций and
      std::vector<VertexPtr> Xs(i_bits);
      for (int32_t j = 0; j < i_bits; j++) {
        if (i < i_bits)
          Xs[j] = (j == i) ? inputs_x[j] : not_x[j];
        else {
          check = true;
          break;
        }
      }
      if (check) {
        // если количество входных значений не было значением степени двойки, то
        // подключается доп. функция, которая создает дополнительные варианты
        // операции and для заполнения недостающих результатов для выходов
        Xs[0] = inputs_x[0];
        Xs[shift] = inputs_x[shift];
        for (int32_t j = shift + 1; j < i_bits; j++)
          Xs[j] = not_x[j];
        for (int32_t j = 1; j < shift; j++)
          Xs[j] = (j <= count) ? inputs_x[j] : Xs[j] = not_x[j];
        count++;
        if (shift == count) {
          count = 0;
          shift++;
        }
      }
      graph->addEdges(Xs, and_xs);
      ands[i] = and_xs;
    }

    int32_t n = 1;
    for (int32_t i = 0; i < i_outbits; i++) {
      VertexPtr or_xs = graph->addGate(Gates::GateOr,
                                       "or_for_output" + std::to_string(i + 1));
      std::vector<VertexPtr> ors;
      for (int32_t j = n; j < pow(2, i_outbits); j += n * 2) {
        ors.insert(ors.end(), ands.begin() + j, ands.begin() + j + n);
      }
      graph->addEdges(ors, or_xs);
      n *= 2;

      VertexPtr y = graph->addOutput("y" + std::to_string(i));
      graph->addEdge(or_xs, y);
    }
  }
  return graph;
}

GraphPtr CoderGenerator::generatorDecoder(uint32_t i_bits) {
  // bits - количество входов
  // T[]- массив для текущего ряда узлов
  // X[]- массив для предыдущего ряда узлов
  //"хi" - входной бит
  // F - функция на выходе
  GraphPtr graph(new OrientedGraph);
  if (i_bits > 1) {
    std::vector<VertexPtr> T(pow(2, i_bits));
    std::vector<VertexPtr> X(pow(2, i_bits));
    std::vector<VertexPtr> Out(pow(2, i_bits));
    for (int32_t i = 0; i < i_bits; i++) {
      std::string Z = std::to_string(i);
      X[i] = graph->addInput("x" + Z);
      X[i + i_bits] = graph->addGate(GateNot, "not_x" + Z + "");
      graph->addEdge(X[i], X[i + i_bits]);
    }
    for (int32_t i = 0; i < pow(2, i_bits); i++) {
      std::string Z = std::to_string(i);
      Out[i] = graph->addOutput("f" + Z);
    }
    int32_t p = i_bits;
    for (int32_t i = 0; i < pow(2, i_bits); i++) {
      T[i] = graph->addGate(GateAnd, "and" + std::to_string(i));
      std::bitset<sizeof(int32_t) * 8> bs(i);
      std::string bit_string = bs.to_string();
      std::string res = bit_string.substr(bit_string.length() - i_bits);
      for (int32_t j = 0; j < res.length(); j++) {
        if (res[j] == '1') {
          graph->addEdge(X[j], T[i]);
        } else {
          graph->addEdge(X[j + i_bits], T[i]);
        }
      }
    }
    for (int32_t i = 0; i < pow(2, i_bits); i++) {
      graph->addEdge(T[i], Out[i]);
    }
  } else {
    VertexPtr x = graph->addInput("x");
    VertexPtr not_x = graph->addGate(GateNot, "not_x_");
    for (int32_t i = 0; i < 2; i++) {
      VertexPtr out = graph->addOutput("f" + std::to_string(i));
      if (i == 0) {
        graph->addEdge(not_x, out);
      } else {
        graph->addEdge(x, out);
      }
    }
  }
  return graph;
}

GraphPtr CoderGenerator::generatorEncoder(const GenerationParameters &i_param) {
  int32_t i_bits = i_param.getInputs();
  return generatorEncoder(i_bits);
}

GraphPtr CoderGenerator::generatorDecoder(const GenerationParameters &i_param) {
  return generatorDecoder(i_param.getInputs());
}

GraphPtr CoderGenerator::generatorEncoder() {
  return generatorEncoder(getParameters());
}

GraphPtr CoderGenerator::generatorDecoder() {
  return generatorDecoder(getParameters());
}