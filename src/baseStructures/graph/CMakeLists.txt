add_library(
  OrientedGraph 
  SHARED 

  enums.h

  GraphVertexBase.cpp
  GraphVertexBase.h

  GraphVertexConstant.cpp
  GraphVertexInput.cpp
  GraphVertexOutput.cpp
  GraphVertexGates.cpp
  GraphVertex.h

  OrientedGraph.cpp 
  OrientedGraph.h
)

target_include_directories(
  OrientedGraph 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src
)