add_library(numOperationsGenerator STATIC NumOperationsGenerator.cpp)

target_include_directories(numOperationsGenerator PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(numOperationsGenerator PUBLIC
  simpleGenerator
  CircuitGenGraph::CircuitGenGraph
)

add_folders(SimpleGenerators)