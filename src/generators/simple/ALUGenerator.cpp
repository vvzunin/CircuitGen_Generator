#include "ALUGenerator.hpp"
#include <additional/AuxiliaryMethods.hpp>
#include <CircuitGenGenerator/ThreadPool.hpp>

#include "ArithmeticGenerator.hpp"
#include "ComparisonGenerator.hpp"
#include "PlexerGenerator.hpp"
#include "FromTruthTableGenerator.hpp"
#include "RandLevelGenerator.hpp"
#include "NumOperationsGenerator.hpp"

#define ADD_WITH_MUTEX_TO_VEC(val) \
  ({ \
    mtx.lock(); \
    outputs_gens.push_back(val); \
    mtx.unlock(); \
  })

#define ADD_WITH_MUTEX_TO_GRAPH(g, inp) \
  ({ \
    mtx.lock(); \
    auto addedGr = graph->addSubGraph(g, inp); \
    outputs_gens.push_back(addedGr); \
    mtx.unlock(); \
  })

ALUGenerator::ALUGenerator() : SimpleGenerator() {}

ALUGenerator::ALUGenerator(uint_fast32_t i_seed) :
  SimpleGenerator(i_seed) {}

ALUGenerator::ALUGenerator(const GenerationParameters& i_param)
 : SimpleGenerator(i_param) {}

