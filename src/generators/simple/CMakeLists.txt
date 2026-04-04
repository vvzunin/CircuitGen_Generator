add_subdirectory(alu)
add_subdirectory(arithmetic)
add_subdirectory(cascade)
add_subdirectory(coder)
add_subdirectory(comparison)
add_subdirectory(dot)
add_subdirectory(fromTruthTable)
add_subdirectory(numOperations)
add_subdirectory(parity)
add_subdirectory(plexer)
add_subdirectory(randLevel)
add_subdirectory(simple)
add_subdirectory(stateMachine)

add_library(simpleGenerators INTERFACE)

target_link_libraries(simpleGenerators INTERFACE
  aluGenerator
  arithmeticGenerator
  cascadeGenerator
  coderGenerator
  comparisonGenerator
  dotGenerator
  fromTruthTableGenerator
  numOperationsGenerator
  parityGenerator
  plexerGenerator
  randLevelGenerator
  stateMachineGenerator
  simpleGenerator
)

add_folders(SimpleGenerators)