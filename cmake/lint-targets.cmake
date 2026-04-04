set(
    FORMAT_PATTERNS
    src/*.cpp
    src/*/*.cpp src/*/*.hpp
    include/*/*.hpp
    include/*/*.hpp.in
    test/*/*.cpp test/*/*.hpp
    CACHE STRING
    "; separated patterns relative to the project source dir to format"
)

# Keep exact formatter command without hardcoded suffixes.
# CI pins 18.x via scripts/setup/install-clang-format-ci.sh; override FORMAT_COMMAND if needed.
set(FORMAT_COMMAND clang-format CACHE STRING "Formatter to use")

add_custom_target(
    format-check
    COMMAND "${CMAKE_COMMAND}"
    -D "FORMAT_COMMAND=${FORMAT_COMMAND}"
    -D "PATTERNS=${FORMAT_PATTERNS}"
    -P "${PROJECT_SOURCE_DIR}/cmake/lint.cmake"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Linting the code"
    VERBATIM
)

add_custom_target(
    format-fix
    COMMAND "${CMAKE_COMMAND}"
    -D "FORMAT_COMMAND=${FORMAT_COMMAND}"
    -D "PATTERNS=${FORMAT_PATTERNS}"
    -D FIX=YES
    -P "${PROJECT_SOURCE_DIR}/cmake/lint.cmake"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Fixing the code"
    VERBATIM
)
