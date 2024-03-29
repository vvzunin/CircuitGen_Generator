add_library(
  baseStructures 
  SHARED
  Parser.cpp
  Parser.h

  graph/OrientedGraph.cpp 
  graph/OrientedGraph.h
  graph/GraphVertexConstant.cpp
  graph/GraphVertexInput.cpp
  graph/GraphVertexOutput.cpp
  graph/GraphVertexGates.cpp
  graph/GraphVertex.h
  graph/enums.h
  graph/GraphVertexBase.cpp
  graph/GraphVertexBase.h

  truthTable/TruthTable.cpp 
  truthTable/TruthTable.h
)

target_include_directories(
  baseStructures
  PUBLIC
  "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)