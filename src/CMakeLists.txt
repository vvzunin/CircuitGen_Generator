add_subdirectory(additional)
add_subdirectory(baseStructures)
add_subdirectory(circuit)
add_subdirectory(CircuitGenGenerator)
add_subdirectory(database)
add_subdirectory(generators)
add_subdirectory(settings)
add_subdirectory(chiselModule)

# ---- Declare executable ----
add_executable(CircuitGenGenerator_exe main.cpp)
add_executable(CircuitGenGenerator::exe ALIAS CircuitGenGenerator_exe)
target_compile_definitions(CircuitGenGenerator_exe PRIVATE
  PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
)

if (CLANG_TIDY AND CircuitGenGenerator_ENABLE_CLANG_TIDY)
  set_target_properties(CircuitGenGenerator_exe PROPERTIES
    CXX_CLANG_TIDY "${GENERATOR_CLANG_TIDY}"
  )
endif()

set_target_properties(CircuitGenGenerator_exe PROPERTIES
  OUTPUT_NAME CircuitGenGenerator
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# target_compile_features(CircuitGenGenerator_exe PRIVATE cxx_std_17)

target_link_libraries(
  CircuitGenGenerator_exe
  PRIVATE
  CircuitGenGenerator::CircuitGenGenerator
  easylogging++
)

add_custom_target(
    run-exe
    COMMAND CircuitGenGenerator_exe
    VERBATIM
)
add_dependencies(run-exe CircuitGenGenerator_exe)

add_folders(Project)