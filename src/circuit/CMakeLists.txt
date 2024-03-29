add_library(
  Circuit 
  SHARED 
  Circuit.cpp 
  Circuit.h
  CircuitParameters.h)

target_include_directories(
  Circuit 
  PUBLIC 
  "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)

target_link_libraries(
  Circuit 
  PUBLIC 
  baseStructures
)