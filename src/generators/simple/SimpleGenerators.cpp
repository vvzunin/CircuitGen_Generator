#include <algorithm>
#include <cassert>
#include <ctime>
#include <functional>
#include <iostream>
#include <stdexcept>

#include "SimpleGenerators.hpp"

#include <additional/AuxiliaryMethods.hpp>
#include <baseStructures/graph/OrientedGraph.hpp>
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

VertexPtr SimpleGenerators::multipleVerteciesToOne(
    std::vector<VertexPtr> curLayout,
    Gates                  operation,
    GraphPtr               graph
) {
  std::vector<VertexPtr> nextLayout;
  int32_t                curSize = 0;

  // Here we add operations in brackets
  while (curLayout.size() != 1) {
    curSize       = 0;

    size_t    pos = d_gatesInputsInfo[operation].size() - 1;
    VertexPtr x_input;
    VertexPtr oper;

    oper = graph->addGate(operation);
    // iterate through i layout
    for (size_t k = 0; k < curLayout.size(); ++k) {
      x_input = curLayout[k];

      graph->addEdge(x_input, oper);
      ++curSize;

      if (d_gatesInputsInfo[operation][pos] == curSize) {
        nextLayout.push_back(oper);

        // if we will have only one gate
        // we do not create a new operation
        if (k == (curLayout.size() - 2)) {
          oper = curLayout.back();
          // we save curSize for saving us from add
          // new edges to oper
          break;
        } else if (k < curLayout.size() - 1) {
          oper = graph->addGate(operation);
        }

        // if we have less elements than we can add, and our logical element
        // has too big gates number, move to lower
        int npos = pos;
        while (npos >= 0 && curSize < d_gatesInputsInfo[operation][npos]) {
          --npos;
        }
        // move if is neccesary
        npos += (curSize > d_gatesInputsInfo[operation][npos]) + (npos == -1);
        pos   = (npos < pos ? npos : pos);

        curSize = 0;
      }
    }

    // if we did not fill all gates
    if (curSize > 1) {
      // if we have less elements than we can add, and our logical element
      // has too big gates number, move to lower
      int npos = pos;
      while (npos >= 0 && curSize < d_gatesInputsInfo[operation][npos]) {
        --npos;
      }
      // move if is neccesary
      npos += (curSize > d_gatesInputsInfo[operation][npos]) + (npos == -1);
      pos   = (npos < pos ? npos : pos);

      while (curSize < d_gatesInputsInfo[operation][pos]) {
        graph->addEdge(x_input, oper);
        ++curSize;
      }
    }

    if (curSize)
      nextLayout.push_back(oper);

    // swap layouts
    curLayout = nextLayout;
    nextLayout.clear();
  }

  return curLayout.back();
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
  if (!d_gatesInputsInfo.count(Gates::GateAnd)
      && !d_gatesInputsInfo.count(Gates::GateOr)) {
    d_gatesInputsInfo[Gates::GateAnd] = {(int32_t)inputs.size()};
    d_gatesInputsInfo[Gates::GateOr]  = {(int32_t)inputs.size()};
  }

  std::map<VertexPtr, VertexPtr> inputs_not;
  VertexPtr                      constGate_0(nullptr), constGate_1(nullptr);

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

      nextLayoutExt.push_back(multipleVerteciesToOne(nextLayout, inter, graph));

      nextLayout.clear();
      ++tmp;
    }

    // and here operations with brackets
    graph->addEdge(multipleVerteciesToOne(nextLayoutExt, exter, graph), out);
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
            {graph->getVerticeByIndex(child2), graph->getVerticeByIndex(child1)
            },
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
    uint32_t i_minLevel,
    uint32_t i_maxLevel,
    uint32_t i_minElements,
    uint32_t i_maxElements,
    uint32_t i_inputs,
    uint32_t i_outputs
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
    // at the beginnig it is zero. So, if it stayed zero, we are still using
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
    int  bits,
    bool overflowIn,
    bool overflowOut,
    bool minus,
    bool act
) {
  GraphPtr graph(new OrientedGraph());
  // if (overflowIn)
  //     graph->addInput("p0");
  // if (act)
  //     graph->addConst('1');
  // std::string pi;
  // std::string x;
  // std::string y;
  // std::string z;
  // std::string cond = std::string(overflowIn ? "t" : "f") + (overflowOut ? "t"
  // : "f") + (minus ? "t" : "f"); z = std::string(minus ? "n" : "") + "s" +
  // (!overflowIn && !overflowOut ? "0" : (!overflowIn && overflowOut ? "1" :
  // (overflowIn && !overflowOut ? "2" : "3"))); for (int i = 0; i < bits; i++)
  // {
  //     std::string S = std::to_string(i);
  //     x = "suma" + cond + S;
  //     y = "sumb" + cond + S;
  //     VertexPtr input_x = graph->addInput(x);
  //     VertexPtr input_y = graph->addInput(y);
  //     if (minus)
  //     {
  //         VertexPtr v1 = graph->addGate(Gates::GateNot,
  //         "na" + S); VertexPtr v2 =
  //         graph->addVertex(Gates::GateNot, "nb" + S); graph->addEdge(input_x,
  //         v1, false); graph->addEdge(input_y, v2, false); x = "na" + S; y =
  //         "nb" + S;
  //     }
  //     if (!act)
  //     {
  //         graph->addOutput(z + S);
  //     }

  //     VertexPtr andab = graph->addGate(Gates::GateAnd,
  //     "andab" + S);

  //     std::string NextS = std::to_string(i + 1);
  //     pi = "p" + S;
  //     VertexPtr anda = graph->addGate(Gates::GateAnd,
  //     "anda" + pi); VertexPtr andb =
  //     graph->addGate(Gates::GateAnd, "andb" + pi);

  //     // PI ЗДЕСЬ НАДО ЗАМЕНИТЬ НА ССЫЛКУ НА НЕЁ
  //     graph->addEdge(input_x, input_y, andab);
  //     graph->addEdge(input_x, pi, anda);
  //     graph->addEdge(input_y, pi, andb);

  //     // TODO КАКОГО ЧЕРТА ВЕРШИНА ИДЕТ КАК РОДИТЕЛЬ, КОГДА ЕЁ ЕЩЁ НЕ СОЗДАЛИ
  //     // ВЫ СОЗДАЛИ p1, А p0 ЕЩЁ НЕТ
  //     graph->addVertex("((andab" + S + ")" + " or " + "(anda" + pi + ")" + "
  //     or " + "(andb" + pi + "))", Gates::GateOr, "p" + NextS);
  //     graph->addEdge("andab" + S, "p" + NextS, false);
  //     graph->addEdge("anda" + pi, "p" + NextS, false);
  //     graph->addEdge("andb" + pi, "p" + NextS, false);
  //     if (overflowOut && i + 1 == bits)
  //     {
  //         if (act)
  //         {
  //             graph->addVertex("(1 and p" + NextS + ")", Gates::GateAnd, z +
  //             "and1_" + NextS); graph->addDoubleEdge("1", "p" + NextS, z +
  //             "and1_" + NextS, false);
  //         }
  //         else
  //         {
  //             graph->addVertex(z + std::to_string(bits), "output");
  //             graph->addEdge("p" + NextS, z + std::to_string(bits), false);
  //         }
  //     }
  //     graph->addVertex("not (p" + NextS + ")", Gates::GateNot, "np" + NextS);
  //     graph->addEdge("p" + NextS, "np" + NextS, false);

  //     graph->addVertex("(" + x + " or " + y + " or " + pi + ")",
  //     Gates::GateOr, "abpor" + S); graph->addEdge(x, "abpor" + S, false);
  //     graph->addEdge(y, "abpor" + S, false);
  //     graph->addEdge(pi, "abpor" + S, false);

  //     graph->addVertex("(abpor" + S + " and np" + NextS + ")",
  //     Gates::GateAnd, "andnp" + NextS); graph->addDoubleEdge("abpor" + S,
  //     "np" + NextS, "andnp" + NextS, false);

  //     graph->addVertex("(" + x + " and " + y + " and " + pi + ")",
  //     Gates::GateAnd, "abpand" + S); graph->addEdge(x, "abpand" + S, false);
  //     graph->addEdge(y, "abpand" + S, false);
  //     graph->addEdge(pi, "abpand" + S, false);

  //     graph->addVertex("(abpand" + S + " or " + "andnp" + NextS + ")",
  //     Gates::GateOr, "pS" + S); graph->addDoubleEdge("abpand" + S, "andnp" +
  //     NextS, "pS" + S, false); if (act)
  //     {
  //         graph->addVertex("(1 and pS" + S + ")", Gates::GateAnd, z + "and1_"
  //         + S); graph->addDoubleEdge("1", "pS" + S, z + "and1_" + S, false);
  //     }
  //     else
  //     {
  //         graph->addEdge("pS" + S, z + S, false);
  //     }
  // }
  return graph;
}

