#pragma once
#include <generators/simple/SimpleGenerator.hpp>
#include <baseStructures/truthTable/TruthTable.hpp>

class FromTruthTableGenerator : public SimpleGenerator {
public:
  FromTruthTableGenerator();
  FromTruthTableGenerator(uint_fast32_t i_seed);
  FromTruthTableGenerator(const GenerationParameters& i_param);

  /// @brief cnfFromTruthTable accepts a truth table as an input in the form of
  /// a Truth Table object and returns a vector of rows representing an
  /// expression in the form of a conjunctive normal form (KNF) that
  /// corresponds to this truth table. The conjunctive normal form form
  /// represents a logical expression in the form of a conjunction of
  /// disjunctions
  /// @param i_table This is an object of the Truth Table type, which is a
  /// truth table. The truth table consists of a set of rows, where each row
  /// represents a possible combination of variable values in a logical
  /// expression, and each column represents the value of a variable in that
  /// combination.
  /// @param i_tp This is a Boolean flag (true/false) that indicates whether
  /// to add negation before variables that have the value "False" in the
  /// truth table. If i_tp is set to true, negation will be added to the
  /// variables with the value "False". If i_tp is set to false, the
  /// negation will not be added. This allows you to choose between the
  /// representation of the truth table in KNF or in disjunctive normal
  /// form (DNF)
  /// @return a vector of strings representing an expression in the form of
  /// conjunctive normal form (KNF) corresponding to the input truth table
  /// @code
  /// // @todo: Examples
  /// @endcode

  GraphPtr cnfFromTruthTable(const TruthTable& i_table, bool i_tp = true);
  GraphPtr zhegalkinFromTruthTable(const TruthTable& i_table);
};
