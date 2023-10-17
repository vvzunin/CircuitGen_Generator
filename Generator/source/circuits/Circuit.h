#pragma once

#include <string>
#include <vector>

#include "CircuitsParameters.h"
#include "../graph/OrientedGraph.h"
#include "../generators/TruthTable.h"

class Circuit
{
public:
  Circuit(const OrientedGraph& i_graph, const std::vector<std::string>& i_logExpressions = {});
  void computeHash();
  void updateCircuitsParameters();
  bool graphToVerilog(const std::string& i_path, bool i_pathExists = false);
  bool saveParameters(bool i_pathExists = false) const;
  bool generate(bool i_pathExists = false);
  void setTable(const TruthTable& i_tt);
  void setPath(const std::string& i_path);
  void setCircuitName(const std::string& i_circName);
  bool addVertex(const std::string i_vertexName, const std::string& i_operation, const std::string& i_wireName = "");
  int getIndexOfWireName(const std::string& i_wireName);
  GraphVertex getVertice(int i) const;
  bool addEdge(const std::string& i_vertexFrom, const std::string& i_vertexTo, bool i_isExpression = true);
  bool addDoubleEdge(const std::string& i_vertexFromFirst, const std::string& i_vertexFromSecond, const std::string& i_vertexTo, bool i_isExpression = true);
  void setVerticeOperation(int i_vertice, const std::string& i_operation);
  
private:
  OrientedGraph d_graph;
  std::vector<std::string> d_logExpressions;
  TruthTable d_tTable;
  std::string d_path;
  std::string d_circuitName;
  CircuitParameters d_circuitParameters;
  Settings* d_settings = Settings::getInstance("GraphVertex");

  bool checkExistingHash();

};
