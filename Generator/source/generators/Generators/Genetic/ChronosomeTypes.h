#pragma once

#include <string>

template<typename Type, typename ParametersTypes>
class ChronosomeType
{
public:
  ChronosomeType(const std::string& i_name, const Type& i_chronosome);
  Type getChronosomeType() const;
  void setChronosomeType(const Type& i_chronosome);
  void adaptationFunction();
private:
  double d_adaptationIndex;
  Type d_chronosome;
  Settings d_settings;
  std::string d_name;
}
