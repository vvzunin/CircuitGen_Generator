add_library(
  additional SHARED
  AuxiliaryMethods.cpp

  filesTools/FilesTools.cpp

  threadPool/ThreadPool.cpp
)

target_include_directories(
  additional
  PUBLIC
  "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)