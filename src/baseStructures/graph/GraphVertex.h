#pragma once

#include <string>
#include <memory>
#include <map>

#include <utility>
#include <vector> 
#include "GraphVertexBase.h"

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

class GraphVertexInput : public GraphVertexBase
{
public:
  GraphVertexInput();

  virtual char updateValue();
  virtual void updateLevel();

protected:
  GraphVertexInput(VertexTypes i_type);
  
private:  

};

class GraphVertexOutput : public GraphVertexBase
{
public:
  GraphVertexOutput(OrientedGraph* i_baseGraph);
  virtual char updateValue();
  virtual void updateLevel();

private:

};

class GraphVertexConstant : public GraphVertexInput
{
public:
  GraphVertexConstant(OrientedGraph* i_baseGraph, char i_const);
  virtual void updateLevel();
  
private:

};

class GraphVertexGates: public GraphVertexBase
{
public:
  GraphVertexGates(OrientedGraph* i_baseGraph, int i_inputs, Gates i_gate);
  virtual char updateValue();
  
private:
  Gates d_gate;
};