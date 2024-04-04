#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include <settings/Settings.hpp>

class CNNFromTruthTableParameters {
public:
  bool getCNFF() { return d_CNFF; }
  bool getCNFT() { return d_CNFT; }
  void setCNFF(bool i_CNFF) { d_CNFF = i_CNFF; }
  void setCNFT(bool i_CNFT) { d_CNFT = i_CNFT; }
  void setLimit(bool i_limit) { d_generateLimitations = i_limit; }

private:
  bool d_generateLimitations = false;
  bool d_CNFF                = false;
  bool d_CNFT                = false;
};

class GeneratorRandLevelParameters {
public:
  int  getMinLevel() const { return d_minLevel; }

  void setMinLevel(int i_minLevel) { d_minLevel = i_minLevel; }

  int  getMaxLevel() const { return d_maxLevel; }

  void setMaxLevel(int i_maxLevel) { d_maxLevel = i_maxLevel; }

  int  getMinElements() const { return d_minElements; }

  void setMinElements(int i_minElements) { d_minElements = i_minElements; }

  int  getMaxElements() const { return d_maxElements; }

  void setMaxElements(int i_maxElements) { d_maxElements = i_maxElements; }

private:
  int d_minLevel    = 0;
  int d_maxLevel    = 0;
  int d_minElements = 0;
  int d_maxElements = 0;
};

class GeneratorNumOperationParameters {
public:
  int getLogicOper(const Gates& i_op) const {
    if (d_logicOper.find(i_op) != d_logicOper.end())
      return d_logicOper.at(i_op);
    return -1;
  }

  std::map<Gates, int> getLogicOpers() const { return d_logicOper; }
  void                 setLogicOper(const std::pair<Gates, int>& i_p) {
    d_logicOper[i_p.first] = i_p.second;
  }

  void setLogicOper(const std::map<Gates, int>& i_p) { d_logicOper = i_p; }

  bool getLeaveEmptyOut() const { return d_leaveEmptyOut; }

  void setLeaveEmptyOut(bool i_leo) { d_leaveEmptyOut = i_leo; }

private:
  std::map<Gates, int> d_logicOper;
  bool                 d_leaveEmptyOut = true;
};

class GeneratorSummatorParameters {
public:
  bool OverFlowIn  = false;
  bool OverFlowOut = false;
  bool minus       = false;
};

class GeneratorComparisonParameters {
public:
  bool compare0 = false;
  bool compare1 = false;
  bool compare2 = false;
};

class GeneratorEncoderParameters {};

class GenerationParameters {
public:
  GenerationParameters(
      const std::string& i_name,
      const std::string& i_requestId,
      int                i_inputs,
      int                i_outputs,
      int                i_iteration,
      std::string        i_libraryName = "",
      bool i_calculateStatsAbc         = false,
      bool i_makeOptimizedFiles        = false,
      bool i_makeFirrtl                = false,
      bool i_makeBench                 = false,
      bool i_makeGraphML               = false
  ) :
    d_name(i_name),
    d_requestId(i_requestId),
    d_inputs(i_inputs),
    d_outputs(i_outputs),
    d_iteration(i_iteration),
    d_libraryName(i_libraryName),
    d_calculateStatsAbc(i_calculateStatsAbc),
    d_makeOptimizedFiles(i_makeOptimizedFiles),
    d_makeFirrtl(i_makeFirrtl),
    d_makeBench(i_makeBench),
    d_makeGraphML(i_makeGraphML) {};

  std::string getName() const { return d_name; }

  void        setName(const std::string& i_name) { d_name = i_name; }

  std::string getRequestId() const { return d_requestId; }

  std::string getLibraryName() const { return d_libraryName; }

  void        setLibraryName(std::string i_libraryName) {
    d_libraryName = i_libraryName;
  }

  int  getInputs() const { return d_inputs; }

  void setInputs(int i_inputs) { d_inputs = i_inputs; }

  int  getOutputs() const { return d_outputs; }

  void setOutputs(int i_outputs) { d_outputs = i_outputs; }

  int  getIteration() const { return d_iteration; }

  void setIteration(int i_iteration) { d_iteration = i_iteration; }

  bool getMakeGraphML() const { return d_makeGraphML; }

  std::uint_fast32_t getSeed() const { return d_seed; }

  void               setSeed(std::uint_fast32_t i_seed) { d_seed = i_seed; }

  std::map<std::string, std::vector<int>> getGatesInputsInfo() const {
    return d_gatesInputsInfo;
  }

  void setGatesInputInfo(
      const std::map<std::string, std::vector<int>>& i_gatesInputsInfo
  ) {
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
  // GeneticParameters getGenetic() const { return d_geneticParameters; }
  void setCNFF(bool i_CNFF) { d_cnfFromTruthTableParameters.setCNFF(i_CNFF); }
  void setCNFT(bool i_CNFT) { d_cnfFromTruthTableParameters.setCNFT(i_CNFT); }
  void setLimit(bool i_limit) {
    d_cnfFromTruthTableParameters.setLimit(i_limit);
  }
  void setRandLevelParameters(
      int i_minLevel,
      int i_maxLevel,
      int i_minElements,
      int i_maxElements
  ) {
    d_generatorRandLevelParameters.setMinLevel(i_minLevel);
    d_generatorRandLevelParameters.setMaxLevel(i_maxLevel);
    d_generatorRandLevelParameters.setMinElements(i_minElements);
    d_generatorRandLevelParameters.setMaxElements(i_maxElements);
  }
  void setNumOperationParameters(
      const std::map<Gates, int>& i_m,
      bool                        i_LeaveEmptyOut
  ) {
    d_generatorNumOperationParameters.setLogicOper(i_m);
    d_generatorNumOperationParameters.setLeaveEmptyOut(i_LeaveEmptyOut);
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
  std::string                             d_name = "";
  std::string                             d_requestId;
  std::string                             d_libraryName;
  int                                     d_inputs    = 0;
  int                                     d_outputs   = 0;
  int                                     d_iteration = 0;
  bool                                    d_calculateStatsAbc;
  bool                                    d_makeOptimizedFiles;
  bool                                    d_makeFirrtl;
  bool                                    d_makeBench;
  bool                                    d_makeGraphML;
  std::map<std::string, std::vector<int>> d_gatesInputsInfo;

  std::uint_fast32_t                      d_seed = 0;

  CNNFromTruthTableParameters             d_cnfFromTruthTableParameters;
  GeneratorRandLevelParameters            d_generatorRandLevelParameters;
  GeneratorNumOperationParameters         d_generatorNumOperationParameters;
  GeneratorSummatorParameters             d_generatorSummatorParameters;
  GeneratorComparisonParameters           d_generatorComparisonParameters;
  GeneratorEncoderParameters              d_generatorEncoderParameters;
  // GeneticParameters d_geneticParameters = GeneticParameters(2, 3);
};