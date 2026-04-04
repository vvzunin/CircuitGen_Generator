# Install main executable into runtime component.
install(
    TARGETS ${CMAKE_PROJECT_NAME}_exe
    RUNTIME COMPONENT ${CMAKE_PROJECT_NAME}_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  # Top-level install keeps versioned include dir to avoid header collisions
  # between simultaneously installed major/minor versions.
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/${CMAKE_PROJECT_VERSION}-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Prefer project-specific package template; fallback to generic one.
set(package "${PROJECT_NAME}")
set(config_template "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in")
if(NOT EXISTS "${config_template}")
  set(config_template "${PROJECT_SOURCE_DIR}/cmake/package-config.cmake.in")
endif()
set(config_output "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake")
set(config_version_output "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake")
set(export_file "${PROJECT_NAME}-shared-targets.cmake")
set(install_cmakedir_var "${PROJECT_NAME}_INSTALL_CMAKEDIR")
set(package_cmakedir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}")

if(NOT BUILD_SHARED_LIBS)
  # Keep file names explicit so consumers can see linkage variant in install tree.
  set(export_file "${PROJECT_NAME}-static-targets.cmake")
endif()

if(DEFINED ${install_cmakedir_var})
  set(package_cmakedir "${${install_cmakedir_var}}")
endif()

if(NOT EXISTS "${config_template}")
  message(FATAL_ERROR "Package config template not found: ${config_template}")
endif()

# Install both public and generated headers.
install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT ${CMAKE_PROJECT_NAME}_Development
)

# Generate package config files consumed by find_package().
configure_package_config_file(
  "${config_template}"
  "${config_output}"
  INSTALL_DESTINATION "${package_cmakedir}"
)

write_basic_package_version_file(
  "${config_version_output}"
  COMPATIBILITY SameMajorVersion
)

# Export targets for downstream projects.
install(
  EXPORT ${PROJECT_NAME}Targets
  FILE "${export_file}"
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION "${package_cmakedir}"
  COMPONENT ${CMAKE_PROJECT_NAME}_Development
)

install(
  FILES
    "${config_output}"
    "${config_version_output}"
  DESTINATION "${package_cmakedir}"
  COMPONENT ${CMAKE_PROJECT_NAME}_Development
)

if(PROJECT_IS_TOP_LEVEL)
  # Enable CPack only for standalone project packaging.
  include(CPack)
endif()
