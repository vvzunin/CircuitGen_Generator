add_library(
  OptimisationUtils 
  STATIC 
  AbcUtils.cpp 
  AbcUtils.h 
  YosysUtils.cpp 
  YosysUtils.h 
  StandartUtil.h)

target_include_directories(
  OptimisationUtils 
  PUBLIC 
)

set_target_properties(
  OptimisationUtils 
  PROPERTIES 
    PUBLIC_HEADER 
    optimisations/*.h
)
