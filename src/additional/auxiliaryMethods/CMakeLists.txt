add_library(auxiliaryMethods STATIC
  AuxiliaryMethods.cpp
)

target_include_directories(auxiliaryMethods PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(auxiliaryMethods PUBLIC
  CircuitGenGraph::CircuitGenGraph
  randomGeneratorWithSeed
)

add_folders(Additional)