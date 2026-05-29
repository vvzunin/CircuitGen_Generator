#pragma once

#include "generators/simple/simple/SimpleGenerator.hpp"

namespace CG_Gen {

class MuxGenerator : public SimpleGenerator {
public:
  MuxGenerator();
  MuxGenerator(uint_fast32_t i_seed);
  MuxGenerator(const GenerationParameters &i_param);

  static VertexPtr addMux2(GraphPtr graph, VertexPtr sel, VertexPtr x,
                           VertexPtr y);

  static std::vector<VertexPtr> addMux2(GraphPtr graph, VertexPtr sel,
                                        const std::vector<VertexPtr> &x,
                                        const std::vector<VertexPtr> &y);

  // TODO: write other mux generators
};

} // namespace CG_Gen
