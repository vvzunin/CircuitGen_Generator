#pragma once

#include <memory>
#include <string>
#include <vector>

#include <baseStructures/graph/enums.hpp>

#include "OrientedGraph.hpp"
#include "settings/Settings.hpp"

class OrientedGraph;  // Проблема циклического определения

#define GraphPtr  std::shared_ptr<OrientedGraph>
#define VertexPtr std::shared_ptr<GraphVertexBase>

namespace VertexUtils {
std::string gateToString(Gates i_type);

std::string vertexTypeToVerilog(VertexTypes i_type);
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
  GraphVertexBase(const VertexTypes i_type, GraphPtr i_graph = nullptr);

  GraphVertexBase(
      const VertexTypes i_type,
      const std::string i_name,
      GraphPtr          i_graph = nullptr
  );

  // TODO crashes add destructor call
  virtual ~GraphVertexBase();

  // Get для типа вершины

  /// @brief calculateHash It is designed to calculate the hash value of the
  /// current vertex of the graph and all its descendants
  /// (outgoing connections)
  /// @param recalculate A flag indicating whether the hash value needs to be
  /// recalculated even if it has already been previously calculated.
  /// The default value is false
  /// @return Hash value of the current vertex of the graph and all its
  /// descendants

  std::string            calculateHash(bool recalculate = false);

  /// @brief getTypeName Designed to get a string representation of the vertex
  /// type.
  /// @return String representation of the vertex type

  virtual VertexTypes    getType() const final;

  // Get для типа вершины в фомате строки

  virtual std::string    getTypeName() const final;

  // Get-Set для имен входов
  /// @brief setName it is intended for setting the vertex name
  /// @param i_name The new vertex name to set

  void                   setName(const std::string i_name);
  std::string            getName() const;

  // Get для значения вершины
  virtual char           getValue() const;
  virtual char           updateValue() = 0;

  // Get-Set для уровня
  void                   setLevel(const unsigned i_level);
  unsigned               getLevel() const;

  virtual void           updateLevel();
  virtual Gates          getGate() const { return Gates::GateDefault; };

  // Get-Set для базового графа
  // void setBaseGraph(std::shared_ptr<OrientedGraph> const i_baseGraph);
  GraphPtr               getBaseGraph() const;

  std::vector<VertexPtr> getInConnections() const;
  int                    addVertexToInConnections(VertexPtr const i_vert);
  bool removeVertexToInConnections(VertexPtr const i_vert, bool i_full = false);

  std::vector<VertexPtr> getOutConnections() const;
  bool                   addVertexToOutConnections(VertexPtr const i_vert);
  bool                   removeVertexToOutConnections(VertexPtr const i_vert);

  std::string            calculateHash(bool recalculate = false);

  virtual std::string    getInstance();

  virtual std::string    toVerilog();

protected:
  GraphPtr                  d_baseGraph = nullptr;

  std::string               d_name;
  char                      d_value;
  unsigned                  d_level;

  std::vector<VertexPtr>    d_inConnections;
  std::vector<VertexPtr>    d_outConnections;

  std::shared_ptr<Settings> d_settings =
      Settings::getInstance("GraphVertexBase");

private:
  // Определяем тип вершины: подграф, вход, выход, константа или одна из базовых
  // логических операций.
  VertexTypes          d_type;

  // Счетчик вершин для именования и подобного
  static uint_fast64_t d_count;
  std::string          hashed = "";
};