GraphPtr SimpleGenerators::generatorComparison(
    int  bits,
    bool compare0,
    bool compare1,
    bool compare2,
    bool act
) {
  GraphPtr graph(new OrientedGraph());
  // VertexPtr prev_pn_;
  // std::string cond = std::string(compare0 ? "t" : "f") + (compare1 ? "t" :
  // "f") + (compare2 ? "t" : "f"); for (int i = bits - 1; i >= 0; i--)
  // {
  //     std::string C = std::to_string(i);
  //     std::string NextC = std::to_string(i - 1);
  //     std::string x = "coma" + cond + C;
  //     std::string y = "comb" + cond + C;
  //     if (i == 0)
  //     {
  //         NextC = "X";
  //     }
  //     VertexPtr input_x = graph->addInput(x);
  //     VertexPtr input_y = graph->addInput(y);
  //     VertexPtr nb = graph->addGate(Gates::GateNot,
  //     "nb" + C); graph->addEdge(input_y, "nb" + C);
  //     VertexPtr na = graph->addGate(Gates::GateNot,
  //     "na" + C); graph->addEdge(input_x, "na" + C, false);

  //     VertexPtr const_1;
  //     if (act)
  //     {
  //         const_1 = graph->addConst('1');
  //     }
  //     VertexPtr En_;
  //     VertexPtr pn_;
  //     VertexPtr Enand1_;
  //     VertexPtr pEn_;
  //     if (compare0)
  //     {
  //         if (!act)
  //         {
  //             // TODO this is made like for three times, is it
  //             // possible to move it in upper part?
  //             En_ = graph->addOutput("E0_" + C);
  //         }
  //         VertexPtr nab =
  //         graph->addGate(Gates::GateAnd, "nab" + C);
  //         VertexPtr ab =
  //         graph->addVertex(Gates::GateAnd, "ab" + C); pn_ =
  //         graph->addVertex(Gates::GateOr, "p0_" + NextC);
  //         graph->addEdges({na, nb}, nab); graph->addEdges({input_x, input_y},
  //         ab); graph->addEdges({nab, ab}, pn_);

  //         // in case of first iteration
  //         if (i == bits - 1)
  //         {
  //             if (act)
  //             {
  //                 Enand1_ = graph->addGate(Gates::GateAnd, "E0and1_" + C);
  //                 graph->addEdges({const_1, pn_}, Enand1_);
  //             }
  //             else
  //             {
  //                 graph->addEdge(pn_, En_);
  //             }
  //         }
  //         else
  //         {
  //             pEn_ = graph->addGate(Gates::GateAnd, "pE0_" + C);
  //             graph->addEdge({prev_pn_, pn_}, pEn_);
  //             if (act)
  //             {
  //                 Enand1_ = graph->addGate(Gates::GateAnd, "E0and1_" + C);
  //                 graph->addEdges({const_1, pEn_}, Enand1_);
  //             }
  //             else
  //             {
  //                 graph->addEdge(pEn_, En_);
  //             }
  //         }
  //         prev_pn_ = pn_;
  //     }
  //     if (compare1)
  //     {
  //         if (!act)
  //         {
  //             En_ = graph->addOutput("E1_" + C);
  //         }

  //         pn_ = graph->addGate(Gates::GateAnd, "p1_" + NextC);
  //         graph->addEdges({input_x, nb}, pn_);

  //         // in case of first iteration
  //         if (i == bits - 1)
  //         {
  //             if (act)
  //             {
  //                 Enand1_ = graph->addVertex(Gates::GateAnd, "E1and1_" + C);
  //                 graph->addEdges({const_1, pn_}, Enand1_);
  //             }
  //             else
  //             {
  //                 graph->addEdge(pn_, En_);
  //             }
  //         }
  //         else
  //         {
  //             VertexPtr np1_ =
  //             graph->addGate(Gates::GateNot, "np1_" + C);
  //             VertexPtr np1_next =
  //             graph->addGate(Gates::GateNot, "np1_" + NextC);
  //             graph->addEdge(prev_pn_, np1_); graph->addEdge(pn_, np1_next);
  //             VertexPtr P11_ =
  //             graph->addGate(Gates::GateAnd, "P11_" + C);
  //             graph->addEdges({np1_, pn1_}, P11_);
  //             VertexPtr P12_ =
  //             graph->addGate(Gates::GateAnd, "P12_" + C);
  //             graph->addEdges({prev_pn_, np1_next}, P12_);
  //             pEn_ = graph->addGate(Gates::GateOr, "pE1_" + C);
  //             graph->addEdges({P11_, P12_}, pEn_);
  //             if (act)
  //             {
  //                 Enand1_ = graph->addGate(Gates::GateAnd, "E1and1_" + C);
  //                 graph->addEdges({const_1, pEn_}, Enand1_);
  //             }
  //             else
  //             {
  //                 graph->addEdge(pEn_, En_);
  //             }
  //         }
  //         prev_pn_ = pn_;
  //     }
  //     if (compare2)
  //     {
  //         if (!act)
  //         {
  //             En_ = graph->addOutput("E2_" + C);
  //         }
  //         pn_ = graph->addGate(Gates::GateAnd, "p2_" + NextC);
  //         graph->addEdges(input_y, na, pn_);

  //         // first iteration
  //         if (i == bits - 1)
  //         {
  //             if (act)
  //             {
  //                 Enand1_ = graph->addVertex(Gates::GateAnd, "E2and1_" + C);
  //                 graph->addEdges({const_1, pn_}, Enand1_);
  //             }
  //             else
  //             {
  //                 graph->addEdge(pn_, En_);
  //             }
  //         }
  //         else
  //         {
  //             VertexPtr np2_ =
  //             graph->addGate(Gates::GateNot, "np2_" + C);
  //             VertexPtr np2_next =
  //             graph->addGate(Gates::GateNot, "np2_" + NextC);
  //             graph->addEdge(prev_pn_, np2_); graph->addEdge(pn_, np2_next);
  //             VertexPtr P21_ =
  //             graph->addVertex(Gates::GateAnd, "P21_"
  //             + C); graph->addEdges({np2_, np2_next}, P21_);
  //             VertexPtr P22_ =
  //             graph->addVertex(Gates::GateAnd, "P22_" + C);
  //             graph->addEdges({prev_pn_, np2_next}, P22_);
  //             pEn_ = graph->addVertex(Gates::GateOr, "pE2_" + C);
  //             graph->addEdges({P21_, P22_}, pEn_);
  //             if (act)
  //             {
  //                 Enand1_ = graph->addGate(Gates::GateAnd, "E2and1_" + C);
  //                 graph->addEdges({const_1, pEn_}, Enand1_);
  //             }
  //             else
  //             {
  //                 graph->addEdge(pEn_, En_);
  //             }
  //         }
  //         prev_pn_ = pn_;
  //     }
  // }
  return graph;
}

