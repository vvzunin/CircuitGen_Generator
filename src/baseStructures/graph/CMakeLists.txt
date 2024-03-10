add_library(
  OrientedGraph 
  SHARED 

  OrientedGraph.cpp 
  OrientedGraph.h

  GraphVertexConstant.cpp
  GraphVertexInput.cpp
  GraphVertexOutput.cpp
  GraphVertexGates.cpp
  GraphVertex.h

  enums.h

  GraphVertexBase.cpp
  GraphVertexBase.h  
)

target_include_directories(
  OrientedGraph 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src
)