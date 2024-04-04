#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "GraphVertexBase.hpp"

class GraphVertexInput : public GraphVertexBase {
 public:
  GraphVertexInput(OrientedGraph *i_baseGraph = nullptr,
                   const VertexTypes i_type = VertexTypes::input);

  GraphVertexInput(const std::string i_name,
                   OrientedGraph *i_baseGraph = nullptr,
                   const VertexTypes i_type = VertexTypes::input);

  virtual char updateValue();
  virtual void updateLevel();

 protected:
  GraphVertexInput(VertexTypes i_type);

 private:
};

class GraphVertexConstant : public GraphVertexInput {
 public:
  GraphVertexConstant(char i_const, OrientedGraph *i_baseGraph = nullptr);

  GraphVertexConstant(char i_const, const std::string i_name,
                      OrientedGraph *i_baseGraph = nullptr);

  virtual void updateLevel();

 private:
};

class GraphVertexOutput : public GraphVertexBase {
 public:
  GraphVertexOutput(OrientedGraph *i_baseGraph = nullptr);

  GraphVertexOutput(const std::string i_name,
                    OrientedGraph *i_baseGraph = nullptr);

  virtual char updateValue();
  virtual void updateLevel();

 private:
};

class GraphVertexGates : public GraphVertexBase {
 public:
  GraphVertexGates(Gates i_gate, OrientedGraph *i_baseGraph = nullptr);

  GraphVertexGates(Gates i_gate, const std::string i_name,
                   OrientedGraph *i_baseGraph = nullptr);

  virtual char updateValue();
  std::string calculateHash(bool recalculate = false);
  std::string getVerilogString() const;
  Gates getGate() const;
 private:
  Gates d_gate;
  std::string hashed;
  // Определяем тип вершины: подграф, вход, выход, константа или одна из базовых
  // логических операций.
  VertexTypes d_type;
};