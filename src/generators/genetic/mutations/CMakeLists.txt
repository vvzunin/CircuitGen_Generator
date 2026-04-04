add_subdirectory(parameters)
add_subdirectory(truthTable)

add_library(geneticMutation STATIC Mutation.cpp)

target_include_directories(geneticMutation PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(geneticMutation PUBLIC
  geneticMutationParameters
  geneticMutationTruthTable
  geneticChromosome
)

add_folders(GeneticGenerators)