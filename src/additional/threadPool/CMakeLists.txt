add_library(threadPool STATIC ThreadPool.cpp)

target_include_directories(threadPool PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

add_folders(Additional)