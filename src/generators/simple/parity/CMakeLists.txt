add_library(parityGenerator STATIC ParityGenerator.cpp)

target_include_directories(parityGenerator PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(parityGenerator PUBLIC
  simpleGenerator
  CircuitGenGraph::CircuitGenGraph
)

add_folders(SimpleGenerators)