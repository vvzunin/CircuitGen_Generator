add_library(arithmeticGenerator STATIC
  ArithmeticGenerator.cpp
  ArithmeticUtils.cpp
  IncrementDecrement.cpp
  NonRestoringDivision.cpp
  SimpleAdder.cpp
  SimpleMultiplier.cpp
  SimpleSubstractor.cpp
)

target_include_directories(arithmeticGenerator PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(arithmeticGenerator PUBLIC
  simpleGenerator
  CircuitGenGraph::CircuitGenGraph
)

add_folders(SimpleGenerators)