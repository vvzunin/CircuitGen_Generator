# Set minimum version of cmake
cmake_minimum_required(VERSION 3.13)

# Define project name, version and description
project(CircuitGen_Generator
  VERSION 0.0.1
  DESCRIPTION "Program for circuits dataset generation"
  HOMEPAGE_URL https://github.com/vvzunin/CircuitGen_Generator
  LANGUAGES CXX
)

# Add path for .cmake files. Needed for "include" directive.
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Define folder for external libraries
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

# Define names of standalone binary and library.
set(MAIN_TARGET circuitgen)
set(MAIN_LIBRARY cgen)


# Configuration file.
configure_file(config.h.in config.h)

# Define folder for external libraries
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/lib)

option(GENERATOR_DEBUG "Extended debug printing" OFF)
option(BUILD_SHARED_PROJECT_LIBS "Build using shared libraries" ON)

# Auxiliary variable definitions
# Define variables for coverage
set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINK_FLAGS "-lgcov")

# Define main cmake project settings
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_INIT} -std=c++17 -fPIC")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")
set(CMAKE_BUILD_TYPE Debug)

# Add all subdirectories for the project.
add_subdirectory(lib)
add_subdirectory(src)
# add_subdirectory(test)

# Doxygen support
find_package(Doxygen)
if (DOXYGEN_FOUND)
  message("Doxygen is installed. Generating documentation...")
  execute_process(COMMAND doxygen doc/Doxyfile)
else ()
  message("Can't find doxygen; to generate docs from sources please install it.")
endif()

# Install a pkg-config file, so other tools can find this.
CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/pkg-config.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
)


# Prepare for cmake
set(CIRCUITGEN_GENERATOR_JSON_TARGET_NAME               ${PROJECT_NAME})
set(CIRCUITGEN_GENERATOR_JSON_CONFIG_INSTALL_DIR        "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}" CACHE INTERNAL "")
set(CIRCUITGEN_GENERATOR_JSON_INCLUDE_INSTALL_DIR       "${CMAKE_INSTALL_INCLUDEDIR}")
set(CIRCUITGEN_GENERATOR_JSON_TARGETS_EXPORT_NAME       "${PROJECT_NAME}Targets")
set(CIRCUITGEN_GENERATOR_JSON_CMAKE_CONFIG_TEMPLATE     "cmake/config.cmake.in")
set(CIRCUITGEN_GENERATOR_JSON_CMAKE_CONFIG_DIR          "${CMAKE_CURRENT_BINARY_DIR}")
set(CIRCUITGEN_GENERATOR_JSON_CMAKE_VERSION_CONFIG_FILE "${CIRCUITGEN_GENERATOR_JSON_CMAKE_CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(CIRCUITGEN_GENERATOR_JSON_CMAKE_PROJECT_CONFIG_FILE "${CIRCUITGEN_GENERATOR_JSON_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake")
set(CIRCUITGEN_GENERATOR_JSON_CMAKE_PROJECT_TARGETS_FILE "${CIRCUITGEN_GENERATOR_JSON_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Targets.cmake")
set(CIRCUITGEN_GENERATOR_JSON_PKGCONFIG_INSTALL_DIR     "${CMAKE_INSTALL_DATADIR}/pkgconfig")

include(CMakePackageConfigHelpers)
configure_file(
    "cmake/CircuitGen_Generator_jsonConfigVersion.cmake.in"
    ${CIRCUITGEN_GENERATOR_JSON_CMAKE_VERSION_CONFIG_FILE}
    @ONLY
)
configure_file(
    ${CIRCUITGEN_GENERATOR_JSON_CMAKE_CONFIG_TEMPLATE}
    ${CIRCUITGEN_GENERATOR_JSON_CMAKE_PROJECT_CONFIG_FILE}
    @ONLY
)

if(JSON_Install)
    install(
        DIRECTORY ${CIRCUITGEN_GENERATOR_JSON_INCLUDE_BUILD_DIR}
        DESTINATION ${CIRCUITGEN_GENERATOR_JSON_INCLUDE_INSTALL_DIR}
    )
    install(
        FILES ${CIRCUITGEN_GENERATOR_JSON_CMAKE_PROJECT_CONFIG_FILE} ${CIRCUITGEN_GENERATOR_JSON_CMAKE_VERSION_CONFIG_FILE}
        DESTINATION ${CIRCUITGEN_GENERATOR_JSON_CONFIG_INSTALL_DIR}
    )
    if (CIRCUITGEN_GENERATOR_ADD_NATVIS)
        install(
            FILES ${CIRCUITGEN_GENERATOR_NATVIS_FILE}
            DESTINATION .
    )
    endif()
    export(
        TARGETS ${CIRCUITGEN_GENERATOR_JSON_TARGET_NAME}
        NAMESPACE ${PROJECT_NAME}::
        FILE ${CIRCUITGEN_GENERATOR_JSON_CMAKE_PROJECT_TARGETS_FILE}
    )
    install(
        TARGETS ${CIRCUITGEN_GENERATOR_JSON_TARGET_NAME}
        EXPORT ${CIRCUITGEN_GENERATOR_JSON_TARGETS_EXPORT_NAME}
        INCLUDES DESTINATION ${CIRCUITGEN_GENERATOR_JSON_INCLUDE_INSTALL_DIR}
    )
    install(
        EXPORT ${CIRCUITGEN_GENERATOR_JSON_TARGETS_EXPORT_NAME}
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CIRCUITGEN_GENERATOR_JSON_CONFIG_INSTALL_DIR}
    )
    install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
        DESTINATION ${CIRCUITGEN_GENERATOR_JSON_PKGCONFIG_INSTALL_DIR}
    )
endif()