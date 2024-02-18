add_library(
  MutationParameters 
  SHARED 
  MutationParameters.cpp 
  MutationParameters.h
)

target_include_directories(
  MutationParameters 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src
)
