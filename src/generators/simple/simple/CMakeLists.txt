add_library(simpleGenerator STATIC SimpleGenerator.cpp)

target_include_directories(simpleGenerator PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(simpleGenerator PUBLIC
  additional
  generationParameters
  CircuitGenGraph::CircuitGenGraph
  settings
)

add_folders(SimpleGenerators)