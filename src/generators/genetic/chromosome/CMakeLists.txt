add_subdirectory(type)

add_library(geneticChromosome INTERFACE)

target_include_directories(geneticChromosome INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(geneticChromosome INTERFACE
  geneticChromosomeType
)

add_folders(GeneticGenerators)