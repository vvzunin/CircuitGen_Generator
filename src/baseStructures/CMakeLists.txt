# Add all subdirectories for the project.
add_subdirectory(graph)
add_subdirectory(truthTable)

add_library(
  Parser 
  SHARED
  Parser.cpp
  Parser.h
)

target_include_directories(
  Parser
  PUBLIC
  ${PROJECT_SOURCE_DIR}/src
)