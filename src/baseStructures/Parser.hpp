
#pragma once

#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "graph/OrientedGraph.hpp"
using GatesInfo = std::map<Gates, std::vector<int>>;

/// class Parser
/// @param d_logExpressions It can represent a set of logical expressions
/// describing the logic of combinational schemes. These expressions can contain
/// combinations of logical operations and variables. for example, A AND B, NOT,
/// C XOR(A, Y)*
/// @param d_graph An object of the Oriented Graph class, which is an oriented
/// graph used to represent relationships between logical expressions.
/// @param d_settings A pointer to an object of the Settings class, which is a
/// singleton and is used to store settings related to the "Parser"
/// */

class Parser {
public:
  Parser(
      const std::string&                             i_logExpression,
      const std::map<std::string, std::vector<int>>& i_info
  );
  Parser(
      const std::vector<std::string>&                i_logExpressions,
      const std::map<std::string, std::vector<int>>& i_info
  );

  Parser(const std::string& i_logExpression, const GatesInfo& i_info);
  Parser(
      const std::vector<std::string>& i_logExpressions,
      const GatesInfo&                i_info
  );

  Parser()                               = default;
  Parser(const Parser& other)            = default;
  Parser& operator=(const Parser& other) = default;
  Parser(Parser&& other)                 = default;
  Parser&  operator=(Parser&& other)     = default;

  /// @brief getGraph
  /// Get the graph object
  /// This method returns a pointer to the graph object associated with the
  /// Parser instance
  /// @return A pointer to the graph object
  GraphPtr getGraph() const;
  std::pair<int32_t, std::vector<std::string>> splitLogicExpression(
      std::string i_expr
  );

  /// @brief multipleVerteciesToOne
  /// This method takes a vector of vertices representing the current layout,
  /// combines them into a single vertex using the specified logical operation,
  /// and returns the resulting vertex
  /// @param curLayout The vector of vertices representing the current layout
  /// @param operation The logical operation to apply
  /// @param graph A pointer to the graph object
  /// @return A pointer to the resulting vertex after combining the input
  /// vertices
  /// @code
  /// std::vector<VertexPtr> vertices = {vertex1, vertex2, vertex3};
  /// Gates operation = Gates::AND;
  /// GraphPtr graph = std::make_shared<Graph>();
  /// Parser parser;
  /// VertexPtr result = parser.multipleVerteciesToOne(vertices, operation, graph);
  /// @endcode

  VertexPtr multipleVerteciesToOne(
      std::vector<VertexPtr> curLayout,
      Gates                  operation,
      GraphPtr               graph
  );


  /// @brief parseToVertex
  /// This method takes a logical expression, splits it, and converts it into a
  /// vertex within the graph. It recursively parses sub-expressions until it
  /// constructs the complete expression tree
  /// @param i_expr The logical expression to parse
  /// @return A pointer to the resulting vertex representing the expression, or
  /// nullptr on failure
  /// @code
  /// Parser parser;
  /// std::string expression = "output A AND B";
  /// VertexPtr result = parser.parseToVertex(expression);
  /// if (result)
  /// {
  ///   std::cout << "Vertex successfully created." << std::endl;
  /// } 
  /// else 
  /// {
  ///   std::cerr << "Failed to parse the expression." << std::endl;
  /// }
  /// @endcode

  VertexPtr parseToVertex(const std::string& i_expr);


  /// @brief parseAll
  /// Parse all logical expressions and construct the graph.
  /// This method initializes a new oriented graph and iterates through all logical
  /// expressions stored in the `d_logExpressions` member variable. For each expression,
  /// it checks if it has balanced brackets using the `createBrackets` method. If the
  /// brackets are balanced, it calls the `parseToVertex` method to parse the expression
  /// and construct the corresponding vertex in the graph. If parsing fails for any
  /// expression, the method returns false. Otherwise, it returns true indicating
  /// successful parsing of all expressions.
  /// @return True if parsing is successful for all expressions, false otherwise
  /// @code
  /// TO DO:
  /// @endcode

  bool      parseAll();

  /// @brief setGatesInputsInfo
  /// Set information about gates inputs
  /// @param i_info A map where keys are gate names as strings and values are
  /// vectors of integers specifying the number of inputs for each gate

  void setGatesInputsInfo(const std::map<std::string, std::vector<int>>& i_info
  );
  
  /// @brief setGatesInputsInfo
  /// TO DO:
  /// Analog setGatesInputsInfo
  /// @param GatesInfo = std::map<Gates, std::vector<int>>
  void setGatesInputsInfo(const GatesInfo& i_info);

private:
  std::vector<std::string>  d_logExpressions;

  GraphPtr                  d_graph;
  std::shared_ptr<Settings> d_settings = Settings::getInstance("Parser");

  std::pair<bool, std::vector<std::pair<int32_t, int32_t>>> createBrackets(
      const std::string& i_expr
  );
  bool inBrackets(
      const std::vector<std::pair<int32_t, int32_t>>& i_brackets,
      int32_t                                         i_position
  ) const;
  VertexPtr   parseInputNot(std::string oper, std::string name);

  std::string deleteExtraSpaces(std::string i_s);
  std::map<std::string, VertexPtr> d_inputsByNames;
  std::map<std::string, VertexPtr> d_notInputsByNames;

  GatesInfo                        d_gatesInputsInfo;
};
