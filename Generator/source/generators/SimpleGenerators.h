#pragma once

#include "../graph/OrientedGraph.h"
#include "./TruthTable.h"

class SimpleGenerators
{
public:
  SimpleGenerators();
  std::vector<std::string> cnfFromTruthTable(const TruthTable& i_table, bool i_tp = true);
  std::vector<std::string> zhegalkinFromTruthTable(const TruthTable& i_table);
  OrientedGraph generatorRandLevel(int i_maxLevel, int i_maxElements, int i_inputs, int i_outputs);
  OrientedGraph generatorNumOperation(
    int i_input,
    int i_output,
    std::map<std::string, int> i_logicOper,
    bool i_leaveEmptyOut = true
  );
  OrientedGraph generatorSummator(int i_bits, bool i_overflowIn, bool i_overflowOut, bool i_minus, bool act = false);
  OrientedGraph generatorComparison(int i_bits, bool i_compare0, bool i_compare1, bool i_compare2, bool act = false);
  OrientedGraph generatorEncoder(int i_bits);
  OrientedGraph generatorMultiplier(int i_bits, bool act = false);
  OrientedGraph generatorMultiplexer(int i_bits, std::string T = "0");
  OrientedGraph generatorParity(int i_bits);
  OrientedGraph generatorDecoder(int i_bits);
  OrientedGraph generatorDemultiplexer(int i_bits);
  OrientedGraph generatorALU (int i_bits, int i_outbits, bool ALL, bool SUM, bool SUB, bool NSUM, bool NSUB, bool MULT,
                              bool COM, bool AND, bool NAND, bool OR, bool NOR, bool XOR, bool XNOR, bool CNF);
private:
  Settings* d_settings = Settings::getInstance("GraphVertex");
  std::map<std::string, int> delNull(std::map<std::string, int> i_copyLogicOper);
  std::string randomGenerator(const std::map<std::string, int>& i_map);
  OrientedGraph ALU(int i_bits, int i_outbits, bool ALL, bool SUM, bool SUB, bool NSUM, bool NSUB, bool MULT,
                    bool COM, bool AND, bool NAND, bool OR, bool NOR, bool XOR, bool XNOR, bool CNF);
};
