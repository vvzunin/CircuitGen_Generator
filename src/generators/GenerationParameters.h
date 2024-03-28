#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include <settings/Settings.h>

class CNNFromTruthTableParameters {
 public:
  bool getCNFF() { return d_CNFF; }
  bool getCNFT() { return d_CNFT; }
  void setCNFF(bool i_CNFF) { d_CNFF = i_CNFF; }
  void setCNFT(bool i_CNFT) { d_CNFT = i_CNFT; }
  void setLimit(bool i_limit) { d_generateLimitations = i_limit; }

 private:
  bool d_generateLimitations = false;
  bool d_CNFF = false;
  bool d_CNFT = false;
};

class GeneratorRandLevelParameters {
 public:
  int getMinLevel() const { return d_minLevel; }

  void setMinLevel(int i_minLevel) { d_minLevel = i_minLevel; }

  int getMaxLevel() const { return d_maxLevel; }

  void setMaxLevel(int i_maxLevel) { d_maxLevel = i_maxLevel; }

  int getMinElements() const { return d_minElements; }

  void setMinElements(int i_minElements) { d_minElements = i_minElements; }

  int getMaxElements() const { return d_maxElements; }

  void setMaxElements(int i_maxElements) { d_maxElements = i_maxElements; }

 private:
  int d_minLevel = 0;
  int d_maxLevel = 0;
  int d_minElements = 0;
  int d_maxElements = 0;
};

class GeneratorNumOperationParameters {
 public:
  int getLogicOper(const Gates &i_op) const {
    if (d_logicOper.find(i_op) != d_logicOper.end())
      return d_logicOper.at(i_op);
    return -1;
  }

  std::map<Gates, int> getLogicOpers() const { return d_logicOper; }
  void setLogicOper(const std::pair<Gates, int> &i_p) {
    d_logicOper[i_p.first] = i_p.second;
  }

  void setLogicOper(const std::map<Gates, int> &i_p) {
    d_logicOper = i_p;
  }

  bool getLeaveEmptyOut() const { return d_leaveEmptyOut; }

  void setLeaveEmptyOut(bool i_leo) { d_leaveEmptyOut = i_leo; }

 private:
  std::map<Gates, int> d_logicOper;
  bool d_leaveEmptyOut = true;
};

class GeneratorSummatorParameters {
 public:
  bool d_OverFlowIn = false;
  bool d_OverFlowOut = false;
  bool d_minus = false;
  bool getOverFlowIn() {return d_OverFlowIn;}
  bool getOverFlowOut() {return d_OverFlowOut;}
  bool getMinus() {return d_minus;}
  void setOverFlowIn(bool i_overflowIn) {d_OverFlowIn = i_overflowIn;}
  void setOverFlowOut(bool i_overflowOut) {d_OverFlowOut = i_overflowOut;}
  void setMinus(bool i_minus) {d_minus = i_minus;}
};

class GeneratorComparisonParameters {
 public:
  bool d_compare0 = false;
  bool d_compare1 = false;
  bool d_compare2 = false;
  bool getCompare0() {return d_compare0;}
  bool getCompare1() {return d_compare1;}
  bool getCompare2() {return d_compare2;}
  void setCompare0(bool i_compare0) {d_compare0 = i_compare0;}
  void setCompare1(bool i_compare1) {d_compare1 = i_compare1;}
  void setCompare2(bool i_compare2) {d_compare2 = i_compare2;}
};

class GeneratorEncoderParameters {};

class GeneratorSubtractorParameters{
public:
    bool getOverFlowIn() {return d_OverFlowIn;}
    bool getOverFlowOut() {return d_OverFlowOut;}
    bool getSub() {return d_sub;}
    void setOverFlowIn(bool i_overflowIn) {d_OverFlowIn = i_overflowIn;}
    void setOverFlowOut(bool i_overflowOut) {d_OverFlowOut = i_overflowOut;}
    void setSub(bool i_sub) {d_sub = i_sub;}
private:
    bool d_OverFlowIn = false;
    bool d_OverFlowOut = false;
    bool d_sub = false;
};


class GenerationParameters {
 public:
  GenerationParameters(const std::string &i_name,
                       const std::string &i_requestId, int i_inputs,
                       int i_outputs, int i_iteration,
                       std::string i_libraryName = "",
                       bool i_calculateStatsAbc = false,
                       bool i_makeOptimizedFiles = false,
                       bool i_makeFirrtl = false, bool i_makeBench = false)
      : d_name(i_name),
        d_requestId(i_requestId),
        d_inputs(i_inputs),
        d_outputs(i_outputs),
        d_iteration(i_iteration),
        d_libraryName(i_libraryName){};

  std::string getName() const { return d_name; }

  void setName(const std::string &i_name) { d_name = i_name; }

  std::string getRequestId() const { return d_requestId; }

  std::string getLibraryName() const { return d_libraryName; }

  void setLibraryName(std::string i_libraryName) {
    d_libraryName = i_libraryName;
  }

  int getInputs() const { return d_inputs; }

  void setInputs(int i_inputs) { d_inputs = i_inputs; }

  int getOutputs() const { return d_outputs; }

  void setOutputs(int i_outputs) { d_outputs = i_outputs; }

  int getIteration() const { return d_iteration; }

