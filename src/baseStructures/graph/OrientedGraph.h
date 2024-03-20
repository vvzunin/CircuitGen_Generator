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
  // TODO here can be some problems!!!
  OrientedGraph& operator=(OrientedGraph&& other) =
      default;  // оператор перемещающего присваивания
  OrientedGraph(const OrientedGraph& other) = default;
  OrientedGraph(OrientedGraph&& other) = default;

  std::shared_ptr<OrientedGraph> shared_from_this();

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

  void setBaseGraph(std::shared_ptr<OrientedGraph> const i_baseGraph);
  std::shared_ptr<OrientedGraph> getBaseGraph() const;

  // TODO: Заменить все const на const &
  std::shared_ptr<GraphVertexBase> addInput(const std::string i_name = "");
  std::shared_ptr<GraphVertexBase> addOutput(const std::string i_name = "");
  std::shared_ptr<GraphVertexBase> addConst(const char i_value,
                                            const std::string i_name = "");
  std::shared_ptr<GraphVertexBase> addGate(const Gates i_gate,
                                           const std::string i_name = "");
  std::shared_ptr<OrientedGraph> addSubGraph(const std::string i_name = "");

  bool addEdge(std::shared_ptr<GraphVertexBase> from,
               std::shared_ptr<GraphVertexBase> to);
  bool addEdges(std::vector<std::shared_ptr<GraphVertexBase>> from1,
                std::shared_ptr<GraphVertexBase> to);

  std::vector<std::shared_ptr<OrientedGraph>> getSubGraphs() const;
  std::map<VertexTypes, std::vector<std::shared_ptr<GraphVertexBase>>>
  getBaseVertexes() const;
  std::shared_ptr<GraphVertexBase> getVerticeByIndex(int idx) const;

  bool toVerilog(std::ofstream& i_fileStream);
  // toAdjencyMatrix
  // toGraphML
  // vizualize
  // calcGraph

  // Сделать матрицу смежности для зранения и быстрого поиска связей?

  std::vector<std::shared_ptr<GraphVertexBase>> getVerticesByType(
      const VertexTypes i_type, const std::string i_name = "",
      const bool i_addSubGraphs = false) const;
  std::vector<std::shared_ptr<GraphVertexBase>> getVerticesByLevel(
      const int i_level);

  std::vector<std::shared_ptr<GraphVertexBase>> getVerticesByName(
      const std::string i_name, const bool i_addSubGraphs = false) const;

  bool operator==(const OrientedGraph& rhs);
  std::string calculateHash(bool recalculate = false);

 private:
  std::shared_ptr<OrientedGraph> this_ptr;
  std::string hashed = "";
  std::shared_ptr<OrientedGraph> d_baseGraph = nullptr;

  std::string d_name;

  // Пока не реализован функционал.
  bool d_needLevelUpdate = true;

  std::vector<std::shared_ptr<OrientedGraph>> d_subGraphs;
  std::map<VertexTypes, std::vector<std::shared_ptr<GraphVertexBase>>>
      d_vertexes{
          {VertexTypes::input, std::vector<std::shared_ptr<GraphVertexBase>>()},
          {VertexTypes::output,
           std::vector<std::shared_ptr<GraphVertexBase>>()},
          {VertexTypes::constant,
           std::vector<std::shared_ptr<GraphVertexBase>>()},
          {VertexTypes::gate, std::vector<std::shared_ptr<GraphVertexBase>>()}};

  static uint_fast64_t d_countGraph;

  std::shared_ptr<Settings> d_settings = Settings::getInstance("OrientedGraph");
};