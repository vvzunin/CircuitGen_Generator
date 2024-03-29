add_library(
  SimpleGenerator 
  SHARED 
  SimpleGenerators.cpp 
  SimpleGenerators.h
)

target_include_directories(
  SimpleGenerator 
  PUBLIC 
  "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)

target_link_libraries(
  SimpleGenerator
  PUBLIC
  baseStructures
)