#pragma once

#include <string>
#include <memory>

#include "settings/Settings.h"

template<typename Type, typename ParametersTypes>
class ChromosomeType
{
public:
  ChromosomeType(const std::string& i_name, const Type& i_Chromosome);
  Type getChromosomeType() const;
  void setChromosomeType(const Type& i_Chromosome);
  double getAdaptationIndex() const;
  void setAdaptationIndex(double i_adaptationIndex);
  std::string getName() const;
  void adaptationFunction();
  bool operator== (const ChromosomeType<Type, ParametersTypes>& r) const;

private:
  double d_adaptationIndex;
  Type d_Chromosome;
  std::shared_ptr<Settings> d_settings = Settings::getInstance("ChromosomeType");
  std::string d_name;
};
