add_library(basisConverter STATIC BasisConverter.cpp)

target_include_directories(basisConverter PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(basisConverter PUBLIC
  CircuitGenGraph::CircuitGenGraph
  generationParameters
)

add_folders(Generators)