GraphPtr ALUGenerator::generatorALU(
    int32_t                  i_bits,
    int32_t                  i_outbits,
    bool                     ALL,
    bool                     SUM,
    bool                     SUB,
    bool                     NSUM,
    bool                     NSUB,
    bool                     MULT,
    bool                     COM,
    bool                     AND,
    bool                     NAND,
    bool                     OR,
    bool                     NOR,
    bool                     XOR,
    bool                     XNOR,
    bool                     CNF,
    bool                     RNL,
    bool                     NUM_OP,
    uint32_t                 minLevel,
    uint32_t                 maxLevel,
    uint32_t                 minElement,
    uint32_t                 maxElement,
    std::map<Gates, int32_t> m,
    bool                     LeaveEmptyOut
) {
  GraphPtr     graph(new OrientedGraph);
  GraphPtrWeak weakGraph = graph;
  VertexPtr    const_0   = graph->addConst('0', "const_0");
  int32_t      x         = 0;
  if (ALL) {
    SUM    = true;
    SUB    = true;
    NSUM   = true;
    NSUB   = true;
    MULT   = true;
    COM    = true;
    AND    = true;
    OR     = true;
    XOR    = true;
    XNOR   = true;
    CNF    = true;
    RNL    = true;
    NUM_OP = true;
  }

  // количество входов мультиплексора
  x = x + (SUM ? 4 : 0) + (SUB ? 4 : 0) + (NSUM ? 4 : 0) + (NSUB ? 4 : 0)
    + (MULT ? 1 : 0) + (COM ? 3 : 0) + (AND ? 1 : 0) + (NAND ? 1 : 0)
    + (OR ? 1 : 0) + (NOR ? 1 : 0) + (XOR ? 1 : 0) + (XNOR ? 1 : 0)
    + (CNF ? 3 : 0) + (RNL ? 1 : 0) + (NUM_OP ? 1 : 0);

  // размерность АЛУ (сколько генераций мультиплексоров необходимо выполнить)
  int32_t size = i_bits;
  size = MULT ? i_bits * 2 : (SUM || NSUM || SUB || NSUB ? i_bits + 1 : i_bits);
  if (CNF || RNL || NUM_OP) {
    if (MULT) {
      size = (i_outbits < i_bits * 2 ? i_bits * 2 : i_outbits);
    } else if (SUM || NSUM || SUB || NSUB) {
      size = (i_outbits < i_bits + 1 ? i_bits + 1 : i_outbits);
    } else if (i_outbits > i_bits) {
      size = i_outbits;
    }
  } else if (MULT) {
    size = i_bits * 2;
  } else if (SUM || NSUM || SUB || NSUB) {
    size = i_bits + 1;
  }

  int32_t k = 0;
  for (int32_t t = 0; t <= x; t++) {
    if (x - 1 >= std::pow(2, t))
      k++;
  }

  std::vector<VertexPtr> controls(k);

  for (int32_t i = 0; i < k; i++) {
    std::string s = std::to_string(i);
    controls[i]   = graph->addInput("cont_ALU" + s);
  }

  std::vector<VertexPtr>              inputs;
  std::vector<VertexPtr>              inputs_A(i_bits);
  std::vector<VertexPtr>              inputs_B(i_bits);
  std::vector<std::vector<VertexPtr>> outputs_gens;
  std::mutex                          mtx;

  auto pool = Threading::ThreadPool(d_settings->getNumThread());

  for (int32_t i = 0; i < i_bits; i++) {
    std::string A     = std::to_string(i);
    VertexPtr   A_alu = graph->addInput("A_alu" + A);
    VertexPtr   B_alu = graph->addInput("B_alu" + A);

    inputs_A[i]       = A_alu;
    inputs_B[i]       = B_alu;
    inputs.push_back(A_alu);
    inputs.push_back(B_alu);
  }

  std::string A;
  if (AND) {
    std::vector<VertexPtr> ands;
    for (int32_t i = 0; i < i_bits; i++) {
      A                 = std::to_string(i);
      VertexPtr and_ALU = graph->addGate(Gates::GateAnd, "and_ALU" + A);
      graph->addEdges({inputs_A[i], inputs_B[i]}, and_ALU);
      ands.push_back(and_ALU);
    }
    ADD_WITH_MUTEX_TO_VEC(ands);
  }
  if (NAND) {
    std::vector<VertexPtr> nands;
    for (int32_t i = 0; i < i_bits; i++) {
      A                  = std::to_string(i);
      VertexPtr nand_ALU = graph->addGate(Gates::GateNand, "nand_ALU" + A);
      graph->addEdges({inputs_A[i], inputs_B[i]}, nand_ALU);
      nands.push_back(nand_ALU);
    }
    ADD_WITH_MUTEX_TO_VEC(nands);
  }
  if (OR) {
    std::vector<VertexPtr> ors;
    for (int32_t i = 0; i < i_bits; i++) {
      A                = std::to_string(i);
      VertexPtr or_ALU = graph->addGate(Gates::GateOr, "or_ALU" + A);
      graph->addEdges({inputs_A[i], inputs_B[i]}, or_ALU);
      ors.push_back(or_ALU);
    }
    ADD_WITH_MUTEX_TO_VEC(ors);
  }
  if (XOR) {
    std::vector<VertexPtr> xors;
    for (int32_t i = 0; i < i_bits; i++) {
      A                 = std::to_string(i);
      VertexPtr xor_ALU = graph->addGate(Gates::GateXor, "xor_ALU" + A);
      graph->addEdges({inputs_A[i], inputs_B[i]}, xor_ALU);
      xors.push_back(xor_ALU);
    }
    ADD_WITH_MUTEX_TO_VEC(xors);
  }
  if (NOR) {
    std::vector<VertexPtr> nors;
    for (int32_t i = 0; i < i_bits; i++) {
      A                 = std::to_string(i);
      VertexPtr nor_ALU = graph->addGate(Gates::GateNor, "nor_ALU" + A);
      graph->addEdges({inputs_A[i], inputs_B[i]}, nor_ALU);
      nors.push_back(nor_ALU);
    }
    ADD_WITH_MUTEX_TO_VEC(nors);
  }
  if (XNOR) {
    std::vector<VertexPtr> xnors;
    for (int32_t i = 0; i < i_bits; i++) {
      A                  = std::to_string(i);
      VertexPtr xnor_ALU = graph->addGate(Gates::GateXnor, "xnor_ALU" + A);
      graph->addEdges({inputs_A[i], inputs_B[i]}, xnor_ALU);
      xnors.push_back(xnor_ALU);
    }
    ADD_WITH_MUTEX_TO_VEC(xnors);
  }

  if (SUM) {
    auto lambda1 = [&]() {
      auto localInp = inputs;

      auto curGraph = generatorSummator(i_bits, false, false, false);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInp);

      curGraph = generatorSummator(i_bits, false, true, false);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInp);
    };

    auto lambda2 = [&]() {
      std::vector<VertexPtr> newInputs = inputs;

      mtx.lock();
      auto add = graph->addInput("sum_p0");
      mtx.unlock();

      newInputs.insert(newInputs.begin() + 2, add);

      auto curGraph = generatorSummator(i_bits, true, true, false);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, newInputs);

      curGraph = generatorSummator(i_bits, true, false, false);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, newInputs);
    };

    pool.submit(lambda1);
    pool.submit(lambda2);
  }
  if (SUB) {
    auto lambda1 = [&]() {
      auto localInpSub = inputs;

      auto curGraph    = generatorSubtractor(i_bits, false, false, false);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInpSub);

      curGraph = generatorSubtractor(i_bits, false, true, false);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInpSub);
    };

    auto lambda2 = [&]() {
      std::vector<VertexPtr> newInputs = inputs;

      mtx.lock();
      auto add = graph->addInput("sub_z0");
      mtx.unlock();

      newInputs.insert(newInputs.begin() + 2, add);

      auto curGraph = generatorSubtractor(i_bits, true, true, false);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, newInputs);

      curGraph = generatorSubtractor(i_bits, true, false, false);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, newInputs);
    };

    pool.submit(lambda1);
    pool.submit(lambda2);
  }
  if (NSUM) {
    auto lambda1 = [&]() {
      auto localInp = inputs;

      auto curGraph = generatorSummator(i_bits, false, false, true);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInp);

      curGraph = generatorSummator(i_bits, false, true, true);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInp);
    };

    auto lambda2 = [&]() {
      std::vector<VertexPtr> newInputs = inputs;

      mtx.lock();
      auto add = graph->addInput("nsum_p0");
      mtx.unlock();

      newInputs.insert(newInputs.begin() + 2, add);

      auto curGraph = generatorSummator(i_bits, true, true, true);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, newInputs);

      curGraph = generatorSummator(i_bits, true, false, true);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, newInputs);
    };

    pool.submit(lambda1);
    pool.submit(lambda2);
  }
  if (NSUB) {
    auto lambda1 = [&]() {
      auto localInpSub = inputs;

      auto curGraph    = generatorSubtractor(i_bits, false, false, true);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInpSub);

      curGraph = generatorSubtractor(i_bits, false, true, true);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInpSub);
    };

    auto lambda2 = [&]() {
      std::vector<VertexPtr> newInputs = inputs;

      mtx.lock();
      auto add = graph->addInput("nsub_z0");
      mtx.unlock();

      newInputs.insert(newInputs.begin() + 2, add);

      auto curGraph = generatorSubtractor(i_bits, true, true, true);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, newInputs);

      curGraph = generatorSubtractor(i_bits, true, false, true);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, newInputs);
    };

    pool.submit(lambda1);
    pool.submit(lambda2);
  }
  if (MULT) {
    auto lambda = [&]() {
      auto localInpMult = inputs;

      auto curGraph     = generatorMultiplier(i_bits);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInpMult);
    };

    pool.submit(lambda);
  }
  if (COM) {
    auto lambda1 = [&]() {
      auto localInpCom = inputs;

      auto curGraph    = generatorComparison(i_bits, true, false, false);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInpCom);
    };

    auto lambda2 = [&]() {
      auto localInpCom = inputs;

      auto curGraph    = generatorComparison(i_bits, false, true, false);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInpCom);
    };

    auto lambda3 = [&]() {
      auto localInpCom = inputs;

      auto curGraph    = generatorComparison(i_bits, false, false, true);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInpCom);
    };

    pool.submit(lambda1);
    pool.submit(lambda2);
    pool.submit(lambda3);
  }

  TruthTable           gen;
  TruthTableParameters d_parameters(i_bits, i_outbits);
  if (CNF) {
    gen.generateRandom(d_parameters);

    auto lambda1 = [&]() {
      auto localInpZheg = inputs_A;
      auto genCopy      = gen;

      auto curGraph     = zhegalkinFromTruthTable(genCopy);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInpZheg);
    };

    auto lambda2 = [&]() {
      auto localInpCnft = inputs_A;
      auto genCopy      = gen;

      auto curGraph     = cnfFromTruthTable(genCopy, true);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInpCnft);
    };

    auto lambda3 = [&]() {
      auto localInpCnff = inputs_A;
      auto genCopy      = gen;

      auto curGraph     = cnfFromTruthTable(genCopy, false);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInpCnff);
    };

    pool.submit(lambda1);
    pool.submit(lambda2);
    pool.submit(lambda3);
  }

  if (RNL) {
    auto lambda = [&]() {
      auto localInpRNL = inputs_A;

      auto curGraph    = generatorRandLevel(
          minLevel, maxLevel, minElement, maxElement, i_bits, i_outbits
      );
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInpRNL);
    };

    pool.submit(lambda);
  }
  if (NUM_OP) {
    auto lambda = [&]() {
      auto localInpNUM_OP = inputs_A;

      auto curGraph =
          generatorNumOperation(i_bits, i_outbits, m, LeaveEmptyOut);
      ADD_WITH_MUTEX_TO_GRAPH(curGraph, localInpNUM_OP);
    };

    pool.submit(lambda);
  }

  pool.wait();

  size_t max = 0;
  for (size_t i = 0; i < outputs_gens.size(); i++) {
    if (outputs_gens[i].size() > max) {
      max = outputs_gens[i].size();
    }
  }
  for (size_t i = 0; i < outputs_gens.size(); i++) {
    if (outputs_gens[i].size() < max) {
      outputs_gens[i].resize(max, const_0);
    }
  }

  std::vector<std::vector<VertexPtr>> inputs_alu =
      AuxMethods::transpose(outputs_gens);
  std::vector<VertexPtr> outputs_alu;

  for (size_t i = 0; i < inputs_alu.size(); i++) {
    inputs_alu[i].insert(
        inputs_alu[i].begin(), controls.begin(), controls.end()
    );
  }

  GraphPtr mult = generatorMultiplexer(x);

  for (auto vertices : inputs_alu) {
    outputs_alu.push_back(graph->addSubGraph(mult, vertices).back());
  }

  for (size_t i = 0; i < outputs_alu.size(); i++) {
    VertexPtr out_ALU = graph->addOutput("out_ALU" + std::to_string(i));
    graph->addEdge(outputs_alu[i], out_ALU);
  }
  return graph;
}

