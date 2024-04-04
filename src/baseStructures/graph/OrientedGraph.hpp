#pragma once

#include <baseStructures/graph/GraphVertexBase.hpp>
#include <baseStructures/graph/enums.hpp>
#include <settings/Settings.hpp>

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>

// TODO: Добавить проверку на имена файлов при доблении новых вершин

class GraphVertexBase;  // Проблема циклического определения
class OrientedGraph : public std::enable_shared_from_this<OrientedGraph> {
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

  void setBaseGraph(OrientedGraph *i_baseGraph);
  OrientedGraph *getBaseGraph() const;

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

  size_t getEdgesCount() { return d_edgesCount; }

  std::vector<std::shared_ptr<OrientedGraph>> getSubGraphs() const;
  std::map<VertexTypes, std::vector<std::shared_ptr<GraphVertexBase>>>
  getBaseVertexes() const;
  std::shared_ptr<GraphVertexBase> getVerticeByIndex(int idx) const;

  bool toVerilog(std::ofstream& i_fileStream);
  // toAdjencyMatrix
  bool toGraphML(std::ofstream& i_fileStream) const;
  std::string toGraphML(int i_nesting = 0) const;
  // vizualize
  // calcGraph

  // Сделать матрицу смежности для хранения и быстрого поиска связей?

  std::vector<std::shared_ptr<GraphVertexBase>> getVerticesByType(
      const VertexTypes i_type, const std::string i_name = "",
      const bool i_addSubGraphs = false) const;
  std::vector<std::shared_ptr<GraphVertexBase>> getVerticesByLevel(
      const int i_level);

  std::vector<std::shared_ptr<GraphVertexBase>> getVerticesByName(
      const std::string i_name, const bool i_addSubGraphs = false) const;

  bool operator==(const OrientedGraph& rhs);
  std::string calculateHash(bool recalculate = false);

  std::map<Gates, int> getGatesCount() const;
  std::map<Gates, std::map<Gates, int>> getEdgesGatesCount() const;

 private:
  size_t d_edgesCount = 0;

  std::string hashed = "";
  OrientedGraph *d_baseGraph = nullptr;

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

  // used for quick gates count
  std::map<Gates, int> d_gatesCount = {
      {Gates::GateAnd, 0}, {Gates::GateNand, 0}, {Gates::GateOr, 0},
      {Gates::GateNor, 0}, {Gates::GateNot, 0},  {Gates::GateBuf, 0},
      {Gates::GateXor, 0}, {Gates::GateXnor, 0}};
  // used for quick edges of gate type count;
  std::map<Gates, std::map<Gates, int>> d_edgesGatesCount;

  std::shared_ptr<Settings> d_settings = Settings::getInstance("OrientedGraph");

};

template<class Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const std::string& fmt, std::ostream& os, const Tuple& t) {
        const size_t idx = fmt.find_last_of('%');
        TuplePrinter<Tuple, N - 1>::print( std::string( fmt, 0, idx ), os, t );
        os << std::get<N - 1>(t) << std::string( fmt, idx + 1 );
    }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1>{
    static void print(const std::string& fmt, std::ostream& os, const Tuple& t) {
        const size_t idx = fmt.find_first_of('%');
        os << std::string( fmt, 0, idx ) << std::get<0>(t) << std::string( fmt, idx + 1 );
    }
};

template<class... Args>
std::string format(const std::string& fmt, Args&&... args) {
    std::stringstream ss;

    const auto t = std::make_tuple(std::forward<Args>(args)...);

    TuplePrinter<decltype(t), sizeof...(Args)>::print(fmt, ss, t);
    return ss.str();
}