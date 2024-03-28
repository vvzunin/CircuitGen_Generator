#include "SimpleGenerators.h"

#include <additional/AuxiliaryMethods.h>
#include <baseStructures/graph/OrientedGraph.h>
#include <math.h>

#include <algorithm>
#include <cassert>
#include <ctime>
#include <functional>
#include <iostream>
#include <stdexcept>

int SimpleGenerators::getRangomAndNumber() {
  return d_gatesInputsInfo[Gates::GateAnd][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateAnd].size())];
}

int SimpleGenerators::getRangomOrNumber() {
  return d_gatesInputsInfo[Gates::GateOr][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateOr].size())];
}

int SimpleGenerators::getRangomNandNumber() {
  return d_gatesInputsInfo[Gates::GateNand][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateNand].size())];
}

int SimpleGenerators::getRangomNorNumber() {
  return d_gatesInputsInfo[Gates::GateNor][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateNor].size())];
}

int SimpleGenerators::getRangomXorNumber() {
  return d_gatesInputsInfo[Gates::GateXor][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateXor].size())];
}

int SimpleGenerators::getRangomXnorNumber() {
  return d_gatesInputsInfo[Gates::GateXnor][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateXnor].size())];
}

std::pair<Gates, int> SimpleGenerators::getRandomElement(
    const GatesInfo &i_info) {
  // rand element of map
  auto val = i_info.begin();
  std::advance(val, d_randGenerator.getRandInt(0, i_info.size()));

  // random gate number from of random element
  return std::make_pair(
      val->first,
      val->second[d_randGenerator.getRandInt(0, val->second.size())]);
}

