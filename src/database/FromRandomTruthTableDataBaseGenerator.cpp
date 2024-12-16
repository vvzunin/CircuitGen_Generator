#include "FromRandomTruthTableDataBaseGenerator.hpp"

#include <generators/simple/FromTruthTableGenerator.hpp>

void FromRandomTruthTableDataBaseGenerator::generateDataBase(
    const GenerationParameters &i_param) {
  TruthTable tt(i_param.getInputs(), i_param.getOutputs(), 0.0);

  FromTruthTableGenerator tftt(i_param);

  std::vector<GraphPtr> allGraphs;

  GraphPtr graph;
  if (i_param.getZhegalkin().getZhegalkin()) {
    graph = tftt.zhegalkinFromTruthTable(tt);
    graph->setName(i_param.getName() + "_" + "Zhegalkin");

    allGraphs.push_back(graph);
  }
  if (i_param.getCNF().getCNFF()) {
    graph = tftt.cnfFromTruthTable(tt, !i_param.getCNF().getCNFF());
    graph->setName(i_param.getName() + "_" + "CNFF");

    allGraphs.push_back(graph);
  }
  if (i_param.getCNF().getCNFT()) {
    graph = tftt.cnfFromTruthTable(tt, i_param.getCNF().getCNFT());
    graph->setName(i_param.getName() + "_" + "CNFT");

    allGraphs.push_back(graph);
  }

  for (auto curGraph: allGraphs)
    processCircuit(curGraph, tt, i_param, curGraph->getName());
}
