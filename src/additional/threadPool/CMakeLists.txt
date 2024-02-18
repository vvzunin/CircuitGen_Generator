add_library(
  ThreadPool SHARED
  ThreadPool.cpp
  ThreadPool.h
  UnboundedMPMCQueue.h
)

target_include_directories(
  FilesTools
  PUBLIC
  .
)

set_target_properties(ThreadPool PROPERTIES PUBLIC_HEADER additional/thread_pool/*.h)