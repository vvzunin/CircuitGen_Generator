#pragma once

#include <baseStructures/graph/GraphVertexBase.h>
#include <baseStructures/graph/enums.h>
#include <settings/Settings.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

// TODO: Добавить проверку на имена файлов при доблении новых вершин

class GraphVertexBase;  // Проблема циклического определения
class OrientedGraph {
 public:
  // friend class Circuit;
  OrientedGraph(const std::string i_name = "");

  // TODO: Добавить использование gates_inputs_info.

  virtual ~OrientedGraph();

  // TODO: Написать руками для полного копирования, а не только указателей.
  OrientedGraph& operator=(const OrientedGraph& other) =
      default;  // оператор копирующего присваивания
  OrientedGraph& operator=(OrientedGraph&& other) =
      default;  // оператор перемещающего присваивания
  OrientedGraph(const OrientedGraph& other) = default;
  OrientedGraph(OrientedGraph&& other) = default;

  // Количество gate в графе, за исключением подграфов
  int baseSize() const;
  // Количество gate в графе, включая подграфы
  int fullSize() const;
  // sum of gates, inputs, outputs and consts sizes
  size_t sumFullSize() const;
  // Имеются ли gate в схеме, включая подграфы
  bool isEmpty() const;
  // Имеются ли в схеме какие-либо vertex
  bool isEmptyFull() const;

  void setName(const std::string& i_name);
  std::string getName() const;
  bool needToUpdateLevel() const;

  void updateLevels();

  unsigned getMaxLevel();

  void setBaseGraph(OrientedGraph* const i_baseGraph);
  OrientedGraph* getBaseGraph() const;

  // TODO: Заменить все const на const &
  GraphVertexBase* addInput(const std::string i_name = "");
  GraphVertexBase* addOutput(const std::string i_name = "");
  GraphVertexBase* addConst(const char i_value, const std::string i_name = "");
  GraphVertexBase* addGate(const Gates i_gate, const std::string i_name = "");
  OrientedGraph* addSubGraph(const std::string i_name = "");

  bool addEdge(GraphVertexBase* from, GraphVertexBase* to);
  bool addEdges(std::vector<GraphVertexBase*> from1, GraphVertexBase* to);

  std::vector<OrientedGraph*> getSubGraphs() const;
  std::map<VertexTypes, std::vector<GraphVertexBase*>> getBaseVertexes() const;
  GraphVertexBase* getVerticeByIndex(int idx) const;

  bool toVerilog(std::ofstream& i_fileStream);
  // toAdjencyMatrix
  // toGraphML
  // vizualize
  // calcGraph

  // Сделать матрицу смежности для зранения и быстрого поиска связей?

  std::vector<GraphVertexBase*> getVerticesByType(
      const VertexTypes i_type, const std::string i_name = "",
      const bool i_addSubGraphs = false) const;
  std::vector<GraphVertexBase*> getVerticesByLevel(const int i_level);

  std::vector<GraphVertexBase*> getVerticesByName(
      const std::string i_name, const bool i_addSubGraphs = false) const;

  bool operator==(const OrientedGraph& rhs);
  std::string calculateHash(bool recalculate = false);

 private:
  std::string hashed = "";
  OrientedGraph* d_baseGraph = nullptr;

  std::string d_name;

  // Пока не реализован функционал.
  bool d_needLevelUpdate = true;

  std::vector<OrientedGraph*> d_subGraphs;
  std::map<VertexTypes, std::vector<GraphVertexBase*>> d_vertexes{
      {VertexTypes::input, std::vector<GraphVertexBase*>()},
      {VertexTypes::output, std::vector<GraphVertexBase*>()},
      {VertexTypes::constant, std::vector<GraphVertexBase*>()},
      {VertexTypes::gate, std::vector<GraphVertexBase*>()}};

  static uint_fast64_t d_countGraph;

  std::shared_ptr<Settings> d_settings = Settings::getInstance("OrientedGraph");
};