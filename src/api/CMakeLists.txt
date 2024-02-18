add_library(
  GeneratorAPI SHARED
  generatorAPI.cpp
  generatorAPI.h
)

target_include_directories(
  GeneratorAPI
  PUBLIC
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(
  GeneratorAPI 
  PUBLIC 
  AuxiliaryMethods
  DataBaseGenerator
)
