#pragma once

#include <string>

#include "../graph/OrientedGraph.h"

class Parser
{
public:
  Parser(const std::string& i_logExpression);
  Parser(const std::vector<std::string>& i_logExpressions);
  OrientedGraph getGraph() const;
  std::pair<int, std::vector<std::string>> splitLogicExpression(std::string i_expr);
  bool parse(const std::string& i_expr);
  bool parseAll();


private:
  std::vector<std::string> d_logExpressions;

  OrientedGraph d_graph;
  Settings* d_settings = Settings::getInstance("Parser");

  std::pair<bool, std::vector<std::pair<int, int>>> createBrackets(const std::string& i_expr);
  bool inBrackets(const std::vector<std::pair<int, int>>& i_brackets, int i_position) const;
  std::string deleteExtraSpaces(std::string i_s);
};
