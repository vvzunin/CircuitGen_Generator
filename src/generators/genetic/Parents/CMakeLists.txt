add_library(
  ParentsParameters 
  SHARED 
  ParentsParameters.cpp 
  ParentsParameters.h)

target_include_directories(
  ParentsParameters 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src)
