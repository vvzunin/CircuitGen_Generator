add_subdirectory(parameters)

add_library(geneticParents INTERFACE)

target_include_directories(geneticParents INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(geneticParents INTERFACE
  geneticParentsParameters
  additional
  baseStructures
  geneticChromosome
)

add_folders(GeneticGenerators)