add_library(truthTable STATIC TruthTable.cpp)

target_include_directories(truthTable PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(truthTable PUBLIC
  settings
  geneticParameters
  additional
)

add_folders(BaseStructures)