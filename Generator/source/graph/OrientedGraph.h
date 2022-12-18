#include <string>
#include <vector>
#include <map>

class OrientedGraph {
public:


private:
  std::vector<GraphVertex> d_vertices;
  std::vector<vector<bool>> d_adjacencyMatrix;
  std::map<std::string, bool> d_error;
  Settings d_settings;

}
