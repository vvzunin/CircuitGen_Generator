add_library(parser STATIC Parser.cpp)

target_include_directories(parser PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(parser PUBLIC
  settings
  CircuitGenGraph::CircuitGenGraph
)

add_folders(BaseStructures)