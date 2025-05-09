#pragma once

#include <CircuitGenGraph/OrientedGraph.hpp>
#include <generators/GenerationParameters.hpp>

namespace CG_Gen {

enum class BasisType { AIG, NOR };

GraphPtr
convertGraphToBasis(GraphPtr graph,
                    GenerationParameters::GatesInputsInfo gatesInputsInfo);

} // namespace CG_Gen