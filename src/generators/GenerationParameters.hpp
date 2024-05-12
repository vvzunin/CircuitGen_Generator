#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include <generators/Genetic/GeneticParameters.h>
#include <settings/Settings.hpp>
#include "easylogger.hpp"

/// class CNNFromTruthTableParameters
/// @param d_generateLimitations It may refer to conditions or restrictions that
/// can be applied to combinational logic, for example, imposing restrictions on
/// input or output signals, or restrictions on the use of certain logical
/// operations
/// @param d_CNFF A Boolean value indicating whether the form of the normal
/// conjunctive normal form (CNF) should be used to generate a combinational
/// scheme.
/// @param d_CNFT A Boolean value indicating whether to use the normal
/// disjunctive normal form (DNF) to generate a combinational scheme
///  */

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

/// @todo: describe the class and what it is for?
/// @brief zhegalkinFromTruthTableParameters
/// @param d_zhegalkin

class zhegalkinFromTruthTableParameters {
public:
  bool getZhegalkin() { return d_zhegalkin; }
  void setZhegalkin(bool i_zhegalkin) { d_zhegalkin = i_zhegalkin; }

private:
  bool d_zhegalkin = false;
};

/// class GeneratorRandLevelParameters
/// @param d_maxLevel It can mean the maximum number of levels in the graph or
/// structure that the level generator generates.
/// @param d_maxElements It can mean the maximum number of logical elements or
/// notes that can be created at each level of the graph structure

