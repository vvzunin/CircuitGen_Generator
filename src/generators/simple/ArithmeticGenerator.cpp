#include "ArithmeticGenerator.hpp"

ArithmeticGenerator::ArithmeticGenerator() : SimpleGenerator() {
}

ArithmeticGenerator::ArithmeticGenerator(uint_fast32_t i_seed) :
    SimpleGenerator(i_seed) {
}

ArithmeticGenerator::ArithmeticGenerator(const GenerationParameters &i_param) :
    SimpleGenerator(i_param) {
}

GraphPtr ArithmeticGenerator::generatorSummator(uint32_t i_bits,
                                                bool i_overflowIn,
                                                bool i_overflowOut,
                                                bool i_minus) {
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
ArithmeticGenerator::generatorSummator(const GenerationParameters &i_param) {
  int32_t bits = i_param.getInputs();
  bool overflowIn = i_param.getSummator().getOverFlowIn();
  bool overflowOut = i_param.getSummator().getOverFlowOut();
  bool minus = i_param.getSummator().getMinus();
  return generatorSummator(bits, overflowIn, overflowOut, minus);
}

GraphPtr
ArithmeticGenerator::generatorSubtractor(const GenerationParameters &i_param) {
  return generatorSubtractor(i_param.getInputs(),
                             i_param.getSubtractor().getOverFlowIn(),
                             i_param.getSubtractor().getOverFlowOut(),
                             i_param.getSubtractor().getSub());
}

GraphPtr
ArithmeticGenerator::generatorMultiplier(const GenerationParameters &i_param) {
  return generatorMultiplier(i_param.getInputs());
}

GraphPtr ArithmeticGenerator::generatorSummator() {
  return generatorSummator(getParameters());
}

GraphPtr ArithmeticGenerator::generatorSubtractor() {
  return generatorSubtractor(getParameters());
}

GraphPtr ArithmeticGenerator::generatorMultiplier() {
  return generatorMultiplier(getParameters());
}
