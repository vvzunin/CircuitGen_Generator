add_library(
  AuxiliaryMethods SHARED
  AuxiliaryMethods.cpp
  AuxiliaryMethods.h
)

target_include_directories(AuxiliaryMethods PUBLIC
  ${CMAKE_SOURCE_DIR}
)