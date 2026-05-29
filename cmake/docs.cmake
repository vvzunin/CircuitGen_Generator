# ---- Dependencies ----

set(extract_timestamps "")
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24")
  set(extract_timestamps DOWNLOAD_EXTRACT_TIMESTAMP YES)
endif()

include(FetchContent)
FetchContent_Declare(
    mcss URL
    https://github.com/friendlyanon/m.css/releases/download/release-1/mcss.zip
    URL_MD5 00cd2757ebafb9bcba7f5d399b3bec7f
    SOURCE_DIR "${PROJECT_BINARY_DIR}/mcss"
    UPDATE_DISCONNECTED YES
    ${extract_timestamps}
)
FetchContent_MakeAvailable(mcss)

include("${CMAKE_CURRENT_LIST_DIR}/mcss-doxygen-patch.cmake")
mcss_patch_doxygen_py("${mcss_SOURCE_DIR}/documentation/doxygen.py")
mcss_patch_search_py("${mcss_SOURCE_DIR}/documentation/_search.py")

find_package(Python3 3.6 REQUIRED)

# ---- Declare documentation target ----

set(
    DOXYGEN_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/docs"
    CACHE PATH "Path for the generated Doxygen documentation"
)
set(
    DOXYGEN_CLANG_ASSISTED_PARSING "YES"
    CACHE STRING "Enable Doxygen libclang-assisted parsing"
)
set(
    DOXYGEN_CLANG_OPTIONS "-std=c++17"
    CACHE STRING "Additional options passed to Doxygen clang parser"
)
set(
    DOXYGEN_CLANG_DATABASE_PATH ""
    CACHE PATH "Path to compile_commands.json directory for Doxygen clang parser"
)
# Clang-assisted parsing needs the same -I flags as the real build (FetchContent, generated headers).
if(DOXYGEN_CLANG_ASSISTED_PARSING STREQUAL "YES" AND DOXYGEN_CLANG_DATABASE_PATH STREQUAL "")
  if(EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json")
    set(DOXYGEN_CLANG_DATABASE_PATH "${CMAKE_BINARY_DIR}")
    message(STATUS "Doxygen clang: CLANG_DATABASE_PATH -> ${DOXYGEN_CLANG_DATABASE_PATH}")
  else()
    message(
      WARNING
      "Doxygen CLANG_ASSISTED_PARSING is ON but no compile_commands.json in ${CMAKE_BINARY_DIR}. "
      "Configure with CMAKE_EXPORT_COMPILE_COMMANDS=ON (dev preset) or set DOXYGEN_CLANG_DATABASE_PATH."
    )
  endif()
endif()
set(
    DOXYGEN_DOCUMENTATION_LANGUAGE "english"
    CACHE STRING "Documentation language: sets Doxygen OUTPUT_LANGUAGE and ENABLED_SECTIONS (english or russian)."
)
set_property(CACHE DOXYGEN_DOCUMENTATION_LANGUAGE PROPERTY STRINGS english russian)
if(DOXYGEN_DOCUMENTATION_LANGUAGE STREQUAL "russian")
  set(DOXYGEN_OUTPUT_LANGUAGE "Russian")
  set(DOXYGEN_ENABLED_SECTIONS "russian")
  set(DOXYGEN_DOCS_LANG_SUBDIR "ru")
  set(MCSS_NAV_CLASSES "Классы")
  set(MCSS_NAV_FILES "Файлы")
else()
  set(DOXYGEN_OUTPUT_LANGUAGE "English")
  set(DOXYGEN_ENABLED_SECTIONS "english")
  set(DOXYGEN_DOCS_LANG_SUBDIR "en")
  set(MCSS_NAV_CLASSES "Classes")
  set(MCSS_NAV_FILES "Files")
endif()
message(
  STATUS
  "Doxygen documentation: OUTPUT_LANGUAGE=${DOXYGEN_OUTPUT_LANGUAGE}, ENABLED_SECTIONS=${DOXYGEN_ENABLED_SECTIONS}, DOCS=${DOXYGEN_DOCS_LANG_SUBDIR}"
)
find_program(DOXYGEN_DOT_EXECUTABLE NAMES dot)
if(DOXYGEN_DOT_EXECUTABLE)
  set(DOXYGEN_HAVE_DOT "YES")
  get_filename_component(DOXYGEN_DOT_PATH "${DOXYGEN_DOT_EXECUTABLE}" DIRECTORY)
else()
  set(DOXYGEN_HAVE_DOT "NO")
  set(DOXYGEN_DOT_PATH "")
endif()

option(
  DOXYGEN_SKIP_DOT_GRAPHS
  "Skip Graphviz dot graphs in Doxygen (faster; no call/collaboration/class graphs)"
  OFF
)
if(DOXYGEN_SKIP_DOT_GRAPHS)
  set(DOXYGEN_HAVE_DOT_VALUE "NO")
  message(STATUS "DOXYGEN_SKIP_DOT_GRAPHS=ON: Graphviz graphs disabled for faster docs")
else()
  set(DOXYGEN_HAVE_DOT_VALUE "${DOXYGEN_HAVE_DOT}")
endif()

find_program(XELATEX_EXECUTABLE NAMES xelatex)
find_program(PDFLATEX_EXECUTABLE NAMES pdflatex)

option(
  DOXYGEN_SKIP_REFMAN_PDF
  "Skip Doxygen LaTeX PDF output (faster; HTML/XML only; copy is <project>.pdf in docs/pdf/)"
  OFF
)
set(DOXYGEN_LATEX_CMD_NAME "")
if(DOXYGEN_SKIP_REFMAN_PDF)
  set(DOXYGEN_GENERATE_LATEX_VALUE "NO")
  message(STATUS "DOXYGEN_SKIP_REFMAN_PDF=ON: LaTeX PDF disabled")
elseif(XELATEX_EXECUTABLE)
  set(DOXYGEN_GENERATE_LATEX_VALUE "YES")
  set(DOXYGEN_LATEX_CMD_NAME "xelatex")
  message(STATUS "Found xelatex: ${XELATEX_EXECUTABLE} (${PROJECT_NAME}.pdf)")
elseif(PDFLATEX_EXECUTABLE)
  set(DOXYGEN_GENERATE_LATEX_VALUE "YES")
  message(STATUS "Found pdflatex: ${PDFLATEX_EXECUTABLE} (${PROJECT_NAME}.pdf; install texlive-xetex if PDF fails on Unicode)")
else()
  set(DOXYGEN_GENERATE_LATEX_VALUE "NO")
  message(STATUS "No LaTeX engine found: skipping LaTeX PDF step")
endif()

# Extra clang flags: compile_commands.json is per-TU; some TUs (e.g. main.cpp) omit transitive
# private deps, so libclang cannot open headers that other TUs compile fine.
set(DOXYGEN_CLANG_OPTIONS_CONFIGURED "${DOXYGEN_CLANG_OPTIONS}")
if(DEFINED CircuitGenGraph_SOURCE_DIR AND DEFINED CircuitGenGraph_BINARY_DIR)
  string(APPEND DOXYGEN_CLANG_OPTIONS_CONFIGURED
    " -I\"${CMAKE_BINARY_DIR}/include\""
    " -isystem \"${CircuitGenGraph_SOURCE_DIR}/include\""
    " -isystem \"${CircuitGenGraph_BINARY_DIR}/include\""
  )
endif()
if(CMAKE_PROJECT_NAME STREQUAL "CircuitGenGenerator")
  string(APPEND DOXYGEN_CLANG_OPTIONS_CONFIGURED
    " -I\"${CMAKE_SOURCE_DIR}/include\""
    " -I\"${CMAKE_SOURCE_DIR}/lib\""
    " -I\"${CMAKE_SOURCE_DIR}/src\""
  )
endif()

set(working_dir "${PROJECT_BINARY_DIR}/docs")

foreach(file IN ITEMS Doxyfile conf.py)
  configure_file("docs/${file}.in" "${working_dir}/${file}" @ONLY)
endforeach()

set(mcss_script "${mcss_SOURCE_DIR}/documentation/doxygen.py")
set(config "${working_dir}/conf.py")

if((XELATEX_EXECUTABLE OR PDFLATEX_EXECUTABLE) AND NOT DOXYGEN_SKIP_REFMAN_PDF)
  add_custom_target(
      docs
      COMMAND "${CMAKE_COMMAND}" -E rm -rRf
      "${DOXYGEN_OUTPUT_DIRECTORY}/html"
      "${DOXYGEN_OUTPUT_DIRECTORY}/xml"
      "${DOXYGEN_OUTPUT_DIRECTORY}/latex"
      "${DOXYGEN_OUTPUT_DIRECTORY}/pdf"
      COMMAND "${CMAKE_COMMAND}" -E copy
      "${CMAKE_SOURCE_DIR}/docs/doxygen-cyrillic.sty"
      "${DOXYGEN_OUTPUT_DIRECTORY}/doxygen-cyrillic.sty"
      COMMAND "${CMAKE_COMMAND}" -E env "PYTHONUNBUFFERED=1" "${Python3_EXECUTABLE}" "${mcss_script}" "${config}"
      COMMAND "${CMAKE_COMMAND}" -E make_directory "${DOXYGEN_OUTPUT_DIRECTORY}/pdf"
      COMMAND "${CMAKE_COMMAND}" -E chdir "${DOXYGEN_OUTPUT_DIRECTORY}/latex" make
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
      "${DOXYGEN_OUTPUT_DIRECTORY}/latex/refman.pdf"
      "${DOXYGEN_OUTPUT_DIRECTORY}/pdf/${PROJECT_NAME}.pdf"
      COMMENT "Building documentation using Doxygen and m.css"
      WORKING_DIRECTORY "${working_dir}"
      VERBATIM
  )
else()
  add_custom_target(
      docs
      COMMAND "${CMAKE_COMMAND}" -E rm -rRf
      "${DOXYGEN_OUTPUT_DIRECTORY}/html"
      "${DOXYGEN_OUTPUT_DIRECTORY}/xml"
      "${DOXYGEN_OUTPUT_DIRECTORY}/latex"
      "${DOXYGEN_OUTPUT_DIRECTORY}/pdf"
      COMMAND "${CMAKE_COMMAND}" -E copy
      "${CMAKE_SOURCE_DIR}/docs/doxygen-cyrillic.sty"
      "${DOXYGEN_OUTPUT_DIRECTORY}/doxygen-cyrillic.sty"
      COMMAND "${CMAKE_COMMAND}" -E env "PYTHONUNBUFFERED=1" "${Python3_EXECUTABLE}" "${mcss_script}" "${config}"
      COMMAND "${CMAKE_COMMAND}" -E echo "Skipping LaTeX PDF (set DOXYGEN_SKIP_REFMAN_PDF=OFF and install texlive-xetex or pdflatex to enable)"
      COMMENT "Building documentation using Doxygen and m.css"
      WORKING_DIRECTORY "${working_dir}"
      VERBATIM
  )
endif()
