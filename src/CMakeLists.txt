# Add all subdirectories for the project.
add_subdirectory(additional)
add_subdirectory(api)
add_subdirectory(baseStructures)
add_subdirectory(circuit)
add_subdirectory(database)
add_subdirectory(generators)
add_subdirectory(settings)


# Set all libraries, using in project.
set(
  PROJECT_LIBS
  # Internal libraries
  additional
  baseStructures
  Circuit
  DataBaseGenerator
  # External libraries
  nlohmann_json::nlohmann_json
  Threads::Threads
)

# Add source files
set(SOURCES
  src/api/generatorAPI.cpp
  src/circuit/Circuit.cpp
  src/generators/simple/SimpleGenerators.cpp
  src/settings/Settings.cpp  
)

# Check if pthreads is installed; adjust compiler/linker options
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

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