std::pair<Gates, int> SimpleGenerators::getRandomElement(
    u_int32_t i_gatesLimit) {
  if (i_gatesLimit >= d_maxGateNumber)
    return getRandomElement(d_gatesInputsInfo);

  if (i_gatesLimit <= 1)
    return std::make_pair(
        d_randGenerator.getRandInt(0, 2) ? Gates::GateNot : Gates::GateBuf, 1);

  GatesInfo info;
  std::vector<int> subval;

  for (auto [key, value] : d_gatesInputsInfo) {
    for (int i = 0; i < value.size() && value[i] <= i_gatesLimit; ++i)
      subval.push_back(value[i]);

    if (subval.size()) info[key] = std::move(subval);
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

std::vector<std::string> SimpleGenerators::cnfFromTruthTable(
    const TruthTable &i_table, bool i_tp) {
  // std::clog << getRangomAndNumber() << " ";
  // std::clog << getRangomNandNumber() << " ";
  // std::clog << getRangomOrNumber() << " ";
  // std::clog << getRangomNorNumber() << " ";
  // std::clog << getRangomXorNumber() << " ";
  // std::clog << getRangomXnorNumber() << std::endl;

  std::vector<std::string> fun;
  fun.reserve(i_table.getOutput());
  std::vector<std::vector<bool>> bin = i_table.convToBinary();

  for (int j = 0; j < i_table.getOutput(); ++j) {
    fun.push_back("f" + std::to_string(j) + " = ");
    int mem = 0;
    int tmp = 0;

    for (int i = 0; i < i_table.size(); ++i) {
      if (!(i_table.getOutTable(i, j) ^ i_tp)) mem++;
    }

    if (mem == 0) {
      if (i_tp)
        fun[j] += "1'b0";
      else
        fun[j] += "1'b1";
      continue;
    }

    if (mem == i_table.size()) {
      if (i_tp)
        fun[j] += "1'b1";
      else
        fun[j] += "1'b0";
      continue;
    }

    for (int i = 0; i < mem; ++i) {
      fun[j] += '(';
      while ((i_table.getOutTable(tmp, j) ^ i_tp) && tmp < i_table.size())
        tmp++;

      for (int k = 0; k < i_table.getInput(); ++k) {
        if (bin[tmp][k] ^ i_tp)
          fun[j] += d_settings->getLogicOperation("not").first + " ";

        fun[j] += 'x';
        fun[j] += std::to_string(k);

        if (k != i_table.getInput() - 1)
          fun[j] += " " +
                    (i_tp ? d_settings->getLogicOperation("and").first
                          : d_settings->getLogicOperation("or").first) +
                    " ";
      }

      fun[j] += ')';

      if (i != mem - 1)
        fun[j] += " " +
                  (i_tp ? d_settings->getLogicOperation("or").first
                        : d_settings->getLogicOperation("and").first) +
                  " ";

      tmp++;
    }
  }

  return fun;
}

OrientedGraph SimpleGenerators::generatorRandLevel(
    int i_minLevel, int i_maxLevel, int i_minElements, int i_maxElements,
    int i_inputs, int i_outputs) {
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

  int choice;
  std::string expr;
  OrientedGraph graph;
  int child1, child2;

  for (int i = 0; i < i_inputs; ++i) {
    expr = "x" + std::to_string(i);
    graph.addInput(expr);
  }

  int currIndex = i_inputs;
  int prevIndex = 0;

  for (int i = 1; i < maxLevel; ++i) {
    int position = 0;
    // how many elements would be at this level
    int elemLevel = i_maxElements > 1
                        ? d_randGenerator.getRandInt(i_minElements, i_maxElements, true)
                        : 2;

    for (int j = 0; j < elemLevel; ++j) {
      choice = d_randGenerator.getRandInt(0, logOper.size());

      if (hasOneGate[choice]) {
        child1 = d_randGenerator.getRandInt(0, currIndex);

        std::shared_ptr<GraphVertexBase>newVertex = graph.addGate(logOper[choice]);
        graph.addEdge(graph.getVerticeByIndex(child1), newVertex);

      } else {
        child1 = d_randGenerator.getRandInt(prevIndex, currIndex);
        child2 = d_randGenerator.getRandInt(prevIndex, currIndex);

        std::shared_ptr<GraphVertexBase>newVertex = graph.addGate(logOper[choice]);
        graph.addEdges(
            {graph.getVerticeByIndex(child2), graph.getVerticeByIndex(child1)},
            newVertex);
      }
      ++position;
    }

    prevIndex += currIndex - prevIndex;
    currIndex += position;

    std::clog << i / (float)maxLevel * 100 << "%" << std::endl;
  }

  // TODO: fix when elements less than outputs

  for (int i = 0; i < i_outputs; ++i) {
    child1 = d_randGenerator.getRandInt(prevIndex, currIndex);
    expr = "f" + std::to_string(i + 1);
    std::shared_ptr<GraphVertexBase>newVertex = graph.addOutput(expr);
    graph.addEdge(graph.getVerticeByIndex(child1), newVertex);
  }

  return graph;
}

OrientedGraph SimpleGenerators::generatorRandLevelExperimental(
    u_int32_t i_minLevel, u_int32_t i_maxLevel, u_int32_t i_minElements,
    u_int32_t i_maxElements, u_int32_t i_inputs, u_int32_t i_outputs) {
  u_int32_t maxLevel;
  if (i_minLevel > i_maxLevel)
    throw std::invalid_argument("min level is biggert than max level");
  if (i_minElements > i_maxElements)
    throw std::invalid_argument("min elem is biggert than max elem");

  if (i_maxLevel)
    maxLevel = d_randGenerator.getRandInt(i_minLevel, i_maxLevel, true) + 1;
  else
    maxLevel = 1;

  std::string expr;
  OrientedGraph graph;

  for (int i = 0; i < i_inputs; ++i) {
    expr = "x" + std::to_string(i);
    graph.addInput(expr);
  }
  // we need it because we:
  // a) can have less possible parents at current level, than is required by
  // minimum gates number of a logical element, so we can use inputs in such
  // case
  // b) need to swap gates
  std::vector<std::shared_ptr<GraphVertexBase>> inputs =
      graph.getVerticesByType(VertexTypes::input);

  // TODO what if we will need to use n-gate elements, should we add consts
  // usage?

  int currIndex = i_inputs;
  int prevIndex = 0;
  int curLen = 0;
  // we need lowest border as d_maxGateNumber, and if it is possible,
  // we set it (it changes speed of generation)
  u_int32_t c_max = i_maxElements > d_maxGateNumber
                        ? std::max(d_maxGateNumber, (int)i_minElements)
                        : i_minElements;

  for (int i = 1; i < maxLevel; ++i) {
    int position = 0;
    // how many elements would be at this level
    int elemLevel = i_maxElements > 1
                        ? d_randGenerator.getRandInt(c_max, i_maxElements, true)
                        : i_minElements;

    // write allowed gates to be used as parent
    std::vector<std::shared_ptr<GraphVertexBase>> curGates;
    for (int val = prevIndex; val < currIndex; ++val)
      curGates.push_back(graph.getVerticeByIndex(val));
    curLen += curGates.size();

    for (int j = 0; j < elemLevel; ++j) {
      // we use inputs only if we are not on the first level
      auto [operation, gatesNumber] = getRandomElement(curLen);
      // from which element we should start shuffle
      // like we do not shuffle whole list, if it is possible
      // but only it's part
      int fromWhichShuffle = d_randGenerator.getRandInt(
          0, std::max(0, (int)curGates.size() - gatesNumber));
      // shuffle curGates
      for (int k = fromWhichShuffle,
               stopVal = std::min(fromWhichShuffle + gatesNumber,
                                  (int)curGates.size());
           k < stopVal; ++k) {
        std::swap(curGates[k],
                  curGates[d_randGenerator.getRandInt(0, curGates.size())]);
      }

      if (gatesNumber == 1) {
        int child1 = d_randGenerator.getRandInt(0, currIndex);

        std::shared_ptr<GraphVertexBase>newVertex = graph.addGate(operation);
        graph.addEdge(graph.getVerticeByIndex(child1), newVertex);
      } else {
        // parents vertexes to be added for a new one
        std::vector<std::shared_ptr<GraphVertexBase>> parents;
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
            // and we added some verticies, e.g. we are not on the first level
            if (i > 1) {
              for (int k = 0; k < inputs.size(); ++k)
                std::swap(inputs[k],
                          inputs[d_randGenerator.getRandInt(0, inputs.size())]);

              idx = inputs.begin();
            } else {
              idx = curGates.begin();
            }
          } else if (idx == inputs.end())
            idx = curGates.begin();
        }

        std::shared_ptr<GraphVertexBase>newVertex = graph.addGate(operation);
        graph.addEdges(parents, newVertex);
      }
      ++position;
    }

    prevIndex += currIndex - prevIndex;
    currIndex += position;
    curLen = inputs.size();

    std::clog << (float)i / (float)maxLevel * 100 << "%" << std::endl;
  }

  std::clog << "writting out gates" << std::endl;
  for (int i = 0; i < i_outputs; ++i) {
    int child1 = d_randGenerator.getRandInt(prevIndex, currIndex);
    expr = "f" + std::to_string(i + 1);
    std::shared_ptr<GraphVertexBase>newVertex = graph.addOutput(expr);

    graph.addEdge(graph.getVerticeByIndex(child1), newVertex);
  }

  std::clog << "writting out gates ended" << std::endl;
  return graph;
}

