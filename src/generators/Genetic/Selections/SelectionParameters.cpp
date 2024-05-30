#include <cstdint>
#include <tuple>

#include "SelectionParameters.hpp"

void SelectionParameters::setSelectionType(SelectionTypes i_selectionType) {
  d_selectionType = i_selectionType;
}

SelectionTypes SelectionParameters::getSelectionType() const {
  return d_selectionType;
}

int32_t SelectionParameters::getNumOfSurvivors() const {
  return d_numOfSurvivors;
}

void SelectionParameters::setNumOfSurvivors(int32_t i_survivors) {
  d_numOfSurvivors = i_survivors;
}

bool SelectionParameters::operator==(const SelectionParameters& r) const {
  return std::tie(d_selectionType, d_numOfSurvivors)
      == std::tie(r.d_selectionType, r.d_numOfSurvivors);
}
