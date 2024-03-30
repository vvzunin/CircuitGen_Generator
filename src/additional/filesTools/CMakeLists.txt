add_library(
  FilesTools SHARED
  FilesTools.cpp
  FilesTools.h
)

target_include_directories(
  FilesTools
  PUBLIC
  "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)