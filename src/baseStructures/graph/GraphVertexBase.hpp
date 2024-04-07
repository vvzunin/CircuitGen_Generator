#pragma once

#include <memory>
#include <string>
#include <vector>

#include <baseStructures/graph/enums.hpp>

#include "OrientedGraph.hpp"
#include "settings/Settings.hpp"

class OrientedGraph;  // Проблема циклического определения

/// class GraphVertexBase
/// @param i_type The vertex type represented by the VertexTypes enumeration.
/// Defines the type of the current vertex, for example, input, output,
/// subgraph, or one of the basic logical operations
/// @param i_name The name of the vertex. It is a string containing the name
/// of a vertex
/// @param i_graph A pointer to an object of the OrientedGraph class
/// representing the oriented graph to which this vertex belongs. The default
/// value is nullptr

class GraphVertexBase {
public:
  GraphVertexBase(const VertexTypes i_type, OrientedGraph* i_graph = nullptr);

  GraphVertexBase(
      const VertexTypes i_type,
      const std::string i_name,
      OrientedGraph*    i_graph = nullptr
  );

  // TODO crashes add destructor call
  virtual ~GraphVertexBase();

  // Get для типа вершины

  /// @brief getType Designed to get the type of vertex
  /// @return The vertex type (d_type), which is represented by the VertexTypes enumeration

  virtual VertexTypes getType() const final;
  // Get для типа вершины в фомате строки

  /// @brief getTypeName Designed to get a string representation of the vertex type.
  /// @return String representation of the vertex type

  virtual std::string getTypeName() const final;

  // Get-Set для имен входов

  /// @brief setName it is intended for setting the vertex name
  /// @param i_name The new vertex name to set

  void                setName(const std::string i_name);

  /// @brief getName it is intended to get the name of the vertex.
  /// @return The name of the vertex in the string representation

  std::string         getName() const;

  // Get для значения вершины

  /// @brief designed to get the value of a vertex
  /// @return the value of the vertex

  virtual char        getValue() const;

  /// @brief updateValue it is designed to update the vertex value based
  /// on the values of the input connections and the logical operation
  /// that the vertex represents
  /// @return New vertex value (type char)

  virtual char        updateValue() = 0;

  // Get-Set для уровня

  /// @brief setLevel Designed to set the vertex level in a graph
  /// @param i_level A new vertex level in the graph

  void                setLevel(const unsigned i_level);

  /// @brief getLevel Designed to get the vertex level in the graph
  /// @return The level of the vertex in the graph

  unsigned            getLevel() const;

  /// @brief updateLevel It is designed to update the level of a vertex
  /// in a graph based on the levels of its input connections

  virtual void        updateLevel();

  /// @brief getGate It is intended to obtain the type of logical gate
  /// represented by this vertex. If the vertex does not represent a
  /// logical gate, the method returns the value Gates::Gates Default
  /// @return Gates: The type of logical gate represented by this vertex

  virtual Gates       getGate() const { return Gates::GateDefault; };

  // Get-Set для базового графа
  // void setBaseGraph(std::shared_ptr<OrientedGraph> const i_baseGraph);

  /// @brief getBaseGraph returns a pointer to the underlying oriented
  /// graph to which this vertex belongs
  /// @return A pointer to the basic oriented graph to which this vertex 
  /// belongs

  OrientedGraph*      getBaseGraph() const;

  /// @brief getInConnections It is designed to receive all input connections
  /// (input vertices) of the current vertex. Returns a vector of pointers to
  /// GraphVertexBase objects representing the input connections of this
  /// vertex
  /// @return Vector of pointers to GraphVertexBase objects representing the
  /// input connections of this vertex

  std::vector<std::shared_ptr<GraphVertexBase>> getInConnections() const;

  /// @brief addVertexToInConnections It is intended for adding an input
  /// connection of a given vertex. The input connection is represented
  /// as a pointer to an object of type GraphVertexBase.
  /// @param i_vert A pointer to a GraphVertexBase object representing the
  /// input connection
  /// @return The number of additions of this compound

  int  addVertexToInConnections(std::shared_ptr<GraphVertexBase> const i_vert);

  /// @brief removeVertexToInConnections designed to remove an input
  /// connection from the list of input connections of the current vertex
  /// @param i_vert A pointer to a GraphVertexBase object representing
  /// the input connection to be deleted
  /// @param i_full A flag indicating whether to delete all input connections
  /// (true) or only the first one encountered (false). The default value
  /// is false
  /// @return The value is true if the connection was successfully deleted, 
  /// otherwise false.

  bool removeVertexToInConnections(
      std::shared_ptr<GraphVertexBase> const i_vert,
      bool                                   i_full = false
  );

  /// @brief getOutConnections Returns a vector of pointers to GraphVertexBase
  /// objects representing outgoing connections of a given vertex
  /// @return Vector of pointers to GraphVertexBase objects representing
  /// outgoing connections of a given vertex

  std::vector<std::shared_ptr<GraphVertexBase>> getOutConnections() const;

  /// @brief addVertexToOutConnections designed to add an outgoing connection
  /// to a given vertex
  /// @param i_vert A pointer to a GraphVertexBase object representing an
  /// @return The value is true if the connection was successfully added,
  /// otherwise false.

  bool addVertexToOutConnections(std::shared_ptr<GraphVertexBase> const i_vert);

  /// @brief removeVertexToOutConnections designed to remove an outgoing
  /// connection from the list of outgoing connections of the current vertex
  /// @param i_vert A pointer to a GraphVertexBase object representing the
  /// outgoing connection to be deleted
  /// @return The value is true if the connection was successfully deleted,
  /// otherwise false.

  bool removeVertexToOutConnections(
      std::shared_ptr<GraphVertexBase> const i_vert
  );

  /// @brief calculateHash It is designed to calculate the hash value of the
  /// current vertex of the graph and all its descendants
  /// (outgoing connections)
  /// @param recalculate A flag indicating whether the hash value needs to be
  /// recalculated even if it has already been previously calculated.
  /// The default value is false
  /// @return Hash value of the current vertex of the graph and all its
  /// descendants

  std::string calculateHash(bool recalculate = false);

protected:
  OrientedGraph*                                d_baseGraph = nullptr;

  std::string                                   d_name;
  char                                          d_value;
  unsigned                                      d_level;

  std::vector<std::shared_ptr<GraphVertexBase>> d_inConnections;
  std::vector<std::shared_ptr<GraphVertexBase>> d_outConnections;

  std::shared_ptr<Settings>                     d_settings =
      Settings::getInstance("GraphVertexBase");

private:
  // Определяем тип вершины: подграф, вход, выход, константа или одна из базовых
  // логических операций.
  VertexTypes          d_type;

  // Счетчик вершин для именования и подобного
  static uint_fast64_t d_count;
  std::string          hashed = "";
};