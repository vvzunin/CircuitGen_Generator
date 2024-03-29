add_library(
  GeneratorAPI SHARED
  generatorAPI.cpp
  generatorAPI.h
)

target_include_directories(
  GeneratorAPI
  PUBLIC
  "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)

target_link_libraries(
  GeneratorAPI 
  PUBLIC 
  additional
  DataBaseGenerator
  nlohmann_json::nlohmann_json
)
