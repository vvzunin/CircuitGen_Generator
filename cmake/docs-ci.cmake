cmake_minimum_required(VERSION 3.14)

foreach(var IN ITEMS PROJECT_BINARY_DIR PROJECT_SOURCE_DIR)
  if(NOT DEFINED "${var}")
    message(FATAL_ERROR "${var} must be defined")
  endif()
endforeach()

set(bin "${PROJECT_BINARY_DIR}")
set(src "${PROJECT_SOURCE_DIR}")

# ---- Dependencies ----

set(mcss_SOURCE_DIR "${bin}/docs/.ci")
if(NOT IS_DIRECTORY "${mcss_SOURCE_DIR}")
  file(MAKE_DIRECTORY "${mcss_SOURCE_DIR}")
  file(
    DOWNLOAD
    https://github.com/friendlyanon/m.css/releases/download/release-1/mcss.zip
    "${mcss_SOURCE_DIR}/mcss.zip"
    STATUS status
    EXPECTED_MD5 00cd2757ebafb9bcba7f5d399b3bec7f
  )
  if(NOT status MATCHES "^0;")
    message(FATAL_ERROR "Download failed with ${status}")
  endif()
  execute_process(
    COMMAND "${CMAKE_COMMAND}" -E tar xf mcss.zip
    WORKING_DIRECTORY "${mcss_SOURCE_DIR}"
    RESULT_VARIABLE result
  )
  if(NOT result EQUAL "0")
    message(FATAL_ERROR "Extraction failed with ${result}")
  endif()
  file(REMOVE "${mcss_SOURCE_DIR}/mcss.zip")
endif()

include("${src}/cmake/mcss-doxygen-patch.cmake")
mcss_patch_doxygen_py("${mcss_SOURCE_DIR}/documentation/doxygen.py")
mcss_patch_search_py("${mcss_SOURCE_DIR}/documentation/_search.py")

find_program(Python3_EXECUTABLE NAMES python3 python)
if(NOT Python3_EXECUTABLE)
  message(FATAL_ERROR "Python executable was not found")
endif()

# ---- Process project() call in CMakeLists.txt ----

file(READ "${src}/CMakeLists.txt" content)

string(FIND "${content}" "project(" index)
if(index EQUAL "-1")
  message(FATAL_ERROR "Could not find \"project(\"")
endif()
string(SUBSTRING "${content}" "${index}" -1 content)

string(FIND "${content}" "\n)\n" index)
if(index EQUAL "-1")
  message(FATAL_ERROR "Could not find \"\\n)\\n\"")
endif()
string(SUBSTRING "${content}" 0 "${index}" content)

file(WRITE "${bin}/docs-ci.project.cmake" "docs_${content}\n)\n")

macro(list_pop_front list out)
  list(GET "${list}" 0 "${out}")
  list(REMOVE_AT "${list}" 0)
endmacro()

function(docs_project name)
  cmake_parse_arguments(PARSE_ARGV 1 "" "" "VERSION;DESCRIPTION;HOMEPAGE_URL" LANGUAGES)
  set(PROJECT_NAME "${name}" PARENT_SCOPE)
  if(DEFINED _VERSION)
    set(PROJECT_VERSION "${_VERSION}" PARENT_SCOPE)
    string(REGEX MATCH "^[0-9]+(\\.[0-9]+)*" versions "${_VERSION}")
    string(REPLACE . ";" versions "${versions}")
    set(suffixes MAJOR MINOR PATCH TWEAK)
    while(NOT versions STREQUAL "" AND NOT suffixes STREQUAL "")
      list_pop_front(versions version)
      list_pop_front(suffixes suffix)
      set("PROJECT_VERSION_${suffix}" "${version}" PARENT_SCOPE)
    endwhile()
  endif()
  if(DEFINED _DESCRIPTION)
    set(PROJECT_DESCRIPTION "${_DESCRIPTION}" PARENT_SCOPE)
  endif()
  if(DEFINED _HOMEPAGE_URL)
    set(PROJECT_HOMEPAGE_URL "${_HOMEPAGE_URL}" PARENT_SCOPE)
  endif()
endfunction()

include("${bin}/docs-ci.project.cmake")

# ---- Generate docs ----

if(NOT DEFINED DOXYGEN_OUTPUT_DIRECTORY)
  set(DOXYGEN_OUTPUT_DIRECTORY "${bin}/docs")
endif()
if(NOT DEFINED DOXYGEN_CLANG_ASSISTED_PARSING)
  set(DOXYGEN_CLANG_ASSISTED_PARSING "YES")
endif()
if(NOT DEFINED DOXYGEN_CLANG_OPTIONS)
  set(DOXYGEN_CLANG_OPTIONS "-std=c++17")
endif()
if(NOT DEFINED DOXYGEN_CLANG_DATABASE_PATH)
  set(DOXYGEN_CLANG_DATABASE_PATH "")
