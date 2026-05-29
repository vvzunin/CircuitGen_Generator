add_library(
  easylogging++ STATIC
  easylogging++.cc
  easylogging++.h
)

target_include_directories(easylogging++ PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/lib>
  $<INSTALL_INTERFACE:include/easylogging++>
)

add_folders(Libraries easylogging++)