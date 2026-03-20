#include "../ArithmeticGenerator.hpp"

namespace CG_Gen {

GraphPtr ArithmeticGenerator::generatorMultiplier(uint32_t i_bits) {
  GraphPtr graph(new OrientedGraph);
  VertexPtr const_1;

  VertexPtr input_xa;
  // a - бит первого множителя
  VertexPtr input_xb;
  // b - бит второго множителя
  VertexPtr c;
  // с - результат логического и
  std::vector<VertexPtr> C_sum(i_bits);
  // C_sum - хранит результаты вычислений прошлой итерации b
  VertexPtr sum;
  // sum - результат суммы
  VertexPtr pSum;
  VertexPtr pNext;
  // pSum - перенос между сумматорами одного уровня, pNext - разных уровней
  VertexPtr m;
  // m - бит полученного умножения, выход

  int32_t n = 1;
  // n - числовой порядок выходов
  for (int32_t ib = 1; ib <= i_bits; ib++) {
    std::string str_i = std::to_string(ib);
    input_xb = graph->addInput("xb" + str_i);
    input_xa = graph->addInput("xa" + str_i);

    std::string IB = std::to_string(ib);      // IB - index b
    std::string IBP = std::to_string(ib - 1); // IBP - index b past
    std::string IBN = std::to_string(ib + 1); // IBN - index b next

    VertexPtr xb = input_xb;
    VertexPtr ABsum;
    // ABsum - получает
    // информацию о результате прошлой итерации b

    for (int32_t ia = 1; ia <= i_bits; ia++) {
      std::string IA = std::to_string(ia);      // IA - index a
      std::string IAN = std::to_string(ia + 1); // IAN - index a next

      VertexPtr xa = input_xa;

      c = graph->addGate(Gates::GateAnd, "c" + IA + IB);
      graph->addEdges({xb, xa}, c);
      if (ib == 1)
        C_sum[ia - 1] = c;

      if (ib == 1) {
        if (ia == 1) {
          std::string N = std::to_string(n);
          m = graph->addOutput("m" + N);
          graph->addEdge(c, m);
          n += 1;
        }
      }
      if (ib > 1) {
        VertexPtr nowAB = c;
        if (ib == 2)
          if (ia < i_bits)
            ABsum = C_sum[ia];
        // второй разряд,
        // вход в сумматор от операции И
        // ABsum = "c" + IAN + IBP;
        if (ib > 2)
          if (ia < i_bits)
            ABsum = C_sum[ia];
        // Следующие разряды, вход
        // в сумматор от результата другого сумматора
        // ABsum = "sum" + IAN + IBP;

        if (ia == i_bits) {
          ABsum = pNext; // для левых боковых сумматоров
          if (i_bits == 2) {
            ABsum = pSum;
          }
          // ABsum = "pNext" + IA + IB;
        }

        std::string nSum;
        if (ia < i_bits)
          nSum = IAN + IB; // nSum - next Summator, по разряду a
        if (ia == i_bits)
          nSum = IA + IBN; // по разряду b

        if (ia == 1) {
          std::string N = std::to_string(n);
          pSum = graph->addGate(Gates::GateAnd, "pSum" + nSum);
          graph->addEdges({nowAB, ABsum}, pSum);
          sum = graph->addGate(Gates::GateXor, "sum" + IA + IB);
          graph->addEdges({nowAB, ABsum}, sum);

          m = graph->addOutput("m" + N);
          graph->addEdge(sum, m);
          n += 1;
        } else if (ib == 2 && ia == i_bits) {
          pNext = graph->addGate(Gates::GateAnd, "pNext" + nSum);
          graph->addEdges({nowAB, pSum}, pNext);
          sum = graph->addGate(Gates::GateXor, "sum" + IA + IB);
          graph->addEdges({nowAB, pSum}, sum);
          C_sum[ia - 1] = sum;

          if (i_bits == 2) {
            std::string N = std::to_string(n);
            m = graph->addOutput("m" + N);
            graph->addEdge(sum, m);

            n += 1;
            N = std::to_string(n);

            m = graph->addOutput("m" + N);
            graph->addEdge(pNext, m);
          }
        } else {
          std::string S = IA + IB;
          std::string
              p_str; // создание переноса нынешнего сумматора в следующий
          VertexPtr p;
          std::string pi_str =
              "pSum" + IA + IB; // перенос из прошлого сумматора
          VertexPtr pi = pSum;

          VertexPtr andab = graph->addGate(Gates::GateAnd, "andab" + S);
          VertexPtr andapi = graph->addGate(Gates::GateAnd, "anda" + pi_str);
          VertexPtr andbpi = graph->addGate(Gates::GateAnd, "andb" + pi_str);

          graph->addEdges({nowAB, ABsum}, andab);
          graph->addEdges({nowAB, pi}, andapi);
          graph->addEdges({pi, ABsum}, andbpi);

          if (ia < i_bits) {
            p_str = "pSum" + nSum; // для соседнего сумматора
          }
          if (ia == i_bits) {
            p_str = "pNext" + nSum; // для левых боковых сумматоров
          }

          p = graph->addGate(Gates::GateOr, p_str);
          graph->addEdges({andab, andapi, andbpi}, p);

          VertexPtr np = graph->addGate(Gates::GateNot, "n" + p_str);
          graph->addEdge(p, np);

          VertexPtr abpor = graph->addGate(Gates::GateOr, "abpor" + S);
          graph->addEdges({nowAB, ABsum, pi}, abpor);

          VertexPtr andnp = graph->addGate(Gates::GateAnd, "andnp" + nSum);
          graph->addEdges({abpor, np}, andnp);

          VertexPtr abpand = graph->addGate(Gates::GateAnd, "abpand" + S);
          graph->addEdges({nowAB, ABsum, pi}, abpand);

          sum = graph->addGate(Gates::GateOr, "sum" + IA + IB);
          graph->addEdges({abpand, andnp}, sum);

          C_sum[ia - 1] = sum;

          if (ib == i_bits) {
            std::string N = std::to_string(n);

            m = graph->addOutput("m" + N);
            graph->addEdge(sum, m);
            n += 1;
            if (ia == i_bits) {
              N = std::to_string(n);
              m = graph->addOutput("m" + N);
              graph->addEdge(p, m);
              n += 1;
            }
          }
        }
      }
    }
  }
  return graph;
}

GraphPtr
ArithmeticGenerator::generatorMultiplier(const GenerationParameters &i_param) {
  return generatorMultiplier(i_param.getInputs());
}

GraphPtr ArithmeticGenerator::generatorMultiplier() {
  return generatorMultiplier(getParameters());
}

} // namespace CG_Gen
