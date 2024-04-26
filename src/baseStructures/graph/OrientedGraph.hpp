#pragma once

#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include <baseStructures/graph/enums.hpp>
#include <baseStructures/graph/GraphVertexBase.hpp>
#include <settings/Settings.hpp>

// TODO: Добавить проверку на имена файлов при доблении новых вершин

class GraphVertexBase;  // Проблема циклического определения

#define GraphPtr      std::shared_ptr<OrientedGraph>
#define GraphPtrWeak  std::weak_ptr<OrientedGraph>

#define VertexPtr     std::shared_ptr<GraphVertexBase>
#define VertexPtrWeak std::weak_ptr<GraphVertexBase>

class OrientedGraph : public std::enable_shared_from_this<OrientedGraph> {
public:
  // friend class Circuit;
  OrientedGraph(const std::string& i_name = "");

  // TODO: Добавить использование gates_inputs_info.

  virtual ~OrientedGraph();

  OrientedGraph& operator=(const OrientedGraph& other
  ) = default;  // оператор копирующего присваивания
  OrientedGraph& operator=(OrientedGraph&& other
  ) = default;  // оператор перемещающего присваивания
  OrientedGraph(const OrientedGraph& other) = default;
  OrientedGraph(OrientedGraph&& other)      = default;

  // Количество gate в графе, за исключением подграфов
  int                       baseSize() const;
  // Количество gate в графе, включая подграфы
  int                       fullSize() const;
  // sum of gates, inputs, outputs and consts sizes
  size_t                    sumFullSize() const;
  // Имеются ли gate в схеме, включая подграфы
  bool                      isEmpty() const;
  // Имеются ли в схеме какие-либо vertex
  bool                      isEmptyFull() const;

  void                      setName(const std::string& i_name);
  std::string               getName() const;
  bool                      needToUpdateLevel() const;

  void                      updateLevels();

  unsigned                  getMaxLevel();

  void                      addParentGraph(GraphPtr i_baseGraph);
  std::vector<GraphPtrWeak> getParentGraphs() const;

  void                      setCurrentParent(GraphPtr parent);
  void                      resetCounters(GraphPtr where);

  // TODO: Заменить все const на const &
  VertexPtr                 addInput(const std::string& i_name = "");
  VertexPtr                 addOutput(const std::string& i_name = "");
  VertexPtr addConst(const char& i_value, const std::string& i_name = "");
  VertexPtr addGate(const Gates& i_gate, const std::string& i_name = "");
  std::vector<VertexPtr>
         addSubGraph(GraphPtr i_subGraph, std::vector<VertexPtr> i_inputs);

  bool   addEdge(VertexPtr from, VertexPtr to);
  bool   addEdges(std::vector<VertexPtr> from1, VertexPtr to);

  size_t getEdgesCount() { return d_edgesCount; }

  std::set<GraphPtr>                            getSubGraphs() const;
  std::set<GraphPtr>                            getSetSubGraphs() const;
  std::map<VertexTypes, std::vector<VertexPtr>> getBaseVertexes() const;
  VertexPtr   getVerticeByIndex(int idx) const;

  std::string getGraphInstance();
  std::pair<bool, std::string>
              toVerilog(std::string i_path, std::string i_filename = "");
  // toAdjencyMatrix
  bool        toGraphML(std::ofstream& i_fileStream) const;
  std::string toGraphML(int i_nesting = 0) const;
  // visualize
  // calcGraph

  // Сделать матрицу смежности для хранения и быстрого поиска связей?

  std::vector<VertexPtr> getVerticesByType(
      const VertexTypes& i_type,
      const std::string& i_name         = "",
      const bool&        i_addSubGraphs = false
  ) const;
  std::vector<VertexPtr> getVerticesByLevel(const int& i_level);

  std::vector<VertexPtr> getVerticesByName(
      const std::string& i_name,
      const bool&        i_addSubGraphs = false
  ) const;

  bool                                  operator==(const OrientedGraph& rhs);
  std::string                           calculateHash(bool recalculate = false);

  std::map<Gates, int>                  getGatesCount() const;
  std::map<Gates, std::map<Gates, int>> getEdgesGatesCount() const;

private:
  static size_t              d_countNewGraphInstance;
  size_t                     d_currentInstance;
  // as we can have multiple parents, we save
  // for toVerilog current parent graph
  GraphPtrWeak               d_currentParentGraph;
  size_t                     d_edgesCount = 0;

  std::string                d_hashed     = "";
  std::vector<GraphPtrWeak>  d_parentGraphs;

  std::string                d_name;

  // Пока не реализован функционал.
  bool                       d_needLevelUpdate = true;

  // also we need to now, was .v file for subgraph created, or not
  bool                       d_alreadyParsed   = false;
  // We can add a subgraph multiple times
  // so we need to count instances to verilog.
  // We are counting to know, which inputs and outputs should we use now
  std::map<size_t, uint64_t> d_graphInstanceToVerilogCount;

  // each subgraph has one or more outputs. We save them,
  // depending on subgraph instance number
  std::map<size_t, std::vector<std::vector<VertexPtr>>> d_subGraphsOutputsPtr;
  std::vector<VertexPtr>                                d_allSubGraphsOutputs;
  // we have such pairs: number of subragh instances,
  std::map<size_t, std::vector<std::vector<VertexPtr>>> d_subGraphsInputsPtr;

  std::set<GraphPtr>                                    d_subGraphs;
  std::map<VertexTypes, std::vector<VertexPtr>>         d_vertexes {
              {VertexTypes::input, std::vector<VertexPtr>()},
              {VertexTypes::output, std::vector<VertexPtr>()},
              {VertexTypes::constant, std::vector<VertexPtr>()},
              {VertexTypes::gate, std::vector<VertexPtr>()},
              {VertexTypes::subGraph, std::vector<VertexPtr>()}
  };

  static uint_fast64_t d_countGraph;

  // used for quick gates count
  std::map<Gates, int> d_gatesCount = {
      {Gates::GateAnd, 0},
      {Gates::GateNand, 0},
      {Gates::GateOr, 0},
      {Gates::GateNor, 0},
      {Gates::GateNot, 0},
      {Gates::GateBuf, 0},
      {Gates::GateXor, 0},
      {Gates::GateXnor, 0}
  };
  // used for quick edges of gate type count;
  std::map<Gates, std::map<Gates, int>> d_edgesGatesCount;

  std::shared_ptr<Settings> d_settings = Settings::getInstance("OrientedGraph");
};