OrientedGraph SimpleGenerators::generatorNumOperation(
    int i_input, int i_output, std::map<Gates, int> i_logicOper,
    bool i_leaveEmptyOut) {
  int sumOper = 0, maxLvl;
  std::string name;
  std::shared_ptr<GraphVertexBase> name_ptr;
  std::map<Gates, int> copyLogicOper;
  std::map<std::shared_ptr<GraphVertexBase>, int> levelName;
  std::vector<std::shared_ptr<GraphVertexBase>> nameOut, nameInput;

  for (const auto &elem : i_logicOper) {
    std::cout << elem.first << " " << elem.second << "\n";
  }

  copyLogicOper = i_logicOper;

  OrientedGraph graph;

  for (int i = 0; i < i_input; ++i) {
    name = "x" + std::to_string(i);
    name_ptr = graph.addInput(name);

    // TODO and how can it be changed?
    levelName[name_ptr] = name_ptr->getLevel();
    if (!i_leaveEmptyOut) nameInput.push_back(name_ptr);
  }

  for (int i = 0; i < i_output; ++i) {
    name = "f" + std::to_string(i);
    name_ptr = graph.addOutput(name);
    nameOut.push_back(name_ptr);
  }

  for (const auto &[key, value] : copyLogicOper) sumOper += value;

  copyLogicOper = delNull(copyLogicOper);
  // TODO it is TOO slow
  for (int i = 0; i < sumOper; ++i) {
    // TODO: optimize
    // TODO change whole gen
    Gates oper = randomGenerator(copyLogicOper);
    --copyLogicOper[oper];

    if (oper == Gates::GateNot || oper == Gates::GateBuf) {
      std::shared_ptr<GraphVertexBase> ver1 = randomGenerator(levelName);
      // name = d_settings->getLogicOperation(oper).first + "(" + ver1 + ")";
      name_ptr = graph.addGate(oper);
      graph.addEdge(ver1, name_ptr);
    } else {
      std::shared_ptr<GraphVertexBase> ver1 = randomGenerator(levelName);
      std::shared_ptr<GraphVertexBase> ver2 = randomGenerator(levelName);
      // name = "(" + ver1 + ") " + d_settings->getLogicOperation(oper).first +
      //        "(" + ver2 + ")";

      // WTF this is not used AT ALL
      // std::string reserveName = "(" + ver2 + ") " +
      //                           d_settings->getLogicOperation(oper).first +
      //                           "(" + ver1 + ")";

      name_ptr = graph.addGate(oper);
      graph.addEdges({ver1, ver2}, name_ptr);
      levelName[name_ptr] = name_ptr->getLevel();
    }

    if (!copyLogicOper[oper]) copyLogicOper.erase(oper);
  }

  while ((nameOut.size() > 0) &
         ((levelName.size() > 0 || i_leaveEmptyOut == false))) {
    if (levelName.size() > 0) {
      std::vector<std::shared_ptr<GraphVertexBase>> help;
      maxLvl = maxValueInMap(levelName);

      for (const auto &[key, value] : levelName) {
        if (value == maxLvl) help.push_back(key);
      }

      while (help.size() > 0 && nameOut.size() > 0) {
        int R1 = d_randGenerator.getRandInt(0, help.size());
        int R2 = d_randGenerator.getRandInt(0, nameOut.size());
        graph.addEdge(help[R1], nameOut[R2]);
        levelName.erase(help[R1]);
        help.erase(help.begin() + R1);
        nameOut.erase(nameOut.begin() + R2);
      }
    } else {
      int R1 = d_randGenerator.getRandInt(0, nameInput.size());
      int R2 = d_randGenerator.getRandInt(0, nameOut.size());

      graph.addEdge(nameInput[R1], nameOut[R2]);
      nameOut.erase(nameOut.begin() + R2);
    }
  }
  return graph;
}

