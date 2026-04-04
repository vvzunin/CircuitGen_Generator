add_library(aluGenerator STATIC ALUGenerator.cpp)

target_include_directories(aluGenerator PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(aluGenerator PUBLIC
  baseStructures
  simpleGenerators
  CircuitGenGraph::CircuitGenGraph
)

add_folders(SimpleGenerators)