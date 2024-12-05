#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

#include <additional/RandomGeneratorWithSeed.hpp>
#include <CircuitGenGraph/OrientedGraph.hpp>
#include <settings/Settings.hpp>

#include <generators/GenerationParameters.hpp>

using GatesInfo = std::map<Gates, std::vector<int32_t>>;

class SimpleGenerator {
public:
  SimpleGenerator();
  SimpleGenerator(uint_fast32_t i_seed);
  SimpleGenerator(const GenerationParameters &i_param);

  // SimpleGenerator(const SimpleGenerator& other)            = delete;
  // SimpleGenerator& operator=(const SimpleGenerator& other) = delete;
  // SimpleGenerator(SimpleGenerator&& other)                 = delete;
  // SimpleGenerator& operator=(SimpleGenerator&& other)      = delete;

  /// @brief setGatesInputsInfo It is designed to set information about the
  /// inputs for various logic gates. It takes as an argument a dictionary,
  /// where the keys are the names of logical gates (Gates), and the values
  /// are vectors of integers representing the entry ports for each gate.
  /// @param i_info A map containing information about the entrances to
  /// various gates. The map keys are the names of the gates, and the values
  /// are vectors of integers representing the entry ports for each gate
  /// @code
  /// SimpleGenerators generators;
  /// // Define input information for logic gates
  /// std::map<std::string, std::vector<int32_t>> gateInputsInfo =
  /// {
  /// {"AND", {2, 3}},
  /// {"OR", {2, 3}},
  /// {"NOT", {1}},
  /// // Add more gate input information as needed
  /// };
  /// // Set the input information for logic gates
  /// generators.setGatesInputsInfo(gateInputsInfo);
  /// @endcode

  void
  setGatesInputsInfo(const std::map<std::string, std::vector<int32_t>> &i_info);
  GatesInfo getGatesInputsInfo() const;

protected:
  GenerationParameters &getParameters() const;

  std::shared_ptr<Settings> d_settings = Settings::getInstance("GraphVertex");
  std::map<Gates, int32_t> delNull(std::map<Gates, int32_t> i_copyLogicOper);

  // moved it here, because we need to use templates
  template<typename T>
  T randomGenerator(const std::map<T, int32_t> &i_map) {
    // rand element of map
    auto val = i_map.begin();
    std::advance(val, d_randGenerator.getRandInt(0, i_map.size()));

    return val->first;
  }

  std::pair<Gates, int32_t> getRandomElement(const GatesInfo &i_info);
  std::pair<Gates, int32_t> getRandomElement(uint32_t i_gatesLimit);

  /// @brief getRangomAndNumber The getRangomAndNumber method returns a random
  /// value from the list of possible input ports for the "AND" operator.
  /// @return a random value representing the input port number for the "AND"
  /// operator.
  /// */

  int32_t getRangomAndNumber();

  /// @brief getRangomOrNumber method is a random value from the list of
  /// possible input ports for the "OR" operator
  /// @return a random value representing the input port number for the "OR"
  /// operator.
  /// */

  int32_t getRangomOrNumber();

  /// @brief getRangomNandNumber The method returns a random value from the list
  /// of possible input ports for the "NAND" operator.
  /// @return a random value representing the input port number for the "NAND"
  /// operator
  /// */

  int32_t getRangomNandNumber();

  /// @brief getRangomNorNumber The method returns a random value from the list
  /// of possible input ports for the "NOR" operator.
  /// @return a random value representing the input port number for the "NOR"
  /// operator
  /// */

  int32_t getRangomNorNumber();

  /// @brief getRangomXorNumber The method returns a random value from the list
  /// of possible input ports for the "XOR" operator.
  /// @return a random value representing the input port number for the "XOR"
  /// operator.
  /// */

  int32_t getRangomXorNumber();

  /// @brief The method returns a random value from the list of possible input
  /// ports for the "XNOR" operator.
  /// @return a random value representing the input port number for the "XNOR"
  /// operator
  /// */

  int32_t getRangomXnorNumber();

  GatesInfo d_gatesInputsInfo;
  RandomGeneratorWithSeed d_randGenerator;
  int32_t d_maxGateNumber = 0;
  int32_t d_minGateNumber = 0;

private:
  std::shared_ptr<GenerationParameters> d_parameters;
};
