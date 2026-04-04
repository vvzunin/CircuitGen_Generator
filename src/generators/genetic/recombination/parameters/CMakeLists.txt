add_library(geneticRecombinationParameters STATIC RecombinationParameters.cpp)

target_include_directories(geneticRecombinationParameters PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(geneticRecombinationParameters PUBLIC
  geneticParentsParameters
)

add_folders(GeneticGenerators)