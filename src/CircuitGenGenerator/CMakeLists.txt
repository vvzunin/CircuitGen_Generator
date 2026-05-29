include(${PROJECT_SOURCE_DIR}/cmake/utils.cmake)
include(GNUInstallDirs)

set(PUBLIC_HEADERS
  ${PROJECT_SOURCE_DIR}/include/CircuitGenGenerator/export.hpp
  ${PROJECT_SOURCE_DIR}/include/CircuitGenGenerator/CircuitGenGenerator.hpp
  ${PROJECT_SOURCE_DIR}/include/CircuitGenGenerator/ThreadPool.hpp
)


add_library(CircuitGenGenerator_lib CircuitGenGenerator.cpp)
add_library(CircuitGenGenerator::CircuitGenGenerator ALIAS CircuitGenGenerator_lib)

if (CLANG_TIDY AND CircuitGenGenerator_ENABLE_CLANG_TIDY)
  set_target_properties(CircuitGenGenerator_lib PROPERTIES
    CXX_CLANG_TIDY "${GENERATOR_CLANG_TIDY}"
  )
endif()

if(DEFINED CircuitGenGenerator_SHARED_LIBS)
  set(BUILD_SHARED_LIBS ${CircuitGenGenerator_SHARED_LIBS})
endif()

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(CircuitGenGenerator_lib PUBLIC CircuitGenGenerator_STATIC_DEFINE)
endif()

set(export_file_name "export_shared.hpp")

if(NOT BUILD_SHARED_LIBS)
  set(export_file_name "export_static.hpp")
endif()

include(GenerateExportHeader)
generate_export_header(
  CircuitGenGenerator_lib
  BASE_NAME CircuitGenGenerator
  # EXPORT_FILE_NAME ${PROJECT_SOURCE_DIR}/include/CircuitGenGenerator/${export_file_name}
  EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/CircuitGenGenerator/${export_file_name}
  CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

configure_file(
  "${PROJECT_SOURCE_DIR}/include/CircuitGenGenerator/info.hpp.in"
  "${PROJECT_BINARY_DIR}/include/CircuitGenGenerator/info.hpp"
)

set_target_properties(
  CircuitGenGenerator_lib PROPERTIES
  VERSION "${PROJECT_VERSION}"
  SOVERSION "${PROJECT_VERSION_MAJOR}"
  EXPORT_NAME CircuitGenGenerator
  OUTPUT_NAME CircuitGenGenerator
  PUBLIC_HEADER "${PUBLIC_HEADERS}"
)

list(APPEND PUBLIC_HEADERS
  "${CMAKE_CURRENT_BINARY_DIR}/include/CircuitGenGenerator/${export_file_name}"
)

target_link_libraries(
  CircuitGenGenerator_lib PRIVATE
  Threads::Threads
  CircuitGenGraph::CircuitGenGraph
  additional
  baseStructures
  circuit
  dataBase
  generators
  "-Wl,--whole-archive"
  arithmeticGenerator
  "-Wl,--no-whole-archive"
  settings
  chiselProject

  PUBLIC
  easylogging++
  nlohmann
)

target_include_directories(
  CircuitGenGenerator_lib ${warning_guard}
  PUBLIC
  "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
  CircuitGenGenerator_lib SYSTEM
  PUBLIC
  "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
)

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)
target_include_directories(CircuitGenGenerator_lib
  PUBLIC
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/lib>"
  "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
  PRIVATE
  "src"
)

target_include_directories(
  CircuitGenGenerator_lib ${warning_guard}
  PUBLIC
  "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)

# target_compile_features(CircuitGenGenerator_lib PUBLIC cxx_std_17)

install(TARGETS CircuitGenGenerator_lib easylogging++ nlohmann
  EXPORT ${PROJECT_NAME}Targets
  RUNTIME COMPONENT CircuitGenGenerator
  LIBRARY COMPONENT CircuitGenGenerator NAMELINK_COMPONENT CircuitGenGenerator-dev
  ARCHIVE COMPONENT CircuitGenGenerator-dev
  PUBLIC_HEADER COMPONENT CircuitGenGenerator-dev
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/CircuitGenGenerator")

# add_folders(Project)
add_folders(Project CircuitGenGenerator_lib)