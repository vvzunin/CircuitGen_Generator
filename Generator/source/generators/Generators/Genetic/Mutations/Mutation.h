#include <vector>

template<typename Type, typename ParametersType>
class Mutations<Type, ParametersType>
{
public:
  std::vector<ChronosomeType<Type, ParametersType>> MutationType(
    MutationParameters i_mutationParameters,
    std::vector<ChronosomeType<Type, ParametersType>> i_population
  );


private:
  
}
