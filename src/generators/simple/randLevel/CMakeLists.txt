add_library(randLevelGenerator STATIC RandLevelGenerator.cpp)

target_include_directories(randLevelGenerator PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(randLevelGenerator PUBLIC
  simpleGenerator
  CircuitGenGraph::CircuitGenGraph
)

add_folders(SimpleGenerators)