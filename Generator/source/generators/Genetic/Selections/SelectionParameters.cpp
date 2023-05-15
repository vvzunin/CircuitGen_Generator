#include <tuple>

#include "SelectionParameters.h"

void SelectionParameters::setSelectionType (SelectionTypes i_selectionType)
{
  d_selectionType = i_selectionType;
}

int SelectionParameters::getNumOfSurvivors() const
{
  return d_numOfSurvivors;
}

void SelectionParameters::setNumOfSurvivors(int i_survivors)
{
  d_numOfSurvivors = i_survivors;
}

bool SelectionParameters::operator== (const SelectionParameters& r) const
{
  return std::tie(d_selectionType, d_numOfSurvivors) == std::tie(r.d_selectionType, r.d_numOfSurvivors);
}
