#pragma once

enum SelectionTypes
{
  Base
};


class SelectionParameters
{
public:
  int getNumOfSurvivors() const;
  void setNumOfSurvivors(int i_survivors);
  bool operator== (const SelectionParameters& r) const;
  void setSelectionType(const SelectionTypes i_selectionType);
private:
  SelectionTypes d_selectionType = SelectionTypes::Base;
  int d_numOfSurvivors = 0;
};
