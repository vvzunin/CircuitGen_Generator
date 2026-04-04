add_library(filesTools STATIC FilesTools.cpp)

target_include_directories(filesTools PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

add_folders(Additional)