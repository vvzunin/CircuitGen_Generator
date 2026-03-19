#pragma once

#include <CircuitGenGraph/GraphUtils.hpp>
#include <CircuitGenGraph/OrientedGraph.hpp>

#include <cstdint>
#include <iterator>
#include <string_view>
#include <vector>


namespace CG_Gen {

struct ArithemticOperations {
  enum Types : uint8_t {
    UNDEFINED = 0u,
    MUL,
    DIV,
    ADD,
    SUB,
    NEG,
    INC,
    DEC
  };

  inline static std::string_view getName(Types i_type) {
    switch (i_type) {
      case MUL:
        return "MUL";
      case DIV:
        return "DIV";
      case ADD:
        return "ADD";
      case SUB:
        return "SUB";
      case NEG:
        return "NEG";
      case INC:
        return "INC";
      case DEC:
        return "DEC";
      case UNDEFINED:
        return "UNDEFINED";
    }
    return "UNDEFINED";
  }

  inline static Types getArithmeticType(const std::string_view &i_name) {
    static const std::pair<std::string_view, Types> names[] = {
      {getName(MUL), MUL},
      {getName(DIV), DIV},
      {getName(ADD), ADD},
      {getName(SUB), SUB},
      {getName(NEG), NEG},
      {getName(INC), INC},
      {getName(DEC), DEC}
    };
    auto lambda =
        [&i_name](const std::pair<std::string_view, Types> &type) -> bool {
      return type.first == i_name;
    };
    const auto *iter = std::find_if(
        std::begin(names), std::end(names), lambda);
    return iter != std::end(names) ? iter->second : UNDEFINED;
  } 
};

std::vector<VertexPtr>
synthLadnerFisherPrefixDecisionTree(
    GraphPtr graph,
    const std::vector<VertexPtr> &inputs,
    uint16_t outSize,
    CG_Graph::Gates operation = CG_Graph::GateOr);

std::vector<VertexPtr>
commonPrefixOperations(GraphPtr graph,
                       const std::vector<VertexPtr> &word,
                       uint32_t width,
                       bool signExtend,
                       ArithemticOperations::Types oper);

std::vector<VertexPtr>
twosComplement(GraphPtr graph,
               const std::vector<VertexPtr> &word,
               uint32_t width,
               bool signExtend);

} // namespace CG_Gen
