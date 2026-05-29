add_library(geneticParameters STATIC GeneticParameters.cpp)

target_include_directories(geneticParameters PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(geneticParameters PUBLIC
  geneticMutationParameters
  geneticRecombinationParameters
  geneticSelectionParameters
)

add_folders(GeneticGenerators)