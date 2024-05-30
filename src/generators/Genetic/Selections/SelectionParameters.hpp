#pragma once

#include <cstdint>

enum SelectionTypes
{
  Base
};


class SelectionParameters
{
public:
  int32_t getNumOfSurvivors() const;
  void setNumOfSurvivors(int32_t i_survivors);
  bool operator== (const SelectionParameters& r) const;
  void setSelectionType(SelectionTypes i_selectionType);
  SelectionTypes getSelectionType() const;
private:
  SelectionTypes d_selectionType = SelectionTypes::Base;
  int32_t d_numOfSurvivors = 0;
};
