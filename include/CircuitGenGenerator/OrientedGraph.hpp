#pragma once

#include <atomic>
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

/// class OrientedGraph
///
/// @param d_countNewGraphInstance Static variable to count new graph instances
/// @param d_currentInstance Current instance count
/// @param d_currentParentGraph Weak pointer to the current parent graph
/// @param d_edgesCount The number of edges in the graph
/// @param d_hashed Hashed value of the graph
/// @param d_parentGraphs Vector of weak pointers to parent graphs
/// @param d_name The name of the graph
/// @param d_needLevelUpdate A flag indicating whether the vertex levels in
/// the graph need to be updated
/// @param d_alreadyParsed TO DO:
/// @param d_graphInstanceToVerilogCount Map to count instances to Verilog
/// This map is used to count how many times each subgraph instance has been
/// converted to Verilog. The key represents the instance number of the
/// subgraph, and the value represents the count of how many times it has been
/// converted to Verilog
/// @param d_subGraphsOutputsPtr Map storing outputs of subgraphs
/// This map stores the outputs of subgraphs. It maps the instance number of
/// the subgraph to a vector of vectors of VertexPtr. The outer vector
/// represents the subgraph instances, and the inner vector represents the
/// outputs of each instance of the subgraph.
/// @param d_allSubGraphsOutputs Vector storing all outputs of subgraphs
/// @param d_subGraphsInputsPtr Map storing inputs of subgraphs
/// This map stores the inputs of subgraphs. It maps the instance number of
/// the subgraph to a vector of vectors of VertexPtr. The outer vector
/// represents the subgraph instances, and the inner vector represents the
/// inputs of each instance of the subgraph.
/// @param d_subGraphs Set of subgraphs
/// This set stores the subgraphs present in the graph. It is used to keep
/// track of all the subgraphs associated with the current graph instance
/// @param d_vertexes Map of vertex types to vectors of vertex pointers
/// @param d_countGraph Static counter for the total number of graphs
/// @param d_gatesCount Map for quick gates count
/// This map is used for quick counting of gates in the graph. It maps each
/// gate type (Gates) to the count of gates of that type present in the graph.
/// @param d_edgesGatesCount Map for quick count of edges of gate type
/// This map is used for quick counting of edges between different types of
/// gates in the graph. It maps each gate type (Gates) to another map, where
/// the inner map maps gate types to the count of edges between them.
/// @param d_settings Shared pointer to Settings instance

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
  /// @brief baseSize returns the number of "gate" type vertices in the graph
  /// @return An integer value representing the number of "gate" type vertices
  /// in the graph

  int                       baseSize() const;
  // Количество gate в графе, включая подграфы
  /// @brief fullSize returns the total number of vertices in the graph,
  /// including vertices from all subgraphs. It recursively traverses all
  /// the subgraphs and sums up the number of vertices in each of them
  /// @return An integer value representing the total number of vertices
  /// in the graph, including vertices from all subgraphs

  int                       fullSize() const;
  // sum of gates, inputs, outputs and consts sizes
  /// @brief sumFullSize returns the total number of vertices of all types
  /// in the graph, including input vertices, constants, gates, and output
  /// vertices
  /// @return the size of all vertices in the graph, summing the number of
  /// vertices of each type
  size_t                    sumFullSize() const;

  // Имеются ли gate в схеме, включая подграфы
  bool                      isEmpty() const;

  /// @brief isEmptyFull It is used to check the emptiness of a graph,
  /// including all its subgraphs. It recursively traverses all the subgraphs
  /// and checks if they are empty
  /// @return bool - true if the graph and all its subgraphs are empty, and
  /// false if at least one of them contains vertice
  bool                      isEmptyFull() const;

  /// @brief setName Used to set the name of the graph. It takes a string as
  /// an argument and sets the d_name field to this string
  /// @param i_name the new name of the graph

  void                      setName(const std::string& i_name);

  /// @brief getName Used to get the name of the graph
  /// @return the name of the graph

  std::string               getName() const;

  /// @brief needToUpdateLevel it is used to check whether the vertex levels
  /// in the graph need to be updated
  /// @return bool - true if updating the vertex levels in the graph is
  /// required, and false if not required

  bool                      needToUpdateLevel() const;

  /// @brief updateLevels TO DO: the method body is commented out!!!
  ///
  /// */

  void                      updateLevels();

  /// @brief getMaxLevel
  /// Calculates and returns the maximum level of the output vertices in the
  /// graph
  /// @return maximum level of the output vertices
  /// @code
  ///  OrientedGraph graph("ExampleGraph");
  /// // Add vertices and edges to the graph (omitted for brevity)
  /// // Calculate the maximum level of output vertices
  /// unsigned maxLevel = graph.getMaxLevel();
  /// // Output the result
  /// std::cout << "Maximum level of output vertices: " << maxLevel << '\n';
  /// @endcode

  unsigned                  getMaxLevel();

  /// @brief addParentGraph
  /// Adds a parent graph to the current graph
  /// @param i_baseGraph A shared pointer to the parent graph to be added
  /// @code
  /// // Create the first OrientedGraph instance
  /// auto graph1 = std::make_shared<OrientedGraph>("Graph1");
  /// // Create the second OrientedGraph instance
  /// auto graph2 = std::make_shared<OrientedGraph>("Graph2");
  /// // Add graph1 as a parent to graph2
  /// graph2->addParentGraph(graph1);
  /// // Now graph2 has graph1 as one of its parent graphs
  /// @endcode
  void                      addParentGraph(GraphPtr i_baseGraph);

  /// @brief getParentGraphs
  /// Retrieves the parent graphs of the current graph
  /// @return A vector containing weak pointers to the parent graphs
  /// @code
  /// // Create an instance of OrientedGraph
  /// auto graph = std::make_shared<OrientedGraph>("ExampleGraph");
  /// // Add some parent graphs to the current graph (omitted for brevity)
  /// // Retrieve the parent graphs of the current graph
  /// std::vector<std::weak_ptr<OrientedGraph>> parentGraphs =
  /// graph->getParentGraphs();
  /// // Iterate over the parent graphs and perform operations (omitted for
  /// brevity)
  /// @endcode

  std::vector<GraphPtrWeak> getParentGraphs() const;

  /// @brief setCurrentParent
  /// Sets the current parent graph of the current graph
  /// @param parent A shared pointer to the parent graph to be set as the
  /// current parent
  /// @code
  /// // Create an instance of OrientedGraph
  /// auto graph = std::make_shared<OrientedGraph>("ExampleGraph");
  /// // Create another instance of OrientedGraph to be set as the current
  /// parent auto parentGraph = std::make_shared<OrientedGraph>("ParentGraph");
  /// // Set parentGraph as the current parent of graph
  /// graph->setCurrentParent(parentGraph);
  /// // Now parentGraph is set as the current parent of graph
  /// @endcode
  void                      setCurrentParent(GraphPtr parent);

  /// @brief resetCounters
  /// Resets counters associated with a specific graph instance
  /// @param where A shared pointer to the subgraph whose counters need to be
  /// reset
  void                      resetCounters(GraphPtr where);

  // TODO: Заменить все const на const &

  /// @brief addInput
  /// Adds an input vertex to the current graph
  /// @param i_name The name of the input vertex to be added
  /// @return A shared pointer to the newly created input vertex
  /// @code
  /// // Create an instance of OrientedGraph
  /// auto graph = std::make_shared<OrientedGraph>("ExampleGraph");
  /// // Add an input vertex to the graph
  /// auto inputVertex = graph->addInput("Input1");
  /// // Now inputVertex is a shared pointer to the newly added input vertex
  /// @endcode

  VertexPtr                 addInput(const std::string& i_name = "");

  /// @brief addOutput
  /// Adds an output vertex to the current graph
  /// @param i_name The name of the output vertex to be added
  /// @return A shared pointer to the newly created output vertex
  /// @code
  /// // Create an instance of OrientedGraph
  /// auto graph = std::make_shared<OrientedGraph>("ExampleGraph");
  /// // Add an output vertex to the graph
  /// auto outputVertex = graph->addOutput("Output1");
  /// // Now outputVertex is a shared pointer to the newly added output vertex
  /// @endcode

  VertexPtr                 addOutput(const std::string& i_name = "");

  /// @brief addConst
  /// Adds a constant vertex to the current graph
  /// @param i_value The value of the constant vertex to be added
  /// @param i_name The name of the constant vertex to be added
  /// @return A shared pointer to the newly created constant vertex
  /// @code
  /// // Create an instance of OrientedGraph
  /// auto graph = std::make_shared<OrientedGraph>("ExampleGraph");
  /// // Add a constant vertex to the graph with value 'A' and name "Constant1"
  /// auto constantVertex = graph->addConst('A', "Constant1");
  /// // Now constantVertex is a shared pointer to the newly added constant
  /// vertex
  /// @endcode

  VertexPtr addConst(const char& i_value, const std::string& i_name = "");

  /// @brief addGate
  /// Adds a gate vertex to the current graph
  /// @param i_gate The type of the gate vertex to be added
  /// @param i_name The name of the gate vertex to be added
  /// @return A shared pointer to the newly created gate vertex
  /// @code
  /// // Create an instance of OrientedGraph
  /// auto graph = std::make_shared<OrientedGraph>("ExampleGraph");
  /// // Add a gate vertex to the graph with type GateAnd and name "Gate1"
  /// auto gateVertex = graph->addGate(Gates::GateAnd, "Gate1");
  /// // Now gateVertex is a shared pointer to the newly added gate vertex
  /// @endcode

  VertexPtr addGate(const Gates& i_gate, const std::string& i_name = "");

  /// @brief addSubGraph
  /// Adds a subgraph to the current graph
  /// @param i_subGraph A shared pointer to the subgraph to be added
  /// @param i_inputs A vector containing the input vertices to be connected
  /// to the subgraph
  /// @return A vector containing the output vertices of the subgraph
  /// @code
  /// // Create an instance of OrientedGraph
  /// auto graph = std::make_shared<OrientedGraph>("ExampleGraph");
  /// // Create a subgraph
  /// auto subGraph = std::make_shared<OrientedGraph>("SubGraph");
  /// // Create input vertices for the subgraph
  /// std::vector<VertexPtr> subGraphInputs;
  /// for (int i = 0; i < 3; ++i)
  /// {
  ///   auto inputVertex = graph->addInput("SubGraphInput" +
  ///   std::to_string(i+1)); subGraphInputs.push_back(inputVertex);
  /// }
  /// // Add the subgraph to the graph with its inputs
  /// auto subGraphOutputs = graph->addSubGraph(subGraph, subGraphInputs);
  /// // Now subGraphOutputs contains the output vertices of the subgraph
  /// @endcode
  /// @throws std::invalid_argument if the number of inputs does not match
  /// the number of input vertices in the subgraph

  std::vector<VertexPtr>
         addSubGraph(GraphPtr i_subGraph, std::vector<VertexPtr> i_inputs);

  /// @brief addEdge
  /// Adds an edge between two vertices in the current graph
  /// @param from A shared pointer to the vertex where the edge originates
  /// @param to A shared pointer to the vertex where the edge terminates
  /// @return true if the edge was successfully added, false otherwise
  /// @code
  /// // Create an instance of OrientedGraph
  /// auto graph = std::make_shared<OrientedGraph>("ExampleGraph");
  /// // Create two vertices
  /// auto vertex1 = graph->addInput("Vertex1");
  /// auto vertex2 = graph->addOutput("Vertex2");
  /// // Add an edge from vertex1 to vertex2
  /// bool edgeAdded = graph->addEdge(vertex1, vertex2);
  /// if (edgeAdded)
  /// {
  ///   std::cout << "Edge successfully added between Vertex1 and Vertex2\n";
  /// }
  /// else
  /// {
  ///   std::cerr << "Failed to add edge between Vertex1 and Vertex2\n";
  /// }
  /// @endcode
  /// @throws std::invalid_argument if attempting to add an edge from one
  /// subgraph to another when the 'from' vertex is not an output, or when
  /// attempting to add an edge to another subgraph when the 'to' vertex is
  /// not an input

  bool   addEdge(VertexPtr from, VertexPtr to);

  /// @brief addEdges
  /// Adds multiple edges from a vector of source vertices to a target vertex
  /// @param from1 A vector containing the source vertices from which edges
  /// will originate
  /// @param to A shared pointer to the target vertex where the edges will
  /// terminate
  /// @return true if all edges were successfully added, false if at least one
  /// edge failed to be added
  /// @code
  /// // Create an instance of OrientedGraph
  /// auto graph = std::make_shared<OrientedGraph>("ExampleGraph");
  /// // Create multiple source vertices
  /// std::vector<VertexPtr> sources;
  /// for (int i = 0; i < 3; ++i)
  /// {
  ///   auto vertex = graph->addInput("Source" + std::to_string(i+1));
  ///   sources.push_back(vertex);
  /// }
  /// // Create a target vertex
  /// auto target = graph->addOutput("Target");
  /// // Add edges from all source vertices to the target vertex
  /// bool edgesAdded = graph->addEdges(sources, target);
  /// if (edgesAdded)
  /// {
  ///   std::cout << "Edges successfully added from all sources to the
  ///   target\n";
  /// }
  /// else
  /// {
  ///   std::cerr << "Failed to add edges from one or more sources to the
  ///   target\n";
  /// }
  /// @endcode

  bool   addEdges(std::vector<VertexPtr> from1, VertexPtr to);

  /// @brief getEdgesCount
  /// Retrieves the total number of edges in the graph
  /// @return The total number of edges in the graph
  size_t getEdgesCount() { return d_edgesCount; }

  std::set<GraphPtr>                            getSubGraphs() const;
  std::set<GraphPtr>                            getSetSubGraphs() const;
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

  bool        toGraphML(std::ofstream& i_fileStream) const;
  std::string toGraphML(int i_indent = 0, const std::string& i_prefix = "")
      const;
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

  // @brief getGatesCount Returns a display containing the number of each gate
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
  static std::atomic_size_t  d_countNewGraphInstance;
  size_t                     d_graphID;
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

  static std::atomic_size_t d_countGraph;

  // used for quick gates count
  std::map<Gates, int>      d_gatesCount = {
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