endif()
if(DOXYGEN_CLANG_ASSISTED_PARSING STREQUAL "YES" AND DOXYGEN_CLANG_DATABASE_PATH STREQUAL "")
  if(EXISTS "${bin}/compile_commands.json")
    set(DOXYGEN_CLANG_DATABASE_PATH "${bin}")
  elseif(EXISTS "${bin}/dev/compile_commands.json")
    set(DOXYGEN_CLANG_DATABASE_PATH "${bin}/dev")
  endif()
endif()
if(NOT DEFINED DOXYGEN_ENABLED_SECTIONS)
  set(DOXYGEN_ENABLED_SECTIONS "english")
endif()
# OUTPUT_LANGUAGE must match the documentation locale (Doxygen UI: chapter titles, index labels, etc.).
if(NOT DEFINED DOXYGEN_OUTPUT_LANGUAGE)
  if(DOXYGEN_ENABLED_SECTIONS STREQUAL "russian")
    set(DOXYGEN_OUTPUT_LANGUAGE "Russian")
  else()
    set(DOXYGEN_OUTPUT_LANGUAGE "English")
  endif()
endif()
if(DOXYGEN_OUTPUT_LANGUAGE STREQUAL "Russian")
  set(DOXYGEN_DOCS_LANG_SUBDIR "ru")
  set(MCSS_NAV_CLASSES "Классы")
  set(MCSS_NAV_FILES "Файлы")
else()
  set(DOXYGEN_DOCS_LANG_SUBDIR "en")
  set(MCSS_NAV_CLASSES "Classes")
  set(MCSS_NAV_FILES "Files")
endif()
find_program(DOXYGEN_DOT_EXECUTABLE NAMES dot)
if(DOXYGEN_DOT_EXECUTABLE)
  set(DOXYGEN_HAVE_DOT "YES")
  get_filename_component(DOXYGEN_DOT_PATH "${DOXYGEN_DOT_EXECUTABLE}" DIRECTORY)
else()
  set(DOXYGEN_HAVE_DOT "NO")
  set(DOXYGEN_DOT_PATH "")
endif()
if(NOT DEFINED DOXYGEN_SKIP_DOT_GRAPHS)
  set(DOXYGEN_SKIP_DOT_GRAPHS OFF)
endif()
if(DOXYGEN_SKIP_DOT_GRAPHS)
  set(DOXYGEN_HAVE_DOT_VALUE "NO")
else()
  set(DOXYGEN_HAVE_DOT_VALUE "${DOXYGEN_HAVE_DOT}")
endif()
find_program(XELATEX_EXECUTABLE NAMES xelatex)
find_program(PDFLATEX_EXECUTABLE NAMES pdflatex)
if(NOT DEFINED DOXYGEN_SKIP_REFMAN_PDF)
  set(DOXYGEN_SKIP_REFMAN_PDF OFF)
endif()
set(DOXYGEN_LATEX_CMD_NAME "")
if(DOXYGEN_SKIP_REFMAN_PDF)
  set(DOXYGEN_GENERATE_LATEX_VALUE "NO")
elseif(XELATEX_EXECUTABLE)
  set(DOXYGEN_GENERATE_LATEX_VALUE "YES")
  set(DOXYGEN_LATEX_CMD_NAME "xelatex")
elseif(PDFLATEX_EXECUTABLE)
  set(DOXYGEN_GENERATE_LATEX_VALUE "YES")
else()
  set(DOXYGEN_GENERATE_LATEX_VALUE "NO")
endif()

set(_doxy_cc_root "${DOXYGEN_CLANG_DATABASE_PATH}")
if(_doxy_cc_root STREQUAL "")
  set(_doxy_cc_root "${bin}")
  if(EXISTS "${bin}/dev/compile_commands.json")
    set(_doxy_cc_root "${bin}/dev")
  endif()
endif()
set(DOXYGEN_CLANG_OPTIONS_CONFIGURED "${DOXYGEN_CLANG_OPTIONS}")
if(EXISTS "${_doxy_cc_root}/_deps/circuitgengraph-src/include")
  string(APPEND DOXYGEN_CLANG_OPTIONS_CONFIGURED
    " -I\"${_doxy_cc_root}/include\""
    " -isystem \"${_doxy_cc_root}/_deps/circuitgengraph-src/include\""
    " -isystem \"${_doxy_cc_root}/_deps/circuitgengraph-build/include\""
    " -I\"${src}/include\" -I\"${src}/lib\" -I\"${src}/src\""
  )
elseif(EXISTS "${src}/include/CircuitGenGraph/GraphUtils.hpp")
  string(APPEND DOXYGEN_CLANG_OPTIONS_CONFIGURED
    " -I\"${_doxy_cc_root}/include\""
    " -isystem \"${src}/include\""
  )
endif()

