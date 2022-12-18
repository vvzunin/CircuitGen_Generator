#pragma once

class SimpleGenerators
{
public:
  SimpleGenerators();
  std::vector<std::string> cnfFromTruthTable(const TruthTable& i_table, bool i_tp = true);
  OrientedGraph generatorRandLevel(int i_maxLevel, int i_maxElements, int i_inputs, int i_outputs);
  OrientedGraph generatorNumOperation(
    int i_input,
    int i_output,
    std::map<std::string, int> i_logicOper,
    bool i_leaveEmptyOut = true,
  );

private:
  Settings settings = Settings::readSettings();
  void delNull(std::map<std::string, int>& i_copyLogicOper);
  std::string randomGenerator(const std::map<std::string, int>& i_map);
}
