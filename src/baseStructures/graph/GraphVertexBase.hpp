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
/// std::cout << "String representation of gate type: " << gateString <<
/// std::endl; gateType = Gates::GateNot; gateString =
/// VertexUtils::gateToString(gateType); std::cout << "String representation of
/// gate type: " << gateString << std::endl;
/// @endcode
std::string gateToString(Gates i_type);

/// @brief vertexTypeToComment
/// Converts a vertex type enum value to its Verilog representation
/// @param i_type The vertex type enum value.
/// @return The Verilog representation of the vertex type
/// @code
/// VertexTypes vertexType = VertexTypes::Input;
/// std::string verilogType = VertexUtils::vertexTypeToVerilog(vertexType);
/// std::cout << "Verilog representation of vertex type: " << verilogType <<
/// std::endl;
/// @endcode
std::string vertexTypeToVerilog(VertexTypes i_type);

/// @brief vertexTypeToComment
/// Converts a vertex type enum value to its comment representation
/// This function takes a vertex type enum value (from the VertexTypes enum) and
/// returns its corresponding comment representation. The comment representation
/// is based on the vertex type and is used for generating comments or
/// documentation
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
/// @param d_baseGraph A weak pointer to the base graph containing this vertex
/// @param i_name The name of the vertex. It is a string containing the name
/// of a vertex
/// @param d_value The value of the vertex
/// @param d_level The vertex level is represented by the unsigned type
/// @param d_inConnections vector of weak pointers to input connections with
/// other vertices
/// @param d_outConnections vector of strong pointers to output connections
/// with other vertices
/// @param d_settings A pointer to the settings object for this vertex
/// @param d_type Vertex Type - Defined by the VertexTypes enumeration
/// @param d_count Vertex counter for naming and other purposes.
/// Represented by the uint_fast64_t type
/// @param hashed A string containing the calculated hash value for the vertex

class GraphVertexBase {
public:
  /// @brief GraphVertexBase
  /// Constructs a GraphVertexBase object with the specified vertex type and
  /// optional graph
  /// @param i_type The type of the vertex (from the VertexTypes enum).
  /// @param i_graph Optional pointer to the graph containing the vertex
  GraphVertexBase(const VertexTypes i_type, GraphPtr i_graph = nullptr);

  /// @brief GraphVertexBase
  /// Constructs a GraphVertexBase object with the specified vertex type, name,
  /// and optional graph.
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
  std::string                getName(const std::string& i_prefix) const;

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

  /// @brief getGate
  /// Returns the type of the basic logic gate represented by this vertex. If
  /// the vertex does not correspond to any basic logic gate, it returns Gate
  /// Default
  /// @return The type of the basic logic gate represented by this vertex
  /// @code
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// Gates gateType = vertex.getGate();
  /// @endcode

  virtual Gates              getGate() const { return Gates::GateDefault; };

  // Get-Set для базового графа
  // void setBaseGraph(std::shared_ptr<OrientedGraph> const i_baseGraph);

  /// @brief getBaseGraph
  /// @return a weak pointer to the base graph associated with this vertex.
  /// @code
  /// TO DO:
  /// @endcode

  GraphPtrWeak               getBaseGraph() const;

  /// @brief getInConnections
  /// @return A vector of weak pointers to the input connections of this vertex
  /// @code
  /// // Creating an instance of the GraphVertexBase class
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// // Get the vector of the input connections of this vertex
  /// std::vector<VertexPtrWeak> inConnections = vertex.getInConnections();
  /// // Iterate over the input connections and do something with them
  /// for (const auto& connection : inConnections)
  /// {
  /// // Checking if the connection is valid
  ///   if (!connection.expired())
  /// {
  /// // Getting shared_ptr from weak_ptr
  /// VertexPtr inputVertex = connection.lock();
  /// if (inputVertex)
  /// {
  ///   // Doing something with the input Vertex
  /// }
  /// }
  /// }
  /// @endcode

  std::vector<VertexPtrWeak> getInConnections() const;