# Doxygen's libclang does not pick up GCC's resource include dirs; without them, parsing system
# headers fails (e.g. stddef.h not found) on Fedora CI.
if(UNIX AND NOT APPLE)
  find_program(_DOXY_GCC_FOR_INCLUDES NAMES gcc)
  if(_DOXY_GCC_FOR_INCLUDES)
    execute_process(
      COMMAND "${_DOXY_GCC_FOR_INCLUDES}" -print-file-name=include
      OUTPUT_VARIABLE _doxy_gcc_builtin_include
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(IS_DIRECTORY "${_doxy_gcc_builtin_include}")
      string(APPEND DOXYGEN_CLANG_OPTIONS_CONFIGURED " -isystem \"${_doxy_gcc_builtin_include}\"")
    endif()
    execute_process(
      COMMAND "${_DOXY_GCC_FOR_INCLUDES}" -print-file-name=include-fixed
      OUTPUT_VARIABLE _doxy_gcc_include_fixed
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(IS_DIRECTORY "${_doxy_gcc_include_fixed}")
      string(APPEND DOXYGEN_CLANG_OPTIONS_CONFIGURED " -isystem \"${_doxy_gcc_include_fixed}\"")
    endif()
  endif()
endif()

set(out "${DOXYGEN_OUTPUT_DIRECTORY}")

foreach(file IN ITEMS Doxyfile conf.py)
  configure_file("${src}/docs/${file}.in" "${bin}/docs/${file}" @ONLY)
endforeach()

set(mcss_script "${mcss_SOURCE_DIR}/documentation/doxygen.py")
set(config "${bin}/docs/conf.py")

file(REMOVE_RECURSE "${out}/html" "${out}/xml" "${out}/latex" "${out}/pdf")

file(COPY "${src}/docs/doxygen-cyrillic.sty" DESTINATION "${bin}/docs")

execute_process(
  COMMAND "${CMAKE_COMMAND}" -E env "PYTHONUNBUFFERED=1" "${Python3_EXECUTABLE}" "${mcss_script}" "${config}"
  WORKING_DIRECTORY "${bin}/docs"
  RESULT_VARIABLE result
)
if(NOT result EQUAL "0")
  message(FATAL_ERROR "m.css returned with ${result}")
endif()

if((XELATEX_EXECUTABLE OR PDFLATEX_EXECUTABLE) AND NOT DOXYGEN_SKIP_REFMAN_PDF)
  file(MAKE_DIRECTORY "${out}/pdf")
  set(result 1)
  foreach(_doxy_latex_pass RANGE 0 3)
    execute_process(
      COMMAND make
      WORKING_DIRECTORY "${out}/latex"
      RESULT_VARIABLE result
    )
    if(result EQUAL "0")
      break()
    endif()
  endforeach()
  if(NOT result EQUAL "0")
    if(EXISTS "${out}/latex/refman.log")
      execute_process(
        COMMAND sh -c "tail -n 120 refman.log"
        WORKING_DIRECTORY "${out}/latex"
        OUTPUT_VARIABLE _doxy_refman_log_tail
        ERROR_QUIET
      )
      string(STRIP "${_doxy_refman_log_tail}" _doxy_refman_log_tail)
      message(WARNING "LaTeX PDF build failed; tail of refman.log:\n${_doxy_refman_log_tail}")
    endif()
    message(FATAL_ERROR "LaTeX/PDF build returned with ${result}")
  endif()
  execute_process(
    COMMAND "${CMAKE_COMMAND}" -E copy "${out}/latex/refman.pdf" "${out}/pdf/${PROJECT_NAME}.pdf"
    RESULT_VARIABLE _doxy_pdf_copy
  )
  if(NOT _doxy_pdf_copy EQUAL "0")
    message(FATAL_ERROR "Copy to ${PROJECT_NAME}.pdf failed with ${_doxy_pdf_copy}")
  endif()
else()
  if(DOXYGEN_SKIP_REFMAN_PDF)
    message(STATUS "DOXYGEN_SKIP_REFMAN_PDF: skipping LaTeX PDF")
  else()
    message(STATUS "No xelatex/pdflatex; skipping LaTeX PDF (HTML docs were generated)")
  endif()
endif()

# set(
#   DOXYGEN_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/docs"
#   CACHE PATH "Path for the generated Doxygen documentation"
# )

# add_custom_target(
#       docs
#       COMMAND "${CMAKE_COMMAND}" -E rm -rRf
#       "${DOXYGEN_OUTPUT_DIRECTORY}/html"
#       "${DOXYGEN_OUTPUT_DIRECTORY}/xml"
#       COMMAND "${Python3_EXECUTABLE}" "${mcss_script}" "${config}"
#       COMMENT "Building documentation using Doxygen and m.css"
#       WORKING_DIRECTORY "${working_dir}"
#       VERBATIM
# )
