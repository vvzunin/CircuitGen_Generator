add_library(geneticSelectionParameters STATIC SelectionParameters.cpp)

target_include_directories(geneticSelectionParameters PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

add_folders(GeneticGenerators)