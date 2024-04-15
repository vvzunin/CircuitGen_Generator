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

#define GraphPtr std::shared_ptr<OrientedGraph>

/// @file OrientedGraph.hpp
/// TODO: Add a check for file names when adding new vertices

// TODO: Добавить проверку на имена файлов при доблении новых вершин

class GraphVertexBase;  // Проблема циклического определения

#define VertexPtr std::shared_ptr<GraphVertexBase>


/// class OrientedGraph A oriented graph that can contain vertices of
/// various types (input, output, constant, etc.) and edges between them
/// @param d_edgesCount The number of edges in the graph
/// @param hashed A string representing the calculated hash value of the graph
/// @param d_baseGraph A pointer to a base graph if that graph is a subgraph
/// of another
/// @param d_name The name of the graph
/// @param d_needLevelUpdate A flag indicating whether the vertex levels in
/// the graph need to be updated
/// @param d_subGraphs The vector of pointers to the subgraphs of this graph
/// @param d_vertexes  A map containing lists of vertices of various types
/// in a graph
/// @param d_countGraph A static variable used to count the number of graphs
/// created
/// @param d_gatesCount A map containing the number of vertices of each type
/// in the graph
/// @param edgesGatesCount A map containing the number of edges between
/// different types of gate vertices in the graph***
/// @param d_settings A pointer to the object of the settings used for this
/// graph
/// 

class OrientedGraph : public std::enable_shared_from_this<OrientedGraph> {
public:
  // friend class Circuit;
  OrientedGraph(const std::string& i_name = "");

  // TODO: Добавить использование gates_inputs_info.

  virtual ~OrientedGraph();

  // TODO: Написать руками для полного копирования, а не только указателей.
  OrientedGraph& operator=(const OrientedGraph& other
  ) = default;  // оператор копирующего присваивания
  // TODO here can be some problems!!!
  OrientedGraph& operator=(OrientedGraph&& other
  ) = default;  // оператор перемещающего присваивания
  OrientedGraph(const OrientedGraph& other) = default;
  OrientedGraph(OrientedGraph&& other)      = default;

  // Количество gate в графе, за исключением подграфов

  /// @brief baseSize returns the number of "gate" type vertices in the graph
  /// @return An integer value representing the number of "gate" type vertices
  /// in the graph

  int                              baseSize() const;
  // Количество gate в графе, включая подграфы

  /// @brief fullSize returns the total number of vertices in the graph,
  /// including vertices from all subgraphs. It recursively traverses all
  /// the subgraphs and sums up the number of vertices in each of them
  /// @return An integer value representing the total number of vertices
  /// in the graph, including vertices from all subgraphs

  int                              fullSize() const;
  // sum of gates, inputs, outputs and consts sizes

  /// @brief sumFullSize returns the total number of vertices of all types
  /// in the graph, including input vertices, constants, gates, and output
  /// vertices
  /// @return the size of all vertices in the graph, summing the number of
  /// vertices of each type

  size_t                           sumFullSize() const;
  // Имеются ли gate в схеме, включая подграфы

  /// @brief isEmpty it is used to check whether the graph is empty, that is,
  /// whether it contains vertices
  /// @return true if the graph is empty (does not contain vertices), and
  /// false if the graph contains vertices

  bool                             isEmpty() const;
  // Имеются ли в схеме какие-либо vertex

  /// @brief isEmptyFull It is used to check the emptiness of a graph,
  /// including all its subgraphs. It recursively traverses all the subgraphs
  /// and checks if they are empty
  /// @return bool - true if the graph and all its subgraphs are empty, and
  /// false if at least one of them contains vertice

  bool                             isEmptyFull() const;

  /// @brief setName Used to set the name of the graph. It takes a string as
  /// an argument and sets the d_name field to this string
  /// @param i_name the new name of the graph

  void                             setName(const std::string& i_name);

  /// @brief getName Used to get the name of the graph
  /// @return the name of the graph

  std::string                      getName() const;

  /// @brief needToUpdateLevel it is used to check whether the vertex levels
  /// in the graph need to be updated
  /// @return bool - true if updating the vertex levels in the graph is
  /// required, and false if not required

  bool                             needToUpdateLevel() const;

  /// @brief updateLevels TO DO: the method body is commented out!!!
  /// 
  /// */

  void                             updateLevels();

  /// @brief getMaxLevel it is used to get the maximum level of vertices
  /// in the graph. It updates the vertex levels by calling the update
  /// Levels() method, and then finds the maximum level among the output
  /// vertices
  /// @return the maximum level of vertices in the graph

  unsigned                         getMaxLevel();

  void               addParentGraph(GraphPtr i_baseGraph);
  std::set<GraphPtr> getParentGraphs() const;

  void               setCurrentParent(GraphPtr parent);
  void               resetCounters(GraphPtr where);

  // TODO: Заменить все const на const &
  VertexPtr          addInput(const std::string& i_name = "");
  VertexPtr          addOutput(const std::string& i_name = "");
  VertexPtr addConst(const char& i_value, const std::string& i_name = "");
  VertexPtr addGate(const Gates& i_gate, const std::string& i_name = "");
  std::vector<VertexPtr>
         addSubGraph(GraphPtr i_subGraph, std::vector<VertexPtr> i_inputs);

