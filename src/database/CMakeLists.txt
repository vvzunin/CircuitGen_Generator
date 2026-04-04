add_subdirectory(dataBaseGenerator)
add_subdirectory(dataBaseGeneratorParameters)

add_library(dataBase INTERFACE)
target_link_libraries(dataBase INTERFACE
  dataBaseGenerator
  dataBaseGeneratorParameters
)

add_folders(DataBase)