#include <cassert>
#include <iostream>

#include "Parser.h"

namespace {
std::string deleteDoubleSpaces(const std::string& s) {
  std::string res         = "";
  bool        isPrevSpace = false;
  for (auto c : s) {
    if (c != ' ') {
      isPrevSpace = false;
      res         += c;
    } else {
      if (!isPrevSpace)
        res += c;
    }
  }
  return res;
}
}  // namespace

Parser::Parser(const std::string& i_logExpression) {
  // d_graph.setVertexCount(0); TODO: wtf?
  // https://github.com/RomeoMe5/CAD_Combinational_Circuits/blob/7ae1fe61eb61e1751147a8598b7a25c976d233b3/Generator/source/Generators/Parsing.cs#L29
  d_logExpressions.push_back(deleteDoubleSpaces(i_logExpression));
}

Parser::Parser(const std::vector<std::string>& i_logExpressions) {
  // d_graph.setVertexCount(0); TODO: wtf?
  // https://github.com/RomeoMe5/CAD_Combinational_Circuits/blob/7ae1fe61eb61e1751147a8598b7a25c976d233b3/Generator/source/Generators/Parsing.cs#L42
  for (const auto& expression : i_logExpressions)
    d_logExpressions.push_back(expression);
}

OrientedGraph Parser::getGraph() const {
  return d_graph;
}

std::pair<bool, std::vector<std::pair<int, int>>> Parser::createBrackets(
    const std::string& i_expr
) {
  std::vector<std::pair<int, int>> brackets;
  for (int i = 0; i < i_expr.length(); ++i) {
    if (i_expr[i] == '(') {
      brackets.push_back({i, -1});
    }
    if (i_expr[i] == ')') {
      int j = static_cast<int>(brackets.size()) - 1;
      while (j >= 0 && brackets[j].second != -1)
        --j;

      if (j == -1)
        return {false, {{-1, -1}}};

      brackets[j] = {brackets[j].first, i};
    }
  }

  int u = static_cast<int>(brackets.size()) - 1;
  // assert(u >= 0);
  while (u >= 0 && brackets[u].second != -1)
    --u;

  if (u == -1)
    return {true, brackets};

  return {false, {{-1, -1}}};
}

bool Parser::inBrackets(
    const std::vector<std::pair<int, int>>& i_brackets,
    int                                     i_position
) const {
  int i = static_cast<int>(i_brackets.size()) - 1;

  while (i >= 0
         && !(
             i_position > i_brackets[i].first
             && i_position < i_brackets[i].second
         ))
    i--;

  if (i == -1)
    return false;
  return true;
}

std::string deleteExtraSpace(const std::string& i_s) {
  int l = i_s.size(), r = static_cast<int>(i_s.size()) - 1;
  for (int i = 0; i < i_s.size(); ++i) {
    if (i_s[i] != ' ') {
      l = std::min(l, i);
      r = i;
    }
  }
  return i_s.substr(l, r - l + 1);
}

std::pair<int, std::vector<std::string>> Parser::splitLogicExpression(
    std::string i_expr
) {
  bool f = true;
  int  l = 0;

  while (f && l <= d_settings->getLogicOperation("input").second) {
    std::vector<std::string> operations =
        d_settings->fromOperationsToHierarchy(l);
    if (i_expr == "1'b1")
      i_expr = i_expr;  // what?

    for (const auto& op : operations) {
      int index = i_expr.find(op);
      while (index != i_expr.length() && index != std::string::npos) {
        std::pair<bool, std::vector<std::pair<int, int>>> brackets =
            createBrackets(i_expr);
        if (!inBrackets(brackets.second, index)) {
          std::vector<std::string> lst;
          std::string              newOp = d_settings->fromOperationsToName(op);
          lst.push_back(deleteExtraSpaces(newOp));
          if (newOp == "not")
            lst.push_back(deleteExtraSpaces(i_expr.substr(index + op.length()))
            );
          else if (newOp == "buff")
            lst.push_back(deleteExtraSpaces(i_expr.substr(index + op.length()))
            );
          else if (newOp == "input")
            lst.push_back(deleteExtraSpaces(i_expr));
          else if (newOp == "const")
            lst.push_back(deleteExtraSpaces(i_expr));
          else {
            lst.push_back(deleteExtraSpaces(i_expr.substr(0, index)));
            lst.push_back(deleteExtraSpaces(i_expr.substr(index + op.length()))
            );
          }
          return {index, lst};  // what?
        }
        index = i_expr.find(op, index + 1);
      }
    }
    l++;
  }
  return {-1, {}};
}

bool Parser::parse(const std::string& i_expr)  // what? change true/false
{
  std::pair<int, std::vector<std::string>> t = splitLogicExpression(i_expr);
  if (t.first == -1)
    return false;

  if (t.second[0] == "output") {
    std::vector<std::pair<int, int>> bl = createBrackets(t.second[2]).second;
    for (auto tl : bl)
      if (tl.first == 0 && tl.second == t.second[2].size() - 1)
        t.second[2] = t.second[2].substr(1, t.second[2].size() - 2);

    std::pair<int, std::vector<std::string>> tt =
        splitLogicExpression(t.second[2]);
    if (tt.first == -1)
      return false;

    d_graph.addVertex(t.second[1], t.second[0]);
    d_graph.addVertex(t.second[2], tt.second[0]);
    d_graph.addEdge(t.second[2], t.second[1]);

    if (tt.second[0] != "input" && tt.second[0] != "const")
      parse(t.second[2]);
  } else {
    d_graph.addVertex(i_expr, t.second[0]);
    for (int i = 1; i < t.second.size(); ++i) {
      std::string                      part = t.second[i];

      std::vector<std::pair<int, int>> bl   = createBrackets(part).second;

      for (auto tl : bl)
        if (tl.first == 0 && tl.second == static_cast<int>(part.size()) - 1)
          part = part.substr(1, static_cast<int>(part.size()) - 2);

      std::pair<int, std::vector<std::string>> tt = splitLogicExpression(part);
      if (tt.first == -1)
        return false;

      d_graph.addVertex(part, tt.second[0]);
      d_graph.addEdge(part, i_expr);
      if (tt.second[0] != "input" && tt.second[0] != "const")
        parse(part);
    }
  }
  return true;
}

bool Parser::parseAll() {
  d_graph = OrientedGraph();
  for (int i = 0; i < d_logExpressions.size(); ++i)
    if (createBrackets(d_logExpressions[i]).first)
      if (!parse(d_logExpressions[i]))
        return false;
  return true;
}

std::string Parser::deleteExtraSpaces(std::string i_s) {
  int i = 0;
  while (i_s[i] == ' ')
    ++i;
  i_s.erase(0, i);

  while (i_s.size() > 0 && i_s.back() == ' ')
    i_s.pop_back();

  return i_s;
}
