#pragma once

#include <baseStructures/graph/OrientedGraph.h>
#include <baseStructures/truthTable/TruthTable.h>

#include <memory>
#include <string>
#include <vector>

#include "CircuitsParameters.h"

class Circuit {
 public:
  Circuit(OrientedGraph *const i_graph,
          const std::vector<std::string> &i_logExpressions = {});
  void computeHash();
  void updateCircuitsParameters();
  bool graphToVerilog(const std::string &i_path, bool i_pathExists = false);
  bool saveParameters(bool i_pathExists = false) const;
  bool generate(bool i_pathExists = false);
  void setTable(const TruthTable &i_tt);
  void setPath(const std::string &i_path);
  void setCircuitName(const std::string &i_circName);
  std::vector<GraphVertexBase *> getIndexOfWireName(
      const std::string &i_wireName);
  void setVerticeOperation(int i_vertice, const std::string &i_operation);

 private:
  OrientedGraph *d_graph;
  std::vector<std::string> d_logExpressions;
  TruthTable d_tTable;
  std::string d_path;
  std::string d_circuitName;
  CircuitParameters d_circuitParameters;
  std::shared_ptr<Settings> d_settings = Settings::getInstance("Circuit");

  bool checkExistingHash();
  void viewSubgraphs(std::string path, OrientedGraph *graph);
};
