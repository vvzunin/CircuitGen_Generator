#pragma once

#include <algorithm>
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
  /// @brief GraphVertexInput
  /// Initializes the GraphVertexInput object with the provided base graph
  /// pointer and type
  /// @param i_baseGraph Pointer to the base graph. Default is nullptr.
  /// @param i_type i_type Type of the vertex. Default is VertexTypes::input.

  GraphVertexInput(
      GraphPtr          i_baseGraph = nullptr,
      const VertexTypes i_type      = VertexTypes::input
  );

  /// @brief GraphVertexInput
  /// Initializes the GraphVertexInput object with the provided name, base
  /// graph pointer, and type
  /// @param i_name Name of the vertex.
  /// @param i_baseGraph Pointer to the base graph.
  /// @param i_type Type of the vertex.
  GraphVertexInput(
      const std::string i_name,
      GraphPtr          i_baseGraph = nullptr,
      const VertexTypes i_type      = VertexTypes::input
  );

  /// @brief updateValue A virtual function for updating the vertex value.
  /// The implementation is provided in derived classes
  /// @return the value of the vertex after its update
  /// @code
  /// TO DO:
  /// @endcode
  /// @throws std::invalid_argument if any input connection is invalid

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
///
/// </summary>

class GraphVertexConstant : public GraphVertexInput {
public:
  GraphVertexConstant(char i_const, GraphPtr i_baseGraph = nullptr);

  GraphVertexConstant(
      char              i_const,
      const std::string i_name,
      GraphPtr          i_baseGraph = nullptr
  );

  /// @brief updateLevel updates the level of the current vertex in the graph
  /// based on the levels of its incoming connections

  virtual void updateLevel();
  std::string  toVerilog() override;

  /// @brief getInstance
  /// TO DO:

  std::string  getInstance();

private:
};

/// class GraphVertexSubGraph It is a class, having a subGruph pointer
/// inside. Is used for storing this pointer for providing graph
/// connectivity
/// @param d_subGraph Pointer to the subgraph associated with this vertex
/// @param hashed Cached hash value of the vertex
class GraphVertexSubGraph : public GraphVertexBase {
public:
  GraphVertexSubGraph(GraphPtr i_subGraph, GraphPtr i_baseGraph = nullptr);

  GraphVertexSubGraph(
      GraphPtr           i_subGraph,
      const std::string& i_name,
      GraphPtr           i_baseGraph = nullptr
  );

  char        updateValue() override;

  std::string toVerilog() override;

  /// @brief This method is used as a substructure for
  /// OrientedGraph methods
  /// @param i_path path to future file storing. Do not add submodule here,
  /// folder would be created there
  /// @param i_filename name of file to be created (default is same as graph
  /// name)
  /// @return pair, first is bool, meaning was file writing successful or not
  /// and second is string, for graph is empty, for subgraph is module instance
  std::pair<bool, std::string>
              toVerilog(std::string i_path, std::string i_filename = "");

  /// @brief This method is used as a substructure for
  /// OrientedGraph methods
  /// @param i_fileStream TO DO:
  /// @return TO DO:
  bool        toGraphML(std::ofstream& i_fileStream) const;

  /// @brief This method is used as a substructure for
  /// OrientedGraph methods
  /// @param i_indent
  /// @return
  std::string toGraphML(uint16_t i_indent = 0, std::string i_prefix = "") const;

  /// @brief This method is used as a substructure for
  /// OrientedGraph methods
  /// @return
  std::string getInstance() override;

  std::string calculateHash(bool recalculate = false);

  void        setSubGraph(GraphPtr i_subGraph);
  GraphPtr    getSubGraph() const;
  std::vector<VertexPtr> getOutputBuffersByOuterInput(VertexPtr i_outerInput
  ) const;
  std::vector<VertexPtr> getOuterInputsByOutputBuffer(VertexPtr i_outputBuffer
  ) const;

private:
  GraphPtr    d_subGraph;
  std::string hashed;
};

/// class GraphVertexOutput It is a vertex of the graph, specially designed for
/// data output. It inherits from the GraphVertexBase class and adds additional
/// functionality related to data output

class GraphVertexOutput : public GraphVertexBase {
public:
  GraphVertexOutput(GraphPtr i_baseGraph = nullptr);

  GraphVertexOutput(const std::string i_name, GraphPtr i_baseGraph = nullptr);

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

/// @brief GraphVertexGates
/// Class representing a vertex in a graph with gates

class GraphVertexGates : public GraphVertexBase {
public:
  GraphVertexGates(Gates i_gate, GraphPtr i_baseGraph = nullptr);

  GraphVertexGates(
      Gates             i_gate,
      const std::string i_name,
      GraphPtr          i_baseGraph = nullptr
  );

  /// @brief updateValue
  /// Updates the value of the vertex
  /// @return The updated value of the vertex
  /// @code
  /// TO DO:
  /// @endcode
  /// @throws std::invalid_argument if any of the input connections point
  /// to a nullptr

  virtual char updateValue();

  /// @brief calculateHash
  /// Calculates the hash value of the vertex
  /// @param recalculate Flag indicating whether to recalculate the hash value
  /// (default false)
  /// @throws None.
  /// @code
  /// TO DO:
  /// @endcode
  /// @return The calculated hash value as a string

  std::string  calculateHash(bool recalculate = false);

  /// @brief getVerilogString
  /// Gets a string in Verilog format representing the current vertex
  /// @return A string in Verilog format representing the current vertex
  /// @throws std::invalid_argument if any input connection is invalid

  std::string  getVerilogString() const;

  /// @brief getGate
  /// Returns the type of valve associated with the current vertex
  /// @return The type of valve associated with the current vertex
  /// @code
  /// GraphVertexGates vertex(Gates::GateAnd);
  /// Gates gateType = vertex.getGate();
  /// std:: cout << "Gate type : " << gateType << std::endl;
  /// @endcode

  Gates        getGate() const;

  /// @brief toVerilog
  /// generates a string in Verilog format for the current vertex,
  /// representing the valve according to its type and input connections.
  /// If a vertex has no input connections, an empty string is returned.
  /// If any input connection is invalid, an exception is thrown.
  /// @return A Verilog format string for the current vertex
  /// @throws std::invalid_argument if any input connection is invalid

  std::string  toVerilog();

  bool         isSubgraphBuffer() const override;

private:
  Gates       d_gate;
  std::string hashed;
  // Определяем тип вершины: подграф, вход, выход, константа или одна из базовых
  // логических операций.
};