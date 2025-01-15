#include "NumOperationsGenerator.hpp"

namespace {
/// @addtogroup UnnamedNamespaces
/// @{
/// @file SimpleGenerators.hpp
/// @brief maxValueInMap Find the maximum value in a map
///
/// @tparam T The type of the map keys
/// @param i_map The map whose maximum value is to be found
/// @return The maximum value in the map. If the map is empty, returns -1
/// @note The function assumes that the map values are of type int32_t
/// @}
template<typename T>
int32_t maxValueInMap(const std::map<T, int32_t> &i_map) {
  if (i_map.size() == 0) {
    return -1;
  }
  int32_t res = (*i_map.begin()).second;

  for (const auto &[key, value]: i_map) {
    res = std::max(res, value);
  }
  return res;
}

// namespace end
} // namespace

NumOperationsGenerator::NumOperationsGenerator() : SimpleGenerator() {
}

NumOperationsGenerator::NumOperationsGenerator(uint_fast32_t i_seed) :
    SimpleGenerator(i_seed) {
}

NumOperationsGenerator::NumOperationsGenerator(
    const GenerationParameters &i_param) :
    SimpleGenerator(i_param) {
}

GraphPtr NumOperationsGenerator::generatorNumOperation(
    uint32_t i_input, uint32_t i_output, std::map<Gates, int32_t> i_logicOper,
    bool i_leaveEmptyOut) {
  int32_t sumOper = 0, maxLvl;
  std::string name;
  VertexPtr name_ptr;
  std::map<Gates, int32_t> copyLogicOper;
  std::map<std::string, int32_t> levelName;
  std::map<std::string, VertexPtr> levelNamePtr;
  std::vector<VertexPtr> nameOut, nameInput;

  for (const auto &elem: i_logicOper) {
    std::cout << elem.first << " " << elem.second << "\n";
  }

  copyLogicOper = i_logicOper;

  GraphPtr graph(new OrientedGraph());

  for (int32_t i = 0; i < i_input; ++i) {
    name = "x" + std::to_string(i);
    name_ptr = graph->addInput(name);

    // TODO and how can it be changed?
    levelName[name_ptr->getName()] = name_ptr->getLevel();
    levelNamePtr[name_ptr->getName()] = name_ptr;
    if (!i_leaveEmptyOut)
      nameInput.push_back(name_ptr);
  }

  for (int32_t i = 0; i < i_output; ++i) {
    name = "f" + std::to_string(i);
    name_ptr = graph->addOutput(name);
    nameOut.push_back(name_ptr);
  }

  for (const auto &[key, value]: copyLogicOper)
    sumOper += value;

  copyLogicOper = delNull(copyLogicOper);
  // TODO it is TOO slow
  for (int32_t i = 0; i < sumOper; ++i) {
    // TODO: optimize
    // TODO change whole gen
    Gates oper = randomGenerator(copyLogicOper);
    --copyLogicOper[oper];

    if (oper == Gates::GateNot || oper == Gates::GateBuf) {
      std::string ver1_name = randomGenerator(levelName);
      auto ver1 = levelNamePtr[ver1_name];

      // name = d_settings->getLogicOperation(oper).first + "(" + ver1 + ")";
      name_ptr = graph->addGate(oper);
      graph->addEdge(ver1, name_ptr);
    } else {
      std::string ver1_name = randomGenerator(levelName);
      std::string ver2_name = randomGenerator(levelName);
      VertexPtr ver1 = levelNamePtr[ver1_name];
      VertexPtr ver2 = levelNamePtr[ver2_name];
      // name = "(" + ver1 + ") " + d_settings->getLogicOperation(oper).first +
      //        "(" + ver2 + ")";

      // WTF this is not used AT ALL
      // std::string reserveName = "(" + ver2 + ") " +
      //                           d_settings->getLogicOperation(oper).first +
      //                           "(" + ver1 + ")";

      name_ptr = graph->addGate(oper);
      graph->addEdges({ver1, ver2}, name_ptr);
      levelName[name_ptr->getName()] = name_ptr->getLevel();
      levelNamePtr[name_ptr->getName()] = name_ptr;
    }

    if (!copyLogicOper[oper])
      copyLogicOper.erase(oper);
  }

  while ((nameOut.size() > 0) &
         ((levelName.size() > 0 || i_leaveEmptyOut == false))) {
    if (levelName.size() > 0) {
      std::vector<std::string> help;
      maxLvl = maxValueInMap(levelName);

      for (const auto &[key, value]: levelName) {
        if (value == maxLvl)
          help.push_back(key);
      }

      while (help.size() > 0 && nameOut.size() > 0) {
        int32_t R1 = d_randGenerator.getRandInt(0, help.size());
        int32_t R2 = d_randGenerator.getRandInt(0, nameOut.size());
        graph->addEdge(levelNamePtr[help[R1]], nameOut[R2]);
        levelName.erase(help[R1]);
        help.erase(help.begin() + R1);
        nameOut.erase(nameOut.begin() + R2);
      }
    } else {
      int32_t R1 = d_randGenerator.getRandInt(0, nameInput.size());
      int32_t R2 = d_randGenerator.getRandInt(0, nameOut.size());

      graph->addEdge(nameInput[R1], nameOut[R2]);
      nameOut.erase(nameOut.begin() + R2);
    }
  }
  return graph;
}

GraphPtr NumOperationsGenerator::generatorNumOperation(
    const GenerationParameters &i_param) {
  return generatorNumOperation(i_param.getInputs(), i_param.getOutputs(),
                               i_param.getNumOperations().getLogicOpers(),
                               i_param.getNumOperations().getLeaveEmptyOut());
}

GraphPtr NumOperationsGenerator::generatorNumOperation() {
  return generatorNumOperation(getParameters());
}
