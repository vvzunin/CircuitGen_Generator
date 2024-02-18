add_library(
  OrientedGraph 
  SHARED 
  OrientedGraph.cpp 
  OrientedGraph.h
  
  GraphVertexConstant.cpp
  GraphVertexInput.cpp
  GraphVertexOutput.cpp  
  GraphVertex.h

  GraphVertexBase.cpp
  GraphVertexBase.h
)

target_include_directories(
  OrientedGraph 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src/baseStructures)