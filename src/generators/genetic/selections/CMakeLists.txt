add_subdirectory(parameters)

add_library(geneticSelections INTERFACE)

target_include_directories(geneticSelections INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(geneticSelections INTERFACE
  additional
  geneticSelectionParameters
  geneticChromosome
)

add_folders(GeneticGenerators)