  void setIteration(int i_iteration) { d_iteration = i_iteration; }

  std::uint_fast32_t getSeed() const { return d_seed; }

  void setSeed(std::uint_fast32_t i_seed) { d_seed = i_seed; }

  std::map<std::string, std::vector<int>> getGatesInputsInfo() const {
    return d_gatesInputsInfo;
  }

  void setGatesInputInfo(
      const std::map<std::string, std::vector<int>> &i_gatesInputsInfo) {
    d_gatesInputsInfo = i_gatesInputsInfo;
  }

  CNNFromTruthTableParameters getCNF() const {
    return d_cnfFromTruthTableParameters;
  }
  GeneratorRandLevelParameters getRandLevel() const {
    return d_generatorRandLevelParameters;
  }
  GeneratorNumOperationParameters getNumOperations() const {
    return d_generatorNumOperationParameters;
  }
  GeneratorSummatorParameters getSummator() const {
    return d_generatorSummatorParameters;
  }
  GeneratorComparisonParameters getComparison() const {
    return d_generatorComparisonParameters;
  }
  GeneratorEncoderParameters getEncoder() const {
    return d_generatorEncoderParameters;
  }
  GeneratorSubtractorParameters getSubtractor() const {
      return d_generatorSubtractorParameters; }
  // GeneticParameters getGenetic() const { return d_geneticParameters; }
  void setCNFF(bool i_CNFF) { d_cnfFromTruthTableParameters.setCNFF(i_CNFF); }
  void setCNFT(bool i_CNFT) { d_cnfFromTruthTableParameters.setCNFT(i_CNFT); }
  void setLimit(bool i_limit) {
    d_cnfFromTruthTableParameters.setLimit(i_limit);
  }
  void setRandLevelParameters(int i_minLevel, int i_maxLevel, int i_minElements,
                              int i_maxElements) {
    d_generatorRandLevelParameters.setMinLevel(i_minLevel);
    d_generatorRandLevelParameters.setMaxLevel(i_maxLevel);
    d_generatorRandLevelParameters.setMinElements(i_minElements);
    d_generatorRandLevelParameters.setMaxElements(i_maxElements);
  }
  void setNumOperationParameters(const std::map<Gates, int> &i_m,
                                 bool i_LeaveEmptyOut) {
    d_generatorNumOperationParameters.setLogicOper(i_m);
    d_generatorNumOperationParameters.setLeaveEmptyOut(i_LeaveEmptyOut);
  }
    void setSubtractorParameters(bool i_overflowIn, bool i_overflowOut, bool i_sub)
    {
        d_generatorSubtractorParameters.setOverFlowIn(i_overflowIn);
        d_generatorSubtractorParameters.setOverFlowOut(i_overflowOut);
        d_generatorSubtractorParameters.setSub(i_sub);
    }
  void setSummatorParameters(bool i_overflowIn, bool i_overflowOut, bool i_minus){
    d_generatorSummatorParameters.setOverFlowIn(i_overflowIn);
    d_generatorSummatorParameters.setOverFlowOut(i_overflowOut);
    d_generatorSummatorParameters.setMinus(i_minus);
  }
  void setComparisonParameters(bool i_compare0, bool i_compare1, bool i_compare2){
    d_generatorComparisonParameters.setCompare0(i_compare0);
    d_generatorComparisonParameters.setCompare1(i_compare1);
    d_generatorComparisonParameters.setCompare2(i_compare2);
  }
  
    // void setNumOfCycles(int i_numOfCycles) {
  // d_geneticParameters.setNumOfCycles(i_numOfCycles); } void
  // setPopulationSize(int i_populationSize) {
  // d_geneticParameters.setPopulationSize(i_populationSize); } void
  // setRecombinationParameters(ParentsTypes i_parentsTypes, int
  // i_tournamentNumber, RecombinationTypes i_recombinationType, int
  // i_refPoints, double maskProbability, int i_recombinationNumber); void
  // setMutationParameters(MutationTypes i_mutationTipe, double
  // i_probabilityGen, int i_exchangeType, double i_probabilityTruthTable); void
  // setSelectionParameters(SelectionTypes i_selectionType, int
  // i_numOfSurvivors); void setKeyEndProcessIndex(double i_keyEndProcessIndex)
  // { d_geneticParameters.setKeyEndProcessIndex(i_keyEndProcessIndex); }

 private:
  std::string d_name = "";
  std::string d_requestId;
  std::string d_libraryName;
  int d_inputs = 0;
  int d_outputs = 0;
  int d_iteration = 0;
  std::map<std::string, std::vector<int>> d_gatesInputsInfo;

  std::uint_fast32_t d_seed = 0;

  CNNFromTruthTableParameters d_cnfFromTruthTableParameters;
  GeneratorRandLevelParameters d_generatorRandLevelParameters;
  GeneratorNumOperationParameters d_generatorNumOperationParameters;
  GeneratorSummatorParameters d_generatorSummatorParameters;
  GeneratorComparisonParameters d_generatorComparisonParameters;
  GeneratorEncoderParameters d_generatorEncoderParameters;
  GeneratorSubtractorParameters d_generatorSubtractorParameters;
  // GeneticParameters d_geneticParameters = GeneticParameters(2, 3);
};