  /// @brief addVertexToInConnections
  /// Adds a vertex to the input connections of this vertex and returns the
  /// count of occurrences of the given vertex in the input connections
  /// @param i_vert The vertex to be added to the input connections
  /// @return The count of occurrences of the given vertex in the input
  /// connections after adding it
  /// @code
  /// // Creating an instance of the GraphVertexBase class
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// // Creating another vertex
  /// VertexPtr anotherVertex =
  /// std::make_shared<GraphVertexBase>(VertexTypes::input, "vertex2");
  /// // Add the second vertex to the input connections of the first vertex
  /// // and get the number of occurrences
  /// int count = vertex.addVertexToInConnections(anotherVertex);
  /// // Output the result
  /// std::cout << "The number of occurrences of the second vertex in the input
  /// connections of the first vertex: " << count << std::endl;
  /// @endcode

  /// @brief addVertexToInConnections
  /// Adds a vertex to the input connections of this vertex and returns the
  /// count of occurrences of the given vertex in the input connections
  /// @param i_vert The vertex to be added to the input connections
  /// @return The count of occurrences of the given vertex in the input
  /// connections after adding it
  /// @code
  /// // Creating an instance of the GraphVertexBase class
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// // Creating another vertex
  /// VertexPtr anotherVertex =
  /// std::make_shared<GraphVertexBase>(VertexTypes::input, "vertex2");
  /// // Adding a second vertex to the input connections of the first vertex
  /// and getting the number of occurrences
  /// int occurrences = vertex.addVertexToInConnections(anotherVertex);
  /// // Output of the result
  /// std::cout << "The number of occurrences of the second vertex in the input
  /// connections of the first vertex: " << occurrences << std::endl;
  /// @endcode

  int                        addVertexToInConnections(VertexPtr i_vert);

  /// @brief removeVertexToInConnections
  /// Removes a vertex from the input connections of this vertex.
  /// @param i_vert The vertex to be removed from the input connections.
  /// @param i_full lag indicating whether to remove all occurrences of the
  /// vertex from the input connections.
  /// If true, all occurrences will be removed. If false, only the first
  /// occurrence will be removed. Default - false
  /// @return true if the vertex was successfully removed, false otherwise.
  /// @code
  /// // Creating an instance of the GraphVertexBase class
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// // Creating another vertex
  /// VertexPtr anotherVertex =
  /// std::make_shared<GraphVertexBase>(VertexTypes::input, "vertex2");
  /// // Adding a second vertex to the input connections of the first vertex
  /// vertex.addVertexToInConnections(anotherVertex);
  /// // Removing the second vertex from the input connections of the first
  /// vertex bool removed = vertex.removeVertexToInConnections(anotherVertex,
  /// false);
  /// // Output of the result
  /// if (removed)
  /// {
  ///    std::cout << "The second vertex has been successfully removed from the
  ///    input connections of the first vertex" << std::endl;
  /// }
  /// else
  /// {
  ///    std::cout << "The second vertex was not found in the input connections
  ///    of the first vertex" << std::endl;
  /// }
  /// @endcode

  bool removeVertexToInConnections(VertexPtr i_vert, bool i_full = false);

  /// @brief getOutConnections
  /// @return A vector of shared pointers to the output connections of this
  /// vertex
  /// @code
  /// // Creating an instance of the GraphVertexBase class
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// // Creating another vertex
  /// VertexPtr anotherVertex =
  /// std::make_shared<GraphVertexBase>(VertexTypes::output, "vertex2");
  /// // Adding the second vertex to the output connections of the first vertex
  /// vertex.addVertexToOutConnections(anotherVertex);
  /// // get the vector of the output connections of the first vertex
  /// std::vector<VertexPtr> outConnections = vertex.getOutConnections();
  /// // output information about the output connections
  /// std::cout << "Output connections of the first vertex:" << std::endl;
  /// for (const auto& connection : outConnections)
  /// {
  ///   std::cout << " - " << connection->getName() << std::endl;
  /// }
  /// @endcode

  std::vector<VertexPtr> getOutConnections() const;

  /// @brief addVertexToOutConnections
  /// Adds a vertex to the output connections of this vertex if it is not
  /// already present
  /// @param i_vert The vertex to be added to the output connections
  /// @return true if the vertex was successfully added, false if it was
  /// already present in the output connections.
  /// @code
  /// TO DO:
  /// @endcode

  bool                   addVertexToOutConnections(VertexPtr i_vert);

