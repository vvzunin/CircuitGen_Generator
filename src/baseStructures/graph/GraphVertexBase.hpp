#pragma once

#include <memory>
#include <string>
#include <vector>

#include <baseStructures/graph/enums.hpp>

#include "OrientedGraph.hpp"
#include "settings/Settings.hpp"

class OrientedGraph;  // Проблема циклического определения

#define GraphPtr      std::shared_ptr<OrientedGraph>
#define GraphPtrWeak  std::weak_ptr<OrientedGraph>

#define VertexPtr     std::shared_ptr<GraphVertexBase>
#define VertexPtrWeak std::weak_ptr<GraphVertexBase>

/// @brief VertexUtils
/// Namespace containing utility functions for working with vertices

namespace VertexUtils {
/// @brief gateToString
/// Converts a gate type enum value to its string representation
/// @param i_type The gate type enum value
/// @return The string representation of the gate type.
/// @code
/// Gates gateType = Gates::GateAnd;
/// std::string gateString = VertexUtils::gateToString(gateType);
/// std::cout << "String representation of gate type: " << gateString << std::endl;
/// gateType = Gates::GateNot;
/// gateString = VertexUtils::gateToString(gateType);
/// std::cout << "String representation of gate type: " << gateString << std::endl;
/// @endcode
std::string gateToString(Gates i_type);


/// @brief vertexTypeToComment
/// Converts a vertex type enum value to its Verilog representation
/// @param i_type The vertex type enum value.
/// @return The Verilog representation of the vertex type
/// @code
/// VertexTypes vertexType = VertexTypes::Input;
/// std::string verilogType = VertexUtils::vertexTypeToVerilog(vertexType);
/// std::cout << "Verilog representation of vertex type: " << verilogType << std::endl;
/// @endcode
std::string vertexTypeToVerilog(VertexTypes i_type);



/// @brief vertexTypeToComment
/// Converts a vertex type enum value to its comment representation
/// This function takes a vertex type enum value (from the VertexTypes enum) and returns 
/// its corresponding comment representation. The comment representation is based 
/// on the vertex type and is used for generating comments or documentation
/// @param i_type The vertex type enum value (from the VertexTypes enum)
/// @return The comment representation of the vertex type.
/// @code
/// VertexTypes vertexType = VertexTypes::Input;
/// std::string comment = VertexUtils::vertexTypeToComment(vertexType);
/// std::cout << "Comment for input vertex type: " << comment << std::endl;
/// @endcode
std::string vertexTypeToComment(VertexTypes i_type);
}  // namespace VertexUtils

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
  /// @brief GraphVertexBase
  /// Constructs a GraphVertexBase object with the specified vertex type and optional graph
  /// @param i_type The type of the vertex (from the VertexTypes enum).
  /// @param i_graph Optional pointer to the graph containing the vertex
  GraphVertexBase(const VertexTypes i_type, GraphPtr i_graph = nullptr);

  /// @brief GraphVertexBase
  /// Constructs a GraphVertexBase object with the specified vertex type, name, and optional graph.
  /// @param i_type The type of the vertex (from the VertexTypes enum)
  /// @param i_name The name of the vertex.
  /// @param i_graph Optional pointer to the graph containing the vertex.
  GraphVertexBase(
      const VertexTypes i_type,
      const std::string i_name,
      GraphPtr          i_graph = nullptr
  );

  GraphVertexBase& operator=(const GraphVertexBase& other
  ) = default;  // оператор копирующего присваивания
  GraphVertexBase& operator=(GraphVertexBase&& other
  ) = default;  // оператор перемещающего присваивания
  GraphVertexBase(const GraphVertexBase& other) = default;
  GraphVertexBase(GraphVertexBase&& other)      = default;

  virtual ~GraphVertexBase();

  /// @brief getType
  /// This method returns the type of the vertex as a value of the VertexTypes
  /// enum
  /// @return The type of the vertex (from the VertexTypes enum).
  /// @code
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// VertexTypes type = vertex.getType();
  /// std::cout << "Type of the vertex: " << type << std::endl;
  /// @endcode

  virtual VertexTypes        getType() const final;

  // Get для типа вершины в фомате строки

  /// @brief getTypeName
  /// This method returns the string representation of the vertex type by
  /// parsing the vertex type enum value using the settings object
  /// associated with the vertex
  /// @return The string representation of the vertex type.
  /// @code
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// std::string typeName = vertex.getTypeName();
  /// std::cout << "String representation of the vertex type: " << typeName;
  /// @endcode

  virtual std::string        getTypeName() const final;

  // Get-Set для имен входов

  /// @brief setName
  /// This method sets the name of the vertex to the specified string.
  /// @param i_name The new name for the vertex.
  /// @code
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// vertex.setName("new_vertex_name");
  /// std::cout << "New name of the vertex: " << vertex.getName() << std::endl;
  /// @endcode

  void                       setName(const std::string i_name);

  /// @brief getName
  /// Returns the name of the vertex
  /// @return The name of the vertex.
  /// @code
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// std::string name = vertex.getName();
  /// std::cout << "Name of the vertex: " << name << std::endl;
  /// @endcode

  std::string                getName() const;

  // Get для значения вершины
  /// @brief getValue
  /// Returns the value of the vertex.
  /// @return The value of the vertex.
  /// @code
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// char value = vertex.getValue();
  /// std::cout << "Value of the vertex: " << value << std::endl;
  /// @endcode

  virtual char               getValue() const;

  /// @brief updateValue
  /// TO DO:

  virtual char               updateValue() = 0;

  // Get-Set для уровня

  /// @brief setLevel
  /// Sets the level of the vertex
  /// @param i_level The new level for the vertex
  /// @code
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// vertex.setLevel(2);
  /// std::cout << "New level of the vertex: " << vertex.getLevel() << '\n';
  /// @endcode

  void                       setLevel(const unsigned i_level);

  /// @brief getLevel
  /// Returns the level of the vertex
  /// @return The level of the vertex
  /// @code
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// unsigned level = vertex.getLevel();
  /// std::cout << "Level of the vertex: " << level << std::endl;
  /// @endcode

  unsigned                   getLevel() const;

  /// @brief updateLevel
  /// This method updates the level of the vertex based on the levels of its
  /// input connections. It iterates through each input connection and sets
  /// the vertex level to the maximum level of its input connections plus one.
  /// @code
  /// TO DO:
  /// @endcode
  /// @throws std::invalid_argument if any of the input connections are invalid
  /// (i.e., null pointers)

  virtual void               updateLevel();
  virtual Gates              getGate() const { return Gates::GateDefault; };

  // Get-Set для базового графа
  // void setBaseGraph(std::shared_ptr<OrientedGraph> const i_baseGraph);
  GraphPtrWeak               getBaseGraph() const;

  std::vector<VertexPtrWeak> getInConnections() const;
  int                        addVertexToInConnections(VertexPtr i_vert);
  bool removeVertexToInConnections(VertexPtr i_vert, bool i_full = false);

  std::vector<VertexPtr> getOutConnections() const;
  bool                   addVertexToOutConnections(VertexPtr i_vert);
  bool                   removeVertexToOutConnections(VertexPtr i_vert);

  virtual std::string    calculateHash(bool recalculate = false);

  virtual std::string    getInstance();

  virtual std::string    toVerilog();

protected:
  GraphPtrWeak               d_baseGraph;

  std::string                d_name;
  char                       d_value;
  unsigned                   d_level;

  std::vector<VertexPtrWeak> d_inConnections;
  std::vector<VertexPtr>     d_outConnections;

  std::shared_ptr<Settings>  d_settings =
      Settings::getInstance("GraphVertexBase");

private:
  // Определяем тип вершины: подграф, вход, выход, константа или одна из базовых
  // логических операций.
  VertexTypes          d_type;

  // Счетчик вершин для именования и подобного
  static uint_fast64_t d_count;
  std::string          hashed = "";
};