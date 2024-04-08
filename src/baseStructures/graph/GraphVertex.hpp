#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "GraphVertexBase.hpp"

/// @file GraphVertex.hpp
/// TO DO: Maybe Description some virtual methods for Graph's classes,
/// such as GraphVertexGates

/// class GraphVertexInput Represents a vertex in a directed graph that
/// serves as an input vertex. It inherits from the GraphVertexBase class
/// and extends its functionality to work with input vertices
/// @param i_baseGraph A pointer to the oriented graph to which this vertex
/// belongs. It can be null ptr, which indicates the absence of a base graph
/// @param i_type Vertex type (VertexTypes enumeration). By default, it is
/// set to VertexTypes::input, indicating that this is the input vertex
/// @param i_name The name of the vertex provided during creation. This is
/// a string of type std::string that identifies a vertex
/// */

class GraphVertexInput : public GraphVertexBase {
public:
  GraphVertexInput(
      OrientedGraph*    i_baseGraph = nullptr,
      const VertexTypes i_type      = VertexTypes::input
  );

  GraphVertexInput(
      const std::string i_name,
      OrientedGraph*    i_baseGraph = nullptr,
      const VertexTypes i_type      = VertexTypes::input
  );

  /// @brief updateValue A virtual function for updating the vertex value.
  /// The implementation is provided in derived classes
  /// @return the value of the vertex after its update

  virtual char updateValue();

  /// @brief updateLevel It is designed to update the level of the current
  /// vertex in a directed graph based on the levels of its input connections

  virtual void updateLevel();

protected:
  GraphVertexInput(VertexTypes i_type);

private:
};

/// class GraphVertexConstant TO DO: Description
/// 
/// </summary>

class GraphVertexConstant : public GraphVertexInput {
public:
  GraphVertexConstant(char i_const, OrientedGraph* i_baseGraph = nullptr);

  GraphVertexConstant(
      char              i_const,
      const std::string i_name,
      OrientedGraph*    i_baseGraph = nullptr
  );

  /// @brief updateLevel updates the level of the current vertex in the graph
  /// based on the levels of its incoming connections

  virtual void updateLevel();

private:
};

/// class GraphVertexOutput It is a vertex of the graph, specially designed for
/// data output. It inherits from the GraphVertexBase class and adds additional
/// functionality related to data output

class GraphVertexOutput : public GraphVertexBase {
public:
  GraphVertexOutput(OrientedGraph* i_baseGraph = nullptr);

  GraphVertexOutput(
      const std::string i_name,
      OrientedGraph*    i_baseGraph = nullptr
  );

  /// @brief updateValue updates the value of the current vertex of the graph
  /// based on the values of its incoming connections and the type of logical
  /// element (or "gate"). Depending on the type of gate and the values of the
  /// incoming links, the method uses the truth tables to perform the
  /// corresponding logical operation and sets a new value for the current
  /// vertex
  /// @return A char that represents the new value of the current vertex after
  /// updating based on the values of its incoming connections and the type of
  /// logical element (or "gate").

  virtual char updateValue();

  /// @brief updateLevel updates the level of the current vertex in the graph
  /// based on the levels of its incoming connections. If a vertex has incoming
  /// connections, the method determines the highest level among all the
  /// vertices to which it is connected, and sets the level of the current
  /// vertex to one higher than the highest level

  virtual void updateLevel();

private:
};

class GraphVertexGates : public GraphVertexBase {
public:
  GraphVertexGates(Gates i_gate, OrientedGraph* i_baseGraph = nullptr);

  GraphVertexGates(
      Gates             i_gate,
      const std::string i_name,
      OrientedGraph*    i_baseGraph = nullptr
  );


  virtual char updateValue();
  std::string  calculateHash(bool recalculate = false);
  std::string  getVerilogString() const;
  Gates        getGate() const;

private:
  Gates       d_gate;
  std::string hashed;
  // Определяем тип вершины: подграф, вход, выход, константа или одна из базовых
  // логических операций.
  VertexTypes d_type;
};