include(ExternalProject)
include(FetchContent)

# Get json
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

# Add all subdirectories for the project.
add_subdirectory(additional)
add_subdirectory(baseStructures)
add_subdirectory(circuits)
add_subdirectory(database)
add_subdirectory(generators)
add_subdirectory(optimisations)
add_subdirectory(parameters)
add_subdirectory(settings)

# Set all libraries, using in project.
set(
  PROJECT_LIBS
  # Internal libraries
  AuxiliaryMethods
  Circuit
  DataBaseGenerator
  FilesTools
  GraphVertex
  OptimisationUtils
  OrientedGraph
  Reliability
  Settings
  ThreadPool
  TruthTable
  # External libraries
  nlohmann_json::nlohmann_json
)

# Add source files
set(SOURCES
  additional/AuxiliaryMethods.cpp
  additional/filesTools/FilesTools.cpp
  additional/threadPool/ThreadPool.cpp
  api/generatorAPI.cpp
  baseStructures/graph/GraphVertexBase.cpp  
  baseStructures/graph/GraphVertexConstant.cpp
  baseStructures/graph/GraphVertexInput.cpp
  baseStructures/graph/GraphVertexOutput.cpp
  baseStructures/graph/OrientedGraph.cpp
  


  baseStructures/Parser.cpp
  baseStructures/truthTable/TruthTable.cpp
  circuits/Circuit.cpp
  database/DataBaseGenerator.cpp
  database/DataBaseGeneratorParameters.cpp
  generators/GenerationParameters.cpp
  generators/Genetic/Chromosome.cpp
  generators/Genetic/ChromosomeType.cpp
  # generators/Genetic/GeneticParameters.cpp
  # generators/Genetic/GenGenerator.cpp
  # generators/Genetic/Mutations/Mutation.cpp
  # generators/Genetic/Mutations/MutationParameters.cpp
  # generators/Genetic/Mutations/MutationTruthTable.cpp
  # generators/Genetic/Parents/Parents.cpp
  # generators/Genetic/Parents/ParentsParameters.cpp
  # generators/Genetic/Parents/ParentsTruthTable.cpp
  # generators/Genetic/Recombination/RecombinationParameters.cpp
  # generators/Genetic/Recombination/Recombinations.cpp
  # generators/Genetic/Recombination/RecombinationsTruthTable.cpp
  # generators/Genetic/Selections/SelectionParameters.cpp
  # generators/Genetic/Selections/Selections.cpp
  # generators/Genetic/Selections/SelectionsTruthTable.cpp
  generators/simple/SimpleGenerators.cpp
  optimisations/AbcUtils.cpp
  optimisations/YosysUtils.cpp
  parameters/reliability/Reliability.cpp
  settings/Settings.cpp

  main.cpp
)

# Check if pthreads is installed; adjust compiler/linker options
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Create executable
add_executable(${MAIN_TARGET} ${SOURCES})

# Add all internal libraries in the project
target_link_libraries(${MAIN_TARGET} ${PROJECT_LIBS} Threads::Threads)




# -----------------------------------------------------------------------------
# Link to shared library
function(gen_properties target visibility)
  target_include_directories(${target} ${visibility} ${PROJECT_SOURCE_DIR}/src)
  target_link_libraries(${target} ${visibility} ${PROJECT_LIBS})
endfunction()

add_library(${MAIN_LIBRARY} SHARED EXCLUDE_FROM_ALL ${SOURCES})
gen_properties(${MAIN_LIBRARY} PRIVATE)

set(public_headers
  api/generatorAPI.h
)

set_target_properties(${MAIN_LIBRARY} PROPERTIES PUBLIC_HEADER "${public_headers}")

set_property(TARGET ${MAIN_LIBRARY} PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET ${MAIN_LIBRARY} PROPERTY OUTPUT_NAME ${MAIN_LIBRARY})
