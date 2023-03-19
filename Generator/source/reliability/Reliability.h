#pragma once

#include <map>
#include <string>

#include "../graph/OrientedGraph.h"

class Reliability
{
public:
  Reliability(const OrientedGraph& i_graph, double i_p = 0.5);
  std::map<std::string, std::vector<bool>> calc(
    bool i_withErrorValues = false,
    bool i_withErrorStrings = false
  );
  double calcReliabilityBase();
  std::map<std::string, double> runNadezhda(const std::string& i_path, const std::string i_circuitName);


private:
  OrientedGraph d_graph;
  double d_p;
  Settings* d_settings = Settings::getInstance("GraphVertex");
};
