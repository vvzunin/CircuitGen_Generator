# Начальные проверки при начала сборки

# Disallow in-source build to avoid polluting repository with CMake artifacts.
if(PROJECT_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(
    FATAL_ERROR
    "In-source builds are not allowed."
    "Please read docs/en/BUILDING.md or docs/ru/BUILDING.md before trying to build this project."
    "You may need to delete 'CMakeCache.txt' and 'CMakeFiles/' first."
    #[=[
    "Сборка в папке исходного кода недопустима."
    "Перед сборкой этого проекта ознакомьтесь с документацией по сборке."
    "Возможно, сначала потребуется удалить файлы CMakeCache.txt и CMakeFiles/"
    ]=]
  )
endif()
