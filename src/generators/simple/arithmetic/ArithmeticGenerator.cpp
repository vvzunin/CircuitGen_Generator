#include "generators/simple/arithmetic/ArithmeticGenerator.hpp"

namespace CG_Gen {

ArithmeticGenerator::ArithmeticGenerator() : SimpleGenerator() {
}

ArithmeticGenerator::ArithmeticGenerator(uint_fast32_t i_seed) :
    SimpleGenerator(i_seed) {
}

ArithmeticGenerator::ArithmeticGenerator(const GenerationParameters &i_param) :
    SimpleGenerator(i_param) {
}

GraphPtr ArithmeticGenerator::generateAdvancedArithmetic(
    const GenerationParameters &i_param) const {
  switch (i_param.getArithmetic().getType()) {
    case ArithemticOperations::DIV:
      return generateNonRestoringDiv(i_param);
    case ArithemticOperations::INC:
      return generateIncrement(i_param);
    case ArithemticOperations::DEC:
      return generateDecrement(i_param);
    case ArithemticOperations::MUL:
    case ArithemticOperations::ADD:
    case ArithemticOperations::SUB:
    case ArithemticOperations::NEG:
    case ArithemticOperations::UNDEFINED:
      std::cerr << "Unsupported operation type found. "
                   "Generationg default division\n";
      return generateNonRestoringDiv(i_param);
  }
  return generateNonRestoringDiv(i_param);
}

GraphPtr ArithmeticGenerator::generateAdvancedArithmetic() const {
  return generateAdvancedArithmetic(getParameters());
}

} // namespace CG_Gen
