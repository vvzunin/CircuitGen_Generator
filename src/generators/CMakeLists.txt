add_subdirectory(genetic)
add_subdirectory(simple)

add_library(
  GenerationParameters 
  SHARED 
  GenerationParameters.cpp 
  GenerationParameters.h
)

target_include_directories(
  GenerationParameters 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src
)