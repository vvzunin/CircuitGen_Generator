add_subdirectory(auxiliaryMethods)
add_subdirectory(filesTools)
add_subdirectory(threadPool)

# Интерфейсная библиотека для генератора случайных чисел
add_library(randomGeneratorWithSeed INTERFACE)

target_include_directories(randomGeneratorWithSeed INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

# Основная интерфейсная библиотека additional
add_library(additional INTERFACE)

target_link_libraries(additional INTERFACE
  randomGeneratorWithSeed
  threadPool
  filesTools
  auxiliaryMethods
)

# Экспортируем включения из additional, если нужно, чтобы клиенты видели .h файлы
target_include_directories(additional INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

add_folders(Additional)