std::map<Gates, int> SimpleGenerators::delNull(
    std::map<Gates, int> i_copyLogicOper) {
  std::vector<Gates> delList;
  for (const auto &[key, value] : i_copyLogicOper)
    if (value == 0) delList.push_back(key);

  for (const auto &op : delList) i_copyLogicOper.erase(op);
  return i_copyLogicOper;
}

OrientedGraph SimpleGenerators::generatorSummator(int bits, bool overflowIn, bool overflowOut, bool minus, bool act)
{
    OrientedGraph graph;
    if (overflowIn)
        graph.addInput("p0");
    if (act)
        graph.addConst('1', "1");
    std::string pi;
    std::string x;
    std::string y;
    std::string z;
    std::string cond = std::string(overflowIn ? "t" : "f") + (overflowOut ? "t" : "f") + (minus ? "t" : "f");
    z = std::string(minus ? "n" : "") + "s" + (!overflowIn && !overflowOut ? "0" : (!overflowIn && overflowOut ? "1" : (overflowIn && !overflowOut ? "2" : "3")));
    for (int i = 0; i < bits; i++)
    {
        std::string S = std::to_string(i);
        x = "x_suma" + cond + S;
        y = "x_sumb" + cond + S;
        std::shared_ptr<GraphVertexBase> input_x = graph.addInput(x);
        std::shared_ptr<GraphVertexBase> input_y = graph.addInput(y);
        if (minus)
        {
            std::shared_ptr<GraphVertexBase> v1 = graph.addGate(Gates::GateNot, "na" + S);
            std::shared_ptr<GraphVertexBase> v2 = graph.addGate(Gates::GateNot, "nb" + S);
            graph.addEdge(input_x, v1);
            graph.addEdge(input_y, v2);
            x = "na" + S;
            y = "nb" + S;
        }
         if (!act)
        {
            graph.addOutput(z + S);
        }

        std::shared_ptr<GraphVertexBase> andab = graph.addGate(Gates::GateAnd, "andab" + S);

        std::string NextS = std::to_string(i + 1);
        pi = "x_p" + S;
        std::shared_ptr<GraphVertexBase> anda = graph.addGate(Gates::GateAnd, "anda" + pi);
        std::shared_ptr<GraphVertexBase> andb = graph.addGate(Gates::GateAnd, "andb" + pi);
        std::shared_ptr<GraphVertexBase> pi_vertex = graph.addGate(Gates::GateAnd, "andb" + pi);

        graph.addEdges({input_x, input_y}, andab);
        graph.addEdges({input_x, pi_vertex}, anda);
        graph.addEdges({input_y, pi_vertex}, andb);

        std::shared_ptr<GraphVertexBase> or_vertex = graph.addGate(Gates::GateOr, "or" + NextS);
        graph.addEdges({andab, anda, andb}, or_vertex);
        graph.addOutput(or_vertex->getName());

        if (overflowOut && i + 1 == bits)
        {
            if (act)
            {
                
                std::shared_ptr<GraphVertexBase> and_vertex = graph.addGate(Gates::GateAnd, z + "and1_" + NextS);
                graph.addEdges({graph.getVerticesByName("1")[0], or_vertex}, and_vertex);
                graph.addOutput(and_vertex->getName());
            }
            else
            {
                graph.addOutput(z + std::to_string(bits));
                graph.addEdge(pi_vertex, graph.getVerticesByName(z + std::to_string(bits))[0]);
            }
        }

        std::shared_ptr<GraphVertexBase> not_pi_vertex = graph.addGate(Gates::GateNot, "np" + NextS);
        graph.addEdge(pi_vertex, not_pi_vertex);

        std::shared_ptr<GraphVertexBase> or_vertex2 = graph.addGate(Gates::GateOr, "or2" + S);
        graph.addEdges({input_x, input_y, pi_vertex}, or_vertex2);

        std::shared_ptr<GraphVertexBase> and_vertex2 = graph.addGate(Gates::GateAnd, "andnp" + NextS);
        graph.addEdges({or_vertex2, not_pi_vertex}, and_vertex2);
        graph.addOutput(and_vertex2->getName());

        std::shared_ptr<GraphVertexBase> or_vertex3 = graph.addGate(Gates::GateOr, "or3" + S);
        graph.addEdges({or_vertex, and_vertex2}, or_vertex3);

        if (act)
        {
            std::shared_ptr<GraphVertexBase> and_vertex3 = graph.addGate(Gates::GateAnd, z + "and1_" + S);
            graph.addEdges({graph.getVerticesByName("1")[0], or_vertex3}, and_vertex3);
            graph.addOutput(and_vertex3->getName());
        }
        else
        {
            graph.addOutput(z + S);
            graph.addEdge(or_vertex3, graph.getVerticesByName(z + S)[0]);
        }
    }
    return graph;
}

