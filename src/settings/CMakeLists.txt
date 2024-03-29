add_library(
  Settings 
  SHARED
  Settings.cpp
  Settings.h
)

target_include_directories(
  Settings 
  PUBLIC
  "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)