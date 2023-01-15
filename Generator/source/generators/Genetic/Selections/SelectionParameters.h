#pragma once

enum SelectionTypes
{
  Base
};


class SelectionParameters
{
public:
  int getNumOfSurvivors() const
  {
    return d_numOfSurvivors;
  }

  void setNumOfSurvivors(int i_survivors)
  {
    d_numOfSurvivors = i_survivors;
  }

private:
  SelectionTypes d_selectionType = SelectionTypes::Base;
  int d_numOfSurvivors = 0;
};
