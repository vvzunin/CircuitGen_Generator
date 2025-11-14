#include "generators/simple/randLevel/RandLevelGenerator.hpp"
#include "additional/AuxiliaryMethods.hpp"
#include <CircuitGenGraph/GraphUtils.hpp>

#include <cstddef>
#include <cstdint>
#include <vector>

namespace CG_Gen {

RandLevelGenerator::RandLevelGenerator() : SimpleGenerator() {
}

RandLevelGenerator::RandLevelGenerator(uint_fast32_t i_seed) :
    SimpleGenerator(i_seed) {
}

RandLevelGenerator::RandLevelGenerator(const GenerationParameters &i_param) :
    SimpleGenerator(i_param) {
}

GraphPtr RandLevelGenerator::generatorRandLevel(
    uint32_t i_minLevel, uint32_t i_maxLevel, uint32_t i_minElements,
    uint32_t i_maxElements, uint32_t i_inputs, uint32_t i_outputs,
    bool syntheticConnected) {
  int32_t maxLevel;

  if (i_minLevel > i_maxLevel)
    throw std::invalid_argument("min level is bigger than max level");
  if (i_minElements > i_maxElements)
    throw std::invalid_argument("min elem is bigger than max elem");

  if (i_maxLevel)
    maxLevel = d_randGenerator.getRandInt(i_minLevel, i_maxLevel, true) + 1;
  else
    maxLevel = 1;

  auto [hasOneGate, logOper] = GraphUtils::getLogicOperationsWithGates();

  if (syntheticConnected) {
    int delta = 0;
    // removes not, buf
    for (int i = 0; i < logOper.size(); ++i) {
      hasOneGate[delta] = hasOneGate[i];
      logOper[delta] = logOper[i]; 
      if (!hasOneGate[i]) {
        delta += 1;
      }
    }
    logOper.resize(delta);
    hasOneGate.resize(delta);
  }

  int32_t choice;
  std::string expr;
  GraphPtr graph = std::make_shared<OrientedGraph>(
      "", (i_maxElements * i_minElements + i_inputs + i_outputs) *
              sizeof(GraphVertexBase));

  graph->reserve(VertexTypes::output, i_outputs);
  graph->reserve(VertexTypes::gate, maxLevel * i_maxElements);

  auto nameGen =
      [] (size_t i) -> std::string { return "x" + std::to_string(i); };
  std::vector<VertexPtr> values = graph->addInputs(i_inputs, nameGen);

  int32_t currIndex = i_inputs;

  for (int32_t i = 1; i < maxLevel; ++i) {
    // how many elements would be at this level
    int32_t elemLevel =
        i_maxElements > 1
            ? d_randGenerator.getRandInt(i_minElements, i_maxElements, true)
            : 2;
    std::vector<VertexPtr> newValues;
    newValues.reserve(elemLevel);
    for (int32_t j = 0; j < elemLevel; ++j) {
      choice = d_randGenerator.getRandInt(0, logOper.size());
      VertexPtr newVertex;
      if (hasOneGate[choice]) {
        int32_t child1 = d_randGenerator.getRandInt(0, currIndex);

        newVertex = graph->addGate(logOper[choice]);
        graph->addEdge(graph->getVerticeByIndex(child1), newVertex);

      } else if (!syntheticConnected) {
        auto [child1, child2] = AuxMethods::getTwoRandomElements(values);

        newVertex = graph->addGate(logOper[choice]);
        graph->addEdges({child2, child1}, newVertex);
      } else {
        newVertex = graph->addGate(logOper[choice]);
        graph->addEdges(values, newVertex);
      }
      newValues.push_back(newVertex);
    }
    currIndex += newValues.size();
    values = std::move(newValues);

    // std::clog << i / (float)maxLevel * 100 << "%" << std::endl;
  }

  // @todo fix when elements less than outputs

  for (int32_t i = 0; i < i_outputs; ++i) {
    VertexPtr child1 = d_randGenerator.getRandomElement(values);
    expr = "f" + std::to_string(i + 1);
    VertexPtr newVertex = graph->addOutput(expr);
    graph->addEdge(child1, newVertex);
  }
  // std::clog << "end\n";

  return graph;
}

GraphPtr RandLevelGenerator::generatorRandLevelExperimental(
    uint32_t i_minLevel, uint32_t i_maxLevel, uint32_t i_minElements,
    uint32_t i_maxElements, uint32_t i_inputs, uint32_t i_outputs) {
  if (i_minLevel > i_maxLevel)
    throw std::invalid_argument("min level is bigger than max level");
  if (i_minElements > i_maxElements)
    throw std::invalid_argument("min elem is bigger than max elem");

  uint32_t maxLevel;
  if (i_maxLevel)
    maxLevel = d_randGenerator.getRandInt(i_minLevel, i_maxLevel, true) + 1;
  else
    maxLevel = 1;

  std::string expr;
  GraphPtr graph = std::make_shared<OrientedGraph>();

  for (uint32_t i = 0; i < i_inputs; ++i) {
    expr = "x" + std::to_string(i);
    graph->addInput(expr);
  }
  // we need it because we:
  // a) can have less possible parents at current level, than is required by
  // minimum gates number of a logical element, so we can use inputs in such
  // case
  // b) need to swap gates
  std::vector<VertexPtr> inputs;
  inputs.reserve(i_inputs);

  for (auto *i: graph->getVerticesByType(VertexTypes::input)) {
    inputs.push_back(i);
  }
  auto curGates(inputs);

  // @todo what if we will need to use n-gate elements, should we add consts
  // usage?

  int32_t currIndex = i_inputs;
  int32_t curLen = 0;
  // we need lowest border as d_maxGateNumber, and if it is possible,
  // we set it (it changes speed of generation)
  uint32_t c_max = i_maxElements > d_maxGateNumber
                       ? std::max(d_maxGateNumber, (int32_t)i_minElements)
                       : i_minElements;

  for (int32_t i = 1; i < maxLevel; ++i) {
    // how many elements would be at this level
    int32_t elemLevel =
        i_maxElements > 1
            ? d_randGenerator.getRandInt(c_max, i_maxElements, true)
            : i_maxElements;

    // write allowed gates to be used as parent
    std::vector<VertexPtr> futureGates;
    curLen += curGates.size();

    for (int32_t j = 0; j < elemLevel; ++j) {
      // we use inputs only if we are not on the first level
      auto [operation, gatesNumber] = getRandomElement(curLen);
      // from which element we should start shuffle
      // like we do not shuffle whole list, if it is possible
      // but only it's part
      int32_t fromWhichShuffle = d_randGenerator.getRandInt(
          0, std::max(1, (int32_t)curGates.size() - gatesNumber));
      // shuffle curGates
      for (int32_t k = fromWhichShuffle,
                   stopVal = std::min(fromWhichShuffle + gatesNumber,
                                      (int32_t)curGates.size());
           k < stopVal; ++k) {
        std::swap(curGates[k],
                  curGates[d_randGenerator.getRandInt(0, curGates.size())]);
      }

      VertexPtr newVertex = graph->addGate(operation);

      if (gatesNumber == 1) {
        int32_t child1 = d_randGenerator.getRandInt(0, currIndex);

        graph->addEdge(graph->getVerticeByIndex(child1), newVertex);
      } else {
        // parents vertices to be added for a new one
        std::vector<VertexPtr> parents;
        // set memory (might be big, so we save time)
        parents.reserve(gatesNumber);
        auto idx = curGates.begin() + fromWhichShuffle;

        // add first parent
        parents.push_back((*idx));
        // move to second
        // it's impossible to have 1-element vector here
        // else we would have curLen = 1 and only buf/not
        // so it's safe
        ++idx;

        // add multiple parents
        for (int32_t l = 1; l < gatesNumber; ++l, ++idx) {
          // if we are at the end of vector
          if (idx == curGates.end()) {
            // and we added some vertices, e.g. we are not on the first level
            if (i > 1) {
              for (int32_t k = 0; k < inputs.size(); ++k)
                std::swap(inputs[k],
                          inputs[d_randGenerator.getRandInt(0, inputs.size())]);

              idx = inputs.begin();
            } else {
              idx = curGates.begin();
            }
          } else if (idx == inputs.end()) {
            idx = curGates.begin();
          }

          parents.push_back((*idx));
        }

        graph->addEdges(parents, newVertex);
      }
      futureGates.push_back(newVertex);
    }

    // at the beginning it is one. So, if it stayed zero, we are still using
    // inputs as gates. So we do not change it's value
    if (!(i ^ 1)) {
      curLen = inputs.size();
    }

    curGates = futureGates;
    futureGates.clear();
    // std::clog << (float)i / (float)maxLevel * 100 << "%" << std::endl;
  }

  // std::clog << "writing out gates" << std::endl;
  for (int32_t i = 0; i < i_outputs; ++i) {
    auto *child1 = curGates[d_randGenerator.getRandInt(0, curGates.size())];
    expr = "f" + std::to_string(i + 1);
    VertexPtr newVertex = graph->addOutput(expr);

    graph->addEdge(child1, newVertex);
  }

  // std::clog << "writing out gates ended" << std::endl;
  return graph;
}

GraphPtr
RandLevelGenerator::generatorRandLevel(const GenerationParameters &i_param) {
  const auto &params = i_param.getRandLevel();
  return generatorRandLevel(params.getMinLevel(),
                            params.getMaxLevel(),
                            params.getMinElements(),
                            params.getMaxElements(),
                            i_param.getInputs(), i_param.getOutputs(),
                            params.getSyntheticConnected());
}

GraphPtr RandLevelGenerator::generatorRandLevelExperimental(
    const GenerationParameters &i_param) {
  const auto &params = i_param.getRandLevel();
  return generatorRandLevelExperimental(params.getMinLevel(),
                                        params.getMaxLevel(),
                                        params.getMinElements(),
                                        params.getMaxElements(),
                                        i_param.getInputs(),
                                        i_param.getOutputs());
}

GraphPtr RandLevelGenerator::generatorRandLevel() {
  return generatorRandLevel(getParameters());
}

GraphPtr RandLevelGenerator::generatorRandLevelExperimental() {
  return generatorRandLevelExperimental(getParameters());
}

} // namespace CG_Gen
