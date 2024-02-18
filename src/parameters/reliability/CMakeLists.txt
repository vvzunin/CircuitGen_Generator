set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/lib)

include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_library(
  Reliability 
  SHARED 
  Reliability.cpp 
  Reliability.h)

target_link_libraries(
  Reliability 
  nlohmann_json::nlohmann_json)
  
target_include_directories(
  Reliability 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/src)
