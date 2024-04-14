
#pragma once

#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "graph/OrientedGraph.hpp"
using GatesInfo = std::map<Gates, std::vector<int>>;

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

  GraphPtr getGraph() const;
  std::pair<int32_t, std::vector<std::string>> splitLogicExpression(
      std::string i_expr
  );

  VertexPtr multipleVerteciesToOne(
      std::vector<VertexPtr> curLayout,
      Gates                  operation,
      GraphPtr               graph
  );
  VertexPtr parseToVertex(const std::string& i_expr);
  bool      parseAll();

  void setGatesInputsInfo(const std::map<std::string, std::vector<int>>& i_info
  );
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
