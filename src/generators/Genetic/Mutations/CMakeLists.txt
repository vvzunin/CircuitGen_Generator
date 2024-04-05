set (SOURCES
  MutationParameters.cpp
  Mutation.cpp
  MutationTruthTable.cpp
  MutationParameters.h
  Mutation.h
  MutationTruthTable.h
)

add_library(MutationParameters SHARED ${SOURCES})

target_include_directories(
  MutationParameters
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(
  MutationParameters
  PUBLIC
  OrientedGraph
  TruthTable
)