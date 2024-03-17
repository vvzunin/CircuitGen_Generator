add_library(
  Circuit 
  SHARED 
  Circuit.cpp 
  Circuit.h
  CircuitsParameters.h)

target_include_directories(
  Circuit 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src
)