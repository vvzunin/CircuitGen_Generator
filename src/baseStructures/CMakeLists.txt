add_subdirectory(parser)
add_subdirectory(truthTable)

add_library(baseStructures INTERFACE)
target_link_libraries(baseStructures INTERFACE
  parser
  truthTable
)
# Только заголовочные файлы доступны внешним зависимостям
target_include_directories(baseStructures INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

add_folders(BaseStructures)