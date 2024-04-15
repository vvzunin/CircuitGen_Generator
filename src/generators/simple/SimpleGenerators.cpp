#include <algorithm>
#include <bitset>
#include <cassert>
#include <ctime>
#include <functional>
#include <iostream>
#include <stdexcept>

#include "SimpleGenerators.hpp"

#include <additional/AuxiliaryMethods.hpp>
#include <baseStructures/graph/OrientedGraph.hpp>
#include <baseStructures/Parser.hpp>
#include <math.h>

int SimpleGenerators::getRangomAndNumber() {
  return d_gatesInputsInfo[Gates::GateAnd][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateAnd].size()
  )];
}

int SimpleGenerators::getRangomOrNumber() {
  return d_gatesInputsInfo[Gates::GateOr][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateOr].size()
  )];
}

int SimpleGenerators::getRangomNandNumber() {
  return d_gatesInputsInfo[Gates::GateNand][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateNand].size()
  )];
}

int SimpleGenerators::getRangomNorNumber() {
  return d_gatesInputsInfo[Gates::GateNor][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateNor].size()
  )];
}

int SimpleGenerators::getRangomXorNumber() {
  return d_gatesInputsInfo[Gates::GateXor][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateXor].size()
  )];
}

int SimpleGenerators::getRangomXnorNumber() {
  return d_gatesInputsInfo[Gates::GateXnor][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateXnor].size()
  )];
}

std::pair<Gates, int> SimpleGenerators::getRandomElement(const GatesInfo& i_info
) {
  // rand element of map
  auto val = i_info.begin();
  std::advance(val, d_randGenerator.getRandInt(0, i_info.size()));

  // random gate number from of random element
  return std::make_pair(
      val->first, val->second[d_randGenerator.getRandInt(0, val->second.size())]
  );
}

std::pair<Gates, int> SimpleGenerators::getRandomElement(u_int32_t i_gatesLimit
) {
  if (i_gatesLimit >= d_maxGateNumber)
    return getRandomElement(d_gatesInputsInfo);

  if (i_gatesLimit <= 1)
    return std::make_pair(
        d_randGenerator.getRandInt(0, 2) ? Gates::GateNot : Gates::GateBuf, 1
    );

  GatesInfo        info;
  std::vector<int> subval;

  for (auto [key, value] : d_gatesInputsInfo) {
    for (int i = 0; i < value.size() && value[i] <= i_gatesLimit; ++i)
      subval.push_back(value[i]);

    if (subval.size())
      info[key] = std::move(subval);
    subval.clear();
  }

  return getRandomElement(info);
}

SimpleGenerators::SimpleGenerators() {
  d_randGenerator.setSeed(AuxMethods::getRandSeed());
}

SimpleGenerators::SimpleGenerators(int i_seed) {
  d_randGenerator.setSeed(i_seed);
}

