#pragma once

#include <string>
#include <memory>

#include "settings/Settings.h"

template<typename Type, typename ParametersTypes>
class ChronosomeType
{
public:
  ChronosomeType(const std::string& i_name, const Type& i_chronosome);
  Type getChronosomeType() const;
  void setChronosomeType(const Type& i_chronosome);
  double getAdaptationIndex() const;
  void setAdaptationIndex(double i_adaptationIndex);
  std::string getName() const;
  void adaptationFunction();
  bool operator== (const ChronosomeType<Type, ParametersTypes>& r) const;

private:
  double d_adaptationIndex;
  Type d_chronosome;
  std::shared_ptr<Settings> d_settings = Settings::getInstance("GraphVertex");
  std::string d_name;
};
