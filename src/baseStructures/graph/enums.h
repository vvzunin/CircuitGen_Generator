#pragma once

#include <map>

const std::map<char, std::map<char, char>> tableAnd{
  {'0', {{'0', '0'}, {'1', '0'}, {'x', '0'}, {'z', '0'}}},
  {'1', {{'0', '0'}, {'1', '1'}, {'x', 'x'}, {'z', 'x'}}},
  {'x', {{'0', '0'}, {'1', 'x'}, {'x', 'x'}, {'z', 'x'}}},
  {'z', {{'0', '0'}, {'1', 'x'}, {'x', 'x'}, {'z', 'x'}}},
};

const std::map<char, std::map<char, char>> tableNand{
  {'0', {{'0', '1'}, {'1', '1'}, {'x', '1'}, {'z', '1'}}},
  {'1', {{'0', '1'}, {'1', '0'}, {'x', 'x'}, {'z', 'x'}}},
  {'x', {{'0', '1'}, {'1', 'x'}, {'x', 'x'}, {'z', 'x'}}},
  {'z', {{'0', '1'}, {'1', 'x'}, {'x', 'x'}, {'z', 'x'}}},
};

const std::map<char, std::map<char, char>> tableOr{
  {'0', {{'0', '0'}, {'1', '1'}, {'x', 'x'}, {'z', 'x'}}},
  {'1', {{'0', '1'}, {'1', '1'}, {'x', '1'}, {'z', '1'}}},
  {'x', {{'0', 'x'}, {'1', '1'}, {'x', 'x'}, {'z', 'x'}}},
  {'z', {{'0', 'x'}, {'1', '1'}, {'x', 'x'}, {'z', 'x'}}},
};

const std::map<char, std::map<char, char>> tableNor{
  {'0', {{'0', '1'}, {'1', '0'}, {'x', 'x'}, {'z', 'x'}}},
  {'1', {{'0', '0'}, {'1', '0'}, {'x', '0'}, {'z', '0'}}},
  {'x', {{'0', 'x'}, {'1', '0'}, {'x', 'x'}, {'z', 'x'}}},
  {'z', {{'0', 'x'}, {'1', '0'}, {'x', 'x'}, {'z', 'x'}}},
};

const std::map<char, std::map<char, char>> tableXor{
  {'0', {{'0', '0'}, {'1', '1'}, {'x', 'x'}, {'z', 'x'}}},
  {'1', {{'0', '1'}, {'1', '0'}, {'x', 'x'}, {'z', 'x'}}},
  {'x', {{'0', 'x'}, {'1', 'x'}, {'x', 'x'}, {'z', 'x'}}},
  {'z', {{'0', 'x'}, {'1', 'x'}, {'x', 'x'}, {'z', 'x'}}},
};

const std::map<char, std::map<char, char>> tableXnor{
  {'0', {{'0', '1'}, {'1', '0'}, {'x', 'x'}, {'z', 'x'}}},
  {'1', {{'0', '0'}, {'1', '1'}, {'x', 'x'}, {'z', 'x'}}},
  {'x', {{'0', 'x'}, {'1', 'x'}, {'x', 'x'}, {'z', 'x'}}},
  {'z', {{'0', 'x'}, {'1', 'x'}, {'x', 'x'}, {'z', 'x'}}},
};

const std::map<char, char> tableBuf{{'0', '0'}, {'1', '1'}, {'x', 'x'}, {'z', 'x'}};
const std::map<char, char> tableNot{{'0', '1'}, {'1', '0'}, {'x', 'x'}, {'z', 'x'}};

const std::vector<Gates> d_logicElements = {
      Gates::GateAnd, Gates::GateNand, Gates::GateOr,  Gates::GateNor,
      Gates::GateXor, Gates::GateXnor, Gates::GateNot, Gates::GateBuf};