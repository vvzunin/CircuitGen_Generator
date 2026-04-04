add_subdirectory(basisConverter)
add_subdirectory(genetic)
add_subdirectory(simple)

add_library(generationParameters STATIC GenerationParameters.cpp)

target_include_directories(generationParameters PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(generationParameters PUBLIC
  geneticParameters
  settings
  CircuitGenGraph::CircuitGenGraph
)

add_library(generators INTERFACE)
target_link_libraries(generators INTERFACE
  basisConverter
  generationParameters
  simpleGenerators
  geneticGenerator
  CircuitGenGraph::CircuitGenGraph
)

add_folders(Generators)