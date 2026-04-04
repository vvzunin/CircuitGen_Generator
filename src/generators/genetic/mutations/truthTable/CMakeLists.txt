add_library(geneticMutationTruthTable STATIC MutationTruthTable.cpp)

target_include_directories(geneticMutationTruthTable PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(geneticMutationTruthTable PUBLIC
  additional
  baseStructures
  geneticChromosome
)

add_folders(GeneticGenerators)