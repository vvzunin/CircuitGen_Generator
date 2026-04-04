add_library(geneticRecombinationsTruthTable STATIC RecombinationsTruthTable.cpp)

target_include_directories(geneticRecombinationsTruthTable PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(geneticRecombinationsTruthTable PUBLIC
  additional
  baseStructures
  geneticMutation
  geneticChromosome
  geneticParents
  geneticParameters
)

add_folders(GeneticGenerators)