add_library(
  SimpleGenerator 
  SHARED 
  SimpleGenerators.cpp 
  SimpleGenerators.h
)

target_include_directories(
  SimpleGenerator 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(
  SimpleGenerator
  PUBLIC
  OrientedGraph
  TruthTable
)