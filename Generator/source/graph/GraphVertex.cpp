#include <string>

#include "GraphVertex.cpp"

GraphVertex::GraphVertex(const std::string& i_expr,
                         const string& i_operation
                         bool i_value = false,
                         const std::string& i_wireName):
                         d_logicExpression(i_expr),
                         d_operation(i_operation),
                         d_value(i_value)
{
  Settings settings;
  settings.loadSettings;
  d_settings = settings.getInstance();
  if (d_operation == "input" || d_operation == "output" || d_operation == "const")
    d_wireName = expr;
  else
  {
    if (d_wireName == "")
        d_wireName += std::stoi(i_count++)
    else
        d_wireName = "";
  }
}

int GraphVertex::getLevel()
{
  return d_level;
}

void GraphVertex::setLevel(int i_level)
{
  d_level = i_level;
}

bool GraphVertex::getValue()
{
  return d_value;
}

void GraphVertex::setValue(bool i_value)
{
  d_value = i_value;
}

std::string GraphVertex::getOperation()
{
  return d_operation;
}

std::string GraphVertex::getWireName()
{
  return d_wireName;
}
