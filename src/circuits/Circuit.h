#pragma once

#include <memory>
#include <string>
#include <vector>

#include "CircuitsParameters.h"
#include <baseStructures/graph/OrientedGraph.h>
#include <baseStructures/truthTable/TruthTable.h>

class Circuit
{
public:
    Circuit(const OrientedGraph &i_graph, const std::vector<std::string> &i_logExpressions = {});
    void computeHash();
    void updateCircuitsParameters(bool i_getAbcStats = false, std::string libraryName = "");
    bool graphToVerilog(const std::string &i_path, bool i_pathExists = false);
    bool saveParameters(bool i_getAbcStats = false, bool i_generateAig = false, bool i_pathExists = false) const;
    bool generate(bool i_getAbcStats = false, std::string libraryName = "", bool i_generateAig = false, bool i_pathExists = false);
    void setTable(const TruthTable &i_tt);
    void setPath(const std::string &i_path);
    void setCircuitName(const std::string &i_circName);
    GraphVertexBase* getIndexOfWireName(const std::string &i_wireName);
    void setVerticeOperation(int i_vertice, const std::string &i_operation);

private:
    OrientedGraph d_graph;
    std::vector<std::string> d_logExpressions;
    TruthTable d_tTable;
    std::string d_path;
    std::string d_circuitName;
    CircuitParameters d_circuitParameters;
    std::shared_ptr<Settings> d_settings = Settings::getInstance("Circuit");

    bool checkExistingHash();
};
