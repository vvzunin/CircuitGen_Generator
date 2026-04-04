add_library(geneticParentsParameters STATIC ParentsParameters.cpp)

target_include_directories(geneticParentsParameters PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

add_folders(GeneticGenerators)