GraphPtr ALUGenerator::generatorSummator(
    uint32_t i_bits,
    bool     i_overflowIn,
    bool     i_overflowOut,
    bool     i_minus
) {
  return ArithmeticGenerator(getParameters())
      .generatorSummator(i_bits, i_overflowIn, i_overflowOut, i_minus);
}

GraphPtr ALUGenerator::generatorSubtractor(
    uint32_t i_bits,
    bool     i_overflowIn,
    bool     i_overflowOut,
    bool     i_sub
) {
  return ArithmeticGenerator(getParameters())
      .generatorSubtractor(i_bits, i_overflowIn, i_overflowOut, i_sub);
}

GraphPtr ALUGenerator::generatorMultiplier(uint32_t i_bits) {
  return ArithmeticGenerator(getParameters())
      .generatorMultiplier(i_bits);
}

GraphPtr ALUGenerator::generatorComparison(
    uint32_t i_bits,
    bool     compare0,
    bool     compare1,
    bool     compare2
) {
  return ComparisonGenerator(getParameters())
      .generatorComparison(i_bits, compare0, compare1, compare2);
}

GraphPtr ALUGenerator::generatorMultiplexer(uint32_t i_bits) {
  return PlexerGenerator(getParameters())
      .generatorMultiplexer(i_bits);
}

