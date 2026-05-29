add_library(commomUtils STATIC
  GeneratorUtils.cpp
)

target_include_directories(commomUtils PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(commomUtils PUBLIC
  simpleGenerator
  CircuitGenGraph::CircuitGenGraph
)

add_folders(SimpleGenerators)