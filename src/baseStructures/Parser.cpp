#include <algorithm>
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

Parser::Parser(
    const std::string&                             i_logExpression,
    const std::map<std::string, std::vector<int>>& i_info
) {
  d_logExpressions.push_back(deleteDoubleSpaces(i_logExpression));
  setGatesInputsInfo(i_info);
}

Parser::Parser(
    const std::vector<std::string>&                i_logExpressions,
    const std::map<std::string, std::vector<int>>& i_info
) {
  for (const auto& expression : i_logExpressions)
    d_logExpressions.push_back(expression);
  setGatesInputsInfo(i_info);
}

Parser::Parser(const std::string& i_logExpression, const GatesInfo& i_info) {
  d_logExpressions.push_back(deleteDoubleSpaces(i_logExpression));

  d_gatesInputsInfo = i_info;
}

Parser::Parser(
    const std::vector<std::string>& i_logExpressions,
    const GatesInfo&                i_info
) {
  for (const auto& expression : i_logExpressions)
    d_logExpressions.push_back(expression);

  d_gatesInputsInfo = i_info;
}

GraphPtr Parser::getGraph() const {
  return d_graph;
}

void Parser::setGatesInputsInfo(
    const std::map<std::string, std::vector<int>>& i_info
) {
  for (auto& [key, value] : i_info) {
    d_gatesInputsInfo[d_settings->parseStringToGate(key)] = value;
  }
}

void Parser::setGatesInputsInfo(const GatesInfo& i_info) {
  d_gatesInputsInfo = i_info;
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

    for (const auto& oper : operations) {
      // so, what was the problem
      // here we have been looking for a substr in string, substr was
      // an operation. Or has higher (I meen lower code number) priority,
      // than it has xor. So, firstly we have been looking for or,
      // than xor. so, we can have two possible variants.
      // Check, if operation in fact is xor, not or, or just to
      // find firstly xor, than or. Was chosen second variant
      size_t index = i_expr.find(oper);
      std::pair<bool, std::vector<std::pair<int32_t, int32_t>>> brackets =
          createBrackets(i_expr);
      std::vector<std::string> lst;

      while (index != std::string::npos) {
        // if we have xor in fact, go to next iteration
        if ((oper == "or" || oper == "nor") && index > 0
            && i_expr[index - 1] == 'x') {
          index = i_expr.find(oper, index + 1);
          continue;
        }

        if (!inBrackets(brackets.second, index)) {
          std::string newOp = d_settings->fromOperationsToName(oper);

          if (lst.empty())
            lst.push_back(deleteExtraSpaces(newOp));

          if (newOp == "not" || newOp == "buf") {
            lst.push_back(deleteExtraSpaces(i_expr.substr(index + oper.length())
            ));
          } else if (newOp == "input" || newOp == "const") {
            lst.push_back(deleteExtraSpaces(i_expr));
          } else {
            lst.push_back(deleteExtraSpaces(i_expr.substr(0, index)));

            i_expr   = deleteExtraSpaces(i_expr.substr(index + oper.length()));
            brackets = createBrackets(i_expr);

            int idx  = i_expr.find(oper);
            // now we are trying to parse whole operations
            if (idx != std::string::npos && !inBrackets(brackets.second, idx)) {
              index = idx;
              continue;
            }
            lst.push_back(i_expr);
          }
          return {index, lst};  // what?
        }
        index = i_expr.find(oper, index + 1);
      }
    }

    l++;
  }
  return {-1, {}};
}

VertexPtr Parser::multipleVerteciesToOne(
    std::vector<VertexPtr> curLayout,
    Gates                  operation,
    GraphPtr               graph
) {
  std::vector<VertexPtr> nextLayout;
  int32_t                curSize = 0;

  // Here we add operations in brackets
  while (curLayout.size() != 1) {
    curSize       = 0;

    size_t    pos = d_gatesInputsInfo[operation].size() - 1;
    VertexPtr x_input;
    VertexPtr oper;

    oper = graph->addGate(operation);
    // iterate through i layout
    for (size_t k = 0; k < curLayout.size(); ++k) {
      x_input = curLayout[k];

      graph->addEdge(x_input, oper);
      ++curSize;

      if (d_gatesInputsInfo[operation][pos] == curSize) {
        nextLayout.push_back(oper);

        // if we will have only one gate
        // we do not create a new operation
        if (k == (curLayout.size() - 2)) {
          oper = curLayout.back();
          // we save curSize for saving us from add
          // new edges to oper
          break;
        } else if (k < curLayout.size() - 1) {
          oper = graph->addGate(operation);
        }

        // if we have less elements than we can add, and our logical element
        // has too big gates number, move to lower
        int npos = pos;
        while (npos >= 0 && curSize < d_gatesInputsInfo[operation][npos]) {
          --npos;
        }
        // move if is necessary
        npos += npos == -1 ? 1 : curSize > d_gatesInputsInfo[operation][npos];
        pos   = (npos < pos ? npos : pos);

        curSize = 0;
      }
    }

    // if we did not fill all gates
    if (curSize > 1) {
      // if we have less elements than we can add, and our logical element
      // has too big gates number, move to lower
      int npos = pos;
      while (npos >= 0 && curSize < d_gatesInputsInfo[operation][npos]) {
        --npos;
      }
      // move if is necessary
      npos += npos == -1 ? 1 : curSize > d_gatesInputsInfo[operation][npos];
      pos   = (npos < pos ? npos : pos);

      while (curSize < d_gatesInputsInfo[operation][pos]) {
        graph->addEdge(x_input, oper);
        ++curSize;
      }
    }

    if (curSize)
      nextLayout.push_back(oper);

    // swap layouts
    curLayout = nextLayout;
    nextLayout.clear();
  }

  return curLayout.back();
}

