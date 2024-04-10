#include <cassert>
#include <iostream>
#include <stack>

#include "Parser.hpp"

namespace {
std::string deleteDoubleSpaces(const std::string& s) {
  std::string res         = "";
  bool        isPrevSpace = false;
  for (auto c : s) {
    if (c != ' ') {
      isPrevSpace  = false;
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
  d_logExpressions.push_back(deleteDoubleSpaces(i_logExpression));
}

Parser::Parser(const std::vector<std::string>& i_logExpressions) {
  for (const auto& expression : i_logExpressions)
    d_logExpressions.push_back(expression);
}

GraphPtr Parser::getGraph() const {
  return d_graph;
}

std::pair<bool, std::vector<std::pair<int32_t, int32_t>>>
    Parser::createBrackets(const std::string& i_expr) {
  std::vector<std::pair<int32_t, int32_t>> brackets;
  std::stack<int32_t>                      bracketsStartPos;

  for (int32_t i = 0; i < i_expr.length(); ++i) {
    if (i_expr[i] == '(') {
      bracketsStartPos.push(i);
    }
    if (i_expr[i] == ')') {
      if (bracketsStartPos.empty())
        return {false, {{-1, -1}}};

      brackets.push_back(std::make_pair(bracketsStartPos.top(), i));
      bracketsStartPos.pop();
    }
  }

  if (bracketsStartPos.empty())
    return {true, brackets};

  return {false, {{-1, -1}}};
}

bool Parser::inBrackets(
    const std::vector<std::pair<int32_t, int32_t>>& i_brackets,
    int32_t                                         i_position
) const {
  int32_t i = static_cast<int32_t>(i_brackets.size()) - 1;

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
  uint32_t l = i_s.size(), r = static_cast<int32_t>(i_s.size()) - 1;
  for (uint32_t i = 0; i < i_s.size(); ++i) {
    if (i_s[i] != ' ') {
      l = std::min(l, i);
      r = i;
    }
  }
  return i_s.substr(l, r - l + 1);
}

std::pair<int32_t, std::vector<std::string>> Parser::splitLogicExpression(
    std::string i_expr
) {
  int32_t l = 0;

  while (l <= d_settings->getLogicOperation("input").second) {
    std::vector<std::string> operations =
        d_settings->fromOperationsToHierarchy(l);

    for (const auto& op : operations) {
      // so, what was the problem
      // here we have been looking for a substr in string, substr was
      // an operation. Or has higher (I meen lower code number) priority,
      // than it has xor. So, firstly we have been looking for or,
      // than xor. so, we can have two possible variants.
      // Check, if operation in fact is xor, not or, or just to
      // find firstly xor, than or. Was chosen second variant
      size_t index = i_expr.find(op);
      std::pair<bool, std::vector<std::pair<int32_t, int32_t>>> brackets =
          createBrackets(i_expr);

      while (index != std::string::npos) {
        if (!inBrackets(brackets.second, index)) {
          std::vector<std::string> lst;
          std::string              newOp = d_settings->fromOperationsToName(op);
          lst.push_back(deleteExtraSpaces(newOp));

          if (newOp == "not" || newOp == "buf")
            lst.push_back(deleteExtraSpaces(i_expr.substr(index + op.length()))
            );
          else if (newOp == "input" || newOp == "const")
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

// TODO rewrite to normal cnft generation
// TODO JUST MAKE IT PARSING DATA IN () NOT REQURSIVE, ONLY () REQURSIVE
bool Parser::parse(const std::string& i_expr)  // what? change true/false
{
  std::pair<int32_t, std::vector<std::string>> t = splitLogicExpression(i_expr);
  if (t.first == -1)
    return false;

  if (t.second[0] == "output") {
    std::vector<std::pair<int32_t, int32_t>> bl =
        createBrackets(t.second[2]).second;
    for (auto tl : bl)
      if (tl.first == 0 && tl.second == t.second[2].size() - 1)
        t.second[2] = t.second[2].substr(1, t.second[2].size() - 2);

    std::pair<int32_t, std::vector<std::string>> tt =
        splitLogicExpression(t.second[2]);
    if (tt.first == -1)
      return false;

    std::shared_ptr<GraphVertexBase> t1 = d_graph->addOutput(t.second[1]);
    std::shared_ptr<GraphVertexBase> t2;
    if (tt.second[0] == "input") {
      // we need to stop duplication
      // that's why we create a map, which do not declare input again
      if (!inputsByNames.count(t.second[2])) {
        inputsByNames[t.second[2]] = d_graph->addInput(t.second[2]);
      }

      t2 = inputsByNames[t.second[2]];
    } else if (tt.second[0] == "const") {
      t2 = d_graph->addConst(t.second[2][0], t.second[2]);
    } else {
      t2 = d_graph->addGate(d_settings->parseStringToGate(tt.second[0]));
    }
    d_graph->addEdge(t2, t1);

    if (tt.second[0] != "input" && tt.second[0] != "const")
      parse(t.second[2]);
  } else {
    VertexPtr expr, part_ptr;
    if (i_expr != "input") {
      if (t.second[0] == "not") {
        // same protection from multiple inputs
        if (!notInputsByNames.count("not " + t.second[1]))
          notInputsByNames["not " + t.second[1]] =
              d_graph->addGate(Gates::GateNot, "not_" + t.second[1]);

        expr = notInputsByNames["not " + t.second[1]];
      } else
        expr = d_graph->addGate(d_settings->parseStringToGate(t.second[0]));
    } else {
      // saving us from duplicate input
      if (!inputsByNames.count(t.second[0]))
        inputsByNames[t.second[0]] = d_graph->addInput(t.second[0]);

      expr = inputsByNames[t.second[0]];
    }

    for (int32_t i = 1; i < t.second.size(); ++i) {
      std::string                              part = t.second[i];

      std::vector<std::pair<int32_t, int32_t>> bl = createBrackets(part).second;

      for (auto tl : bl)
        if (tl.first == 0 && tl.second == (part.size() - 1))
          part = part.substr(1, part.size() - 2);

      std::pair<int32_t, std::vector<std::string>> tt =
          splitLogicExpression(part);
      if (tt.first == -1)
        return false;

      if (tt.second[0] == "input") {
        // same protection from multiple inputs
        if (!inputsByNames.count(part))
          inputsByNames[part] = d_graph->addInput(part);

        part_ptr = inputsByNames[part];

      } else if (tt.second[0] == "not") {
        // same protection from multiple inputs
        if (!notInputsByNames.count("not " + tt.second[1]))
          notInputsByNames["not " + tt.second[1]] =
              d_graph->addGate(Gates::GateNot, "not_" + tt.second[1]);

        part_ptr = notInputsByNames["not " + tt.second[1]];

      } else if (tt.second[0] == "const")
        part_ptr = d_graph->addConst(part[0], part);
      else {
        for (auto word : tt.second) {
          std::clog << word + ", ";
        }
        std::clog << std::endl;
        std::clog << expr->getName() << "\n";
        if (doneOperations.empty()) {
          doneOperations.push(tt.second[0]);
        }

        if (doneOperations.top() == tt.second[0]) {
          if (!operationByCreatedVertex.count(tt.second[0])) {
            operationByCreatedVertex[tt.second[0]] = {};
            inputsByCreatedVertex[tt.second[0]]    = {};
          }

          operationByCreatedVertex[tt.second[0]].push(
              {d_graph->addGate(d_settings->parseStringToGate(tt.second[0]))}
          );
          inputsByCreatedVertex[tt.second[0]].push(inputsByNames[tt.second[1]]);

          part_ptr = operationByCreatedVertex[tt.second[0]].top();

          if (inputsByNames.count(tt.second[2])) {
            inputsByCreatedVertex[tt.second[0]].push(inputsByNames[tt.second[2]]
            );
          }
        } else {
          std::string prev = doneOperations.top();

          VertexPtr   inp  = inputsByCreatedVertex[prev].top();
          while (!operationByCreatedVertex.empty()) {}
        }
      }

      d_graph->addEdge(part_ptr, expr);
      if (tt.second[0] != "input" && tt.second[0] != "const")
        parse(part);
    }
  }
  return true;
}

VertexPtr Parser::parseToVertex(const std::string& i_expr) {
  std::pair<int32_t, std::vector<std::string>> t = splitLogicExpression(i_expr);
  if (t.first == -1)
    return nullptr;
  
  
}

bool Parser::parseAll() {
  d_graph.reset(new OrientedGraph);
  for (auto exp : d_logExpressions)
    if (createBrackets(exp).first)
      if (!parse(exp))
        return false;
  return true;
}

std::string Parser::deleteExtraSpaces(std::string i_s) {
  int32_t i = 0;
  for (; i_s[i] == ' '; ++i)
    ;
  i_s.erase(0, i);

  while (i_s.size() > 0 && i_s.back() == ' ')
    i_s.pop_back();

  return i_s;
}