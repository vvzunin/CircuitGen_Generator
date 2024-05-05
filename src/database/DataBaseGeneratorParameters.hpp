#pragma once

#include <generators/GenerationParameters.hpp>
#include <settings/Settings.hpp>

/// class DataBaseGeneratorParameters
/// @param d_minInputs Minimum number of input signals for database generation
/// @param d_maxInputs The maximum number of input signals to generate a
/// database.
/// @param d_minOutputs Minimum number of output signals for database generation
/// @param d_maxOutputs The maximum number of output signals for database
/// generation
/// @param d_eachIteration The number of generation iterations for each
/// combination of input and output signals
/// @param d_generationTypes Type of database generation
/// @param d_generationParameters Parameters for a specific database generation
/// method
/// */

/// @todo: maybe it need heritance from
/// GenerationParameters?
class DataBaseGeneratorParameters  
                                   
{
public:
  DataBaseGeneratorParameters(
      int                  i_minInputs,
      int                  i_maxInputs,
      int                  i_minOutputs,
      int                  i_maxOutputs,
      int                  i_eachIteration,
      GenerationTypes      i_gt,
      GenerationParameters i_gp
  );

  /// @brief setInputs The method sets the number of input signals to generate
  /// the database
  /// @param i_inputs An integer value representing the number of input signals
  /// that must be set to generate the database
  /// */

  void                 setInputs(int i_inputs);

  /// @brief setOutputs The method sets the number of output signals to generate
  /// the database
  /// @param i_outputs An integer value representing the number of output
  /// signals that must be set to generate the database
  /// */

  void                 setOutputs(int i_outputs);

  /// @brief setIteration The method sets the iteration number for database
  /// generation
  /// @param i_iteration An integer value representing the iteration number that
  /// must be set to generate the database
  /// */

  void                 setIteration(int i_iteration);

  /// @brief setName The method is used to set the name for database generation
  /// @param i_name A string containing the name to be set to generate the
  /// database
  /// */

  void                 setName(const std::string& i_name);

  /// @brief getMinInputs This method is used to get the minimum number of
  /// inputs set in the database generation parameters.
  /// @return Minimum number of inputs for database generation
  /// */

  int                  getMinInputs() const;

  /// @brief getMaxInputs This method is used to get the maximum number of
  /// inputs set in the database generation parameters.
  /// @return Maximum number of inputs for database generation
  /// */

  int                  getMaxInputs() const;

  /// @brief getMinOutputs This method is used to get the minimum number of
  /// outputs set in the database generation parameters.
  /// @return The minimum number of outputs for database generation.
  /// */

  int                  getMinOutputs() const;

  /// @brief getMaxOutputs This one is used to get the maximum number of outputs
  /// set in the database generation parameters.
  /// @return Maximum number of outputs for database generation
  /// */

  int                  getMaxOutputs() const;

  /// @brief getEachIteration This method is used to get the number of
  /// iterations that need to be performed for each combination of inputs and
  /// outputs when generating a database.
  /// @return The number of iterations for each combination of inputs and
  /// outputs during database generation.
  /// */

  int                  getEachIteration() const;

  /// @brief getGenerationParameters This method is used to get the database
  /// generation parameters
  /// @return Database Generation Parameters
  /// */

  GenerationParameters getGenerationParameters() const;

  /// @brief getGenerationType This method returns a GenerationTypes type
  /// variable representing the database generation type
  /// @return GenerationTypes of the database generation type
  /// */
  GenerationTypes      getGenerationType() const;

private:
  int             d_minInputs       = 0;
  int             d_maxInputs       = 0;
  int             d_minOutputs      = 0;
  int             d_maxOutputs      = 0;
  int             d_eachIteration   = 0;
  GenerationTypes d_generationTypes = GenerationTypes::FromRandomTruthTable;
  GenerationParameters d_generationParameters;
};