class GeneratorRandLevelParameters {
public:
  std::string getDataForLogging() const {
  	std::vector<std::string> result = {};
	result.push_back("minLevel: " + std::to_string(d_minLevel));
	result.push_back("maxLevel: " + std::to_string(d_maxLevel));
	result.push_back("minElements: " + std::to_string(d_minLevel));
	result.push_back("maxElements: " + std::to_string(d_maxElements));
	std::string concat = "";
	for(const auto& s: result)
		if (concat.empty())
			concat = s;
		else
			concat += "; " + s;
	return concat;
  }

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

/// class GeneratorNumOperationParameters
/// @param d_logicOper This is used to store information about logical
/// operations that can be used to generate combinational circuits. Map
/// <name_log_Op, key(value)>
/// @param d_leaveEmptyOut A Boolean value indicating whether to leave an empty
/// output node (for example, if it is not associated with any logical
/// operation)
/// */

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

/// GeneratorSummatorParameters
/// @param OverFlowIn A Boolean value indicating whether overflow of input
/// values is allowed. It relate to the behavior of the adder when the maximum
/// value of the summed inputs is exceeded*
/// @param OverFlowOut A Boolean value indicating whether overflow of the output
/// value is allowed. The adder can generate an additional bit to handle
/// overflow. Default - false
/// @param minus In the context of combinational circuits, this may mean that
/// the adder can work not only with the addition operation, but also with
/// subtractions*
/// */

class GeneratorSummatorParameters {
public:
  bool d_OverFlowIn  = false;
  bool d_OverFlowOut = false;
  bool d_minus       = false;
  bool getOverFlowIn() { return d_OverFlowIn; }
  bool getOverFlowOut() { return d_OverFlowOut; }
  bool getMinus() { return d_minus; }
  void setOverFlowIn(bool i_overflowIn) { d_OverFlowIn = i_overflowIn; }
  void setOverFlowOut(bool i_overflowOut) { d_OverFlowOut = i_overflowOut; }
  void setMinus(bool i_minus) { d_minus = i_minus; }
};

/// class GeneratorComparisonParameters
/// @param compare0 A Boolean value indicating whether a comparison with zero is
/// enabled. In the context of combinational circuits, this may mean that the
/// circuit must perform a comparison with a zero value.
/// @param compare1 A Boolean value indicating whether a comparison with a unit
/// is enabled. In the context of combinational circuits, this may mean that the
/// circuit must perform a comparison with a single value
/// @param compare2 A Boolean value indicating whether a comparison with two is
/// enabled. In the context of combinational circuits, this may mean that the
/// circuit must perform a comparison with a double value
///
/// */

/// @todo: Desc class
class GeneratorComparisonParameters {
public:
  bool d_compare0 = false;
  bool d_compare1 = false;
  bool d_compare2 = false;
  bool getCompare0() { return d_compare0; }
  bool getCompare1() { return d_compare1; }
  bool getCompare2() { return d_compare2; }
  void setCompare0(bool i_compare0) { d_compare0 = i_compare0; }
  void setCompare1(bool i_compare1) { d_compare1 = i_compare1; }
  void setCompare2(bool i_compare2) { d_compare2 = i_compare2; }
};

/// @todo: Desc class
class GeneratorSubtractorParameters {
public:
  bool getOverFlowIn() { return d_OverFlowIn; }
  bool getOverFlowOut() { return d_OverFlowOut; }
  bool getSub() { return d_sub; }
  void setOverFlowIn(bool i_overflowIn) { d_OverFlowIn = i_overflowIn; }
  void setOverFlowOut(bool i_overflowOut) { d_OverFlowOut = i_overflowOut; }
  void setSub(bool i_sub) { d_sub = i_sub; }

private:
  bool d_OverFlowIn  = false;
  bool d_OverFlowOut = false;
  bool d_sub         = false;
};

/// @todo: Desc class
class GeneratorALUParameters {
public:
  bool                 getALL() { return d_ALL; }
  bool                 getSUM() { return d_SUM; }
  bool                 getSUB() { return d_SUB; }
  bool                 getNSUM() { return d_NSUM; }
  bool                 getNSUB() { return d_NSUB; }
  bool                 getMULT() { return d_MULT; }
  bool                 getCOM() { return d_COM; }
  bool                 getAND() { return d_AND; }
  bool                 getNAND() { return d_NAND; }
  bool                 getOR() { return d_OR; }
  bool                 getNOR() { return d_NOR; }
  bool                 getXOR() { return d_XOR; }
  bool                 getXNOR() { return d_XNOR; }
  bool                 getCNF() { return d_CNF; }
  bool                 getRNL() { return d_RNL; }
  bool                 getNUMOP() { return d_NUM_OP; }
  int                  getminLevel() { return d_minLevel; }
  int                  getmaxLevel() { return d_maxLevel; }
  int                  getminElement() { return d_minElement; }
  int                  getmaxElement() { return d_maxElement; }
  std::map<Gates, int> getm() { return d_m; }
  bool                 getLeaveEmptyOut() { return d_LeaveEmptyOut; }
  void                 setALL(bool i_ALL) { d_ALL = i_ALL; }
  void                 setSUM(bool i_SUM) { d_SUM = i_SUM; }
  void                 setSUB(bool i_SUB) { d_SUB = i_SUB; }
  void                 setNSUM(bool i_NSUM) { d_NSUM = i_NSUM; }
  void                 setNSUB(bool i_NSUB) { d_NSUB = i_NSUB; }
  void                 setMULT(bool i_MULT) { d_MULT = i_MULT; }
  void                 setCOM(bool i_COM) { d_COM = i_COM; }
  void                 setAND(bool i_AND) { d_AND = i_AND; }
  void                 setNAND(bool i_NAND) { d_NAND = i_NAND; }
  void                 setOR(bool i_OR) { d_OR = i_OR; }
  void                 setNOR(bool i_NOR) { d_NOR = i_NOR; }
  void                 setXOR(bool i_XOR) { d_XOR = i_XOR; }
  void                 setXNOR(bool i_XNOR) { d_XNOR = i_XNOR; }
  void                 setCNF(bool i_CNF) { d_CNF = i_CNF; }
  void                 setRNL(int i_RNL) { d_RNL = i_RNL; }
  void                 setNUMOP(int i_NUM_OP) { d_NUM_OP = i_NUM_OP; }
  void                 setminLevel(int i_minLevel) { d_minLevel = i_minLevel; }
  void                 setmaxLevel(int i_maxLevel) { d_maxLevel = i_maxLevel; }
  void setminElement(int i_minElement) { d_minElement = i_minElement; }
  void setmaxElement(int i_maxElement) { d_maxElement = i_maxElement; }
  void setm(std::map<Gates, int> i_m) { d_m = i_m; }
  void setLeaveEmptyOut(bool i_LeaveEmptyOut) {
    d_LeaveEmptyOut = i_LeaveEmptyOut;
  }

private:
  bool                 d_ALL    = false;
  bool                 d_SUM    = false;
  bool                 d_SUB    = false;
  bool                 d_NSUM   = false;
  bool                 d_NSUB   = false;
  bool                 d_MULT   = false;
  bool                 d_COM    = false;
  bool                 d_AND    = false;
  bool                 d_NAND   = false;
  bool                 d_OR     = false;
  bool                 d_NOR    = false;
  bool                 d_XOR    = false;
  bool                 d_XNOR   = false;
  bool                 d_CNF    = false;
  bool                 d_RNL    = false;
  bool                 d_NUM_OP = false;
  int                  d_minLevel;
  int                  d_maxLevel;
  int                  d_minElement;
  int                  d_maxElement;
  std::map<Gates, int> d_m;
  bool                 d_LeaveEmptyOut;
};

/// @todo: To add desc some fields
/// class GenerationParameters
/// @param d_name Generation name
/// @param d_requestId request ID
/// @param d_libraryName library name***
/// @param d_inputs number of inputs
/// @param d_outputs number of outputs
/// @param d_iteration ???
/// @param d_calculateStatsAbc A Boolean value indicating whether ABC statistics
/// should be calculated
/// @param d_makeOptimizedFiles A Boolean value indicating whether optimized
/// files should be created
/// @param d_makeFirrtl A Boolean value indicating whether FIRRTL files should
/// be created
/// @param d_makeBench A Boolean value indicating whether to create Bench files
/// @param d_gatesInputsInfo A mapping where the key is a string representing
/// information about the inputs, and the value is a vector of integers
/// representing information about the inputs for the gates***
///
///
/// */

/// @todo: To add desc some fields
/// class GenerationParameters
/// @param d_name Generation name
/// @param d_requestId request ID
/// @param d_libraryName library name***
/// @param d_inputs number of inputs
/// @param d_outputs number of outputs
/// @param d_iteration ???
/// @param d_calculateStatsAbc A Boolean value indicating whether ABC statistics
/// should be calculated
/// @param d_makeOptimizedFiles A Boolean value indicating whether optimized
/// files should be created
/// @param d_makeFirrtl A Boolean value indicating whether FIRRTL files should
/// be created
/// @param d_makeBench A Boolean value indicating whether to create Bench files
/// @param d_gatesInputsInfo A mapping where the key is a string representing
/// information about the inputs, and the value is a vector of integers
/// representing information about the inputs for the gates***
///
///
/// */

class GenerationParameters {
public:
  GenerationParameters(
      const std::string& i_name,
      const std::string& i_requestId,
      int                i_inputs,
      int                i_outputs,
      int                i_iteration,
      std::string        i_libraryName        = "",
      bool               i_calculateStatsAbc  = false,
      bool               i_makeOptimizedFiles = false,
      bool               i_makeFirrtl         = false,
      bool               i_makeBench          = false,
      bool               i_makeGraphML        = false
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
  zhegalkinFromTruthTableParameters getZhegalkin() const {
    return d_ZhegalkinFromTruthTableParameters;
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
  GeneratorSubtractorParameters getSubtractor() const {
    return d_generatorSubtractorParameters;
  }
  GeneratorALUParameters getALU() const { return d_generatorALUParameters; }
  GeneticParameters      getGenetic() const { return d_geneticParameters; }
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
  void setSubtractorParameters(
      bool i_overflowIn,
      bool i_overflowOut,
      bool i_sub
  ) {
    d_generatorSubtractorParameters.setOverFlowIn(i_overflowIn);
    d_generatorSubtractorParameters.setOverFlowOut(i_overflowOut);
    d_generatorSubtractorParameters.setSub(i_sub);
  }
  void setSummatorParameters(
      bool i_overflowIn,
      bool i_overflowOut,
      bool i_minus
  ) {
    d_generatorSummatorParameters.setOverFlowIn(i_overflowIn);
    d_generatorSummatorParameters.setOverFlowOut(i_overflowOut);
    d_generatorSummatorParameters.setMinus(i_minus);
  }
  void setComparisonParameters(
      bool i_compare0,
      bool i_compare1,
      bool i_compare2
  ) {
    d_generatorComparisonParameters.setCompare0(i_compare0);
    d_generatorComparisonParameters.setCompare1(i_compare1);
    d_generatorComparisonParameters.setCompare2(i_compare2);
  }
  void setALUParameters(
      bool                 i_ALL,
      bool                 i_SUM,
      bool                 i_SUB,
      bool                 i_NSUM,
      bool                 i_NSUB,
      bool                 i_MULT,
      bool                 i_COM,
      bool                 i_AND,
      bool                 i_NAND,
      bool                 i_OR,
      bool                 i_NOR,
      bool                 i_XOR,
      bool                 i_XNOR,
      bool                 i_CNF,
      bool                 i_RNL,
      bool                 i_NUM_OP,
      int                  i_minLevel,
      int                  i_maxLevel,
      int                  i_minElement,
      int                  i_maxElement,
      std::map<Gates, int> i_m,
      bool                 i_LeaveEmptyOut
  ) {
    d_generatorALUParameters.setALL(i_ALL);
    d_generatorALUParameters.setSUM(i_SUM);
    d_generatorALUParameters.setSUB(i_SUB);
    d_generatorALUParameters.setNSUM(i_NSUM);
    d_generatorALUParameters.setNSUB(i_NSUB);
    d_generatorALUParameters.setMULT(i_MULT);
    d_generatorALUParameters.setCOM(i_COM);
    d_generatorALUParameters.setAND(i_AND);
    d_generatorALUParameters.setNAND(i_NAND);
    d_generatorALUParameters.setOR(i_OR);
    d_generatorALUParameters.setNOR(i_NOR);
    d_generatorALUParameters.setXOR(i_XOR);
    d_generatorALUParameters.setXNOR(i_XNOR);
    d_generatorALUParameters.setCNF(i_CNF);
    d_generatorALUParameters.setRNL(i_RNL);
    d_generatorALUParameters.setNUMOP(i_NUM_OP);
    d_generatorALUParameters.setminLevel(i_minLevel);
    d_generatorALUParameters.setmaxLevel(i_maxLevel);
    d_generatorALUParameters.setminElement(i_minElement);
    d_generatorALUParameters.setmaxElement(i_maxElement);
    d_generatorALUParameters.setm(i_m);
    d_generatorALUParameters.setLeaveEmptyOut(i_LeaveEmptyOut);
  }

  void setZhegalkin(bool i_zhegalkin) {
    d_ZhegalkinFromTruthTableParameters.setZhegalkin(i_zhegalkin);
  }
  void setNumOfCycles(int i_numOfCycles) {
    d_geneticParameters.setNumOfCycles(i_numOfCycles);
  }
  void setPopulationSize(int i_populationSize) {
    d_geneticParameters.setPopulationSize(i_populationSize);
  }
  void setRecombinationParameters(
      ParentsTypes       i_parentsTypes,
      int                i_tournamentNumber,
      RecombinationTypes i_recombinationType,
      int                i_refPoints,
      double             maskProbability,
      int                i_recombinationNumber
  ) {
    RecombinationParameters RP;
    RP.setParentsParameters(i_parentsTypes, i_tournamentNumber);
    RP.setRefPoints(i_refPoints);
    RP.setRecombinationParameters(i_recombinationNumber);
    RP.setRecombinationType(i_recombinationType);
    RP.setMaskProbability(maskProbability);
    d_geneticParameters.setRecombinationParameters(RP);
  }
  void setMutationParameters(
      MutationTypes i_mutationType,
      double        i_probabilityGen,
      int           i_exchangeType,
      double        i_probabilityTruthTable
  ) {
    MutationParameters MP;
    MP.setMutationType(i_mutationType);
    MP.setProbabilityGen(i_probabilityGen);
    MP.setExchangeType(i_exchangeType);
    MP.setProbabilityTruthTable(i_probabilityTruthTable);
    d_geneticParameters.setMutationParameters(MP);
  }
  void setSelectionParameters(
      SelectionTypes i_selectionType,
      int            i_numOfSurvivors
  ) {
    SelectionParameters SP;
    SP.setSelectionType(i_selectionType);
    SP.setNumOfSurvivors(i_numOfSurvivors);
    d_geneticParameters.setSelectionParameters(SP);
  }
  void setKeyEndProcessIndex(double i_keyEndProcessIndex) {
    d_geneticParameters.setKeyEndProcessIndex(i_keyEndProcessIndex);
  }
  std::string getDataForLogging() const {
  	std::vector<std::string> result = {};
	result.push_back(std::string("name: ") + d_name);
	result.push_back(std::string("requestId: ") + d_requestId);
	result.push_back(std::string("libraryName: ") + d_libraryName);
	result.push_back(std::string("inputs: ") + std::to_string(d_inputs));
	result.push_back(std::string("outputs: ") + std::to_string(d_outputs));
	result.push_back(std::string("iteration: ") + std::to_string(d_iteration));
	result.push_back(std::string("calculateStatsAbc: ") + (d_calculateStatsAbc ? "true" : "false"));
	result.push_back(std::string("makeOptimizedFiles: ") + (d_makeOptimizedFiles ? "true" : "false"));
	result.push_back(std::string("makeFirrtl: ") + (d_makeFirrtl ? "true" : "false"));
	result.push_back(std::string("makeBench: ") + (d_makeBench ? "true" : "false") );
	result.push_back(std::string("makeGraphML: ") + (d_makeGraphML ? "true" : "false"));
	std::string concat = "";
	for(const auto& s: result)
		if (concat.empty())
			concat = s;
		else
			concat += "; " + s;
	return concat;
  }

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
  zhegalkinFromTruthTableParameters       d_ZhegalkinFromTruthTableParameters;
  GeneratorRandLevelParameters            d_generatorRandLevelParameters;
  GeneratorNumOperationParameters         d_generatorNumOperationParameters;
  GeneratorSummatorParameters             d_generatorSummatorParameters;
  GeneratorComparisonParameters           d_generatorComparisonParameters;
  GeneratorSubtractorParameters           d_generatorSubtractorParameters;
  GeneratorALUParameters                  d_generatorALUParameters;
  GeneticParameters d_geneticParameters = GeneticParameters(2, 3);
};
