add_subdirectory(chromosome)
add_subdirectory(mutations)
add_subdirectory(parameters)
add_subdirectory(parents)
add_subdirectory(recombination)
add_subdirectory(selections)

add_library(geneticGenerator INTERFACE)

target_include_directories(geneticGenerator INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(geneticGenerator
  INTERFACE
  additional
  baseStructures
  geneticChromosome
  geneticMutation
  geneticParameters
  geneticParents
  geneticRecombination
  geneticSelections
  circuit
  fromTruthTableGenerator
)

add_folders(GeneticGenerators)