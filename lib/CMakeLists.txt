if(CircuitGen_Generator_USE_EXTERNAL_JSON)
  #find_package(nlohmann_json 3.2.0 REQUIRED)
  include(FetchContent)
  FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.3
  )
  FetchContent_MakeAvailable(nlohmann_json)
else()
  set(JSON_BuildTests OFF CACHE INTERNAL "")
  add_subdirectory(nlohmann_json)
endif()