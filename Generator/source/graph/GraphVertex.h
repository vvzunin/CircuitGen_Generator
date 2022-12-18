


class GraphVertex {
public:
  GraphVertex(const std::string& i_expr,
              const string& i_operation
              bool i_value = false,
              const std::string& i_wireName);
  int GraphVertex::getLevel();
  void GraphVertex::setLevel(int i_level);
  bool GraphVertex::getValue();
  void GraphVertex::setValue(bool i_value);
  std::string GraphVertex::getOperation();
  std::string GraphVertex::getWireName();

private:
  std::string d_logicExpression = "";
  std::string d_operation = "";
  int d_level = 0;
  bool d_value = false;
  std::string d_wireName = "wr";
  int d_count = 0;
  Settings d_settings;
}
