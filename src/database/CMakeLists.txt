add_library(
  DataBaseGenerator 
  SHARED 
  DataBaseGenerator.cpp 
  DataBaseGenerator.h 
  DataBaseGeneratorParameters.cpp 
  DataBaseGeneratorParameters.h)

target_include_directories(
  DataBaseGenerator 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src)