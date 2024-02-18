add_library(
  SelectionParameters 
  SHARED 
  SelectionParameters.cpp 
  SelectionParameters.h)

target_include_directories(
  SelectionParameters 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src)