OrientedGraph SimpleGenerators::generatorComparison(int bits, bool compare0,
                                                    bool compare1,
                                                    bool compare2, bool act) {
  OrientedGraph graph;
  // std::shared_ptr<GraphVertexBase> prev_pn_;
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
  //     std::shared_ptr<GraphVertexBase> input_x = graph.addInput(x);
  //     std::shared_ptr<GraphVertexBase> input_y = graph.addInput(y);
  //     std::shared_ptr<GraphVertexBase> nb = graph.addGate(Gates::GateNot,
  //     "nb" + C); graph.addEdge(input_y, "nb" + C);
  //     std::shared_ptr<GraphVertexBase> na = graph.addGate(Gates::GateNot,
  //     "na" + C); graph.addEdge(input_x, "na" + C, false);

  //     std::shared_ptr<GraphVertexBase> const_1;
  //     if (act)
  //     {
  //         const_1 = graph.addConst('1');
  //     }
  //     std::shared_ptr<GraphVertexBase> En_;
  //     std::shared_ptr<GraphVertexBase> pn_;
  //     std::shared_ptr<GraphVertexBase> Enand1_;
  //     std::shared_ptr<GraphVertexBase> pEn_;
  //     if (compare0)
  //     {
  //         if (!act)
  //         {
  //             // TODO this is made like for three times, is it
  //             // possible to move it in upper part?
  //             En_ = graph.addOutput("E0_" + C);
  //         }
  //         std::shared_ptr<GraphVertexBase> nab =
  //         graph.addGate(Gates::GateAnd, "nab" + C);
  //         std::shared_ptr<GraphVertexBase> ab =
  //         graph.addVertex(Gates::GateAnd, "ab" + C);
  //         pn_ = graph.addVertex(Gates::GateOr, "p0_" + NextC); graph.addEdges({na, nb}, nab); graph.addEdges({input_x, input_y}, ab);
  //         graph.addEdges({nab, ab}, pn_);

  //         // in case of first iteration
  //         if (i == bits - 1)
  //         {
  //             if (act)
  //             {
  //                 Enand1_ = graph.addGate(Gates::GateAnd, "E0and1_" + C);
  //                 graph.addEdges({const_1, pn_}, Enand1_);
  //             }
  //             else
  //             {
  //                 graph.addEdge(pn_, En_);
  //             }
  //         }
  //         else
  //         {
  //             pEn_ = graph.addGate(Gates::GateAnd, "pE0_" + C);
  //             graph.addEdge({prev_pn_, pn_}, pEn_);
  //             if (act)
  //             {
  //                 Enand1_ = graph.addGate(Gates::GateAnd, "E0and1_" + C);
  //                 graph.addEdges({const_1, pEn_}, Enand1_);
  //             }
  //             else
  //             {
  //                 graph.addEdge(pEn_, En_);
  //             }
  //         }
  //         prev_pn_ = pn_;
  //     }
  //     if (compare1)
  //     {
  //         if (!act)
  //         {
  //             En_ = graph.addOutput("E1_" + C);
  //         }

  //         pn_ = graph.addGate(Gates::GateAnd, "p1_" + NextC);
  //         graph.addEdges({input_x, nb}, pn_);

  //         // in case of first iteration
  //         if (i == bits - 1)
  //         {
  //             if (act)
  //             {
  //                 Enand1_ = graph.addVertex(Gates::GateAnd, "E1and1_" + C);
  //                 graph.addEdges({const_1, pn_}, Enand1_);
  //             }
  //             else
  //             {
  //                 graph.addEdge(pn_, En_);
  //             }
  //         }
  //         else
  //         {
  //             std::shared_ptr<GraphVertexBase> np1_ =
  //             graph.addGate(Gates::GateNot, "np1_" + C);
  //             std::shared_ptr<GraphVertexBase> np1_next = graph.addGate(Gates::GateNot, "np1_" + NextC);
  //             graph.addEdge(prev_pn_, np1_); graph.addEdge(pn_, np1_next);
  //             std::shared_ptr<GraphVertexBase> P11_ = graph.addGate(Gates::GateAnd, "P11_" + C);
  //             graph.addEdges({np1_, pn1_}, P11_);
  //             std::shared_ptr<GraphVertexBase> P12_ =
  //             graph.addGate(Gates::GateAnd, "P12_" + C);
  //             graph.addEdges({prev_pn_, np1_next}, P12_);
  //             pEn_ = graph.addGate(Gates::GateOr, "pE1_" + C);
  //             graph.addEdges({P11_, P12_}, pEn_);
  //             if (act)
  //             {
  //                 Enand1_ = graph.addGate(Gates::GateAnd, "E1and1_" + C);
  //                 graph.addEdges({const_1, pEn_}, Enand1_);
  //             }
  //             else
  //             {
  //                 graph.addEdge(pEn_, En_);
  //             }
  //         }
  //         prev_pn_ = pn_;
  //     }
  //     if (compare2)
  //     {
  //         if (!act)
  //         {
  //             En_ = graph.addOutput("E2_" + C);
  //         }
  //         pn_ = graph.addGate(Gates::GateAnd, "p2_" + NextC);
  //         graph.addEdges(input_y, na, pn_);

  //         // first iteration
  //         if (i == bits - 1)
  //         {
  //             if (act)
  //             {
  //                 Enand1_ = graph.addVertex(Gates::GateAnd, "E2and1_" + C);
  //                 graph.addEdges({const_1, pn_}, Enand1_);
  //             }
  //             else
  //             {
  //                 graph.addEdge(pn_, En_);
  //             }
  //         }
  //         else
  //         {
  //             std::shared_ptr<GraphVertexBase> np2_ =
  //             graph.addGate(Gates::GateNot, "np2_" + C);
  //             std::shared_ptr<GraphVertexBase> np2_next =
  //             graph.addGate(Gates::GateNot, "np2_" + NextC);
  //             graph.addEdge(prev_pn_, np2_); graph.addEdge(pn_, np2_next);
  //             std::shared_ptr<GraphVertexBase> P21_ =
  //             graph.addVertex(Gates::GateAnd, "P21_"
  //             + C); graph.addEdges({np2_, np2_next}, P21_);
  //             std::shared_ptr<GraphVertexBase> P22_ =
  //             graph.addVertex(Gates::GateAnd, "P22_" + C);
  //             graph.addEdges({prev_pn_, np2_next}, P22_);
  //             pEn_ = graph.addVertex(Gates::GateOr, "pE2_" + C);
  //             graph.addEdges({P21_, P22_}, pEn_);
  //             if (act)
  //             {
  //                 Enand1_ = graph.addGate(Gates::GateAnd, "E2and1_" + C);
  //                 graph.addEdges({const_1, pEn_}, Enand1_);
  //             }
  //             else
  //             {
  //                 graph.addEdge(pEn_, En_);
  //             }
  //         }
  //         prev_pn_ = pn_;
  //     }
  // }
  return graph;
}

