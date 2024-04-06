#pragma once

#include <memory>
#include <string>
#include <vector>

#include <baseStructures/graph/OrientedGraph.hpp>
#include <baseStructures/truthTable/TruthTable.hpp>

#include "CircuitParameters.hpp"

class Circuit {
public:
  Circuit(
      GraphPtr const                  i_graph,
      const std::vector<std::string>& i_logExpressions = {}
  );
  void computeHash();
  void updateCircuitParameters();
  bool graphToVerilog(const std::string& i_path, bool i_pathExists = false);
  bool graphToGraphML(const std::string& i_path, bool i_pathExists = false);
  bool saveParameters(bool i_pathExists = false) const;
  bool generate(bool i_makeGraphML = false, bool i_pathExists = false);
  void setTable(const TruthTable& i_tt);
  void setPath(const std::string& i_path);
  void setCircuitName(const std::string& i_circName);
  std::vector<std::shared_ptr<GraphVertexBase>> getIndexOfWireName(
      const std::string& i_wireName
  );
  void    setVerticeOperation(int i_vertice, const std::string& i_operation);
  Circuit fromVerilog(const std::string& i_filepath);

private:
  GraphPtr                  d_graph;
  std::vector<std::string>  d_logExpressions;
  TruthTable                d_tTable;
  std::string               d_path;
  std::string               d_circuitName;
  CircuitParameters         d_circuitParameters;
  std::shared_ptr<Settings> d_settings = Settings::getInstance("Circuit");

  bool                      checkExistingHash();
};