add_library(geneticChromosomeType INTERFACE)

target_include_directories(geneticChromosomeType INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(geneticChromosomeType INTERFACE
  baseStructures
  settings
)

add_folders(GeneticGenerators)