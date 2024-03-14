#pragma once

#include <string>
#include <memory>

#include <settings/Settings.h>

/// class GraphVertex
/// @param d_logicExpression Stores a logical expression associated with a graph vertex
/// @param d_operation Stores the operation associated with the vertex of the graph. This operation can be any operation defined for a given vertex, for example, "AND", "OR", "NOT", "XOR", etc.
/// @param d_level The level of the vertex in the graph
/// @param d_value The value of the vertex. This Boolean value represents the current state of the vertex, which can be true or false depending on the execution of the operation or the calculation of the Boolean expression.
/// @param d_wireName This name can be used to identify the wire or connection associated with a given vertex in the graph*
/// @param d_count This static field is used to count the number of Graph Vertex class objects created
/// @param d_settings A pointer to the settings object for the vertex of the graph
/// 
/// 
/// */

class GraphVertex
{
public:
    GraphVertex(const std::string &i_expr,
                const std::string &i_operation,
                bool i_value = false,
                const std::string &i_wireName = "");
    GraphVertex(const GraphVertex &other) = default;
    GraphVertex &operator=(const GraphVertex &other) = default;
    GraphVertex(GraphVertex &&other) = default;
    GraphVertex &operator=(GraphVertex &&other) = default;

    /// @brief getLevel The method returns the vertex level in the graph
   /// @return The value of the d_level variable, which represents the vertex level in the graph
   /// */

    int getLevel() const;

    /// @brief setLevel The method sets the vertex level in the graph
    /// @param i_level The new value of the vertex level in the graph that will be set for this vertex
    /// */

    void setLevel(int i_level);

    /// @brief getValue The method returns the value of a vertex in the graph
    /// @return if d_value is true, the method returns false, and if d_value is false, the method returns true.
    /// */

    bool getValue() const;

    /// @brief setWireName The method sets the wire name for a given vertex in the graph.
  /// @param i_wireName the new name of the wire
  /// */

    void setWireName(std::string i_wireName);

    /// @brief setValue The method sets the value of a vertex in the graph.
    /// @param i_value new value
    /// */

    void setValue(bool i_value);

    /// @brief setLogicExpression The method sets a Boolean expression for a given vertex in the graph.
   /// @param i_logicExpression A new logical expression
   /// */

    void setLogicExpression(const std::string &i_logicExpression);

    /// @brief getLogicExpression The method returns a Boolean expression associated with a given vertex in the graph
   /// @return the value of the d_logic Expression variable, which stores the Boolean expression associated with a given vertex in the graph
   /// */


    std::string getLogicExpression() const;

    /// @brief getOperation The method returns the operation associated with a given vertex in the graph
   /// @return the value of the d_operation variable, which stores the operation associated with a given vertex in the graph
   /// */

    std::string getOperation() const;

    /// @brief setOperation The method sets the operation for a given vertex in the graph.
   /// @param i_operation a new operation
   /// */

    void setOperation(const std::string &i_operation);


    /// @brief getWireName The method returns the name of the wire associated with this vertex in the graph
    /// @return the value of the variable d_wireName, which stores the name of the wire associated with this vertex in the graph
    /// */

    std::string getWireName() const;
    bool wrongVertex = false;

private:
    std::string d_logicExpression = "";
    std::string d_operation = "";
    int d_level = 0;
    bool d_value = false;
    std::string d_wireName = "";
    static int d_count;

    std::shared_ptr<Settings> d_settings = Settings::getInstance("GraphVertex");
};
