add_library(fromTruthTableGenerator STATIC FromTruthTableGenerator.cpp)

target_include_directories(fromTruthTableGenerator PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(fromTruthTableGenerator PUBLIC
  baseStructures
  simpleGenerator
  CircuitGenGraph::CircuitGenGraph
)

add_folders(SimpleGenerators)