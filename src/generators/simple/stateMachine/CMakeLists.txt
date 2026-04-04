add_library(stateMachineGenerator STATIC MealyMooreGenerator.cpp)

target_include_directories(stateMachineGenerator PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(stateMachineGenerator PUBLIC
  simpleGenerator
  CircuitGenGraph::CircuitGenGraph
)

add_folders(SimpleGenerators)