GraphPtr ALUGenerator::cnfFromTruthTable(const TruthTable& i_table, bool i_tp) {
  return FromTruthTableGenerator(getParameters())
      .cnfFromTruthTable(i_table, i_tp);
}

GraphPtr ALUGenerator::zhegalkinFromTruthTable(const TruthTable& i_table) {
  return FromTruthTableGenerator(getParameters())
      .zhegalkinFromTruthTable(i_table);
}

GraphPtr ALUGenerator::generatorRandLevel(
    uint32_t i_minLevel,
    uint32_t i_maxLevel,
    uint32_t i_minElements,
    uint32_t i_maxElements,
    uint32_t i_inputs,
    uint32_t i_outputs
) {
  return RandLevelGenerator(getParameters())
      .generatorRandLevel(i_minLevel, i_maxLevel, i_minElements, i_maxElements, i_inputs, i_outputs);
}

GraphPtr ALUGenerator::generatorNumOperation(
    uint32_t                 i_input,
    uint32_t                 i_output,
    std::map<Gates, int32_t> i_logicOper,
    bool                     i_leaveEmptyOut
) {
  return NumOperationsGenerator(getParameters())
      .generatorNumOperation(i_input, i_output, i_logicOper, i_leaveEmptyOut);
}

GraphPtr ALUGenerator::generatorALU(const GenerationParameters &i_param) {
  return generatorALU(
      i_param.getInputs(), i_param.getOutputs(), i_param.getALU().getALL(),
      i_param.getALU().getSUM(), i_param.getALU().getSUB(),
      i_param.getALU().getNSUM(), i_param.getALU().getNSUB(),
      i_param.getALU().getMULT(), i_param.getALU().getCOM(),
      i_param.getALU().getAND(), i_param.getALU().getNAND(),
      i_param.getALU().getOR(), i_param.getALU().getNOR(),
      i_param.getALU().getXOR(), i_param.getALU().getXNOR(),
      i_param.getALU().getCNF(), i_param.getALU().getRNL(),
      i_param.getALU().getNUMOP(), i_param.getALU().getminLevel(),
      i_param.getALU().getmaxLevel(), i_param.getALU().getminElement(),
      i_param.getALU().getmaxElement(), i_param.getALU().getm(),
      i_param.getALU().getLeaveEmptyOut());
}

GraphPtr ALUGenerator::generatorALU() {
  return generatorALU(getParameters());
}

