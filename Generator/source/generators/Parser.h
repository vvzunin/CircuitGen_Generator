#pragma once

#include <string>
#include <memory>

#include <graph/OrientedGraph.h>

/// class Parser
/// @param d_logExpressions It can represent a set of logical expressions describing the logic of combinational schemes. These expressions can contain combinations of logical operations and variables. for example, A AND B, NOT, C XOR(A, Y)*
/// @param d_graph An object of the Oriented Graph class, which is an oriented graph used to represent relationships between logical expressions.
/// @param d_settings A pointer to an object of the Settings class, which is a singleton and is used to store settings related to the "Parser"
/// 
/// 
/// */

class Parser
{
public:

    /// @brief Parser The Parser constructor accepts a single argument of type const std::string &i_logExpression. this constructor initializes the Parser object by adding one Boolean expression (after removing the extra spaces) to the d_logExpressions vector. TO DO:  d_graph.setVertexCount(0)
    /// @param i_logExpression This argument is assumed to contain a single Boolean expression that will be processed by the parser.
    /// */

    Parser(const std::string &i_logExpression);

    /// @brief Parser This constructor initializes the Parser object using the passed i_log Expressions vector. It goes through each element of the i_expressions vector using a for loop and adds each Boolean expression to the internal d_logExpressions vector of the Parser object. TO DO:  d_graph.setVertexCount(0)
    ///
    /// @param i_logExpressions The i_log Expressions vector contains a set of logical expressions that will be processed by the parser
    /// */


    Parser(const std::vector<std::string> &i_logExpressions);


    OrientedGraph getGraph() const;


    std::pair<int, std::vector<std::string>> splitLogicExpression(std::string i_expr);

    /// @brief parse The method takes the string i_expr representing a Boolean expression and parses it to build an oriented graph of dependencies between Boolean expressions
    /// @param o_expr This is a string containing a Boolean expression that needs to be parsed
    /// @return true, indicating the successful completion of the logical expression parsing, otherwise, false
    /// */

    bool parse(const std::string &i_expr);

    /// @brief parseAll The method parses all logical expressions stored in the Parser object and builds a graph of dependencies between them.
    /// @return If all logical expressions are successfully parsed and added to the graph, the method returns true, indicating the successful completion of the operation, otherwise, false
    /// */

    bool parseAll();

private:
    std::vector<std::string> d_logExpressions;

    OrientedGraph d_graph;
    std::shared_ptr<Settings> d_settings = Settings::getInstance("Parser");

    std::pair<bool, std::vector<std::pair<int, int>>> createBrackets(const std::string &i_expr);
    bool inBrackets(const std::vector<std::pair<int, int>> &i_brackets, int i_position) const;
    std::string deleteExtraSpaces(std::string i_s);
};
