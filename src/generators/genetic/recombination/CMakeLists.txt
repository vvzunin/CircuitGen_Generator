add_subdirectory(parameters)
add_subdirectory(truthTable)

add_library(geneticRecombination INTERFACE)

target_include_directories(geneticRecombination INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(geneticRecombination INTERFACE
  geneticRecombinationParameters
  geneticRecombinationsTruthTable
  geneticChromosome
)

add_folders(GeneticGenerators)