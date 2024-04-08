#pragma once

#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include <baseStructures/graph/enums.hpp>
#include <baseStructures/graph/GraphVertexBase.hpp>
#include <settings/Settings.hpp>

/// @file OrientedGraph.hpp
/// TODO: Add a check for file names when adding new vertices

// TODO: Добавить проверку на имена файлов при доблении новых вершин

class GraphVertexBase;  // Проблема циклического определения

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
  OrientedGraph(const std::string i_name = "");

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

  /// @brief setBaseGraph Used to set the base graph for the current graph.
  /// This method sets the d_baseGraph pointer to the base graph passed as an
  /// argument
  /// @param i_baseGraph a pointer to an object of the OrientedGraph class as
  /// an argument to i_baseGraph, which represents the base graph

  void                             setBaseGraph(OrientedGraph* i_baseGraph);

  /// @brief getBaseGraph Used to get a pointer to the base graph associated
  /// with the current graph
  /// @return a pointer to the base graph associated with the current graph.
  /// There may be a null ptr if the base graph is not set

  OrientedGraph*                   getBaseGraph() const;

  // TODO: Заменить все const на const &

  /// @brief addInput Used to add a new input vertex to the graph.
  /// @param i_name name of the new input vertex
  /// @return a pointer to the newly created input vertex

  std::shared_ptr<GraphVertexBase> addInput(const std::string i_name = "");

  /// @brief addOutput Used to add a new output vertex to the graph
  /// @param i_name name of the new output vertex
  /// @return pointer to the newly created output vertex

  std::shared_ptr<GraphVertexBase> addOutput(const std::string i_name = "");

  /// @brief addConst used to add a new constant vertex to the graph
  /// @param i_value the value (char) of the constant that will be set for
  /// the new constant vertex
  /// @param i_name the name of the new constant vertex. By default, an empty
  /// name will be assigned
  /// @return a pointer to a newly created constant vertex

  std::shared_ptr<GraphVertexBase>
      addConst(const char i_value, const std::string i_name = "");

  /// @brief addGate It is used to add a new vertex-gate to the graph
  /// @param i_gate The Gates enumeration representing the type of gate to be
  /// added to the graph
  /// @param i_name the name of the new vertex is the valve
  /// @return Pointer to the newly created vertex-gate

  std::shared_ptr<GraphVertexBase>
      addGate(const Gates i_gate, const std::string i_name = "");

  /// @brief addSubGraph Used to add a new subgraph to the current graph
  /// @param i_name name of the new subgraph
  /// @return A pointer to the newly created subgraph

  std::shared_ptr<OrientedGraph> addSubGraph(const std::string i_name = "");

  /// @brief addEdge Used to add an edge (connection) between two vertices
  /// in a graph
  /// @param from A smart pointer of type std::shared_ptr<GraphVertexBase>
  /// representing the vertex from which the edge originates
  /// @param to A smart pointer of type std::shared_ptr<GraphVertexBase>
  /// representing the vertex that the edge is included in
  /// @return bool: true if the addition of links was successful, and false
  /// otherwise

  bool                           addEdge(
                                std::shared_ptr<GraphVertexBase> from,
                                std::shared_ptr<GraphVertexBase> to
                            );

  /// @brief addEdges It is used to add edges (links) between several vertices
  /// and one target vertex in the graph
  /// @param from1 A vector of smart pointers of type
  /// std::shared_ptr<GraphVertexBase> representing the vertices from which
  /// the edges originate
  /// @param to A smart pointer of type std::shared_ptr<GraphVertexBase>,
  /// representing a vertex that includes edges
  /// @return bool: true if all edges were successfully added, and false
  /// otherwise

  bool addEdges(
      std::vector<std::shared_ptr<GraphVertexBase>> from1,
      std::shared_ptr<GraphVertexBase>              to
  );
  
  /// @brief Returns the number of edges in the graph
  /// @return The number of edges in the graph

  size_t getEdgesCount() { return d_edgesCount; }

  /// @brief getSubGraphs Returns a vector of pointers to subgraphs
  /// of a given graph
  /// @return std::vector<std::shared_ptr<OrientedGraph>>: Vector of smart
  /// pointers to subgraphs of this graph

  std::vector<std::shared_ptr<OrientedGraph>> getSubGraphs() const;

  /// @brief getBaseVertexes Returns a map containing a list of vertices of
  /// the basic types of this graph
  /// @return A map containing a list of vertices of the basic types of this
  /// graph

  std::map<VertexTypes, std::vector<std::shared_ptr<GraphVertexBase>>>
                                   getBaseVertexes() const;

  /// @brief getVerticeByIndex Returns the vertex of the graph at the
  /// specified index
  /// @param An integer value representing the index of the vertex to
  /// be retrieved
  /// @return A smart pointer to the top of the graph

  std::shared_ptr<GraphVertexBase> getVerticeByIndex(int idx) const;

  /// @brief toVerilog generates a description of the Verilog module
  /// based on the graph structure
  /// @i_fileStream A reference to the std::ofstream object, which
  /// represents the file in which the description of the Verilog
  /// module will be written
  /// @return bool: Returns true if the Verilog description generation
  /// of the module was successful, and false otherwise. In this case,
  /// it always returns true.

  bool                             toVerilog(std::ofstream& i_fileStream);
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

  /// @brief getVerticesByType returns a list of vertices of a graph of a
  /// certain type, taking into account the specified name and the
  /// possibility of adding subgraphs
  /// @param i_type The type of vertices to be obtained
  /// (for example, input, output, gate elements, etc.)
  /// @param i_name The name of the vertex to be filtered by. By default,
  /// an empty string, which means that there is no filtering by name
  /// @param i_addSubGraphs A flag that determines whether to include
  /// vertices from subgraphs. By default, false.
  /// @return A list of graph vertices of the specified type and, if
  /// necessary, of subgraphs.

  std::vector<std::shared_ptr<GraphVertexBase>> getVerticesByType(
      const VertexTypes i_type,
      const std::string i_name         = "",
      const bool        i_addSubGraphs = false
  ) const;

  /// @brief getVerticesByLevel TO DO: it is necessary to write the body
  /// of the method
  /// 
  /// */

  std::vector<std::shared_ptr<GraphVertexBase>> getVerticesByLevel(
      const int i_level
  );

  /// @brief getVerticesByName it is designed to get all the vertices of a
  /// graph with the specified name, with the possibility of including
  /// vertices from subgraphs
  /// @param i_name A string containing the name of the vertex to be found
  /// in the graph
  /// @param i_addSubGraphs A Boolean value that determines whether to include
  /// vertices from subgraphs. By default, false.
  /// @return Returns a vector containing pointers to all vertices with the
  /// specified name in the graph and, if necessary, from subgraphs

  std::vector<std::shared_ptr<GraphVertexBase>> getVerticesByName(
      const std::string i_name,
      const bool        i_addSubGraphs = false
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
  size_t                                      d_edgesCount = 0;

  std::string                                 hashed       = "";
  OrientedGraph*                              d_baseGraph  = nullptr;

  std::string                                 d_name;

  // Пока не реализован функционал.
  bool                                        d_needLevelUpdate = true;

  std::vector<std::shared_ptr<OrientedGraph>> d_subGraphs;
  std::map<VertexTypes, std::vector<std::shared_ptr<GraphVertexBase>>>
      d_vertexes {
          {VertexTypes::input, std::vector<std::shared_ptr<GraphVertexBase>>()},
          {VertexTypes::output,
           std::vector<std::shared_ptr<GraphVertexBase>>()},
          {VertexTypes::constant,
           std::vector<std::shared_ptr<GraphVertexBase>>()},
          {VertexTypes::gate, std::vector<std::shared_ptr<GraphVertexBase>>()}};

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