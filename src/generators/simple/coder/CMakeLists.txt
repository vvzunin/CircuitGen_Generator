add_library(coderGenerator STATIC CoderGenerator.cpp)

target_include_directories(coderGenerator PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(coderGenerator PUBLIC
  simpleGenerator
  CircuitGenGraph::CircuitGenGraph
)

add_folders(SimpleGenerators)