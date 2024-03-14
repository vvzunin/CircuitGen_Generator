#pragma once

enum MutationTypes
{
  Binary,
  Density,
  AccessionDel,
  InsertDel,
  Exchange,
  Delete
};

/// class MutationParameters
/// @param d_mutationType The type of mutation. Default - binary mutation
/// @param d_probabilityGen Probability of generation, default - 0.1
/// @param d_exchangeType Type of exchange***
/// @param d_probabilityTruthTable Probability of the truth table, default - 0.1
/// */

class MutationParameters
{
public:
  MutationParameters() = default;

  /// @brief getMutationType The method returns the current mutation type stored in the private d_mutationType field
  /// @return the current value of the mutation type
  /// */

  MutationTypes getMutationType() const;

  /// @brief getProbabilityGen The method returns the current value of the probability of mutation generation stored in the private d_probabilityGen field.
  /// @return Current probability of mutation generation (double)
  /// */

  double getProbabilityGen() const;

  /// @brief getExchangeType The method returns the current value of the exchange type stored in the private d_exchangeType field.
  /// @return The current value of the exchange type
  /// */

  int getExchangeType() const;

  /// @brief getProbabilityTruthTable The method returns the current value of the probability of changing the truth table, stored in the private field d_probabilityTruthTable.
  /// @return The current value of the probability of changing the truth table
  /// */

  double getProbabilityTruthTable() const;


  bool operator== (const MutationParameters& r) const;

  /// @brief setMutationType The method sets a new value for the mutation type
  /// @param i_mutationType A new mutation type to be set for the MutationParameters object.
  /// */

  void setMutationType(MutationTypes i_mutationType);

  /// @brief setProbabilityGen The method sets a new value for the probability of mutation generation.
 /// @param i_probabilityGen A new value for the probability of mutation generation, which will be set for the MutationParameters object
 /// </summary>
 /// */

  void setProbabilityGen(double i_probabilityGen);

  /// @brief setExchangeType The method sets a new value for the exchange type.
 /// @param i_exchangeType The new value of the exchange type to be set for the MutationParameters object
 /// */


  void setExchangeType(int i_exchangeType);

  /// @brief setProbabilityTruthTable The method sets a new probability value for the truth table
  /// @param i_probabilityTruthTable a new probability value for the truth table that will be set for the MutationParameters object.
  /// */


  void setProbabilityTruthTable(double i_probabilityTruthTable);
private:
  MutationTypes d_mutationType = MutationTypes::Binary;
  double d_probabilityGen = 0.1;
  int d_exchangeType = 0;
  double d_probabilityTruthTable = 0.1;
};
