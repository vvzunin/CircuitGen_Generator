add_library(
  TruthTable 
  SHARED 
  TruthTable.cpp 
  TruthTable.h)

target_include_directories(
  TruthTable 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(
  TruthTable
  PUBLIC
  AuxiliaryMethods
)