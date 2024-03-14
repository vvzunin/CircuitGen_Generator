#pragma once

#include <memory>
#include <string>
#include <vector>

#include "CircuitsParameters.h"
#include <graph/OrientedGraph.h>
#include <generators/TruthTable.h>
#include <optimization_utils/StandartUtil.h>

/// class Circuit
/// @param OrientedGraph pointer to a Oriented graph = nullptr
/// @param d_logExpressions A string vector containing logical expressions associated with a given Circuit
/// @param d_tTable an object of the Truth Table class representing the truth table for the Circuit.
/// @param d_path A string containing the path to the Circuit files
/// @param d_circuitName A string containing the Circuit name.
/// @param d_circuitParameters An object of the Circuit Parameters class containing circuit parameters such as the number of inputs, number of outputs, maximum level, etc.
/// @param d_settings a smart pointer to an object of the Settings class that represents the settings for this schema. It is usually used to adjust the parameters of the vertices of the graph
/// */ 


/// @brief saveParameters 
///
/// */


class Circuit
{
public:
    Circuit(OrientedGraph *i_graph, const std::vector<std::string> &i_logExpressions = {});

    /// @brief computeHash A method for calculating the hash of a combinational scheme
/// */


    void computeHash();

    /// @brief updateCircuitsParameters A method for updating the parameters of a combinational circuit
/// @param i_getAbcStats A flag indicating whether to receive statistics from the ABC program (a program for synthesizing digital circuits).
/// @param libraryName The name of the library associated with the Circuit.
/// 
/// */
    void updateCircuitsParameters(bool i_getAbcStats = false, std::string libraryName = "");

    /// @brief graphToVerilog The graph To Verilog method in the Circuit class converts the combinational circuit into code in the Verilog hardware description language and writes it to a file.
/// @param i_path The path to the file where the Verilog code will be written.
/// @param i_pathExists A flag indicating whether the path to the file already exists.
/// @return true, indicating the successful completion of the operation.
/// */

    bool graphToVerilog(const std::string &i_path, bool i_pathExists = false);

    /// @brief saveParameters The save Parameters method in the Circuit class is designed to save circuit parameters to a file in JSON format
/// The method saves the main parameters of the circuit, such as the name, number of inputs and outputs, maximum level, etc., in JSON format.
/// @param i_getAbcStats A flag indicating whether statistics from the ABC program should also be saved
/// @param i_generateAig A flag indicating whether to generate an AIG (And-Inverter Graph).
/// @param i_pathExists A flag indicating whether there is already a path to save the file
/// return The file is closed, and the method returns true if the parameters are saved successfully.
/// */

    bool saveParameters(bool i_getAbcStats = false, bool i_generateAig = false, bool i_pathExists = false) const;

    /// @brief saveAdditionalStats This save Additional Stats method is designed to save additional statistics related to the execution of the ABC command (a program for synthesizing digital circuits) in a JSON file.
/// 
/// 
/// @param i_res The result of the ABC command, containing the output of the command and information about the correctness of execution***
/// @param i_optimizationName The name of the optimization or type of statistics to be saved
/// @param i_lastData A flag indicating whether the current statistics are the latest in the JSON file
/// */

    void saveAdditionalStats(CommandWorkResult i_res, std::string i_optimizationName = "Balanced", bool i_lastData = true) const;

    /// @brief generate This generate method is designed to generate various representations of a digital circuit (for example, Verilog, RTL, Bench) and perform optimizations using the ABC program (if necessary), as well as save digital circuit parameters and additional statistics
/// 
/// @param i_makeFirrtl A flag indicating whether to create a FIRRTL representation for a digital circuit
/// @param i_makeBench A flag indicating whether to create a Bench view for a digital circuit.
/// @param i_getAbcStats A flag indicating whether to receive statistics from the ABC program after performing optimizations.
/// @param libraryName The name of the library used for optimization using the ABC program
/// @param i_generateAig A flag indicating whether to generate an AIG (And-Inverter Graph) after performing optimizations.
/// @param i_pathExists A flag indicating whether there is already a path to save the file
/// @return The method returns true if the generation and saving were successful

