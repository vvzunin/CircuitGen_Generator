cmake_minimum_required(VERSION 3.1)

project(MyProjectName)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Add source files
set(SOURCES
  Settings.cpp
  AuxiliaryMethods.cpp
  FilesTools.cpp
  Generators/Genetic/Parents/ParentsParameters.cpp
  Generators/Genetic/Recombination/RecombinationParameters.cpp
  Generators/Genetic/Mutations/MutationParameters.cpp
  Generators/Genetic/Selections/SelectionParameters.cpp
  Generators/Genetic/GeneticParameters.cpp
  graph/GraphVertex.cpp
  graph/OrientedGraph.cpp
  reliability/Reliability.cpp
  Generators/TruthTable.cpp
  Generators/Genetic/ChronosomeTypes.cpp
  circuits/Circuit.cpp
  Generators/Parser.cpp
  Generators/SimpleGenerators.cpp
  Generators/Genetic/GenGenerator.cpp
  DataBase/DataBaseGenerator.cpp
  DataBase/DataBaseGeneratorParameters.cpp
  main.cpp
)

# Add include directories
include_directories(
  /opt/homebrew/Cellar/nlohmann-json/3.11.2/include
)

# Create executable
add_executable(prog ${SOURCES})
