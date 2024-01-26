add_library(
  Settings SHARED
  Settings.cpp
  Settings.h
)

target_include_directories(Settings PUBLIC
${CMAKE_SOURCE_DIR})