    bool generate(bool i_makeFirrtl = false, bool i_makeBench = false, bool i_getAbcStats = false, std::string libraryName = "", bool i_generateAig = false, bool i_pathExists = false);

    /// @brief setTable This method is designed to set up a truth table for a digital circuit.
/// 
/// @param i_tt The Truth Table, which must be installed for the digital circuit.
/// */

    void setTable(const TruthTable &i_tt);

    /// @brief setPath This method is designed to set the path where the files associated with the digital circuit will be saved.
/// 
/// @param i_path A string containing the path to the directory where the digital circuit files will be saved
/// */

    void setPath(const std::string &i_path);

    /// @brief setCircuitName This method is used to set the name of the digital circuit.
/// 
/// @param i_circName A string containing a new name for the digital circuit
/// */

    void setCircuitName(const std::string &i_circName);

    /// @brief addVertex This method is designed to add a vertex to the diagram graph.
    /// 
    /// @param i_vertexName A string containing the name of the vertex to be added to the graph of the digital circuit
    /// @param i_operation A string representing the operation performed by the vertex. For example, it can be an operation "AND", "OR", "NOT", etc.
    /// @param i_wireName a string containing the name of the wire connected to the vertex. This parameter is optional and can be empty
    /// @return If the vertex is successfully added, the method returns true, otherwise false.
    /// */

    bool addVertex(const std::string i_vertexName, const std::string &i_operation, const std::string &i_wireName = "");

    /// @brief getIndexOfWireName This method is designed to get the index of the vertex in the graph by the name of the wire.
    /// @param i_wireName A string containing the name of the wire for which you want to get the vertex index in the graph of the circuit
    /// 
    /// @return An integer value representing the index of a vertex in a graph of a digital circuit. If the vertex with the specified wire name is not found, the method returns -1.
    /// */

    int getIndexOfWireName(const std::string &i_wireName);

    /// @brief calculateReliability This method is designed to calculate the reliability of a circuit.
   /// @param inputs_size An integer value representing the number of digital circuit inputs
   /// @return An integer value representing the number of inconsistencies in the output values of the circuit with different combinations of input signals
   /// */


    int calculateReliability(int inputs_size);



    GraphVertex getVertice(int i) const;

    /// @brief addEdge This method adds an edge between the vertices of the diagram graph
    /// 
    /// @param i_vertexFrom A string representing the name of the vertex from which the edge originates
    /// @param i_vertexTo A string representing the name of the vertex to which the edge is directed
    /// @param i_isExpression A Boolean value indicating whether an edge is an expression (for example, a logical operator) or not
    /// @return ttrue if the edge was successfully added, otherwise it is false
    /// */

    bool addEdge(const std::string &i_vertexFrom, const std::string &i_vertexTo, bool i_isExpression = true);

    /// @brief addDoubleEdge This method adds a double edge between two vertices coming from two different sources and one end vertex
   /// 
   /// @param i_vertexFromFirst A string representing the name of the first vertex from which the first edge originates
   /// @param i_vertexFromSecond A string representing the name of the second vertex from which the second edge originates
   /// @param i_vertexTo A string representing the name of the end vertex to which both edges are directed
   /// @param i_isExpression A Boolean value indicating whether an edge is an expression (for example, a logical operator) or not
   /// @return true if both edges are successfully added; false if an error occurred when adding edges.
   /// */

    bool addDoubleEdge(const std::string &i_vertexFromFirst, const std::string &i_vertexFromSecond, const std::string &i_vertexTo, bool i_isExpression = true);

    /// @brief setVerticeOperation This method sets up an operation for a given vertex in the graph.
    /// @param i_vertice Index of the vertex to set the operation for
    /// @param i_operation A string representing the operation to be set for the vertex
    /// */

    void setVerticeOperation(int i_vertice, const std::string &i_operation);

private:
    OrientedGraph *d_graph = nullptr;
    std::vector<std::string> d_logExpressions;
    TruthTable d_tTable;
    std::string d_path;
    std::string d_circuitName;
    CircuitParameters d_circuitParameters;
    std::shared_ptr<Settings> d_settings = Settings::getInstance("GraphVertex");

    bool checkExistingHash();
};
