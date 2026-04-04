add_library(dataBaseGeneratorParameters STATIC DataBaseGeneratorParameters.cpp)

target_include_directories(dataBaseGeneratorParameters PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(dataBaseGeneratorParameters PUBLIC
  CircuitGenGraph::CircuitGenGraph
  settings
  generationParameters
)

add_folders(DataBase)