GraphPtr SimpleGenerators::generatorEncoder(int bits) {
  GraphPtr graph;
  // int k = 0;
  // for (int t = 0; t <= bits; t++)
  //     if (bits - 1 >= pow(2, t))
  //     {
  //         k = k + 1;
  //     }
  // for (int l = 0; l <= bits - 1; l++)
  // {
  //     std::string Z = std::to_string(l);
  //     graph->addInput("x" + Z);
  // }
  // if (bits > 1)
  //     for (int p = k - 1; p >= 0; p--)
  //     {
  //         std::string L = "";
  //         std::string P = "";
  //         std::string M = "";
  //         std::string K = "";
  //         std::string S = std::to_string(p);
  //         VertexPtrout = graph->addOutput("a" + S);

  //         for (int i = 0; i <= bits - 1; i++)
  //             for (double t = pow(2, p); t <= pow(2, p + 1) - 1; t++)
  //                 if (pow(2, p + 1) * i + t <= bits - 1)
  //                 {
  //                     std::string R = std::to_string(pow(2, p + 1) * i + t);
  //                     K = M + " or x" + R;
  //                     L = P + "orx" + R;
  //                     // graph->addEdge("x" + R, "a" + S, false);
  //                     P = L;
  //                     L = "";
  //                     M = K;
  //                     K = "";
  //                 }
  //         M = M.erase(0, 3);

  //         // TODO solve this name strange thing
  //         // VertexPtrP_ref = graph->addVertex(M,
  //         Gates::GateOr, P); VertexPtrP_ref =
  //         graph->addVertex(Gates::GateOr, P); for (int i = 0; i <= bits - 1;
  //         i++)
  //             for (double t = pow(2, p); t <= pow(2, p + 1) - 1; t++)
  //                 if (pow(2, p + 1) * i + t <= bits - 1)
  //                 {
  //                     std::string R = std::to_string(pow(2, p + 1) * i + t);
  //                     // here getting input number R
  //                     graph->addEdge(graph->getVerticeByIndex(R), P_ref);
  //                 }
  //         graph->addEdge(P_ref, out);
  //     }
  // else
  //    std::cout << "Недостаточно входных сигналов\n";

  return graph;
}