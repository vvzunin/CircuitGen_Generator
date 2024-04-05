add_subdirectory(Parents)
add_subdirectory(Mutations)
add_subdirectory(Selections)
add_subdirectory(Recombination)

add_library(GeneticParameters SHARED GeneticParameters.cpp GeneticParameters.h)

target_include_directories(
  GeneticParameters
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(
  GeneticParameters
  PUBLIC
  MutationParameters
  ParentsParameters
  RecombinationParameters
)