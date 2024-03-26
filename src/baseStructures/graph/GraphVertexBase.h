#pragma once

#include <baseStructures/graph/enums.h>

#include <memory>
#include <string>
#include <vector>

#include "OrientedGraph.h"
#include "settings/Settings.h"

class OrientedGraph;  // Проблема циклического определения
class GraphVertexBase {
 public:
  GraphVertexBase(const VertexTypes i_type,
                  OrientedGraph *i_graph = nullptr);

  GraphVertexBase(const VertexTypes i_type, const std::string i_name,
                  OrientedGraph *i_graph = nullptr);

  // TODO craches ad destructor call
  virtual ~GraphVertexBase();

  // Get для типа вершины
  virtual VertexTypes getType() const final;
  // Get для типа вершины в фомате строки
  virtual std::string getTypeName() const final;

  // Get-Set для имен входов
  void setName(const std::string i_name);
  std::string getName() const;

  // Get для значения вершины
  virtual char getValue() const;
  virtual char updateValue() = 0;

  // Get-Set для уровня
  void setLevel(const unsigned i_level);
  unsigned getLevel() const;

  virtual void updateLevel();
  virtual Gates getGate() const { return Gates::GateDefault; };

  // Get-Set для базового графа
  // void setBaseGraph(std::shared_ptr<OrientedGraph> const i_baseGraph);
  OrientedGraph *getBaseGraph() const;

  std::vector<std::shared_ptr<GraphVertexBase>> getInConnections() const;
  int addVertexToInConnections(std::shared_ptr<GraphVertexBase> const i_vert);
  bool removeVertexToInConnections(
      std::shared_ptr<GraphVertexBase> const i_vert, bool i_full = false);

  std::vector<std::shared_ptr<GraphVertexBase>> getOutConnections() const;
  bool addVertexToOutConnections(std::shared_ptr<GraphVertexBase> const i_vert);
  bool removeVertexToOutConnections(
      std::shared_ptr<GraphVertexBase> const i_vert);

  std::string calculateHash(bool recalculate = false);

 protected:
  OrientedGraph *d_baseGraph = nullptr;

  std::string d_name;
  char d_value;
  unsigned d_level;

  std::vector<std::shared_ptr<GraphVertexBase>> d_inConnections;
  std::vector<std::shared_ptr<GraphVertexBase>> d_outConnections;

  std::shared_ptr<Settings> d_settings =
      Settings::getInstance("GraphVertexBase");

 private:
  // Определяем тип вершины: подграф, вход, выход, константа или одна из базовых
  // логических операций.
  VertexTypes d_type;

  // Счетчик вершин для именования и подобного
  static uint_fast64_t d_count;
  std::string hashed = "";
};