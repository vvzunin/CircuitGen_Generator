add_library(geneticMutationParameters STATIC MutationParameters.cpp)

target_include_directories(geneticMutationParameters PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

add_folders(GeneticGenerators)