#pragma once

#include <CircuitGenGraph/OrientedGraph.hpp>
#include <additional/RandomGeneratorWithSeed.hpp>
#include <algorithm>
#include <generators/GenerationParameters.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <settings/Settings.hpp>
#include <vector>

using GatesInfo = std::map<CG_Graph::Gates, std::vector<int32_t>>;

namespace CG_Gen {

using namespace CG_Graph;

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
  /// are vectors of integers representing the entry ports for each gate.
  /// @note Example:
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
  const GenerationParameters &getParameters() const;

  std::shared_ptr<Settings> d_settings = Settings::getInstance("GraphVertex");
  std::map<Gates, int32_t> delNull(std::map<Gates, int32_t> i_copyLogicOper);

  std::pair<Gates, int32_t> getRandomElement(const GatesInfo &i_info);
  std::pair<Gates, int32_t> getRandomElement(uint32_t i_gatesLimit);

#if FALSE

  /// @brief getRandomAndNumber The getRandomAndNumber method returns a random
  /// value from the list of possible input ports for the "AND" operator.
  /// @return a random value representing the input port number for the "AND"
  /// operator.
  /// */

  int32_t getRandomAndNumber();

  /// @brief getRandomOrNumber method is a random value from the list of
  /// possible input ports for the "OR" operator
  /// @return a random value representing the input port number for the "OR"
  /// operator.
  /// */

  int32_t getRandomOrNumber();

  /// @brief getRandomNandNumber The method returns a random value from the list
  /// of possible input ports for the "NAND" operator.
  /// @return a random value representing the input port number for the "NAND"
  /// operator
  /// */

  int32_t getRandomNandNumber();

  /// @brief getRandomNorNumber The method returns a random value from the list
  /// of possible input ports for the "NOR" operator.
  /// @return a random value representing the input port number for the "NOR"
  /// operator
  /// */

  int32_t getRandomNorNumber();

  /// @brief getRandomXorNumber The method returns a random value from the list
  /// of possible input ports for the "XOR" operator.
  /// @return a random value representing the input port number for the "XOR"
  /// operator.
  /// */

  int32_t getRandomXorNumber();

  /// @brief The method returns a random value from the list of possible input
  /// ports for the "XNOR" operator.
  /// @return a random value representing the input port number for the "XNOR"
  /// operator
  /// */

  int32_t getRandomXnorNumber();

#endif

  GatesInfo d_gatesInputsInfo;
  RandomGeneratorWithSeed d_randGenerator;
  int32_t d_maxGateNumber = 0;
  int32_t d_minGateNumber = 0;

private:
  const GenerationParameters *d_parameters = nullptr;
};

} // namespace CG_Gen
