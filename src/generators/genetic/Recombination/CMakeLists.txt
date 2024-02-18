add_library(
  RecombinationParameters 
  SHARED 
  RecombinationParameters.cpp 
  RecombinationParameters.h)

target_include_directories(
  RecombinationParameters 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src)