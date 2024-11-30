#pragma once
#include <generators/simple/SimpleGenerator.hpp>
#include <baseStructures/truthTable/TruthTable.hpp>

class ALUGenerator : public SimpleGenerator {
public:
  ALUGenerator();
  ALUGenerator(uint_fast32_t i_seed);
  ALUGenerator(const GenerationParameters& i_param);

  GraphPtr generatorALU(
      int32_t                  i_bits,
      int32_t                  i_outbits,
      bool                     ALL,
      bool                     SUM,
      bool                     SUB,
      bool                     NSUM,
      bool                     NSUB,
      bool                     MULT,
      bool                     COM,
      bool                     AND,
      bool                     NAND,
      bool                     OR,
      bool                     NOR,
      bool                     XOR,
      bool                     XNOR,
      bool                     CNF,
      bool                     RNL,
      bool                     NUM_OP,
      uint32_t                 minLevel,
      uint32_t                 maxLevel,
      uint32_t                 minElement,
      uint32_t                 maxElement,
      std::map<Gates, int32_t> m,
      bool                     LeaveEmptyOut
  );

private:
  GenerationParameters&                 getParameters() const;
  std::shared_ptr<GenerationParameters> parameters;

private:
  GraphPtr generatorSummator(
      uint32_t i_bits,
      bool     i_overflowIn,
      bool     i_overflowOut,
      bool     i_minus
  );
  GraphPtr generatorSubtractor(
      uint32_t i_bits,
      bool     i_overflowIn,
      bool     i_overflowOut,
      bool     i_sub
  );
  GraphPtr generatorMultiplier(uint32_t i_bits);
  GraphPtr generatorComparison(
      uint32_t i_bits,
      bool     compare0,
      bool     compare1,
      bool     compare2
  );
  GraphPtr generatorMultiplexer(uint32_t i_bits);
  GraphPtr cnfFromTruthTable(const TruthTable& i_table, bool i_tp = true);
  GraphPtr zhegalkinFromTruthTable(const TruthTable& i_table);
  GraphPtr generatorRandLevel(
      uint32_t i_minLevel,
      uint32_t i_maxLevel,
      uint32_t i_minElements,
      uint32_t i_maxElements,
      uint32_t i_inputs,
      uint32_t i_outputs
  );
  GraphPtr generatorNumOperation(
      uint32_t                 i_input,
      uint32_t                 i_output,
      std::map<Gates, int32_t> i_logicOper,
      bool                     i_leaveEmptyOut = true
  );
};