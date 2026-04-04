add_subdirectory(parameters)

add_library(circuit STATIC Circuit.cpp)

target_include_directories(circuit PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(circuit PUBLIC
  additional
  baseStructures
  CircuitGenGraph::CircuitGenGraph
  circuitParameters
  settings
)

add_folders(Circuit)