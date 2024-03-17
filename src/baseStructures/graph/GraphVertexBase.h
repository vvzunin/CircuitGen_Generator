#pragma once

#include <string>
#include <vector>

#include "settings/Settings.h"

#include "OrientedGraph.h"

#include <baseStructures/graph/enums.h>

class OrientedGraph; // Проблема циклического определения
class GraphVertexBase {
public:
  GraphVertexBase(
    const VertexTypes i_type, 
    OrientedGraph* const i_graph = nullptr);

  GraphVertexBase(
    const VertexTypes i_type, 
    const std::string i_name, 
    OrientedGraph* const i_graph = nullptr);

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

  // Get-Set для базового графа
  // void setBaseGraph(OrientedGraph* const i_baseGraph);
  OrientedGraph* getBaseGraph() const;

  std::vector<GraphVertexBase*> getInConnections() const;
  int addVertexToInConnections(GraphVertexBase* const i_vert);
  bool removeVertexToInConnections(GraphVertexBase* const i_vert, bool i_full = false);

  std::vector<GraphVertexBase*> getOutConnections() const;
  bool addVertexToOutConnections(GraphVertexBase* const i_vert);
  bool removeVertexToOutConnections(GraphVertexBase* const i_vert);

  std::string calculateHash(bool recalculate = false);

protected:

  OrientedGraph* d_baseGraph = nullptr;
  
  std::string d_name;
  char d_value;
  unsigned d_level;
  
  std::vector<GraphVertexBase*> d_inConnections;
  std::vector<GraphVertexBase*> d_outConnections;

  std::shared_ptr<Settings> d_settings = Settings::getInstance("GraphVertexBase");
private:

  // Определяем тип вершины: подграф, вход, выход, константа или одна из базовых логических операций.
  VertexTypes d_type;    

  // Счетчик вершин для именования и подобного
  static uint_fast64_t d_count;
  std::string hashed = "";
};