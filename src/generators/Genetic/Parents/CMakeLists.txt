add_library(ParentsParameters SHARED ParentsParameters.cpp ParentsParameters.h)

target_include_directories(
  ParentsParameters
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(
  ParentsParameters
  PUBLIC
  OrientedGraph
  TruthTable
)