  bool   addEdge(VertexPtr from, VertexPtr to);
  bool   addEdges(std::vector<VertexPtr> from1, VertexPtr to);

  size_t getEdgesCount() { return d_edgesCount; }

  std::vector<GraphPtr>                         getSubGraphs() const;
  std::map<VertexTypes, std::vector<VertexPtr>> getBaseVertexes() const;
  VertexPtr   getVerticeByIndex(int idx) const;

  std::string getGraphInstance();
  std::pair<bool, std::string>
              toVerilog(std::string i_path, std::string i_filename = "");
  // toAdjencyMatrix

  /// @brief toGraphML Writes the graph structure in GraphML format to the
  /// specified output stream
  /// @param i_fileStream A reference to the std::ofstream object, which
  /// represents the file in which the graph structure will be written in
  /// GraphML format
  /// @return bool: Returns true if the graph structure has been successfully
  /// written in GraphML format, and false otherwise. In this case, it always
  /// returns true.

  bool                             toGraphML(std::ofstream& i_fileStream) const;

  /// @brief toGraphML generates a string representation of the graph structure
  /// in GraphML format with a nesting level
  /// @param i_nesting The nesting level, which determines the number of
  /// indents before each element in GraphML format
  /// @return String representation of the graph structure in GraphML format

  std::string                      toGraphML(int i_nesting = 0) const;
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

  /// @brief calculateHash calculates hash values for a graph based on the hash
  /// values of its vertices
  /// @param recalculate A Boolean value indicating whether the hash value
  /// should be recalculated even if it has already been previously calculated.
  /// By default, false.
  /// @return A string representing the hash value of the graph

  std::string                           calculateHash(bool recalculate = false);

  /// @brief getGatesCount Returns a display containing the number of each gate
  /// type in the graph
  /// @return A display where each key is a type of gate (Gates), and the
  /// corresponding value is the number of gates of this type in the graph

  std::map<Gates, int>                  getGatesCount() const;

  /// @brief getEdgesGatesCount Returns a mapping containing the number of
  /// edges between different types of gates in the graph
  /// @return A mapping where each external key is a gate type, and the
  /// corresponding value is an internal mapping containing the number of
  /// edges between different types of gates in the graph

  std::map<Gates, std::map<Gates, int>> getEdgesGatesCount() const;

private:
  // as we can have multiple parents, we save
  // for toVerilog current parent graph
  GraphPtr                     d_currentParentGraph;
  size_t                       d_edgesCount = 0;

  std::string                  d_hashed     = "";
  std::set<GraphPtr>           d_parentGraphs;

  std::string                  d_name;

  // Пока не реализован функционал.
  bool                         d_needLevelUpdate = true;

  // also we need to now, was .v file for subgraph created, or not
  bool                         d_alreadyParsed   = false;
  // We can add a subgraph multiple times
  // so we need to count instances to verilog.
  // We are counting to know, which inputs and outputs should we use now
  std::map<GraphPtr, uint64_t> d_graphInstanceToVerilogCount;

  // each subgraph has one or more outputs. We save them,
  // depending on subgraph instance number
  std::map<GraphPtr, std::vector<std::vector<VertexPtr>>> d_subGraphsOutputsPtr;
  std::vector<VertexPtr>                                  d_allSubGraphsOutputs;
  // we have such pairs: number of subragh instances,
  std::map<GraphPtr, std::vector<std::vector<VertexPtr>>> d_subGraphsInputsPtr;

  std::vector<GraphPtr>                                   d_subGraphs;
  std::map<VertexTypes, std::vector<VertexPtr>>           d_vertexes {
                {VertexTypes::input, std::vector<VertexPtr>()},
                {VertexTypes::output, std::vector<VertexPtr>()},
                {VertexTypes::constant, std::vector<VertexPtr>()},
                {VertexTypes::gate, std::vector<VertexPtr>()}};

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
      {Gates::GateXnor, 0}};
  // used for quick edges of gate type count;
  std::map<Gates, std::map<Gates, int>> d_edgesGatesCount;

  std::shared_ptr<Settings> d_settings = Settings::getInstance("OrientedGraph");
};

template<class Tuple, std::size_t N>
struct TuplePrinter {
  static void print(const std::string& fmt, std::ostream& os, const Tuple& t) {
    const size_t idx = fmt.find_last_of('%');
    TuplePrinter<Tuple, N - 1>::print(std::string(fmt, 0, idx), os, t);
    os << std::get<N - 1>(t) << std::string(fmt, idx + 1);
  }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
  static void print(const std::string& fmt, std::ostream& os, const Tuple& t) {
    const size_t idx = fmt.find_first_of('%');
    os << std::string(fmt, 0, idx) << std::get<0>(t)
       << std::string(fmt, idx + 1);
  }
};

template<class... Args>
std::string format(const std::string& fmt, Args&&... args) {
  std::stringstream ss;

  const auto        t = std::make_tuple(std::forward<Args>(args)...);

  TuplePrinter<decltype(t), sizeof...(Args)>::print(fmt, ss, t);
  return ss.str();
}