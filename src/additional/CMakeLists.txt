add_subdirectory(filesTools)
add_subdirectory(threadPool)

add_library(
  AuxiliaryMethods SHARED
  AuxiliaryMethods.cpp
  AuxiliaryMethods.h
  RandomGeneratorWithSeed.h
)

target_include_directories(
  AuxiliaryMethods
  PUBLIC
  .
)

target_link_libraries(
  AuxiliaryMethods 
  PUBLIC 
  Circuit
)
