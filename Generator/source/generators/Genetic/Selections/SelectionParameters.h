#pragma once

enum SelectionTypes
{
  Base
};


/// class SelectionParameters
/// @param d_selectionType The type of selection represented by the 
/// SelectionTypes enumeration. By default, it is set to SelectionTypes::Base
/// @param d_numOfSurvivors The number of surviving elements after selection.
/// By default, it is set to 0.
/// */

class SelectionParameters
{
public:
  /// @brief getNumOfSurvivors Returns the number of surviving elements after selection
  /// @return Returns an integer equal to the number of surviving elements after selection
  /// */
  int getNumOfSurvivors() const;

  /// @brief setNumOfSurvivors The method sets the number of surviving elements after selection
  /// @param i_survivors An integer value representing the number of surviving elements to be set
  /// */

  void setNumOfSurvivors(int i_survivors);
  bool operator== (const SelectionParameters& r) const;

  /// @brief setSelectionType The method sets the type of selection for the combination scheme
  /// @param i_selectionType A SelectionTypes enumeration representing the type of selection to be set
  /// */

  void setSelectionType(SelectionTypes i_selectionType);

  /// @brief getSelectionType The method returns the current selection type for the combination scheme
  /// @return SelectionTypes - an enumeration representing the current selection type
  /// */

  SelectionTypes getSelectionType() const;
private:
  SelectionTypes d_selectionType = SelectionTypes::Base;
  int d_numOfSurvivors = 0;
};
