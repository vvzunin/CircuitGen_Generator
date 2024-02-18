# Временная сборка
add_library(
  Chromosome 
  SHARED 
  Chromosome.cpp 
  Chromosome.h
)

target_include_directories(
  Chromosome 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src
)


add_library(
  ChromosomeType 
  SHARED 
  ChromosomeType.cpp 
  ChromosomeType.h
)

target_include_directories(
  ChromosomeType 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(
  ChromosomeType 
  PUBLIC 
  Settings
  TruthTable
)