cmake_minimum_required(VERSION 3.15)

find_package(nlohmann-json)

project(coursach)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(
  main.cpp
  Settings.cpp
  Generators/GenerationParameters.cpp
  Generators/Genetic/GeneticParameters.cpp
  Generators/Genetic/Mutations/MutationParameters.cpp
  DataBase/DataBaseGenerator.cpp
  Generators/TruthTable.cpp
  Generators/SimpleGenerators.cpp
  graph/GraphVertex.cpp
  graph/OrientedGraph.cpp
  Generators/Genetic/GenGenerator.cpp
  DataBase/DataBaseGenerator.cpp
  circuits/Circuit.cpp
  reliability/Reliability.cpp
)