OrientedGraph SimpleGenerators::generatorEncoder(int bits) {
  OrientedGraph graph;
  // int k = 0;
  // for (int t = 0; t <= bits; t++)
  //     if (bits - 1 >= pow(2, t))
  //     {
  //         k = k + 1;
  //     }
  // for (int l = 0; l <= bits - 1; l++)
  // {
  //     std::string Z = std::to_string(l);
  //     graph.addInput("x" + Z);
  // }
  // if (bits > 1)
  //     for (int p = k - 1; p >= 0; p--)
  //     {
  //         std::string L = "";
  //         std::string P = "";
  //         std::string M = "";
  //         std::string K = "";
  //         std::string S = std::to_string(p);
  //         std::shared_ptr<GraphVertexBase>out = graph.addOutput("a" + S);

  //         for (int i = 0; i <= bits - 1; i++)
  //             for (double t = pow(2, p); t <= pow(2, p + 1) - 1; t++)
  //                 if (pow(2, p + 1) * i + t <= bits - 1)
  //                 {
  //                     std::string R = std::to_string(pow(2, p + 1) * i + t);
  //                     K = M + " or x" + R;
  //                     L = P + "orx" + R;
  //                     // graph.addEdge("x" + R, "a" + S, false);
  //                     P = L;
  //                     L = "";
  //                     M = K;
  //                     K = "";
  //                 }
  //         M = M.erase(0, 3);

  //         // TODO solve this name strange thing
  //         // std::shared_ptr<GraphVertexBase>P_ref = graph.addVertex(M, Gates::GateOr, P);
  //         std::shared_ptr<GraphVertexBase>P_ref = graph.addVertex(Gates::GateOr, P);
  //         for (int i = 0; i <= bits - 1; i++)
  //             for (double t = pow(2, p); t <= pow(2, p + 1) - 1; t++)
  //                 if (pow(2, p + 1) * i + t <= bits - 1)
  //                 {
  //                     std::string R = std::to_string(pow(2, p + 1) * i + t);
  //                     // here getting input number R
  //                     graph.addEdge(graph.getVerticeByIndex(R), P_ref);
  //                 }
  //         graph.addEdge(P_ref, out);
  //     }
  // else
  //    std::cout << "Недостаточно входных сигналов\n";

  return graph;
}

