add_library(settings STATIC Settings.cpp)

target_include_directories(settings PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(settings PUBLIC
  CircuitGenGraph::CircuitGenGraph
)

add_folders(Settings)