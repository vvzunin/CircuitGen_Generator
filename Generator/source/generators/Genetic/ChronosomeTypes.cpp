#include <string>
#include <cmath>

#include "ChronosomeTypes.h"


ChronosomeType::ChronosomeType(const std::string& i_name, const Type& i_chronosome) :
 d_chronosome(i_chronosome),
 d_name(i_name)
{
  adaptationFunction();
}

Type ChronosomeType::getChronosomeType() const
{
  return d_chronosome;
}

void ChronosomeType::setChronosomeType(const Type& i_chronosome)
{
  d_chronosome = i_chronosome;
}

void adaptationFunction()
{
  if constexpr (std::is_same_v<Type, TruthTable>)
  {
    int numInt = 0;
    for (const auto& nucleosoms : d_chronosome)
      for (const auto& nucleosom : nucleosoms)
        if (nucleosom)
          numInt++;

    d_adaptationIndex = abs(0.5 - (numInt / (d_chronosome.size() * d_chronosome.Output())));
  }
}