OrientedGraph SimpleGenerators::generatorSubtractor(int i_bits, bool i_overflowIn, bool i_overflowOut, bool i_sub, bool act)
{
    OrientedGraph graph;
    std::shared_ptr<GraphVertexBase> const_1;
    if (act)
        const_1 = graph.addConst('1');

    std::string cond = std::string(i_overflowIn ? "t" : "f") + (i_overflowOut ? "t" : "f") + (i_sub ? "t" : "f");
    std::string s = std::string(i_sub ? "n" : "") + "d" + (!i_overflowIn && !i_overflowOut ? "0" : (!i_overflowIn && i_overflowOut ? "1" : (i_overflowIn && !i_overflowOut ? "2" : "3")));

    for (int i = 0; i < i_bits; i++)
    {

        std::string Z = std::to_string(i); //нынешний индекс
        std::string NextZ = std::to_string(i + 1); //следующий индекс
        std::string x = "suba" + cond + Z;
        std::string y = "subb" + cond + Z;
        std::shared_ptr<GraphVertexBase> input_x = graph.addInput(x);
        std::shared_ptr<GraphVertexBase> input_y = graph.addInput(y);
        std::shared_ptr<GraphVertexBase> output_sub;
        if (!act)
        {
            output_sub = graph.addOutput(s + Z);
        }

        std::shared_ptr<GraphVertexBase> abxor = graph.addGate(Gates::GateXor, "abxor" + Z);
        graph.addEdges({input_x, input_y}, abxor);

        std::shared_ptr<GraphVertexBase> abandn;
        //i_sub отвечает за определение вычитателя и вычитываемого: B-A или A-B
        if (!i_sub)
        {
            std::shared_ptr<GraphVertexBase> nx = graph.addGate(Gates::GateNot, "na" + Z);
            graph.addEdge(input_x, nx);

            abandn = graph.addGate(Gates::GateAnd, "bna" + Z);
            graph.addEdges({input_y, nx}, abandn);
        }
        if (i_sub)
        {
            std::shared_ptr<GraphVertexBase> ny = graph.addGate(Gates::GateNot, "nb" + Z);
            graph.addEdge(input_y, ny);

            abandn = graph.addGate(Gates::GateAnd, "anb" + Z);
            graph.addEdges({input_x, ny}, abandn);
        }

        std::shared_ptr<GraphVertexBase> d; //результат
        std::shared_ptr<GraphVertexBase> next_z; //следующий заем
        std::shared_ptr<GraphVertexBase> curr_z; //нынешний заём
        if (i == 0){
            if (!i_overflowIn){
                graph.addEdge(abxor, output_sub);

                next_z = graph.addGate(Gates::GateDefault, "z" + NextZ);
                graph.addEdge(abandn, next_z);
                continue;
            }
            else{
                curr_z = graph.addInput("z" + Z);
            }
        }
        else{
            curr_z = graph.addGate(Gates::GateDefault, "z" + Z);
        }
        d = graph.addGate(Gates::GateXor, "d" + Z);
        next_z = graph.addGate(Gates::GateOr, "z" + NextZ);

        std::shared_ptr<GraphVertexBase> nabxor = graph.addGate(Gates::GateNot, "nabxor" + Z);
        graph.addEdge(abxor, nabxor);

        std::shared_ptr<GraphVertexBase> nabxorz = graph.addGate(Gates::GateAnd, "nabxorz" + Z);
        graph.addEdges({curr_z, nabxor}, nabxorz);

        graph.addEdges({nabxorz, abandn}, next_z); //перенос заема
        graph.addEdges({abxor, curr_z}, d);
        graph.addEdge(d, output_sub);

        if (i_overflowOut && i + 1 == i_bits)
        {
            if (act)
            {
                std::shared_ptr<GraphVertexBase> and1_ = graph.addGate(Gates::GateAnd, s + "and1_" + NextZ);
                graph.addEdges({const_1, next_z}, and1_);
            }
            else
            {
                graph.addEdge(next_z, output_sub);
            }

        }
    }

    return graph;
}
