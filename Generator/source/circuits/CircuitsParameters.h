#include <string>
#include <map>

class CircuitParameters
{
public:
  CircuitParameters(){};


private:
  std::string name = "";
  int d_numInputs = 0;
  int d_munOutputs = 0;
  int d_maxLevel = 0;
  int d_munEdges = 0;
  double d_reliability = 0.;
  double d_size = 0.;
  double d_area = 0.;
  int d_longestPath = 0;
  int d_gates = 0;
  double d_sensitivityFactor = 0.;
  double d_reliabilityPercent = 0.;
  double d_sensitiveArea = 0.;
  double d_sensitiveAreaPercent = 0.;
  std::string hashCode = "";
  std::map<std::string, int> numElementsOfEachType;
  std::map<std::pair<std::string, std::string>, int> numEdgesOfEachType;

  


}
