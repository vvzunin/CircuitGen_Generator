#include "GeneratorUtils.hpp"

#include <CircuitGenGraph/GraphUtils.hpp>
#include <vector>

namespace CG_Gen {

VertexPtr MuxGenerator::addMux2(GraphPtr graph, VertexPtr sel, VertexPtr x,
                                VertexPtr y) {
  if (!sel || !x || !y) {
    return nullptr;
  }
  auto *inv = graph->addGate(GateNot);
  graph->addEdge(sel, inv);

  auto *ifFirst = graph->addGate(GateAnd);
  auto *ifSecond = graph->addGate(GateAnd);

  graph->addEdges({inv, x}, ifFirst);
  graph->addEdges({sel, y}, ifSecond);

  auto *result = graph->addGate(GateOr);
  graph->addEdges({ifFirst, ifSecond}, result);

  return result;
}

std::vector<VertexPtr> MuxGenerator::addMux2(GraphPtr graph, VertexPtr sel,
                                             const std::vector<VertexPtr> &x,
                                             const std::vector<VertexPtr> &y) {
  if (x.size() != y.size() || x.empty() || !sel) {
    return {};
  }
  std::vector<VertexPtr> result(x.size());
  for (auto i = 0; i < x.size(); ++i) {
    result[i] = addMux2(graph, sel, x[i], y[i]);
  }
  return result;
}

} // namespace CG_Gen
