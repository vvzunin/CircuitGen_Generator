add_library(nlohmann INTERFACE)

# json.hpp lives at lib/nlohmann/json.hpp; consumers use <nlohmann/json.hpp>, so the
# interface include directory must be the parent of the "nlohmann" folder (lib/).
target_include_directories(nlohmann INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_LIBDIR}>
)

add_folders(Libraries nlohmann)