VertexPtr Parser::parseInputNot(std::string oper, std::string name) {
  // saving us from duplicate input
  if (!d_inputsByNames.count(name))
    d_inputsByNames[name] = d_graph->addInput(name);

  // same protection from multiple inputs
  if (!d_notInputsByNames.count("not " + name)) {
    d_notInputsByNames["not " + name] =
        d_graph->addGate(Gates::GateNot, "not_" + name);

    d_graph->addEdge(d_inputsByNames[name], d_notInputsByNames["not " + name]);
  }

  if (oper == "input")
    return d_inputsByNames[name];

  return d_notInputsByNames["not " + name];
}

VertexPtr Parser::parseToVertex(const std::string& i_expr) {
  std::pair<int32_t, std::vector<std::string>> splited_expr =
      splitLogicExpression(i_expr);
  if (splited_expr.first == -1)
    return nullptr;

  VertexPtr                                    outputVert = nullptr;
  std::pair<int32_t, std::vector<std::string>> splited_expr_next;

  // here create output for future parsing
  if (splited_expr.second[0] == "output") {
    outputVert = d_graph->addOutput(splited_expr.second[1]);

    std::vector<std::pair<int32_t, int32_t>> brackets =
        createBrackets(splited_expr.second[2]).second;

    for (auto tl : brackets) {
      if (tl.first == 0 && tl.second == splited_expr.second[2].size() - 1) {
        splited_expr.second[2] =
            splited_expr.second[2].substr(1, splited_expr.second[2].size() - 2);
        break;
      }
    }

    // splitting left data
    splited_expr_next = splitLogicExpression(splited_expr.second[2]);

    if (splited_expr_next.first == -1)
      return nullptr;
  }
  // if it is input (or not, for which it is necessary to create an input),
  // just create it and return
  else if (splited_expr.second[0] == "input"
           || splited_expr.second[0] == "not") {
    return parseInputNot(splited_expr.second[0], splited_expr.second[1]);
  } else {
    splited_expr_next = splited_expr;
  }

  // if we are here, we have a gate or an output
  // so we need to parse data further

  std::vector<VertexPtr> allGates;
  VertexPtr              outPtr;

  // when we have input or not, return it
  if (splited_expr_next.second[0] == "input"
      || splited_expr_next.second[0] == "not") {
    return parseInputNot(
        splited_expr_next.second[0], splited_expr_next.second[1]
    );
  }
  // in case of const we also need to add gate to it
  else if (splited_expr_next.second[0] == "const") {
    outPtr =
        d_graph->addConst(splited_expr.second[2][0], splited_expr.second[2]);
  } else {
    allGates.reserve(splited_expr_next.second.size() - 1);

    Gates oper = d_settings->parseStringToGate(splited_expr_next.second[0]);
    splited_expr_next.second.erase(splited_expr_next.second.begin());

    for (auto futureVertex : splited_expr_next.second) {
      std::vector<std::pair<int32_t, int32_t>> brackets =
          createBrackets(futureVertex).second;
      for (auto tl : brackets) {
        if (tl.first == 0 && tl.second == futureVertex.size() - 1) {
          futureVertex = futureVertex.substr(1, futureVertex.size() - 2);
          break;
        }
      }

      VertexPtr ptr = parseToVertex(futureVertex);
      if (!ptr)
        return ptr;

      allGates.push_back(ptr);
    }

    // creating from vertex
    outPtr = multipleVerteciesToOne(allGates, oper, d_graph);
  }

  if (outputVert != nullptr) {
    d_graph->addEdge(outPtr, outputVert);
  }

  return outPtr;
}

bool Parser::parseAll() {
  d_graph.reset(new OrientedGraph);

  for (auto exp : d_logExpressions)
    if (createBrackets(exp).first)
      if (!parseToVertex(exp))
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