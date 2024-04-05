install(
    TARGETS CircuitGenGenerator_exe
    RUNTIME COMPONENT CircuitGenGenerator_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/CircuitGenGenerator-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package CircuitGenGenerator)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT CircuitGenGenerator_Development
)

install(
    TARGETS CircuitGenGenerator_lib
    EXPORT CircuitGenGeneratorTargets
    RUNTIME #
    COMPONENT CircuitGenGenerator_Runtime
    LIBRARY #
    COMPONENT CircuitGenGenerator_Runtime
    NAMELINK_COMPONENT CircuitGenGenerator_Development
    ARCHIVE #
    COMPONENT CircuitGenGenerator_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    CircuitGenGenerator_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE CircuitGenGenerator_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(CircuitGenGenerator_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${CircuitGenGenerator_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT CircuitGenGenerator_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${CircuitGenGenerator_INSTALL_CMAKEDIR}"
    COMPONENT CircuitGenGenerator_Development
)

install(
    EXPORT CircuitGenGeneratorTargets
    NAMESPACE CircuitGenGenerator::
    DESTINATION "${CircuitGenGenerator_INSTALL_CMAKEDIR}"
    COMPONENT CircuitGenGenerator_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