GraphPtr
    SimpleGenerators::cnfFromTruthTable(const TruthTable& i_table, bool i_tp) {
  std::vector<std::string> fun;
  fun.reserve(i_table.getOutput());
  std::vector<std::vector<bool>> bin = i_table.convToBinary();

  GraphPtr                       graph(new OrientedGraph());
  std::vector<VertexPtr>         inputs;
  inputs.reserve(i_table.getInput());
  for (int k = 0; k < i_table.getInput(); ++k) {
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
  VertexPtr                      constGate_0(nullptr), constGate_1(nullptr);

  Parser                         parserMany;
  parserMany.setGatesInputsInfo(d_gatesInputsInfo);

  for (size_t j = 0; j < i_table.getOutput(); ++j) {
    VertexPtr out = graph->addOutput("f" + std::to_string(j));
    int       mem = 0;
    int       tmp = 0;

    for (int i = 0; i < i_table.size(); ++i) {
      if (!(i_table.getOutTable(i, j) ^ i_tp))
        mem++;
    }

    if (mem == 0 || mem == i_table.size()) {
      if (i_tp && mem == 0 || !i_tp && mem == i_table.size()) {
        if (constGate_0.get() == nullptr) {
          constGate_0 = graph->addConst('0');
        }
        graph->addEdge(constGate_0, out);
      } else {
        if (constGate_1.get() == nullptr) {
          constGate_1 = graph->addConst('1');
        }
        graph->addEdge(constGate_1, out);
      }
      continue;
    }

    Gates                  exter   = i_tp ? Gates::GateOr : Gates::GateAnd;
    Gates                  inter   = i_tp ? Gates::GateAnd : Gates::GateOr;
    int32_t                curSize = 0;

    std::vector<VertexPtr> nextLayoutExt;
    std::vector<VertexPtr> nextLayout;

    nextLayout.reserve(inputs.size());

    // Here we create operations in brackets
    for (int i = 0; i < mem; ++i) {
      while ((i_table.getOutTable(tmp, j) ^ i_tp) && tmp < i_table.size())
        ++tmp;

      // create layout of "input"
      for (size_t k = 0; k < inputs.size(); ++k) {
        VertexPtr x_input = inputs[k];

        // add NOT
        if (bin[tmp][k] ^ i_tp) {
          if (!inputs_not.count(x_input)) {
            inputs_not[x_input] =
                graph->addGate(Gates::GateNot, x_input->getName() + "_not");
          }

          // Get NOT operation
          x_input = inputs_not[x_input];
          graph->addEdge(inputs[k], x_input);
        }

        nextLayout.push_back(x_input);
      }

      nextLayoutExt.push_back(
          parserMany.multipleVerteciesToOne(nextLayout, inter, graph)
      );

      nextLayout.clear();
      ++tmp;
    }

    // and here operations with brackets
    graph->addEdge(
        parserMany.multipleVerteciesToOne(nextLayoutExt, exter, graph), out
    );
  }

  return graph;
}

GraphPtr SimpleGenerators::zhegalkinFromTruthTable(const TruthTable& i_table) {
  int                    num_inputs  = i_table.getInput();
  int                    num_outputs = i_table.getOutput();

  GraphPtr               graph(new OrientedGraph());
  std::vector<VertexPtr> inputs;
  inputs.reserve(num_inputs);

  for (int k = 0; k < num_inputs; ++k) {
    inputs.push_back(graph->addInput("x" + std::to_string(k)));
  }

  for (int j = 0; j < num_outputs; ++j) {
    VertexPtr out = graph->addOutput("f" + std::to_string(j));

    int       mem = 0;
    for (int i = 0; i < i_table.size(); ++i) {
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

      for (int term = 0; term < (1 << num_inputs); ++term) {
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

            for (int i = 0; i < num_inputs; ++i) {
              VertexPtr x_input = inputs[i];
              bool      negated = ((term >> (num_inputs - i - 1)) & 1) == 0;

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

GraphPtr SimpleGenerators::generatorRandLevel(
    int i_minLevel,
    int i_maxLevel,
    int i_minElements,
    int i_maxElements,
    int i_inputs,
    int i_outputs
) {
  int maxLevel;

  if (i_minLevel > i_maxLevel)
    throw std::invalid_argument("min level is biggert than max level");
  if (i_minElements > i_maxElements)
    throw std::invalid_argument("min elem is biggert than max elem");

  if (i_maxLevel)
    maxLevel = d_randGenerator.getRandInt(i_minLevel, i_maxLevel, true) + 1;
  else
    maxLevel = 1;

  auto [hasOneGate, logOper] = d_settings->getLogicOperationsWithGates();

  // maxLevel++ // what?

  int         choice;
  std::string expr;
  GraphPtr    graph(new OrientedGraph);
  int         child1, child2;

  for (int i = 0; i < i_inputs; ++i) {
    expr = "x" + std::to_string(i);
    graph->addInput(expr);
  }

  int currIndex = i_inputs;
  int prevIndex = 0;

  for (int i = 1; i < maxLevel; ++i) {
    int position = 0;
    // how many elements would be at this level
    int elemLevel =
        i_maxElements > 1
            ? d_randGenerator.getRandInt(i_minElements, i_maxElements, true)
            : 2;

    for (int j = 0; j < elemLevel; ++j) {
      choice = d_randGenerator.getRandInt(0, logOper.size());

      if (hasOneGate[choice]) {
        child1              = d_randGenerator.getRandInt(0, currIndex);

        VertexPtr newVertex = graph->addGate(logOper[choice]);
        graph->addEdge(graph->getVerticeByIndex(child1), newVertex);

      } else {
        child1              = d_randGenerator.getRandInt(prevIndex, currIndex);
        child2              = d_randGenerator.getRandInt(prevIndex, currIndex);

        VertexPtr newVertex = graph->addGate(logOper[choice]);
        graph->addEdges(
            {graph->getVerticeByIndex(child2),
             graph->getVerticeByIndex(child1)},
            newVertex
        );
      }
      ++position;
    }

    prevIndex += currIndex - prevIndex;
    currIndex += position;

    // std::clog << i / (float)maxLevel * 100 << "%" << std::endl;
  }

  // TODO: fix when elements less than outputs

  for (int i = 0; i < i_outputs; ++i) {
    child1              = d_randGenerator.getRandInt(prevIndex, currIndex);
    expr                = "f" + std::to_string(i + 1);
    VertexPtr newVertex = graph->addOutput(expr);
    graph->addEdge(graph->getVerticeByIndex(child1), newVertex);
  }

  return graph;
}

GraphPtr SimpleGenerators::generatorRandLevelExperimental(
    u_int32_t i_minLevel,
    u_int32_t i_maxLevel,
    u_int32_t i_minElements,
    u_int32_t i_maxElements,
    u_int32_t i_inputs,
    u_int32_t i_outputs
) {
  if (i_minLevel > i_maxLevel)
    throw std::invalid_argument("min level is biggert than max level");
  if (i_minElements > i_maxElements)
    throw std::invalid_argument("min elem is biggert than max elem");

  u_int32_t maxLevel;
  if (i_maxLevel)
    maxLevel = d_randGenerator.getRandInt(i_minLevel, i_maxLevel, true) + 1;
  else
    maxLevel = 1;

  std::string expr;
  GraphPtr    graph(new OrientedGraph);

  for (int i = 0; i < i_inputs; ++i) {
    expr = "x" + std::to_string(i);
    graph->addInput(expr);
  }
  // we need it because we:
  // a) can have less possible parents at current level, than is required by
  // minimum gates number of a logical element, so we can use inputs in such
  // case
  // b) need to swap gates
  std::vector<VertexPtr> inputs = graph->getVerticesByType(VertexTypes::input);

  // TODO what if we will need to use n-gate elements, should we add consts
  // usage?

  int                    currIndex = i_inputs;
  int                    prevIndex = 0;
  int                    curLen    = 0;
  // we need lowest border as d_maxGateNumber, and if it is possible,
  // we set it (it changes speed of generation)
  u_int32_t              c_max     = i_maxElements > d_maxGateNumber
                                       ? std::max(d_maxGateNumber, (int)i_minElements)
                                       : i_minElements;

  for (int i = 1; i < maxLevel; ++i) {
    int                    position  = 0;
    // how many elements would be at this level
    int                    elemLevel = i_maxElements > 1
                                         ? d_randGenerator.getRandInt(c_max, i_maxElements, true)
                                         : i_maxElements;

    // write allowed gates to be used as parent
    std::vector<VertexPtr> curGates;
    for (int val = prevIndex; val < currIndex; ++val)
      curGates.push_back(graph->getVerticeByIndex(val));
    curLen += curGates.size();

    for (int j = 0; j < elemLevel; ++j) {
      // we use inputs only if we are not on the first level
      auto [operation, gatesNumber] = getRandomElement(curLen);
      // from which element we should start shuffle
      // like we do not shuffle whole list, if it is possible
      // but only it's part
      int fromWhichShuffle          = d_randGenerator.getRandInt(
          0, std::max(1, (int)curGates.size() - gatesNumber)
      );
      // shuffle curGates
      for (int k       = fromWhichShuffle,
               stopVal = std::min(
                   fromWhichShuffle + gatesNumber, (int)curGates.size()
               );
           k < stopVal;
           ++k) {
        std::swap(
            curGates[k],
            curGates[d_randGenerator.getRandInt(0, curGates.size())]
        );
      }

      if (gatesNumber == 1) {
        int       child1    = d_randGenerator.getRandInt(0, currIndex);

        VertexPtr newVertex = graph->addGate(operation);
        graph->addEdge(graph->getVerticeByIndex(child1), newVertex);
      } else {
        // parents vertices to be added for a new one
        std::vector<VertexPtr> parents;
        // set memory (might be big, so we save time)
        parents.reserve(gatesNumber);
        auto idx = curGates.begin() + fromWhichShuffle;

        // add first parent
        parents.push_back(*idx);
        // move to second
        // it's impossible to have 1-element vector here
        // else we would have curLen = 1 and only buf/not
        // so it's safe
        ++idx;

        // add multiple parents
        for (int l = 1; l < gatesNumber; ++l, ++idx) {
          parents.push_back(*idx);

          // if we are at the end of vector
          if (idx == curGates.end()) {
            // and we added some vertices, e.g. we are not on the first level
            if (i > 1) {
              for (int k = 0; k < inputs.size(); ++k)
                std::swap(
                    inputs[k],
                    inputs[d_randGenerator.getRandInt(0, inputs.size())]
                );

              idx = inputs.begin();
            } else {
              idx = curGates.begin();
            }
          } else if (idx == inputs.end())
            idx = curGates.begin();
        }

        VertexPtr newVertex = graph->addGate(operation);
        graph->addEdges(parents, newVertex);
      }
      ++position;
    }
    // if something was added to graph, we move parent parts of
    if (position) {
      prevIndex += currIndex - prevIndex;
      currIndex += position;
    }
    // at the beginning it is zero. So, if it stayed zero, we are still using
    // inputs as gates. So we do not change it's value
    if (prevIndex) {
      curLen = inputs.size();
    }

    // std::clog << (float)i / (float)maxLevel * 100 << "%" << std::endl;
  }

  // std::clog << "writing out gates" << std::endl;
  for (int i = 0; i < i_outputs; ++i) {
    int child1          = d_randGenerator.getRandInt(prevIndex, currIndex);
    expr                = "f" + std::to_string(i + 1);
    VertexPtr newVertex = graph->addOutput(expr);

    graph->addEdge(graph->getVerticeByIndex(child1), newVertex);
  }

  // std::clog << "writing out gates ended" << std::endl;
  return graph;
}

GraphPtr SimpleGenerators::generatorNumOperation(
    int                  i_input,
    int                  i_output,
    std::map<Gates, int> i_logicOper,
    bool                 i_leaveEmptyOut
) {
  int                      sumOper = 0, maxLvl;
  std::string              name;
  VertexPtr                name_ptr;
  std::map<Gates, int>     copyLogicOper;
  std::map<VertexPtr, int> levelName;
  std::vector<VertexPtr>   nameOut, nameInput;

  for (const auto& elem : i_logicOper) {
    std::cout << elem.first << " " << elem.second << "\n";
  }

  copyLogicOper = i_logicOper;

  GraphPtr graph(new OrientedGraph());

  for (int i = 0; i < i_input; ++i) {
    name                = "x" + std::to_string(i);
    name_ptr            = graph->addInput(name);

    // TODO and how can it be changed?
    levelName[name_ptr] = name_ptr->getLevel();
    if (!i_leaveEmptyOut)
      nameInput.push_back(name_ptr);
  }

  for (int i = 0; i < i_output; ++i) {
    name     = "f" + std::to_string(i);
    name_ptr = graph->addOutput(name);
    nameOut.push_back(name_ptr);
  }

  for (const auto& [key, value] : copyLogicOper)
    sumOper += value;

  copyLogicOper = delNull(copyLogicOper);
  // TODO it is TOO slow
  for (int i = 0; i < sumOper; ++i) {
    // TODO: optimize
    // TODO change whole gen
    Gates oper = randomGenerator(copyLogicOper);
    --copyLogicOper[oper];

    if (oper == Gates::GateNot || oper == Gates::GateBuf) {
      VertexPtr ver1 = randomGenerator(levelName);
      // name = d_settings->getLogicOperation(oper).first + "(" + ver1 + ")";
      name_ptr       = graph->addGate(oper);
      graph->addEdge(ver1, name_ptr);
    } else {
      VertexPtr ver1 = randomGenerator(levelName);
      VertexPtr ver2 = randomGenerator(levelName);
      // name = "(" + ver1 + ") " + d_settings->getLogicOperation(oper).first +
      //        "(" + ver2 + ")";

      // WTF this is not used AT ALL
      // std::string reserveName = "(" + ver2 + ") " +
      //                           d_settings->getLogicOperation(oper).first +
      //                           "(" + ver1 + ")";

      name_ptr       = graph->addGate(oper);
      graph->addEdges({ver1, ver2}, name_ptr);
      levelName[name_ptr] = name_ptr->getLevel();
    }

    if (!copyLogicOper[oper])
      copyLogicOper.erase(oper);
  }

  while ((nameOut.size() > 0)
         & ((levelName.size() > 0 || i_leaveEmptyOut == false))) {
    if (levelName.size() > 0) {
      std::vector<VertexPtr> help;
      maxLvl = maxValueInMap(levelName);

      for (const auto& [key, value] : levelName) {
        if (value == maxLvl)
          help.push_back(key);
      }

      while (help.size() > 0 && nameOut.size() > 0) {
        int R1 = d_randGenerator.getRandInt(0, help.size());
        int R2 = d_randGenerator.getRandInt(0, nameOut.size());
        graph->addEdge(help[R1], nameOut[R2]);
        levelName.erase(help[R1]);
        help.erase(help.begin() + R1);
        nameOut.erase(nameOut.begin() + R2);
      }
    } else {
      int R1 = d_randGenerator.getRandInt(0, nameInput.size());
      int R2 = d_randGenerator.getRandInt(0, nameOut.size());

      graph->addEdge(nameInput[R1], nameOut[R2]);
      nameOut.erase(nameOut.begin() + R2);
    }
  }
  return graph;
}

std::map<Gates, int> SimpleGenerators::delNull(
    std::map<Gates, int> i_copyLogicOper
) {
  std::vector<Gates> delList;
  for (const auto& [key, value] : i_copyLogicOper)
    if (value == 0)
      delList.push_back(key);

  for (const auto& op : delList)
    i_copyLogicOper.erase(op);
  return i_copyLogicOper;
}

GraphPtr SimpleGenerators::generatorSummator(
    int  i_bits,
    bool i_overflowIn,
    bool i_overflowOut,
    bool i_minus
) {
  GraphPtr    graph(new OrientedGraph);
  std::string str_x;
  std::string str_y;

  VertexPtr   const_1;

  std::string cond = std::string(i_overflowIn ? "t" : "f")
                   + (i_overflowOut ? "t" : "f") + (i_minus ? "t" : "f");
  std::string z = std::string(i_minus ? "n" : "") + "s"
                + (!i_overflowIn && !i_overflowOut
                       ? "0"
                       : (!i_overflowIn && i_overflowOut
                              ? "1"
                              : (i_overflowIn && !i_overflowOut ? "2" : "3")))
                + "_";
  VertexPtr curr_p;
  VertexPtr next_p;

  for (int i = 0; i < i_bits; i++) {
    std::string S     = std::to_string(i);
    std::string NextS = std::to_string(i + 1);

    str_x             = "sum_a" + cond + S;
    str_y             = "sum_b" + cond + S;

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

    output_sum      = graph->addOutput(z + S);

    VertexPtr xorab = graph->addGate(Gates::GateXor, "xorab" + S);
    graph->addEdges({i_minus ? nx : input_x, i_minus ? ny : input_y}, xorab);
    VertexPtr andab = graph->addGate(Gates::GateAnd, "andab" + S);
    graph->addEdges({i_minus ? nx : input_x, i_minus ? ny : input_y}, andab);

    if (i == 0) {
      if (i_overflowIn) {
        curr_p           = graph->addInput("p" + S);

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

GraphPtr SimpleGenerators::generatorComparison(
    int  i_bits,
    bool compare0,
    bool compare1,
    bool compare2
) {
  GraphPtr    graph(new OrientedGraph);
  VertexPtr   prev_pn_;
  std::string cond = std::string(compare0 ? "t" : "f") + (compare1 ? "t" : "f")
                   + (compare2 ? "t" : "f");
  for (int i = i_bits - 1; i >= 0; i--) {
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
        graph->addEdges({prev_pn_, pn_}, pEn_);
        graph->addEdge(pEn_, En_);
      }
      prev_pn_ = pn_;
    }
    if (compare1) {
      En_ = graph->addOutput("E1_" + C);
      pn_ = graph->addGate(Gates::GateAnd, "p1_" + NextC);
      graph->addEdges({input_x, nb}, pn_);

      // in case of first iteration
      if (i == i_bits - 1) {
        graph->addEdge(pn_, En_);
      } else {
        VertexPtr np1_     = graph->addGate(Gates::GateNot, "np1_" + C);
        VertexPtr np1_next = graph->addGate(Gates::GateNot, "np1_" + NextC);
        graph->addEdge(prev_pn_, np1_);
        graph->addEdge(pn_, np1_next);
        VertexPtr P11_ = graph->addGate(Gates::GateAnd, "P11_" + C);
        graph->addEdges({np1_, pn_}, P11_);
        VertexPtr P12_ = graph->addGate(Gates::GateAnd, "P12_" + C);
        graph->addEdges({prev_pn_, np1_next}, P12_);
        pEn_ = graph->addGate(Gates::GateOr, "pE1_" + C);
        graph->addEdges({P11_, P12_}, pEn_);
        graph->addEdge(pEn_, En_);
      }
      prev_pn_ = pn_;
    }
    if (compare2) {
      En_ = graph->addOutput("E2_" + C);
      pn_ = graph->addGate(Gates::GateAnd, "p2_" + NextC);
      graph->addEdges({input_y, na}, pn_);

      // first iteration
      if (i == i_bits - 1) {
        graph->addEdge(pn_, En_);
      } else {
        VertexPtr np2_     = graph->addGate(Gates::GateNot, "np2_" + C);
        VertexPtr np2_next = graph->addGate(Gates::GateNot, "np2_" + NextC);
        graph->addEdge(prev_pn_, np2_);
        graph->addEdge(pn_, np2_next);
        VertexPtr P21_ = graph->addGate(Gates::GateAnd, "P21_" + C);
        graph->addEdges({np2_, np2_next}, P21_);
        VertexPtr P22_ = graph->addGate(Gates::GateAnd, "P22_" + C);
        graph->addEdges({prev_pn_, np2_next}, P22_);
        pEn_ = graph->addGate(Gates::GateOr, "pE2_" + C);
        graph->addEdges({P21_, P22_}, pEn_);
        graph->addEdge(pEn_, En_);
      }
      prev_pn_ = pn_;
    }
  }
  return graph;
}

GraphPtr SimpleGenerators::generatorEncoder(int i_bits) {
  GraphPtr graph(new OrientedGraph);
  if (i_bits < 2) {
    std::cout << "Недостаточно входных сигналов" << std::endl;
  } else {
    int i_outbits = 0;
    while (i_bits > pow(2, i_outbits))
      i_outbits++;

    std::vector<VertexPtr> inputs_x(i_bits);
    std::vector<VertexPtr> not_x(i_bits);
    std::vector<VertexPtr> ands(pow(2, i_outbits));

    // создание инверсий входов
    for (int i = 0; i < i_bits; i++) {
      VertexPtr x = graph->addInput("x" + std::to_string(i + 1));
      inputs_x[i] = x;
      VertexPtr nx =
          graph->addGate(Gates::GateNot, "nx" + std::to_string(i + 1));
      graph->addEdge(x, nx);
      not_x[i] = nx;
    }

    int  shift = 1;
    int  count = 0;
    bool check = false;
    for (int i = 0; i < pow(2, i_outbits); i++) {
      VertexPtr and_xs =
          graph->addGate(Gates::GateAnd, "and_for_or" + std::to_string(i + 1));
      // создание массива значений для операций and
      std::vector<VertexPtr> Xs(i_bits);
      for (int j = 0; j < i_bits; j++) {
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
        Xs[0]     = inputs_x[0];
        Xs[shift] = inputs_x[shift];
        for (int j = shift + 1; j < i_bits; j++)
          Xs[j] = not_x[j];
        for (int j = 1; j < shift; j++)
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

    int n = 1;
    for (int i = 0; i < i_outbits; i++) {
      VertexPtr or_xs = graph->addGate(
          Gates::GateOr, "or_for_output" + std::to_string(i + 1)
      );
      std::vector<VertexPtr> ors;
      for (int j = n; j < pow(2, i_outbits); j += n * 2) {
        ors.insert(ors.end(), ands.begin() + j, ands.begin() + j + n);
      }
      graph->addEdges(ors, or_xs);
      n           *= 2;

      VertexPtr y = graph->addOutput("y" + std::to_string(i));
      graph->addEdge(or_xs, y);
    }
  }
  return graph;
}

GraphPtr SimpleGenerators::generatorSubtractor(
    int  i_bits,
    bool i_overflowIn,
    bool i_overflowOut,
    bool i_sub
) {
  GraphPtr    graph(new OrientedGraph);
  VertexPtr   const_1;

  std::string cond = std::string(i_overflowIn ? "t" : "f")
                   + (i_overflowOut ? "t" : "f") + (i_sub ? "t" : "f");
  std::string s = std::string(i_sub ? "n" : "") + "d"
                + (!i_overflowIn && !i_overflowOut
                       ? "0"
                       : (!i_overflowIn && i_overflowOut
                              ? "1"
                              : (i_overflowIn && !i_overflowOut ? "2" : "3")))
                + "_";

  VertexPtr next_z;  // следующий заем
  VertexPtr curr_z;  // нынешний заём

  for (int i = 0; i < i_bits; i++) {
    std::string Z = std::to_string(i);          // нынешний индекс
    std::string NextZ = std::to_string(i + 1);  // следующий индекс
    std::string x       = "suba" + cond + Z;
    std::string y       = "subb" + cond + Z;
    VertexPtr   input_x = graph->addInput(x);
    VertexPtr   input_y = graph->addInput(y);
    VertexPtr   output_sub;

    output_sub      = graph->addOutput(s + Z);

    VertexPtr abxor = graph->addGate(Gates::GateXor, "abxor" + Z);
    graph->addEdges({input_x, input_y}, abxor);

    VertexPtr abandn;
    // i_sub отвечает за определение вычитателя и вычитываемого: B-A или A-B
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

    VertexPtr d;  // результат

    if (i_overflowIn) {
      d      = graph->addGate(Gates::GateXor, "d" + Z);
      next_z = graph->addGate(Gates::GateOr, "z" + NextZ);
      if (i == 0)
        curr_z = graph->addInput("z" + Z);

      VertexPtr nabxor = graph->addGate(Gates::GateNot, "nabxor" + Z);
      graph->addEdge(abxor, nabxor);

      VertexPtr nabxorz = graph->addGate(Gates::GateAnd, "abxornz" + Z);
      graph->addEdges({curr_z, nabxor}, nabxorz);

      graph->addEdges({nabxorz, abandn}, next_z);  // перенос заема
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
        d                = graph->addGate(Gates::GateXor, "d" + Z);
        next_z           = graph->addGate(Gates::GateOr, "z" + NextZ);

        VertexPtr nabxor = graph->addGate(Gates::GateNot, "nabxor" + Z);
        graph->addEdge(abxor, nabxor);

        VertexPtr nabxorz = graph->addGate(Gates::GateAnd, "abxornz" + Z);
        graph->addEdges({curr_z, nabxor}, nabxorz);

        graph->addEdges({nabxorz, abandn}, next_z);  // перенос заема
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

GraphPtr SimpleGenerators::generatorMultiplexer(int i_bits) {
  GraphPtr               graph(new OrientedGraph);
  VertexPtr              output_f = graph->addOutput("f");
  std::vector<VertexPtr> inputs_x;
  int                    k = 0;
  for (int t = 0; t <= i_bits; t++) {
    if (i_bits - 1 >= std::pow(2, t))
      k++;
  }

  std::vector<std::string> F(i_bits);
  std::vector<VertexPtr>   ands(i_bits);
  std::vector<std::string> S(k);
  std::vector<VertexPtr>   Sp(k);
  std::vector<VertexPtr>   NSp(k);
  std::vector<std::string> Z(i_bits);
  std::vector<VertexPtr>   Zp(i_bits);

  if (i_bits > 1) {
    // механизм создания управляющих входов и их инверсий
    for (int p = 0; p < k; p++) {
      S[p]   = std::to_string(p);
      Sp[p]  = graph->addInput("a" + S[p]);
      // graph->addVertex("not a" + S[p], "not", "not a" + S[p]);
      NSp[p] = graph->addGate(Gates::GateNot, "not_a" + S[p]);
      graph->addEdge(Sp[p], NSp[p]);
    }
    // механизм создания входов
    for (int i = 0; i < i_bits; i++) {
      Z[i]  = std::to_string(i);
      Zp[i] = graph->addInput("x" + Z[i]);
      F[i]  = std::bitset<8>(i).to_string();
    }
    // механизм создания связей между входами и and
    for (int i = 0; i < i_bits; i++) {
      ands[i] = graph->addGate(Gates::GateAnd, "and_for_or_" + Z[i]);
      graph->addEdge(Zp[i], ands[i]);
    }

    for (int i = 0; i < i_bits; i++) {
      int len = F[i].size();
      for (int w = 0; w < k; w++) {
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
  } else
    std::cout << "Недостаточно входных сигналов" << std::endl;
  return graph;
}

GraphPtr SimpleGenerators::generatorDemultiplexer(int i_bits) {
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

  GraphPtr  graph(new OrientedGraph);
  VertexPtr input_f = graph->addInput("f");

  int       k       = 0;
  for (int t = 0; t <= i_bits; t++) {
    if (i_bits - 1 >= std::pow(2, t))
      k++;
  }

  std::vector<std::string> F(i_bits);
  std::vector<VertexPtr>   ands(i_bits);
  std::vector<std::string> S(k);
  std::vector<VertexPtr>   Sp(k);
  std::vector<VertexPtr>   NSp(k);
  std::vector<std::string> Z(i_bits);
  std::vector<VertexPtr>   Zp(i_bits);

  if (i_bits > 1) {
    for (int p = 0; p <= k - 1; p++) {
      S[p]   = std::to_string(p);
      Sp[p]  = graph->addInput("a" + S[p]);
      // graph->addVertex("not a" + S[p], "not", "not a" + S[p]);
      NSp[p] = graph->addGate(Gates::GateNot, "not_a" + S[p]);
      graph->addEdge(Sp[p], NSp[p]);
    }

    for (int i = 0; i <= i_bits - 1; i++) {
      Z[i]  = std::to_string(i);
      Zp[i] = graph->addOutput("x" + Z[i]);
      F[i]  = std::bitset<8>(i).to_string();
    }

    for (int i = 0; i <= i_bits - 1; i++) {
      ands[i] = graph->addGate(Gates::GateAnd, "and_for_output_" + Z[i]);
      graph->addEdge(input_f, ands[i]);
      graph->addEdge(ands[i], Zp[i]);
    }

    for (int i = 0; i <= i_bits - 1; i++) {
      int len = F[i].size();
      for (int w = 0; w <= k - 1; w++) {
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

GraphPtr SimpleGenerators::generatorDecoder(int i_bits) {
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
    for (int i = 0; i < i_bits; i++) {
      std::string Z = std::to_string(i);
      X[i]          = graph->addInput("x" + Z);
      X[i + i_bits] = graph->addGate(GateNot, "not (x" + Z + ")");
      graph->addEdge(X[i], X[i + i_bits]);
    }
    for (int i = 0; i < pow(2, i_bits); i++) {
      std::string Z = std::to_string(i);
      Out[i]        = graph->addOutput("f" + Z);
    }
    int p = i_bits;
    for (int i = 0; i < pow(2, i_bits); i++) {
      T[i] = graph->addGate(GateAnd, "and" + std::to_string(i));
      std::bitset<sizeof(int) * 8> bs(i);
      std::string                  bit_string = bs.to_string();
      std::string res = bit_string.substr(bit_string.length() - i_bits);
      for (int j = 0; j < res.length(); j++) {
        if (res[j] == '1') {
          graph->addEdge(X[j], T[i]);
        } else {
          graph->addEdge(X[j + i_bits], T[i]);
        }
      }
    }
    for (int i = 0; i < pow(2, i_bits); i++) {
      graph->addEdge(T[i], Out[i]);
    }
  } else {
    VertexPtr x     = graph->addInput("x");
    VertexPtr not_x = graph->addGate(GateNot, "not (x)");
    for (int i = 0; i < 2; i++) {
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

GraphPtr SimpleGenerators::generatorParity(int i_bits) {
  // i_bits - количество входов
  // elem - массив для сохранения вершин
  // xors - промежуточный массив для сохранения вершин
  // F - функция на выходе

  GraphPtr graph(new OrientedGraph);
  if (i_bits <= 1) {
    std::cout << "Недостаточно входных сигналов" << std::endl;
    return graph;
  }
  VertexPtr              output_f = graph->addOutput("F");
  std::vector<VertexPtr> elem(i_bits);
  std::vector<VertexPtr> xors;

  for (int i = 0; i < i_bits; i++) {
    elem[i] = graph->addInput("x" + std::to_string(i));
  }

  int  k = 0;
  bool shift;
  int  count = i_bits;
  while (count != 1) {
    count % 2 == 1 ? shift = true : shift = false;
    xors.clear();
    std::string str_k = std::to_string(k);
    int         n     = 0;
    for (int i = 1; i < count; i += 2) {
      std::string str_n = std::to_string(n);
      VertexPtr   Xor =
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

GraphPtr SimpleGenerators::generatorMultiplier(int i_bits) {
  GraphPtr               graph(new OrientedGraph);
  VertexPtr              const_1;

  VertexPtr              input_xa;
  // a - бит первого множителя
  VertexPtr              input_xb;
  // b - бит второго множителя
  VertexPtr              c;
  // с - результат логического и
  std::vector<VertexPtr> C_sum(i_bits);
  // C_sum - хранит результаты вычислений прошлой итерации b
  VertexPtr              sum;
  // sum - результат суммы
  VertexPtr              pSum;
  VertexPtr              pNext;
  // pSum - перенос между сумматорами одного уровня, pNext - разных уровней
  VertexPtr              m;
  // m - бит полученного умножения, выход

  int                    n = 1;
  // n - числовой порядок выходов
  for (int ib = 1; ib <= i_bits; ib++) {
    std::string str_i = std::to_string(ib);
    input_xb          = graph->addInput("xb" + str_i);
    input_xa          = graph->addInput("xa" + str_i);

    std::string IB    = std::to_string(ib);      // IB - index b
    std::string IBP   = std::to_string(ib - 1);  // IBP - index b past
    std::string IBN   = std::to_string(ib + 1);  // IBN - index b next

    VertexPtr   xb    = input_xb;
    VertexPtr   ABsum;
    // ABsum - получает
    // информацию о результате прошлой итерации b

    for (int ia = 1; ia <= i_bits; ia++) {
      std::string IA  = std::to_string(ia);      // IA - index a
      std::string IAN = std::to_string(ia + 1);  // IAN - index a next

      VertexPtr   xa  = input_xa;

      c               = graph->addGate(Gates::GateAnd, "c" + IA + IB);
      graph->addEdges({xb, xa}, c);
      if (ib == 1)
        C_sum[ia - 1] = c;

      if (ib == 1) {
        if (ia == 1) {
          std::string N = std::to_string(n);
          m             = graph->addOutput("m" + N);
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
          ABsum = pNext;  // для левых боковых сумматоров
          if (i_bits == 2) {
            ABsum = pSum;
          }
          // ABsum = "pNext" + IA + IB;
        }

        std::string nSum;
        if (ia < i_bits)
          nSum = IAN + IB;  // nSum - next Summator, по разряду a
        if (ia == i_bits)
          nSum = IA + IBN;  // по разряду b

        if (ia == 1) {
          std::string N = std::to_string(n);
          pSum          = graph->addGate(Gates::GateAnd, "pSum" + nSum);
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
            m             = graph->addOutput("m" + N);
            graph->addEdge(sum, m);

            n += 1;
            N = std::to_string(n);

            m = graph->addOutput("m" + N);
            graph->addEdge(pNext, m);
          }
        } else {
          std::string S = IA + IB;
          std::string
              p_str;  // создание переноса нынешнего сумматора в следующий
          VertexPtr   p;
          std::string pi_str =
              "pSum" + IA + IB;  // перенос из прошлого сумматора
          VertexPtr pi     = pSum;

          VertexPtr andab  = graph->addGate(Gates::GateAnd, "andab" + S);
          VertexPtr andapi = graph->addGate(Gates::GateAnd, "anda" + pi_str);
          VertexPtr andbpi = graph->addGate(Gates::GateAnd, "andb" + pi_str);

          graph->addEdges({nowAB, ABsum}, andab);
          graph->addEdges({nowAB, pi}, andapi);
          graph->addEdges({pi, ABsum}, andbpi);

          if (ia < i_bits) {
            p_str = "pSum" + nSum;  // для соседнего сумматора
          }
          if (ia == i_bits) {
            p_str = "pNext" + nSum;  // для левых боковых сумматоров
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

            m             = graph->addOutput("m" + N);
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

GraphPtr SimpleGenerators::ALU(
    int  i_bits,
    int  i_outbits,
    bool ALL,
    bool SUM,
    bool SUB,
    bool NSUM,
    bool NSUB,
    bool MULT,
    bool COM,
    bool AND,
    bool NAND,
    bool OR,
    bool NOR,
    bool XOR,
    bool XNOR,
    bool CNF
) {
  GraphPtr graph(new OrientedGraph);
  if (ALL) {
    SUM  = true;
    SUB  = true;
    NSUM = true;
    NSUB = true;
    MULT = true;
    COM  = true;
    AND  = true;
    OR   = true;
    NOR  = true;
    XOR  = true;
    XNOR = true;
    CNF  = true;
  }
  /*
  if (SUM){
      graph.Extend(generatorSummator(i_bits, false, false, false, true));
      graph.Extend(generatorSummator(i_bits, false, true, false, true));
      graph.Extend(generatorSummator(i_bits, true, true, false, true));
      graph.Extend(generatorSummator(i_bits, true, false, false, true));
  }

  if (SUB){

      graph.Extend(generatorSubtractor(i_bits, false, false, false, true));
      graph.Extend(generatorSubtractor(i_bits, false, true, false, true));
      graph.Extend(generatorSubtractor(i_bits, true, false, false, true));
      graph.Extend(generatorSubtractor(i_bits, true, true, false, true));

  }

  if (NSUM)
  {
      graph.Extend(generatorSummator(i_bits, false, false, true, true));
      graph.Extend(generatorSummator(i_bits, false, true, true, true));
      graph.Extend(generatorSummator(i_bits, true, true, true, true));
      graph.Extend(generatorSummator(i_bits, true, false, true, true));

  }

  if (NSUB)
  {

      graph.Extend(generatorSubtractor(i_bits, false, false, true, true));
      graph.Extend(generatorSubtractor(i_bits, false, true, true, true));
      graph.Extend(generatorSubtractor(i_bits, true, false, true, true));
      graph.Extend(generatorSubtractor(i_bits, true, true, true, true));

  }

  if (MULT)
  {
      graph.Extend(generatorMultiplier(i_bits, true));
  }
  if (COM)
  {
      graph.Extend(generatorComparison(i_bits, true, false, false, true));
      graph.Extend(generatorComparison(i_bits, false, true, false, true));
      graph.Extend(generatorComparison(i_bits, false, false, true, true));
  }

  if (CNF)
  {
      TruthTable tt(i_bits, i_outbits, {});
      tt.generateRandom({i_bits, i_outbits});

      SimpleGenerators tftt;

      std::vector<std::pair<std::string, std::vector<std::string>>> circs;
      circs.push_back({"CNFT", tftt.cnfFromTruthTable(tt, true)});
      circs.push_back({"CNFF", tftt.cnfFromTruthTable(tt, false)});

      for (const auto& [name, expr] : circs)
      {
          Parser pCNFT(expr);
          pCNFT.parseAll();
          graph.Extend(pCNFT.getGraph());
      }

  }
  */
  for (int i = 0; i < i_bits; i++) {
    std::string A  = std::to_string(i);
    VertexPtr   xi = graph->addInput("xi" + A);
    VertexPtr   xj = graph->addInput("xj" + A);
    /*
    if (SUM)
    {
        graph.Substitute("xi" + A, "x_sumafff" + A, false);
        graph.Substitute("xj" + A, "x_sumbfff" + A, false);

        graph.Substitute("xi" + A, "x_sumaftf" + A, false);
        graph.Substitute("xj" + A, "x_sumbftf" + A, false);

        graph.Substitute("xi" + A, "x_sumattf" + A, false);
        graph.Substitute("xj" + A, "x_sumbttf" + A, false);

        graph.Substitute("xi" + A, "x_sumatff" + A, false);
        graph.Substitute("xj" + A, "x_sumbtff" + A, false);
    }

    if (SUB)
    {

        graph.Substitute("xi" + A, "x_subafff" + A, false);
        graph.Substitute("xj" + A, "x_subbfff" + A, false);

        graph.Substitute("xi" + A, "x_subaftf" + A, false);
        graph.Substitute("xj" + A, "x_subbftf" + A, false);

        graph.Substitute("xi" + A, "x_subatff" + A, false);
        graph.Substitute("xj" + A, "x_subbtff" + A, false);

        graph.Substitute("xi" + A, "x_subattf" + A, false);
        graph.Substitute("xj" + A, "x_subbttf" + A, false);

    }
    if (NSUM)
    {
        graph.Substitute("xi" + A, "x_sumafft" + A, false);
        graph.Substitute("xj" + A, "x_sumbfft" + A, false);

        graph.Substitute("xi" + A, "x_sumaftt" + A, false);
        graph.Substitute("xj" + A, "x_sumbftt" + A, false);

        graph.Substitute("xi" + A, "x_sumattt" + A, false);
        graph.Substitute("xj" + A, "x_sumbttt" + A, false);

        graph.Substitute("xi" + A, "x_sumatft" + A, false);
        graph.Substitute("xj" + A, "x_sumbtft" + A, false);
    }
    if (NSUB)
    {

        graph.Substitute("xi" + A, "x_subafft" + A, false);
        graph.Substitute("xj" + A, "x_subbfft" + A, false);

        graph.Substitute("xi" + A, "x_subaftt" + A, false);
        graph.Substitute("xj" + A, "x_subbftt" + A, false);

        graph.Substitute("xi" + A, "x_subatft" + A, false);
        graph.Substitute("xj" + A, "x_subbtft" + A, false);

        graph.Substitute("xi" + A, "x_subattt" + A, false);
        graph.Substitute("xj" + A, "x_subbttt" + A, false);

    }
    if (MULT)
    {
        graph.Substitute("xi" + A, "xa" + A, false);
        graph.Substitute("xj" + A, "xb" + A, false);
    }
    if (COM)
    {
        graph.Substitute("xi" + A, "comatffx_" + A, false);
        graph.Substitute("xj" + A, "combtffx_" + A, false);

        graph.Substitute("xi" + A, "comaftfx_" + A, false);
        graph.Substitute("xj" + A, "combftfx_" + A, false);

        graph.Substitute("xi" + A, "comafftx_" + A, false);
        graph.Substitute("xj" + A, "combfftx_" + A, false);
    }
    */
    if (AND) {
      VertexPtr and_ij = graph->addGate(Gates::GateAnd, "and_ij" + A);
      graph->addEdges({xi, xj}, and_ij);
    }
    if (NAND) {
      VertexPtr nand_ij = graph->addGate(Gates::GateNand, "nand_ij" + A);
      graph->addEdges({xi, xj}, nand_ij);
    }
    if (OR) {
      VertexPtr or_ij = graph->addGate(Gates::GateOr, "or_ij" + A);
      graph->addEdges({xi, xj}, or_ij);
    }
    if (XOR) {
      VertexPtr xor_ij = graph->addGate(Gates::GateXor, "xor_ij" + A);
      graph->addEdges({xi, xj}, xor_ij);
    }
    if (NOR) {
      VertexPtr nor_ij = graph->addGate(Gates::GateNor, "nor_ij" + A);
      graph->addEdges({xi, xj}, nor_ij);
    }
    if (XNOR) {
      VertexPtr xnor_ij = graph->addGate(Gates::GateXnor, "xnor_ij" + A);
      graph->addEdges({xi, xj}, xnor_ij);
    }
    /*
    if (CNF)
    {

        graph.Substitute("xi" + A, "xT" + A, false);
        graph.Substitute("xi" + A, "xF" + A, false);

    }
     */
  }
  return graph;
}

GraphPtr SimpleGenerators::generatorALU(
        int  i_bits,
        int  i_outbits,
        bool ALL,
        bool SUM,
        bool SUB,
        bool NSUM,
        bool NSUB,
        bool MULT,
        bool COM,
        bool AND,
        bool NAND,
        bool OR,
        bool NOR,
        bool XOR,
        bool XNOR,
        bool CNF
) {
    GraphPtr  graph(new OrientedGraph);
    VertexPtr const_0 = graph->addConst('0', "const_0");
    int       x       = 0;
    if (ALL) {
        SUM  = true;
        SUB  = true;
        NSUM = true;
        NSUB = true;
        MULT = true;
        COM  = true;
        AND  = true;
        OR   = true;
        XOR  = true;
        XNOR = true;
        CNF  = true;
    }

    // количество входов мультиплексора
    x = x + (SUM ? 4 : 0) + (SUB ? 4 : 0) + (NSUM ? 4 : 0) + (NSUB ? 4 : 0)
        + (MULT ? 1 : 0) + (COM ? 3 : 0) + (AND ? 1 : 0) + (NAND ? 1 : 0)
        + (OR ? 1 : 0) + (NOR ? 1 : 0) + (XOR ? 1 : 0) + (XNOR ? 1 : 0)
        + (CNF ? 3 : 0);

    int size = i_bits;
    size = MULT ? i_bits * 2 : (SUM || NSUM || SUB || NSUB ? i_bits + 1 : i_bits);
    if (CNF) {
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

    std::vector<VertexPtr>              inputs;
    std::vector<std::vector<VertexPtr>> outputs_gens;

    for (int a = 0; a < i_bits; a++) {
        std::string A  = std::to_string(a);
        VertexPtr   xi = graph->addInput("xi" + A);
        VertexPtr   xj = graph->addInput("xj" + A);

        inputs.push_back(xi);
        inputs.push_back(xj);

        if (AND) {
            VertexPtr and_ij = graph->addGate(Gates::GateAnd, "and_ij" + A);
            graph->addEdges({xi, xj}, and_ij);
        }
        if (NAND) {
            VertexPtr nand_ij = graph->addGate(Gates::GateNand, "nand_ij" + A);
            graph->addEdges({xi, xj}, nand_ij);
        }
        if (OR) {
            VertexPtr or_ij = graph->addGate(Gates::GateOr, "or_ij" + A);
            graph->addEdges({xi, xj}, or_ij);
        }
        if (XOR) {
            VertexPtr xor_ij = graph->addGate(Gates::GateXor, "xor_ij" + A);
            graph->addEdges({xi, xj}, xor_ij);
        }
        if (NOR) {
            VertexPtr nor_ij = graph->addGate(Gates::GateNor, "nor_ij" + A);
            graph->addEdges({xi, xj}, nor_ij);
        }
        if (XNOR) {
            VertexPtr xnor_ij = graph->addGate(Gates::GateXnor, "xnor_ij" + A);
            graph->addEdges({xi, xj}, xnor_ij);
        }
    }

    VertexPtr add;

    if (SUM) {
        std::vector<VertexPtr> output_sum;

        output_sum = graph->addSubGraph(generatorSummator(i_bits, false, false, false), inputs);
        outputs_gens.push_back(output_sum);
        output_sum = graph->addSubGraph(generatorSummator(i_bits, false, true, false),inputs);
        outputs_gens.push_back(output_sum);

        add = graph->addInput("ij_p0");
        inputs.insert(inputs.begin() + 2, add);

        output_sum = graph->addSubGraph(generatorSummator(i_bits, true, true,false), inputs);
        outputs_gens.push_back(output_sum);
        output_sum = graph->addSubGraph(generatorSummator(i_bits, true,false, false), inputs);
        outputs_gens.push_back(output_sum);

        inputs.erase(inputs.begin() + 2);
    }
    if (SUB) {
        std::vector<VertexPtr> output_sub;

        output_sub = graph->addSubGraph(generatorSubtractor(i_bits, false, false, false), inputs);
        outputs_gens.push_back(output_sub);
        output_sub = graph->addSubGraph(generatorSubtractor(i_bits, false, true, false),inputs);
        outputs_gens.push_back(output_sub);

        add = graph->addInput("ij_z0");
        inputs.insert(inputs.begin() + 2, add);

        output_sub = graph->addSubGraph(generatorSubtractor(i_bits, true, true,false), inputs);
        outputs_gens.push_back(output_sub);
        output_sub = graph->addSubGraph(generatorSubtractor(i_bits, true,false, false), inputs);
        outputs_gens.push_back(output_sub);

        inputs.erase(inputs.begin() + 2);
    }
    if (NSUM) {
        std::vector<VertexPtr> output_nsum;

        output_nsum = graph->addSubGraph(generatorSummator(i_bits, false, false, true),inputs);
        outputs_gens.push_back(output_nsum);
        output_nsum = graph->addSubGraph(generatorSummator(i_bits, false, true,true), inputs);
        outputs_gens.push_back(output_nsum);

        add = graph->addInput("ij_p0");
        inputs.insert(inputs.begin() + 2, add);

        output_nsum = graph->addSubGraph(generatorSummator(i_bits, true, true, true), inputs);
        outputs_gens.push_back(output_nsum);
        output_nsum = graph->addSubGraph(generatorSummator(i_bits, true, false, true),inputs);
        outputs_gens.push_back(output_nsum);

        inputs.erase(inputs.begin() + 2);
    }
    if (NSUB) {
        std::vector<VertexPtr> output_nsub;

        output_nsub = graph->addSubGraph(generatorSubtractor(i_bits, false, false, true),inputs);
        outputs_gens.push_back(output_nsub);
        output_nsub = graph->addSubGraph(generatorSubtractor(i_bits, false, true,true), inputs);
        outputs_gens.push_back(output_nsub);

        add = graph->addInput("ij_z0");
        inputs.insert(inputs.begin() + 2, add);

        output_nsub = graph->addSubGraph(generatorSubtractor(i_bits, true, true, true),inputs);
        outputs_gens.push_back(output_nsub);
        output_nsub = graph->addSubGraph(generatorSubtractor(i_bits, true, false,true), inputs);
        outputs_gens.push_back(output_nsub);

        inputs.erase(inputs.begin() + 2);
    }
    if (MULT) {
        std::vector<VertexPtr> output_mult;

        output_mult = graph->addSubGraph(generatorMultiplier(i_bits), inputs);
        outputs_gens.push_back(output_mult);
    }
    if (COM) {
        std::vector<VertexPtr> output_com;

        output_com = graph->addSubGraph(generatorComparison(i_bits, true, false, false),inputs);
        outputs_gens.push_back(output_com);
        output_com = graph->addSubGraph(generatorComparison(i_bits, false, true,false), inputs);
        outputs_gens.push_back(output_com);
        output_com = graph->addSubGraph(generatorComparison(i_bits, false,false, true), inputs);
        outputs_gens.push_back(output_com);
    }



    //
    //
    //    graph.Extend(ALU(i_bits, i_outbits, ALL, SUM, SUB, NSUM, NSUB, MULT,
    //    COM, AND, NAND, OR, NOR, XOR, XNOR, CNF));
    //
    //
    //    for (int j = 0; j < size; j++)
    //    {
    //        std::string T = std::to_string(j);
    //        graph.Extend(generatorMultiplexer(x, T));
    //        int c = 0;
    //        if (SUM)
    //        {
    //            for (int i = c; i < 4; i++)
    //            {
    //                std::string T1 = std::to_string(c); std::string T01 =
    //    std::to_string(i); c += 1; if (MULT ? (j == i_bits && (i == 0 || i ==
    //    2)) || j > i_bits : j == i_bits && (i == 0 || i == 2))
    //                {
    //                    graph.Substitute("0", "x" + T + "_" + T1, false);
    //                }
    //                else
    //                {
    //                    graph.Substitute("s" + T01 + "and1_" + T, "x" + T + "_"
    //                    + T1,
    //    false);
    //                }
    //
    //            }
    //
    //        }
    //        if (NSUM)
    //        {
    //            for (int i = c; i < 4; i++)
    //            {
    //                std::string T1 = std::to_string(c); std::string T01 =
    //    std::to_string(i); c += 1; if (MULT ? (j == i_bits && (i == 0 || i ==
    //    2)) || j > i_bits : j == i_bits && (i == 0 || i == 2))
    //                {
    //                    graph.Substitute("0", "x" + T + "_" + T1, false);
    //                }
    //                else
    //                {
    //                    graph.Substitute("ns" + T01 + "and1_" + T, "x" + T + "_"
    //                    + T1,
    //    false);
    //                }
    //            }
    //
    //
    //        }
    //        if (SUB)
    //        {
    //            for (int i = c; i < 4; i++)
    //            {
    //                std::string T1 = std::to_string(c); std::string T01 =
    //    std::to_string(i); c += 1; if (MULT ? (j == i_bits && (i == 0 || i ==
    //    2)) || j > i_bits : j == i_bits && (i == 0 || i == 2))
    //                {
    //                    graph.Substitute("0", "x" + T + "_" + T1, false);
    //                }
    //                else
    //                {
    //                    graph.Substitute("d" + T01 + "and1_" + T, "x" + T + "_"
    //                    + T1,
    //    false);
    //                }
    //            }
    //        }
    //        if (NSUB)
    //        {
    //            for (int i = c; i < 4; i++)
    //            {
    //                std::string T1 = std::to_string(c); std::string T01 =
    //    std::to_string(i); c += 1;
    //
    //                if (MULT ? (j == i_bits && (i == 0 || i == 2)) || j > i_bits
    //                : j
    //    == i_bits && (i == 0 || i == 2))
    //                {
    //                    graph.Substitute("0", "x" + T + "_" + T1, false);
    //                }
    //                else
    //                {
    //                    graph.Substitute("and" + T01 + "and1_" + T, "x" + T +
    //                    "_" +
    //    T1, false);
    //                }
    //            }
    //        }
    //        if (MULT)
    //        {
    //
    //            std::string T1 = std::to_string(c);
    //            c += 1;
    //            if (j >= i_bits * 2)
    //            {
    //                graph.Substitute("0", "x" + T + "_" + T1, false);
    //            }
    //            else
    //            {
    //                graph.Substitute("mand1_" + T, "x" + T + "_" + T1, false);
    //            }
    //
    //        }
    //        if (COM)
    //        {
    //            for (int i = c; i < 3; i++)
    //            {
    //                std::string T1 = std::to_string(c); std::string T01 =
    //    std::to_string(i); c += 1; if (j >= i_bits)
    //                {
    //                    graph.Substitute("0", "x" + T + "_" + T1, false);
    //                }
    //                else
    //                {
    //                    graph.Substitute("E" + T01 + "and1_" + T, "x" + T + "_"
    //                    + T1,
    //    false);
    //                }
    //
    //            }
    //        }
    //        if (AND)
    //        {
    //
    //            std::string T1 = std::to_string(c);
    //            if (j >= i_bits)
    //            {
    //                graph.Substitute("0", "x" + T + "_" + T1, false);
    //            }
    //            else
    //            {
    //                graph.Substitute("ij1_" + T, "x" + T + "_" + T1, false);
    //            }
    //
    //            c += 1;
    //
    //        }
    //        if (NAND)
    //        {
    //            std::string T1 = std::to_string(c);
    //            if (j >= i_bits)
    //            {
    //                graph.Substitute("0", "x" + T + "_" + T1, false);
    //            }
    //            else
    //            {
    //                graph.Substitute("ij2_" + T, "x" + T + "_" + T1, false);
    //            }
    //
    //            c += 1;
    //
    //        }
    //        if (OR)
    //        {
    //
    //            std::string T1 = std::to_string(c);
    //            if (j >= i_bits)
    //            {
    //                graph.Substitute("0", "x" + T + "_" + T1, false);
    //            }
    //            else
    //            {
    //                graph.Substitute("ij3_" + T, "x" + T + "_" + T1, false);
    //            }
    //
    //            c += 1;
    //
    //        }
    //        if (XOR)
    //        {
    //            std::string T1 = std::to_string(c);
    //            if (j >= i_bits)
    //            {
    //                graph.Substitute("0", "x" + T + "_" + T1, false);
    //            }
    //            else
    //            {
    //                graph.Substitute("ij5_" + T, "x" + T + "_" + T1, false);
    //            }
    //
    //            c += 1;
    //        }
    //        if (NOR)
    //        {
    //            std::string T1 = std::to_string(c);
    //            if (j >= i_bits)
    //            {
    //                graph.Substitute("0", "x" + T + "_" + T1, false);
    //            }
    //            else
    //            {
    //                graph.Substitute("ij4_" + T, "x" + T + "_" + T1, false);
    //            }
    //
    //            c += 1;
    //        }
    //        if (XNOR)
    //        {
    //            std::string T1 = std::to_string(c);
    //            if (j >= i_bits)
    //            {
    //                graph.Substitute("0", "x" + T + "_" + T1, false);
    //            }
    //            else
    //            {
    //                graph.Substitute("ij6_" + T, "x" + T + "_" + T1, false);
    //            }
    //
    //            c += 1;
    //        }
    //        if (CNF)
    //        {
    //            std::string T1 = std::to_string(c);
    //            if (j >= i_outbits)
    //            {
    //                graph.Substitute("0", "x" + T + "_" + T1, false);
    //                c += 1;
    //                T1 = std::to_string(c);
    //                graph.Substitute("0", "x" + T + "_" + T1, false);
    //            }
    //            else
    //            {
    //                graph.Substitute("fT" + T, "x" + T + "_" + T1, false);
    //                c += 1;
    //                T1 = std::to_string(c);
    //                graph.Substitute("fF" + T, "x" + T + "_" + T1, false);
    //            }
    //
    //        }
    //    }
    //
    return graph;
}
