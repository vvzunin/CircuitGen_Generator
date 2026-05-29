add_library(circuitParameters INTERFACE)

target_include_directories(circuitParameters INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

add_folders(Circuit)