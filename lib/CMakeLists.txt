if(NOT TARGET easylogging++)
  add_subdirectory(easyloggingpp)
endif()

if(NOT TARGET nlohmann)
  add_subdirectory(nlohmann)
endif()

list(APPEND external_targets easyloggingpp)
list(APPEND external_targets nlohmann)