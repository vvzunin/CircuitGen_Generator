#include <vector>
#include <string>
#include <function>

#include "Parents.h"

template<typename Type, typename ParametersType>
std::vector<int> ParentsTypes(ParentsParameters i_parentsParameters,
                              std::vector<ChronosomeType<Type, ParametersType>> i_population
)
{
  std::string s = i_parentsParameters.ParentsType.toString();
  std::method = "Parents" + s;
  std::function = getFunction(method);
  return function(i_parentsParameters, i_population);
}
