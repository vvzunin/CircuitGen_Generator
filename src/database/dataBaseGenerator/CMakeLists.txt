add_library(dataBaseGenerator STATIC DataBaseGenerator.cpp)

target_include_directories(dataBaseGenerator PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(dataBaseGenerator PUBLIC
  CircuitGenGraph::CircuitGenGraph
  additional
  baseStructures
  dataBaseGeneratorParameters
  settings
  generators
  circuit
)

add_folders(DataBase)