  /// @brief removeVertexToOutConnections
  /// Removes a vertex from the output connections of this vertex.
  /// @param i_vert The vertex to be removed from the output connections.
  /// @return true if the vertex was successfully removed, false otherwise.
  /// @code
  /// // Creating an instance of the GraphVertexBase class
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// // Creating another vertex
  /// VertexPtr anotherVertex =
  /// std::make_shared<GraphVertexBase>(VertexTypes::output, "vertex2");
  /// // Adding the second vertex to the output connections of the first vertex
  /// vertex.addVertexToOutConnections(anotherVertex);
  /// // Removing the second vertex from the output connections of the first
  /// vertex bool removed = vertex.removeVertexToOutConnections(anotherVertex);
  /// // Output of the result
  /// if (removed)
  /// {
  ///   std::cout << "Вторая вершина успешно удалена из выходных соединений
  ///   первой вершины." << std::endl;
  /// }
  /// else
  /// {
  ///   std::cout << "Вторая вершина не найдена в выходных соединениях первой
  ///   вершины." << std::endl;
  /// }
  /// @endcode

  bool                   removeVertexToOutConnections(VertexPtr i_vert);

  /// @brief calculateHash
  /// Calculates the hash value for the vertex based on its outgoing
  /// connections.
  /// @param recalculate Flag indicating whether to recalculate the hash
  /// value even if it has already been calculated.
  /// If true, the hash value will be recalculated.
  /// If false and the hash value has already been calculated,
  /// the cached hash value will be returned without recalculation.
  /// @return The hash value of the vertex based on its outgoing connections.
  /// @code
  /// // Creating an instance of the GraphVertexBase class
  /// GraphVertexBase vertex(VertexTypes::output, "vertex1");
  /// // Creating two more vertices
  /// VertexPtr vertex2 = std::make_shared<GraphVertexBase>(VertexTypes::input,
  /// "vertex2"); VertexPtr vertex3 =
  /// std::make_shared<GraphVertexBase>(VertexTypes::input, "vertex3");
  /// // Adding the second and third vertices to the output connections of the
  /// first vertex vertex.addVertexToOutConnections(vertex2);
  /// vertex.addVertexToOutConnections(vertex3);
  /// // Calculating the hash for the first vertex
  /// std::string hashValue = vertex.calculateHash();
  /// // Output of the result
  /// std::cout << "Hash for the first vertex: " << hashValue << std::endl;
  /// @endcode

  virtual std::string    calculateHash(bool recalculate = false);

  /// @brief getInstance
  /// Generates an instance declaration for the vertex in Verilog format.
  /// @return A string containing the instance declaration for the vertex
  /// in Verilog format.
  /// @code
  /// // Creating an instance of the GraphVertexBase class
  /// GraphVertexBase vertex(VertexTypes::input, "vertex1");
  /// // Generating an instance for a vertex in Verilog format
  /// std::string instanceDeclaration = vertex.getInstance();
  /// // Displaying the instance on the screen
  /// std::cout << "Instance declaration for vertex: " << instanceDeclaration <<
  /// std::endl;
  /// @endcode

  virtual std::string    getInstance();

  /// @brief toVerilog
  /// Generates Verilog code for the vertex
  /// @return A string containing Verilog code for the vertex, or an empty
  /// string if the vertex type is not "output" or if the incoming connection
  /// is invalid
  /// @code
  /// // Creating an instance of the GraphVertexBase class with the type
  /// "output" and the name "output_vertex"
  /// GraphVertexBase outputVertex(VertexTypes::output, "output_vertex");
  /// // Creating another vertex with the type "input" and the name
  /// "input_vertex" VertexPtr inputVertex =
  /// std::make_shared<GraphVertexBase>(VertexTypes::input, "input_vertex");
  /// // Setting the input connection for the vertex "output_vertex"
  /// outputVertex.addVertexToInConnections(inputVertex);
  /// // Generating the Verilog code for the vertex "output_vertex"
  /// std::string verilogCode = outputVertex.toVerilog();
  /// // Display the generated Verilog code on the screen
  /// std::cout << "Generated Verilog code:\n" << verilogCode << std::endl;
  /// @endcode

  virtual std::string    toVerilog();

  virtual bool           isSubgraphBuffer() const { return false; }

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