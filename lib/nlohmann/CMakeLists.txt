add_library(nlohmann INTERFACE)

target_include_directories(nlohmann INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:lib/nlohmann>
)

add_folders(Libraries nlohmann)